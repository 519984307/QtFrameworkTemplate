//
//  EventTrackProvider.m
//  pghuifudashi
//
//  Created by Apple on 2018/12/26.
//  Copyright © 2018年 Auntec. All rights reserved.
//

#import "EventTrackProvider.h"
#import "ATAnalyticsSDK.h"
#import "ATAnalyticsSDKDefines.h"
#include "SOFTWARE_ERROR_CODE.h"
#include "APP_GLOBAL_CONSTANT.h"
#include "EventTrackCInterface.h"
#include <QtCore>
#include "mac_appver.h"
#import "SAGzipUtility.h"
#import "SSZipArchive.h"
//#include "sysutils.h"
//#include "../../Platform/MacOs/os_define.h"
#include "ILogServer.h"


// MARK: common event
#define ATCommon_Event_AppStart                   @"pSoftStart"
#define ATCommon_Event_AppClose                   @"pSoftClose"
#define ATCommon_Event_AppCrash                   @"pSoftCrash"
#define ATCommon_Event_AppInstall                 @"pSoftInstallResult"


@interface EventTrackProvider ()

@property (nonatomic, copy) NSString *channel;
@property (nonatomic, copy) NSString *channelCode;
+ (NSDictionary*)variantToNSDictionary:(QVariantMap)settings;
@end
//@interface AClass (private)
//
//-(void)privateSayHello;
//
//@end
@implementation EventTrackProvider


+ (instancetype)sharedInstance
{
    static id onlyInstance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        onlyInstance = [[self alloc] init];
    });
    return onlyInstance;
}

- (instancetype)init {
    if (self = [super init]) {
        [self setup];
    }
    return self;
}

- (void)setup {
    // get Package Config
    NSString *path = [[NSBundle mainBundle] pathForResource:@"PackageConfig" ofType:@"plist"];
    NSDictionary *config = [NSDictionary dictionaryWithContentsOfFile:path];
    if (config) {
        _channel = [config valueForKey:@"Channel_Name"];
        _channelCode = [config valueForKey:@"Channel_Code"];
    } else {
#ifdef AppStore_Chanel
        _channel = @"AppStore";
#else
        _channel = @"Website";
#endif
    }
}



#pragma mark public

+ (void)setupTracker
{
    NSString *channel = [EventTrackProvider sharedInstance].channel;
    NSString *channelCode = [EventTrackProvider sharedInstance].channelCode;
    ATAnalyticsSDK *sharedSDK = [ATAnalyticsSDK sharedInstance];

    [sharedSDK setAppId:[NSString stringWithUTF8String:APP_ID]];
    [sharedSDK setAppKey:[NSString stringWithUTF8String:APP_KEY]];
        
    [sharedSDK setPubKey:[NSString stringWithUTF8String:RSA_PUB_KEY]];
    [sharedSDK setPriKey:[NSString stringWithUTF8String:RSA_PRI_KEY]];
    
    [sharedSDK setHost:[NSString stringWithUTF8String:UPGRADE_SERVER_HOST]];
    
    [sharedSDK setChannel:channel];
    [sharedSDK setChannelCode:channelCode];
    //[sharedSDK setLogEnabled:true];
    [sharedSDK setupAnalytics];
    
    // 配置崩溃收集    

    FSRef ref;
    OSType folderType = kApplicationSupportFolderType;
    char supportDir[PATH_MAX];

    FSFindFolder( kUserDomain, folderType, kCreateFolder, &ref );
    FSRefMakePath( &ref, (UInt8*)&supportDir, PATH_MAX );

    std::string folder = supportDir;
//    MoyeaBased::path_connect(folder,  "Billfish");
//    if (!MoyeaBased::dir_exists(folder.c_str())) {
//        MoyeaBased::make_dir(folder.c_str());
//    }

    NSString* crashPath = [[NSString alloc] initWithCString:folder.c_str()];
    //NSString* crashPath =     appDataPath.toNSString();
    [sharedSDK installCrashReporterAtDirectory:crashPath
                             sendReportHandler:^BOOL(ATACrashManager *crashManager, NSString *crashFile) {
        return [self handlerSendCrashReport:crashManager crashFile:crashFile];
    }];
    [sharedSDK enableCrashReporter];
    //[sharedSDK generateTestCrash];// TEST ONLY
    
    ATALogInfo(@"Channel_Name is :%@", channel);
    ATALogInfo(@"Channel_Code is :%@", channelCode);
    ATALogInfo(@"JNZmid is :%@", sharedSDK.mid);
}

+ (void)trackKeyValueEvent:(NSString *)event_id
{
    [[ATAnalyticsSDK sharedInstance] trackKeyValueEvent:event_id props:nil];
}

+ (void)trackKeyValueEvent:(NSString *)event_id props:(NSDictionary *)props
{
    [[ATAnalyticsSDK sharedInstance] trackKeyValueEvent:event_id props:props];
}

+ (void)flush
{
    [[ATAnalyticsSDK sharedInstance] flush];
}


#pragma mark  Common Event
// 上报安装事件
+ (void)trackInstallEvent
{
    QString settingsFile = QStandardPaths::writableLocation(QStandardPaths::DataLocation)+ "/Billfish/billfish.plist";
    QSettings macSettings(settingsFile,QSettings::NativeFormat);
    
    BOOL isFirstLaunch = !macSettings.value("Launch").toBool();
    QString strOldVersion = macSettings.value("Version").toString();
    char* version = GetMacAppVersion();
    QString strVersion;
    if(NULL == version){
        strVersion = "";
    }else{
        strVersion = QString::fromUtf8(version);
    }
    
    if(isFirstLaunch || (strVersion != strOldVersion)){
        macSettings.setValue("Version", strVersion);
        macSettings.sync();
        
        [[ATAnalyticsSDK sharedInstance] trackInstall];
        NSString *appName = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleDisplayName"];
        NSString *packageName = [NSString stringWithFormat:@"%@_%@", appName, ([EventTrackProvider sharedInstance].channelCode.length > 0 ? [EventTrackProvider sharedInstance].channelCode : [EventTrackProvider sharedInstance].channel)];
        BOOL isFirstInstall = isFirstLaunch;
        NSDictionary *props = @{
                                @"is_first_install":@(isFirstInstall),
                                @"soft_package_name":packageName,
                                };
        [[ATAnalyticsSDK sharedInstance] trackKeyValueEvent:ATCommon_Event_AppInstall props:props];
		[[ATAnalyticsSDK sharedInstance] flush];
    }
}

// 上报启动事件
+ (void)trackLaunchEvent
{
    [[ATAnalyticsSDK sharedInstance] trackFunctionLog:ATAErrorLevelInfo
                                             category:@SOFTWARE_STATE
                                                 code:@SOFTWARE_STATE_OPEN
                                                 logs:@"software open"
                                              extends:nil
                                                files:nil
                                          competition:nil];
    QString settingsFile = QStandardPaths::writableLocation(QStandardPaths::DataLocation)+ "/Billfish/billfish.plist";
    QSettings macSettings(settingsFile,QSettings::NativeFormat);
    
    BOOL isFirstLaunch = !macSettings.value("Launch").toBool();
    NSDictionary *props = @{
                            @"if_pc_first_start":@(isFirstLaunch),
                            };
    [[ATAnalyticsSDK sharedInstance] trackKeyValueEvent:ATCommon_Event_AppStart props:props];
	[[ATAnalyticsSDK sharedInstance] flush];
    if(isFirstLaunch){
        macSettings.setValue("Launch", YES);
        macSettings.sync();
    }
    
}

// 上报退出事件
+ (void)trackTerminateEvent
{
    [[ATAnalyticsSDK sharedInstance] trackFunctionLog:ATAErrorLevelInfo
                                             category:@SOFTWARE_STATE
                                                 code:@SOFTWARE_STATE_CLOSE
                                                 logs:@"software close"
                                              extends:nil
                                                files:nil
                                          competition:nil];
    [[ATAnalyticsSDK sharedInstance] trackKeyValueEvent:ATCommon_Event_AppClose props:nil];
    [[ATAnalyticsSDK sharedInstance] flush];
}

// 上报崩溃日志和崩溃事件
+ (BOOL)handlerSendCrashReport:(ATACrashManager *)crashManager crashFile:(NSString *)crashFile
{
    __block BOOL beenReported = false;
	std::string crash_file_path = [crashFile UTF8String];
	
	SERVER_SEND_CRASH_STACK_FILE(crash_file_path.c_str());
	beenReported = true;
    return beenReported;
}

+ (void)clearSubprocessCrash{
	[[ATAnalyticsSDK sharedInstance] clearSubprocessCrash];
}

#pragma mark interface



void setupTracker(){
    return [EventTrackProvider setupTracker];
}

void trackKeyValueEvent(const char* event_id){
    return [EventTrackProvider trackKeyValueEvent:[NSString stringWithUTF8String:event_id]];
}

void trackKeyValueEventWithProps(const char* event_id ,const QVariantMap& map){
    NSDictionary* props = [EventTrackProvider variantToNSDictionary:map];
    return [EventTrackProvider trackKeyValueEvent:[NSString stringWithUTF8String:event_id]
            props:props];
}

void flush(){
    return [EventTrackProvider flush];
}


void trackInstallEvent(){
    return [EventTrackProvider trackInstallEvent];
}

void trackLaunchEvent(){
    return [EventTrackProvider trackLaunchEvent];
}

void trackTerminateEvent(){
    return [EventTrackProvider trackTerminateEvent];
}

const char* getMid(){
    return [[[ATAnalyticsSDK sharedInstance]  mid] UTF8String];
}

void clearSubprocessCrash(){
	return [EventTrackProvider clearSubprocessCrash];
}

+ (NSDictionary*)variantToNSDictionary:(QVariantMap)settings {

   NSMutableDictionary* userInfoDic = nil;
   if(!settings.isEmpty()) {
       userInfoDic = [NSMutableDictionary dictionary];
       foreach(QString key, settings.keys()){
           QVariant item = settings[key];
           if(!item.isNull()) {
               if(item.type() == QVariant::String) {
                   NSString* value = item.toString().toNSString();
                   if(value) {
                       [userInfoDic setObject: value forKey: key.toNSString()];
                   }
               } else if(item.type() == QVariant::Bool || item.type() == QVariant::Int || item.type() == QVariant::Double ||
                       item.type() == QVariant::LongLong || item.type() == QVariant::UInt || item.type() == QVariant::ULongLong) {
                   if(item.type() == QVariant::Int) {
                       NSNumber* value = [NSNumber numberWithInt:item.toInt()];
                       if(value) {
                           [userInfoDic setObject: value forKey: key.toNSString()];
                       }
                   } else if(item.type() == QVariant::UInt) {
                       NSNumber* value = [NSNumber numberWithUnsignedInt:item.toUInt()];
                       if(value) {
                           [userInfoDic setObject: value forKey: key.toNSString()];
                       }
                   } else if(item.type() == QVariant::LongLong) {
                       NSNumber* value = [NSNumber numberWithLongLong:item.toLongLong()];
                       if(value) {
                           [userInfoDic setObject: value forKey: key.toNSString()];
                       }
                   } else if(item.type() == QVariant::ULongLong) {
                       NSNumber* value = [NSNumber numberWithUnsignedLongLong:item.toULongLong()];
                       if(value) {
                           [userInfoDic setObject: value forKey: key.toNSString()];
                       }
                   } else if(item.type() == QVariant::Double) {
                       NSNumber* value = [NSNumber numberWithDouble:item.toDouble()];
                       if(value) {
                           [userInfoDic setObject: value forKey: key.toNSString()];
                       }
                   } else if(item.type() == QVariant::Bool) {
                       BOOL flag = ((item.toBool() == true) ? YES : NO);
                       NSNumber* value = [NSNumber numberWithBool:flag];
                       if(value) {
                           [userInfoDic setObject: value forKey: key.toNSString()];
                       }
                   }
               } else if(item.type() == QVariant::Url) {
                   QUrl url = item.toUrl();
                   NSURL* urlPath = [NSURL URLWithString: (url.toString().toNSString())];
                   [userInfoDic setObject: urlPath forKey: key.toNSString()];
               }
           }
       }
   }
   return userInfoDic;
}

@end


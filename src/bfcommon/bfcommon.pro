include(../config.pri)
include(../install.pri)


#名称
TARGET = bfcommon
#该项目是一个库工程模板
TEMPLATE = lib
#支持c++11
CONFIG += c++11
#输出目录
DESTDIR = $$LIBSDESTDIR
#插件化
CONFIG += plugin
#dll输出目录
DLLDESTDIR = $$BINDESTDIR
DEFINES += BUILD_COMMON_LIB
#禁用去除gui模块
QT -= gui

win32 {
    contains(QT_ARCH, x86_64){
        LIBS += -L$$PWD/../../dependency/zlib_r/win-x64-msvc/lib \
                -lzlib

        LIBS += -L$$PWD/../../dependency/ui_sdk/win-x64-msvc/lib \
                -lLogServer \
                -lNetwork \
                -lSetting
        LIBS += -L$$PWD/../../dependency/json_r/win-x64-msvc/lib
        CONFIG(debug, debug|release){
                LIBS+= -lCommond
                LIBS+= -ljson_vs19_v142_libmdd_a
        }else{
                LIBS+= -lCommon
                LIBS+= -ljson_vs19_v142_libmd_a
        }
    }else{
        LIBS += -L$$PWD/../../dependency/zlib_r/win-x86-msvc/lib \
                -lzlib

        LIBS += -L$$PWD/../../dependency/ui_sdk/win-x86-msvc/lib \
                -lLogServer \
                -lNetwork \
                -lSetting

        LIBS += -L$$PWD/../../dependency/json_r/win-x86-msvc/lib
        CONFIG(debug, debug|release){
                LIBS+= -lCommond
                   LIBS+= -ljson_vs19_v142_libmdd_a
        }else{
                LIBS+= -lCommon
                   LIBS+= -ljson_vs19_v142_libmd_a
        }
    }

}


INCLUDEPATH += $$PWD/../../dependency/zlib_r/include
INCLUDEPATH += $$PWD/../../dependency/ui_sdk/include
INCLUDEPATH += $$PWD/../../dependency/json_r/include
INCLUDEPATH += $$PWD/../../dependency/openssl_r/include
INCLUDEPATH += $$PWD/../../dependency/base_platform_sdk/include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bfcommon.cpp \
    update_thread/CUpdateThread.cpp \
    zip/unzip.c \
        zip/zip.c \
    zip/ioapi.c \

    
    
HEADERS += \
    APP_GLOBAL_CONSTANT.h \
    bfcommon.h \
    bfcommon_export.h \
    update_thread/CUpdateThread.h \
    zip/unzip.h \
    zip/zip.h \
    zip/crypt.h \
    zip/ioapi.h \

win32{
SOURCES += \
    send_thread/CSendDataThread.cpp \
    thread/thread_cond.c \
    zip/ztool.c


    HEADERS += \
    send_thread/CSendDataThread.h \
    thread/thread_cond.h \
    zip/ztool.h
}

macx{
    QMAKE_OBJECTIVE_CFLAGS += -fobjc-arc

INCLUDEPATH +=  \
    ../../dependency/openssl_r/include \
    ../../dependency/iconv_r/include \
    ../../dependency/sqlite3_r/include \
    ../../dependency/zlib_r/include


LIBS += \
        -L"$$PWD/../../dependency/ATAnalytics/PLCrashReporter" \
        -L"$$PWD/../../dependency/openssl_r/osx-x64" \
        -L"$$PWD/../../dependency/sqlite3_r/osx-x64" \
        -L"$$PWD/../../dependency/iconv_r/osx-x64" \
        -L"/usr/lib"\
        -lCrashReporter-MacOSX-Static \
        -lcrypto \
        -lssl \
        -lsqlite3 \


    LIBS += -L$$PWD/../../dependency/ui_sdk/osx-x64 \
            -lCommon \
            -lLogServer \

    LIBS += -L$$PWD/../../dependency/zlib_r/osx-x64 \
             -lz

        LIBS += -L$$PWD/../../dependency/billfish_sdk/sdk/osx-x64 \
                -licuuc.54 \
                -licui18n.54 \
                -licudata.54 \
                -liconv.2.4.0 \




LIBS += -L$$PWD/../../dependency/zlib_r/osx-x64 \
         -lz

INCLUDEPATH += ../../dependency/ATAnalytics/PLCrashReporter/include \
    ../../dependency/ATAnalytics \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/Utils \
    ../../dependency/ATAnalytics/ATAEventTracker/SensorsAnalyticsSDK \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATALogTracker \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/Utils \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor \
    ../../dependency/ATAnalytics/ATAnalyticsSDK \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool \
    zip \

HEADERS += \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATACrashDetails.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATACrashManager.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATASystemProfile.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/ATAEventTracker.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/JSONUtil.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/MessageQueueBySqlite.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/NSString+HashCode.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SACommonUtility.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAGzipUtility.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SALogger.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAReachability.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SensorsAnalyticsExceptionHandler.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SensorsAnalyticsSDK.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SSZipArchive.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATALogTracker/ATALogTracker.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/ATAMidTool.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool/md5.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool/md5_tool.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/cpu_id.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/disk_serialno.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/mac_address.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/mac_appver.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/platform_info.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATANetWorkClient.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/ATARSACryptor.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/GTMBase64.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/GTMDefines.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAnalyticsSDK.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAnalyticsSDKDefines.h \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/Utils/ATAnalyticsSDKHelper.h \
    ../../dependency/ATAnalytics/UpgradeInfo/UpdateViewModel.h \
    ../../dependency/ATAnalytics/UpgradeInfo/NewVersionInfo.h \
    ../../dependency/ATAnalytics/Feedback/FeedbackInfo.h \
    common_util.h \

SOURCES += \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool/md5.c \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/md5_tool/md5_tool.cpp \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/cpu_id.cpp \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/disk_serialno.cpp \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/mac_address.cpp \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/platform_info.cpp \
    common_util.cpp \


OBJECTIVE_SOURCES += \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATACrashDetails.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATACrashManager.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATACrashManager/ATASystemProfile.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/ATAEventTracker.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/JSONUtil.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/MessageQueueBySqlite.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/NSString+HashCode.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SACommonUtility.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAGzipUtility.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SALogger.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SAReachability.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SensorsAnalyticsExceptionHandler.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SensorsAnalyticsSDK.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAEventTracker/SensorsAnalyticsSDK/SSZipArchive.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATALogTracker/ATALogTracker.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/ATAMidTool.mm \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAMidTool/platform/mac_appver.mm \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATANetWorkClient.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/ATARSACryptor.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATANetWorkClient/ATARSACryptor/GTMBase64.m \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/ATAnalyticsSDK.m \
    ../../dependency/ATAnalytics/UpgradeInfo/UpdateViewModel.mm \
    ../../dependency/ATAnalytics/UpgradeInfo/NewVersionInfo.mm \
    ../../dependency/ATAnalytics/Feedback/FeedbackInfo.mm \
    ../../dependency/ATAnalytics/ATAnalyticsSDK/Utils/ATAnalyticsSDKHelper.m \


HEADERS += \
    ./macos/EventTracker.h \
    ./macos/EventTrackProvider.h \
    ./macos/SOFTWARE_ERROR_CODE.h \
    ./macos/EventTrackCInterface.h \

OBJECTIVE_SOURCES += \
    ./macos/EventTrackProvider.mm \

}



# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

include(../symbols.pri)

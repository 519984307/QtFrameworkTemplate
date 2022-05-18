//
//  EventTrackProvider.h
//  pghuifudashi
//
//  Created by Apple on 2018/12/26.
//  Copyright © 2018年 Auntec. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface EventTrackProvider : NSObject

+ (void)setupTracker;

+ (void)trackKeyValueEvent:(NSString *)event_id;

+ (void)trackKeyValueEvent:(NSString *)event_id props:(NSDictionary *)props;

+ (void)flush;


#pragma mark  Common Event

+ (void)trackInstallEvent;

+ (void)trackLaunchEvent;

+ (void)trackTerminateEvent;

//+ (void)trackCrashEvent;

+ (void)clearSubprocessCrash;

@end


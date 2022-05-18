//
//  SystemUtils.h
//  Billfish
//
//  Created by luqi on 2021/1/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SystemUtils : NSObject
+ (NSArray*)getApplicationURLsForURL:(NSString *)filePath;
@end

NS_ASSUME_NONNULL_END

//
//  DRHelper.h
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 02/10/12.
//
//

#import <Foundation/Foundation.h>

@interface DRHelper : NSObject

+ (void)showAlertWithMessageError:(NSString *)message;
+ (void)showAlertWithMessage:(NSString *)message;

+ (NSString *)defaultTimestampForDate:(NSDate *)date;
+ (UIImage *)defaultImageForNavigationBar;

@end

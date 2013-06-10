//
//  DRHelper.m
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 02/10/12.
//
//

#import "DRHelper.h"

@implementation DRHelper

+ (void)showAlertWithTitle:(NSString *)title message:(NSString *)message
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:message
                                                   delegate:nil
                                          cancelButtonTitle:@"Aceptar"
                                          otherButtonTitles:nil];
    [alert show];
}

+ (void)showAlertWithMessageError:(NSString *)message
{
    [self showAlertWithTitle:@"Error" message:message];
}

+ (void)showAlertWithMessage:(NSString *)message
{
    [self showAlertWithTitle:@"Información" message:message];
}

+ (NSString *)defaultTimestampForDate:(NSDate *)date
{
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"yyyyMMddHHmm"];
    return [dateFormatter stringFromDate:date];
}

+ (UIImage *)defaultImageForNavigationBar
{
    return [UIImage imageNamed:@"NavBar_Header"];
}

@end

//
//  DRDisplayOTPViewController.m
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import "DRDisplayOTPViewController.h"

@interface DRDisplayOTPViewController ()
@property (nonatomic, strong) id<MTToken> token;
@property (nonatomic, strong) NSTimer *timer;
@end

@implementation DRDisplayOTPViewController

- (id)initWithToken:(id<MTToken>)token
{
    self = [super initWithNibName:@"DRDisplayOTPView" bundle:nil];
    if (self) {
        self.title = @"OTP";
        self.token = token;
    }
    return self;
}

- (void)dealloc
{
    [_timer invalidate];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    if ([self.token calculateTimeOTP]) {
        self.otpLabel.text = self.token.otp;
        self.timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(updateOTP:) userInfo:nil repeats:YES];
        self.progressView.progress = [_token getCycleProgress];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - Helper methods
- (void)updateOTP:(id)sender
{
    if ([self.token updateTimeOTP]) {
        self.otpLabel.text = self.token.otp;
        self.progressView.progress = [self.token getCycleProgress];
    }
}

@end

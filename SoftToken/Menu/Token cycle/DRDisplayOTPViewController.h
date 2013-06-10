//
//  DRDisplayOTPViewController.h
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DRViewController.h"

@interface DRDisplayOTPViewController : DRViewController

@property (weak, nonatomic) IBOutlet UILabel *otpLabel;
@property (weak, nonatomic) IBOutlet UIProgressView *progressView;

- (id)initWithToken:(id<MTToken>)token;

@end

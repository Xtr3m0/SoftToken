//
//  DRLoginOTPViewController.h
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DRViewController.h"

@class DRLoginOTPViewController;

typedef void (^DRLoginOTPViewBlock)(DRLoginOTPViewController *viewController, BOOL userLoged);

@interface DRLoginOTPViewController : DRViewController<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *usernameTextField;
@property (weak, nonatomic) IBOutlet UITextField *nipTextField;

@property (nonatomic, copy) DRLoginOTPViewBlock completionBlock;

@end

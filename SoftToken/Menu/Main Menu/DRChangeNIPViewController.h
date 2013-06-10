//
//  DRChangeNIPViewController.h
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DRViewController.h"

@class DRChangeNIPViewController;

typedef void (^DRChangeNIPViewBlock)(DRChangeNIPViewController *viewController, BOOL userCreated);

@interface DRChangeNIPViewController : DRViewController<UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *usernameTextField;
@property (weak, nonatomic) IBOutlet UITextField *nipTextField;
@property (weak, nonatomic) IBOutlet UITextField *confirmNipTextField;

@property (nonatomic, copy) DRChangeNIPViewBlock completionBlock;

@end

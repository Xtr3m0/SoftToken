//
//  DRActivateTokenViewController.h
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DRViewController.h"

@class DRActivateTokenViewController;

typedef void (^DRActivateTokenViewBlock)(DRActivateTokenViewController *viewController, BOOL tokenActivated);

@interface DRActivateTokenViewController : DRViewController<MTDeploymentListener, UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *serialNumberTextField;
@property (weak, nonatomic) IBOutlet UITextField *activationCodeTextField;

@property (nonatomic, copy) DRActivateTokenViewBlock completionBlock;

@end

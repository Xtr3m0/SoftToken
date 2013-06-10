//
//  DRLoginOTPViewController.m
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import "DRLoginOTPViewController.h"

@interface DRLoginOTPViewController ()

@end

@implementation DRLoginOTPViewController

- (id)init
{
    self = [super initWithNibName:@"DRLoginOTPView" bundle:nil];
    if (self) {
        self.title = @"OTP";
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(loginSoftTokenUser:)];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(cancelLoginSoftTokenUser:)];
    
    [self.nipTextField becomeFirstResponder];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)cancelLoginSoftTokenUser:(id)sender
{
    if (self.completionBlock) {
        self.completionBlock(self, NO);
    }
}

- (void)loginSoftTokenUser:(id)sender
{
    if (self.nipTextField.text.length > 0) {
        if ([[DRGemaltoTokenManager sharedTokenManager] loginWithPassword:self.nipTextField.text]) {
            if (self.completionBlock) {
                self.completionBlock(self, YES);
            }
        }else{
            [DRHelper showAlertWithMessageError:@"Información incorrecta"];
        }
    }else{
        [DRHelper showAlertWithMessageError:@"Información faltante"];
    }
}

#pragma mark - Delegates
- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (textField == self.usernameTextField) {
        [self.nipTextField becomeFirstResponder];
    }else if (textField == self.nipTextField) {
        [self loginSoftTokenUser:textField];
    }
    [textField resignFirstResponder];
    return YES;
}

@end

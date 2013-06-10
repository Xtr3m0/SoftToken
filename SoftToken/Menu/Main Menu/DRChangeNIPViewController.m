//
//  DRChangeNIPViewController.m
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import "DRChangeNIPViewController.h"

@interface DRChangeNIPViewController ()

@end

@implementation DRChangeNIPViewController

- (id)init
{
    self = [super initWithNibName:@"DRChangeNIPView" bundle:nil];
    if (self) {
        self.title = @"Configurar";
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(createSoftTokenUser:)];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(cancelCreateSoftTokenUser:)];
    [self.nipTextField becomeFirstResponder];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)cancelCreateSoftTokenUser:(id)sender
{
    if (self.completionBlock) {
        self.completionBlock(self, NO);
    }
}

- (void)createSoftTokenUser:(id)sender
{
    if (self.nipTextField.text.length > 0 && self.confirmNipTextField.text.length > 0) {
        if ([self.nipTextField.text isEqualToString:self.confirmNipTextField.text]) {
            if ([[DRGemaltoTokenManager sharedTokenManager] initializeWithPassword:self.nipTextField.text]) {
                [DRGemaltoTokenManager setSoftTokenCreated:YES];
                if (self.completionBlock) {
                    self.completionBlock(self, YES);
                }
            }else{
                [DRHelper showAlertWithMessageError:@"No se pudo crear al usuario"];
            }
        }else{
            [DRHelper showAlertWithMessageError:@"No coinciden NIP y Confirmación de NIP"];
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
        [self.confirmNipTextField becomeFirstResponder];
    }else{
        [self createSoftTokenUser:textField];
    }
    [textField resignFirstResponder];
    return YES;
}

@end

//
//  DRActivateTokenViewController.m
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import "DRActivateTokenViewController.h"
#import "MBProgressHUD.h"

@interface DRActivateTokenViewController ()
@property (nonatomic, strong) UITextField *currentTextField;
@end

@implementation DRActivateTokenViewController

- (id)init
{
    self = [super initWithNibName:@"DRActivateTokenView" bundle:nil];
    if (self) {
        self.title = @"Activación";
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(createSoftToken:)];
    
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemCancel target:self action:@selector(cancelCreateSoftToken:)];
    
    [self.serialNumberTextField becomeFirstResponder];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)createSoftToken:(id)sender
{
    if (self.serialNumberTextField.text.length > 0 && self.activationCodeTextField.text.length > 0) {
        [self.currentTextField resignFirstResponder];
        [self showHUDView];
        [[DRGemaltoTokenManager sharedTokenManager] activateOnlineWithSerial:self.serialNumberTextField.text activationCode:self.activationCodeTextField.text deploymentDelegate:self];
    }else{
        [DRHelper showAlertWithMessageError:@"Información faltante"];
    }
}

- (void)cancelCreateSoftToken:(id)sender
{
    [self hideHUDView];
    if (self.completionBlock) {
        self.completionBlock(self, NO);
    }
}

#pragma mark - Helper
- (void)showHUDView
{
    if (self.navigationController) {
        MBProgressHUD *progressHUD = [MBProgressHUD showHUDAddedTo:self.navigationController.view animated:YES];
        progressHUD.labelText = @"ACTIVANDO";
    }else{
        [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    }
}

- (void)hideHUDView
{
    if (self.navigationController) {
        [MBProgressHUD hideHUDForView:self.navigationController.view animated:YES];
    }else{
        [MBProgressHUD hideHUDForView:self.view animated:YES];
    }
}

#pragma mark - Delegates
#pragma mark UITextFieldDelegate
- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    self.currentTextField = textField;
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
    self.currentTextField = nil;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    if (textField == self.serialNumberTextField) {
        [self.activationCodeTextField becomeFirstResponder];
    }else if (textField == self.activationCodeTextField){
        [self createSoftToken:nil];
    }
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    NSString *text = [textField.text stringByReplacingCharactersInRange:range withString:string];
    if (textField == self.serialNumberTextField) {
        if (text.length > GEMALTO_SERIAL_NUMBER_LENGTH) {
            return NO;
        }
    }else if (textField == self.activationCodeTextField){
        if (text.length > GEMALTO_ACTIVATION_CODE_LENGTH) {
            return NO;
        }
    }
    return YES;
}

#pragma mark MTDeploymentListener
- (void) deploymentStepCompleted: (MTDeploymentStep) step fromSource: (id) source
{
    switch (step) {
        case MTDeploymentStep_STARTING:
            break;
        case MTDeploymentStep_REGISTRATION:
            break;
        case MTDeploymentStep_BROKER_HANDSHAKE:
            break;
        case MTDeploymentStep_ENTERPRISE_REQUEST:
            break;
        case MTDeploymentStep_ENTERPRISE_HANDSHAKE:
            break;
        case MTDeploymentStep_ACCOUNT_REQUEST:
            break;
        case MTDeploymentStep_COMPLETED:
            [self hideHUDView];
            [[DRGemaltoTokenManager sharedTokenManager] commitDeployment];
            self.completionBlock(self, YES);
            break;
        default:
            break;
    }
}

- (void) deploymentError: (NSError *) error fromSource: (id) source
{
    [self hideHUDView];
    [DRHelper showAlertWithMessageError:[error localizedDescription]];
}

- (void) deploymentCanceledFromSource: (id) source
{
    [self hideHUDView];
}

@end

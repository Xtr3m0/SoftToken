//
//  DRMenuViewController.m
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/10/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import "DRMenuViewController.h"
#import "DRChangeNIPViewController.h"
#import "DRLoginOTPViewController.h"
#import "DRActivateTokenViewController.h"
#import "DRDisplayOTPViewController.h"

#import "UIColor+TemplateColor.h"

@interface DRMenuViewController ()
@property (nonatomic, strong) NSMutableArray *options;
@end

@implementation DRMenuViewController

- (id)init
{
    self = [super initWithNibName:@"DRMenuView" bundle:nil];
    if (self) {
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.options = [NSMutableArray arrayWithObjects:@"Banca Móvil", @"Localizador de Cajeros y Oficinas", @"SoftToken", @"Videos de ayuda", @"Atención en Línea",  nil];
    
    UIImage *image = [UIImage imageNamed:@"Background"];
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    self.tableView.backgroundView = imageView;
    
    self.navigationItem.titleView = [[UIImageView alloc] initWithImage:[DRHelper defaultImageForNavigationBar]];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - Table view data source
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.options count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    cell.textLabel.font = [UIFont systemFontOfSize:14];
    cell.textLabel.textColor = [UIColor fontColor];
    
    NSString *option = self.options[indexPath.row];
    cell.textLabel.text = option;
    cell.imageView.image = [UIImage imageNamed:option];
    return cell;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *option = self.options[indexPath.row];
    if ([option isEqualToString:@"SoftToken"]) {
        if ([DRGemaltoTokenManager softTokenCreated]) {
            DRLoginOTPViewController *viewController = [[DRLoginOTPViewController alloc] init];
            UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:viewController];
            [self presentViewController:navController animated:YES completion:NULL];
            
            [viewController setCompletionBlock:^(DRLoginOTPViewController *viewController, BOOL userLoged){
                [viewController dismissViewControllerAnimated:YES completion:^{
                    if (userLoged) {
                        id<MTToken> token = [[DRGemaltoTokenManager sharedTokenManager] tokenForCurrentAccount];
                        if (token) {
                            DRDisplayOTPViewController *viewController = [[DRDisplayOTPViewController alloc] initWithToken:token];
                            [self.navigationController pushViewController:viewController animated:YES];
                        }else{
                            [self showActivationView];
                        }
                    }
                }];
            }];
        }else{
            DRChangeNIPViewController *viewController = [[DRChangeNIPViewController alloc] init];
            UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:viewController];
            [self presentViewController:navController animated:YES completion:NULL];
            
            [viewController setCompletionBlock:^(DRChangeNIPViewController *viewController, BOOL userCreated){
                [viewController dismissViewControllerAnimated:YES completion:^{
                    if (userCreated) {
                        [self showActivationView];
                    }
                }];
            }];
        }
    }
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

#pragma mark - Helpers
- (void)showActivationView
{
    DRActivateTokenViewController *viewController = [[DRActivateTokenViewController alloc] init];
    [self.navigationController pushViewController:viewController animated:YES];
    
    [viewController setCompletionBlock:^(DRActivateTokenViewController *viewController, BOOL tokenCreated){
        [[DRGemaltoTokenManager sharedTokenManager] logout];
        if (tokenCreated) {
            [DRHelper showAlertWithMessage:@"Token activado correctamente"];
        }else{
            [DRHelper showAlertWithMessage:@"El Token no fue activado"];
        }
        [viewController.navigationController popViewControllerAnimated:YES];
    }];
}

@end

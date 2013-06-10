//
//  DRViewController.m
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 5/13/13.
//  Copyright (c) 2013 Daniel Rueda Jimenez. All rights reserved.
//

#import "DRViewController.h"

@interface DRViewController ()
@property (nonatomic, strong) UIImageView *backgroundView;
@end

@implementation DRViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    UIImage *image = [UIImage imageNamed:@"Background"];
    UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
    imageView.autoresizingMask = UIViewAutoresizingFlexibleHeight;
    self.backgroundView = imageView;
    [self.view addSubview:self.backgroundView];
    [self.view sendSubviewToBack:self.backgroundView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    [self.backgroundView removeFromSuperview];
}

@end

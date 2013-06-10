//
//  DRGemaltoTokenManager.h
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 28/09/12.
//
//

#import <Foundation/Foundation.h>
#import <mtcore-ios/MTAppCore.h>
#import <mtcore-ios/MTCoreFactory.h>

#define GEMALTO_NIP_LENGTH 8
#define GEMALTO_SERIAL_NUMBER_LENGTH 8
#define GEMALTO_ACTIVATION_CODE_LENGTH 10

@interface DRGemaltoTokenManager : NSObject

@property (nonatomic, strong) id<MTAppCore> core;
@property (nonatomic, strong) id<MTDeployer> deployer;
@property (nonatomic, strong) NSString *username;

+ (DRGemaltoTokenManager *)sharedTokenManager;

- (BOOL)initializeWithUsername:(NSString *)username
                      password:(NSString *)password;
- (BOOL)activateOnlineWithSerial:(NSString *)serial
                  activationCode:(NSString *)activationCode
              deploymentDelegate:(id<MTDeploymentListener>)delegate;

- (id<MTToken>)tokenForCurrentAccount;

- (BOOL)commitDeployment;

- (BOOL)initializeWithPassword:(NSString *)password;
- (BOOL)loginWithPassword:(NSString *)password;

- (BOOL)loginWithUsername:(NSString *)username
                 password:(NSString *)password;

- (BOOL)logout;

+ (BOOL)validateNIP:(NSString *)nip;

+ (BOOL)softTokenCreated;
+ (void)setSoftTokenCreated:(BOOL)status;

@end

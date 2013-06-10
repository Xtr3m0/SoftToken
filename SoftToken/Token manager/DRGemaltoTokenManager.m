//
//  DRGemaltoTokenManager.m
//  SoftToken
//
//  Created by Daniel Rueda Jimenez on 28/09/12.
//
//

#import "DRGemaltoTokenManager.h"

#import "DRHelper.h"

#define kGemaltoDownloadURL @"http://otpmt.net/token/AccountDownload.aspx"

@interface DRGemaltoTokenManager ()
@end

@implementation DRGemaltoTokenManager
@synthesize core = _core;
@synthesize deployer = _deployer;

+ (DRGemaltoTokenManager *)sharedTokenManager
{
    static DRGemaltoTokenManager *_sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedInstance = [[DRGemaltoTokenManager alloc] init];
    });
    return _sharedInstance;
}

- (id)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void)dealloc
{
    if (_deployer) {
        [_deployer cancelDeployment];
    }
}

#pragma mark - Helpers methods
+ (NSString *)createPUK {
    unichar tmp[32];
    int length = 4;
    int i;
    
    // Generate a random PUK
    for (i = 0; i < length; i++) {
        tmp[i] = (abs(rand()) % 10) + '0';
    }
    return [[NSString alloc] initWithCharacters: tmp length: length];
}

- (NSString *)defaultDatabasePath
{
    NSMutableString *dbPath = [[NSMutableString alloc] initWithString:NSHomeDirectory()];
    [dbPath appendString: @"/Library/tokendb/"];
    return dbPath;
}

- (BOOL)createCoreWithDatabaseName:(NSString *)filename
{
    NSString *path = [[self defaultDatabasePath] stringByAppendingPathComponent:filename];
    self.core = [MTCoreFactory createCore:filename usingDatabase:path];
    [_core setDownloadURL:kGemaltoDownloadURL];
    return (_core != nil);
}

- (id<MTEnterprise>)firstEnterprise
{
    id<MTEnterprise> e = nil;
    id<MTEnterpriseList> eList = [self.core loadEnterpriseList];
    if ([eList count] > 0) {
        e = [eList enterpriseAt:0];
    }
    return e;
}

- (id<MTAccount>)firstAccountAtEnterprise:(id<MTEnterprise>)enterprise
{
    id<MTAccount> a = nil;
    id<MTAccountList> aList = [self.core loadAccountListForEnterprise:enterprise];
    if ([aList count] > 0) {
        a = [aList accountAt:0];
    }
    return a;
}

- (id<MTToken>)tokenForAccount:(id<MTAccount>)account
{
    id<MTToken> t = [self.core loadTokenForAccount:account];
    return t;
}

- (id<MTToken>)tokenForCurrentAccount
{
    id<MTEnterprise> e = [self firstEnterprise];
    if (e) {
        id<MTAccount> a = [self firstAccountAtEnterprise:e];
        return [self tokenForAccount:a];
    }else{
        return nil;
    }
}

- (BOOL)logout
{
    return [self.core logout];
}

+ (BOOL)validateNIP:(NSString *)nip
{
    return (nip.length == GEMALTO_NIP_LENGTH);
}

+ (BOOL)softTokenCreated
{
    return [[NSUserDefaults standardUserDefaults] boolForKey:@"thereIsToken"];
}

+ (void)setSoftTokenCreated:(BOOL)status
{
    [[NSUserDefaults standardUserDefaults] setBool:status forKey:@"thereIsToken"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

#pragma mark - Activation
- (BOOL)initializeWithPassword:(NSString *)password
{
    return [self initializeWithUsername:@"aUsername" password:password];
}

- (BOOL)loginWithPassword:(NSString *)password
{
    return [self loginWithUsername:@"aUsername" password:password];
}

- (BOOL)initializeWithUsername:(NSString *)username password:(NSString *)password
{
    if (username.length > 0) {
        if ([self createCoreWithDatabaseName:username]) {
            NSString *puk = [DRGemaltoTokenManager createPUK];
            return [self.core initializeWithPassword:password andPUK:puk];
        }
    }else{
        
    }
    return NO;
}

- (BOOL)loginWithUsername:(NSString *)username password:(NSString *)password
{
    self.username = nil;
    if (username.length > 0) {
        NSFileManager *fileManager = [NSFileManager defaultManager];
        if ([fileManager fileExistsAtPath:[[self defaultDatabasePath] stringByAppendingPathComponent:username]]) {
            if ([self createCoreWithDatabaseName:username]) {
                if (password.length > 0) {
                    return [self.core loginWithPassword:password];
                }else{
                    
                }
            }else{
                
            }
        }else{
            
        }
    }else{
        
    }
    return NO;
}

- (void)resetPasswordTo:(NSString *)password withPUK:(NSString *)puk
{
    if ([self.core resetPasswordTo:password withPUK:puk]) {
        //[self showLoginScreen];
    } else {
        if (self.core.state != MTAppCoreState_DEAD) {
            //[self showErrorMessage: @"Incorrect PUK." withTitle: self.title];
        } else {
            //[self showDeadScreen];
        }
    }
}

- (void)activateOnlineWithSerial:(NSString *)serial activationCode:(NSString *)activationCode
{
    [self activateOnlineWithSerial:serial activationCode:activationCode deploymentDelegate:nil];
}

- (BOOL)activateOnlineWithSerial:(NSString *)serial
                  activationCode:(NSString *)activationCode
              deploymentDelegate:(id<MTDeploymentListener>)delegate
{
    id <MTSerialActivation> sa = [MTCoreFactory createSerialActivation];
    if ([sa setSerial:serial]) {
        if ([sa setActivation:activationCode]) {
            self.deployer = [self.core deployTokenForSerialActivation:sa];
            if (_deployer) {
                if (delegate) {
                    return [_deployer startUsingDelegate:delegate];
                }
            }else {
                [DRHelper showAlertWithMessageError:@"Unable to start the deployment."];
            }
        }else {
            [DRHelper showAlertWithMessageError:@"Invalid activation."];
        }
    }else {
        [DRHelper showAlertWithMessageError:@"Invalid serial number."];
    }
    return NO;
}

- (BOOL)commitDeployment
{
    return [self.deployer commitDeployment];
}

@end

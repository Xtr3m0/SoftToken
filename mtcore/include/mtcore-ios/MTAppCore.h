/**
 * @file
 * This file contains the definition of the protocol MTAppCore.
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id:$
#import <Foundation/Foundation.h>
#import <mtcore-ios/MTAccountList.h>
#import <mtcore-ios/MTEnterpriseList.h>
#import <mtcore-ios/MTToken.h>
#import <mtcore-ios/MTDeployer.h>
#import <mtcore-ios/MTSerialActivation.h>

/**
 * This enumeration defines the m-Trusted application core status.
 *
 * @since 5.0
 * @see MTAppCore
 * @since 5.0
 * @author Fabio Jun Takda Chino
 * @author Rafael Teixeira
 */
typedef enum _MTAppCoreState {
    /**
     * The core is new and must be initialized.
     */
    MTAppCoreState_NOT_INITIALIZED,
    /**
     * The core is ready to be used.
     */
    MTAppCoreState_READY,
    /**
     * The password of the core is blocked and cannot be used
     * until it is unblocked.
     */
    MTAppCoreState_BLOCKED,
    /**
     * The core is dead and can no longer be used. The database must be
     * disposed.
     */
    MTAppCoreState_DEAD
}MTAppCoreState;

/**
 * This is the protocol implemented by the mobile token application core. Each instance
 * of this class represents a fully functional mobile token application.
 *
 * <p>The application core is the main component of a mobile token. It is responsible for
 * almost all functionalities of the application, such as the credential management
 * (passwords and database encryption), database management (opaque to the API user),
 * token deployment and token management.
 *
 * <p>A typical appplication usually creates a single instance of this class, 
 * uses it to perform all the token's operations and releases at at exit.
 *
 * <p>It is possible to work with more than one instance of this class if, and only if
 * those instances don't share the same database. This means that each instance will
 * act as a distinct mobile token application.
 *
 * <p>Instances of the application core must be created by the method 
 * MTCoreFactory::createCore:usingDatabase:. The following code illustrates how
 * the core must be created:
 *
 * @include create-core.m
 *
 * @note This class is not thread safe.
 * @since 5.0
 * @author Fabio Jun Takda Chino
 * @author Rafael Teixeira
 */
@protocol MTAppCore <NSObject>
@required

/**
 * @name Credential management
 * @{
 */

/**
 * Returns the current state of this core.
 */
@property (readonly) MTAppCoreState state;

/**
 * Verifies if this core is logged or not.
 */
@property (readonly) BOOL logged;

/**
 * Determines if the password is used or not. 
 */
@property (readonly) BOOL usingPassword;

/**
 * Initializes this core without using a password. 
 *
 * @return YES for success or NO othewise.
 * @note On success, this core will be left logged.
 * @note This method works only if the state of the core is MTAppCoreState_NOT_INITIALIZED.
 */
- (BOOL) initializeWithoutPassword;

/**
 * Initializes this core with a given password and puk.
 *
 * @param[in] passwd The password to be used. It cannot be empty.
 * @param[in] puk The PUK used to unblock the password. It cannot be empty. If your
 * application is not willing to support PUK,  set this value to a large string random 
 * string and do not display it to the user.
 * @return YES for success or NO othewise.
 * @note On success, this core will be left logged.
 * @note This method works only if the state of the core is MTAppCoreState_NOT_INITIALIZED.
 */
- (BOOL) initializeWithPassword: (NSString *) passwd andPUK: (NSString *) puk;

/**
 * Performs the login without a password. It can only be used if the property
 * self.usingPassword is false otherwise it always fails.
 *
 * @return YES for success or NO othewise.
 */
- (BOOL) loginWithoutPassword;

/**
 * Performs the login using the given password. It can only be used if the property
 * self.usingPassword is true.
 *
 * @param[in] passwd The password to be used.
 * @return YES for success or NO othewise.
 */
- (BOOL) loginWithPassword: (NSString *) passwd;

/**
 * Performs the logout.
 *
 * @return YES for success or NO othewise.
 */
- (BOOL) logout;

/**
 * Checks the current password.
 *
 * @param[in] passwd The password.
 * @return YES for success or NO othewise.
 * @note This method will not work if the core is not logged of the core is not
 * using a password.
 */
- (BOOL) checkPassword: (NSString *) passwd;

/**
 * Sets the current password. It can also be used to disable the
 * password if it is in use.
 *
 * @param[in] passwd The password of nil to disable it.
 * @return YES for success or NO othewise.
 * @note This method will not work if the core is not logged.
 * @note This method does not change the PUK so, when enabling the password,
 * it is a good practice to set a new PUK too. 
 */
- (BOOL) setPassword: (NSString *) passwd;

/**
 * Sets the current PUK.
 *
 * @param[in] puk The puk.
 * @return YES for success or NO othewise.
 * @note This method fails if the core is not logged.
 */
- (BOOL) setPUK: (NSString *) puk;

/**
 * Resets the password using the current PUK. It will fail if the
 * state of the token is not MTAppCoreState_BLOCKED.
 *
 * @param[in] passwd The new password.
 * @param[in] puk The puk current PUK.
 * @return YES for success or NO othewise.
 * @note On success this method will left the token unlogged.
 * @note This method may kill the token after 3 wrong attempts. If this happens,
 * the token will be unusable.
 */
- (int) resetPasswordTo: (NSString *) passwd withPUK: (NSString *) puk;

/**
 * Get the remaining number of reset password attempts before it becomes Dead. 
 *
 * @return number of attempts or -1 if dead
 */
- (int) getRemainingPUKCount;

/**
 * Get the remaining number of login attempts before block it 
 *
 * @return number of attempts or -1 if blocked
 */
- (int) getRemainingPasswdCount;

/** @} */ //Credential management

/**
 * @name Token management
 * @{
 */

/**
 * Returns current list of enterprises.
 *
 * @return The list of enterprises.
 * @note Do not cache this instance because it may be replaced by the core at any time.
 */
- (id <MTEnterpriseList>) loadEnterpriseList;

/**
 * Returns current list of accounts for a given enterprise.
 *
 * @param[in] enterprise The enterprise.
 * @return The list of accounts for the given enterprise.
 * @note Do not cache this instance because it may be replaced by the core at any time.
 */
- (id <MTAccountList>) loadAccountListForEnterprise: (id <MTEnterprise>) enterprise;

/**
 * Deletes the given account.
 *
 * @param[in] account The account to be deleted.
 * @return YES on success or NO otherwise.
 */
- (BOOL) deleteAccount: (id <MTAccount>) account;

/**
 * Loads the token for a given account.
 *
 * @param[in] account The account to be loaded.
 * @return An object that represents the token or nil in case of failure.
 * @note It is possible to cache this instance by adding a reference to it.
 */
- (id <MTToken>) loadTokenForAccount: (id <MTAccount>) account;

/** @} */ //Token management

/**
 * @name Token deployment
 * @{
 */

/**
 * Sets the token dowload URL.
 *
 * @param[in] url The token download URL.
 * @return YES for success or NO othewise.
 * @note It is not possible to download a token the URL is not set.
 */
- (BOOL) setDownloadURL: (NSString *) url;

/**
 * Create a token deployer for the specified serial and activation numbers.
 *
 * @param[in] serialActivation The serial/activation pair.
 * @return A new deployer or nil on failure.
 * @note This method will not work if the
 */
- (id <MTDeployer>) deployTokenForSerialActivation: (id <MTSerialActivation>) serialActivation;

/** @} */ // Token deployment

@end

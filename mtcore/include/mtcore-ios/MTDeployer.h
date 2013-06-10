/**
 * @file
 * This file contains the definition of the protocol MTDeployer.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id: MTDeployer.h 907 2011-08-30 21:28:27Z fchino@opencs.com.br $
#import <Foundation/Foundation.h>
#import <mtcore-ios/MTDeploymentListener.h>

/**
 * This is the protocol implemented by a deployer object. The deployer is the class 
 * responsible to perform a token deployment (download).
 * 
 * <p>Instances of this class are created by the core with the method 
 * MTAppCore::deployTokenForSerialActivation:.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
@protocol MTDeployer <NSObject>
@required

/**
 * Starts the token deployment using the given listener.
 *
 * @param[in] listener The lister that will receive the deployment events.
 * @return YES for success or NO otherwise.
 * @note Never invoke this method more then once per deployer instance.
 */
- (BOOL) startUsingDelegate: (id <MTDeploymentListener>) listener;

/**
 * Posts a cancel request into the token deployment. The result of this
 * operation will be reported to the listener.
 *
 * @return YES for success or NO otherwise.
 */
- (BOOL) cancelDeployment;

/**
 * Commit the deployed token into the database. This method must to save the
 * token into the database after the deployment is completed.
 *
 * @return YES for success or NO otherwise.
 */
- (BOOL) commitDeployment;

@end

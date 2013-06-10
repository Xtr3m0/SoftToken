/**
 * @file
 * This file contains the definition of the protocol MTDeploymentListener.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id:$
#import <Foundation/Foundation.h>

/**
 * This type defines the possible deployment steps.
 */
typedef enum _MTDeploymentStep {
    /**
     * Initial step.
     */
    MTDeploymentStep_STARTING,
    /**
     * Requesting registration from the server.
     */
    MTDeploymentStep_REGISTRATION,
    /**
     * Stablishing a secure connection with the broker.
     */
    MTDeploymentStep_BROKER_HANDSHAKE,
    /**
     * Requesting the enterprise data from the broker.
     */
    MTDeploymentStep_ENTERPRISE_REQUEST,
    /**
     * Stablishing a secure connection with the enterprise
     * using the broker as a proxy.
     */
    MTDeploymentStep_ENTERPRISE_HANDSHAKE,
    /**
     * Requesting the token data from the enterprise.
     */
    MTDeploymentStep_ACCOUNT_REQUEST,
    /**
     * The deployment has been completed successfully.
     */
    MTDeploymentStep_COMPLETED
} MTDeploymentStep;

/**
 * This is the protocol that must be implemented by the deployment listener object. The application
 * must implement at least one class with this protocol in order to perform the
 * token deployment.
 *
 * <p>The listener is used by the MTDeployer instance to report the events related
 * to the deployment of the token.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
@protocol MTDeploymentListener <NSObject>
@required

/**
 * This method is called by the deployer to notify the current deployment step.
 *
 * <p>If the value of step is MTDeploymentStep_COMPLETED, the deployment process is completed
 * and the token can be saved into the database otherwise the depĺoyment process is still
 * running.
 *
 * @param[in] step The current deployment step.
 * @param[in] source The source deployer.
 */
- (void) deploymentStepCompleted: (MTDeploymentStep) step fromSource: (id) source;

/**
 * This method is called by the deployer to notify that the deployment has failed
 * due to an error during the process.
 *
 * @param[in] error The error descriptor or nil if it is not available.
 * @param[in] source The source deployer.
 */
- (void) deploymentError: (NSError *) error fromSource: (id) source;

/**
 * This method is called by the deployer to notify that the deployment process
 * has ended because it was cancelled by the user.
 *
 * @param[in] source The source deployer.
 */
- (void) deploymentCanceledFromSource: (id) source;
@end

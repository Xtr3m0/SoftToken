/**
 * @file
 * This file contains the definition of the protocol MTSerialActivation.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id: MTSerialActivation.h 907 2011-08-30 21:28:27Z fchino@opencs.com.br $
#import <Foundation/Foundation.h>

/**
 * This is the protocol implemented by the object that handles the serial 
 * and activation values.
 *
 * <p>On the @prodname, the serial/activation pair is used to identify
 * a token that must be deployed into the mobile token. This pair is send
 * to the user by the token issuer.
 *
 * <p>Instances of this protocol can be acquired using the method
 * MTCoreFactory::createSerialActivation:.
 *
 * @note This library does not support off-line token deployment, thus
 * this object will consider all off-line serial/activation pairs as
 * invalid values.
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
@protocol MTSerialActivation <NSObject>
@required

/**
 * Verifies if the serial and activation are set.
 * 
 * @return YES if they are set or NO otherwise.
 */
- (BOOL) isReady;

/**
 * Sets the serial number. It is always a 8 digit decimal number provided
 * to the user by the token's issuer.
 *
 * @param[in] value The new value for the serial number.
 * @return YES for success or NO otherwise.
 * @note If called twice, the old serial is replaced by the new one on
 * success or none on failure.
 */
- (BOOL) setSerial: (NSString *) value;

/**
 * Sets the activation number. It is always a 10 digit decimal number provided
 * to the user by the token's issuer.
 *
 * @param[in] value The new value for the activation number.
 * @return YES for success or NO otherwise.
 * @note If called twice, the old serial is replaced by the new one on
 * success or none on failure.
 */
- (BOOL) setActivation: (NSString *) value;

/**
 * Verifies if the given serial/activation pair refers to an on-line
 * token deployment.
 * 
 * @return YES if the pair is on-line or NO otherwise.
 * @note When this instance is not ready, the result of this method is
 * meaningless.
 */
- (BOOL) isOnline;
@end

/**
 * @file
 * This file contains the definition of the class MTCoreFactory.
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id: MTCoreFactory.h 907 2011-08-30 21:28:27Z fchino@opencs.com.br $
#import <Foundation/Foundation.h>
#import <mtcore-ios/MTAppCore.h>
#import <mtcore-ios/MTSerialActivation.h>
#import <mtcore-ios/MTTransactionSigning.h>

/**
 * This static class implements the object factory used to create the instances of the
 * main classes of the @prodname.
 *
 * @note Do not create instances of this class.
 * @since 5.0
 * @author Fabio Jun Takda Chino
 * @author Rafael Teixeira
 */
@interface MTCoreFactory : NSObject

/**
 * Creates a new instance of the application core for the specified device using
 * the specified database.
 *
 * @param[in] deviceId A string with that represents a unique identifier for the device.
 * This value must be the same all the times or the database will not work well.
 * @param[in] dataDir The directory that will be used by this core as the database.
 * @return The core instance or nil for failure.
 * @note The new instance is added to the autorelease pool, given that, do not forget to retain
 * this instance if required.
 * @warning Do not instantiate more than one core using the same database at same time.
 */
+ (id <MTAppCore>) createCore: (NSString *) deviceId usingDatabase: (NSString *) dataDir;

/**
 * Creates a non initialized instance of the protocol MTSerialActivation.
 *
 * @return A new non initialized instance of the a MTSerialActivation instance.
 * @note The new instance is added to the autorelease pool, given that, do not forget to retain
 * this instance if required.
 */
+ (id <MTSerialActivation>) createSerialActivation;

/**
 * Creates a new instance of the protocol MTTransactionSignign based on a given start code.
 *
 * @param[in] startCode The start code that describes the transaction signature.
 * @return The new instance or nil in case of failure (low memory or an invalid start code).
 * @note The new instance is added to the autorelease pool, given that, do not forget to retain
 * this instance if required.
 */
+ (id <MTTransactionSigning>) createTransactionSigningForStartCode: (NSString *) startCode;

/**
 * Deletes the database located on the given path. This method may be used to reset
 * the application when the database is dead or corrupted.
 *
 * @param[in] dataDir The path to the token database.
 * @return YES for success or NO otherwise.
 * @warning Do not invoke this method if an instance of the MTAppCore is using 
 * this database.
 */
+ (BOOL) resetDatabase: (NSString *) dataDir;

@end

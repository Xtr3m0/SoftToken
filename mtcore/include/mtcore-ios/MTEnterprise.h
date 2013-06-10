/**
 * @file
 * This file contains the definition of the protocol MTEnterprise.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id: MTEnterprise.h 907 2011-08-30 21:28:27Z fchino@opencs.com.br $

#import <Foundation/Foundation.h>

/**
 * This is the protocol implemented by the enterprise objects.
 *
 * <p>In the @prodname, the enterprise represents the issuer of the 
 * tokens.
 *
 * <p>Instances of this class must be acquired by the method
 * MTEnterpriseList::enterpriseAt:.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
@protocol MTEnterprise <NSObject>
@required

/**
 * Returns the name of the enterprise.
 */
@property (readonly) NSString * name;

/**
 * Returns the logo of the enterprise. It is always
 * a PNG image file.
 */
@property (readonly) NSData * logo;

@end

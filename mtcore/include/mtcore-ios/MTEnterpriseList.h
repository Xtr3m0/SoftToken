/**
 * @file
 * This file contains the definition of the protocol MTEnterpriseList.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id: MTEnterpriseList.h 907 2011-08-30 21:28:27Z fchino@opencs.com.br $

#import <Foundation/Foundation.h>
#import <mtcore-ios/MTEnterprise.h>

/**
 * This is the protocol implemented by the enterprise list.
 *
 * <p>Instances of this class must be acquired by the method
 * MTAppCore::loadEnterpriseList:.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
@protocol MTEnterpriseList  <NSObject>
@required
/**
 * Returns the number of available enterprises.
 */
@property (readonly) int count;

/**
 * Returns the enterprise at a given index.
 *
 * @param[in] idx The index of the enterprise.
 * @return A pointer to the enterprise object or nil if the index is invalid.
 * @note Do not cache the object returned by this method. 
 */
- (id <MTEnterprise>) enterpriseAt: (int) idx;
@end

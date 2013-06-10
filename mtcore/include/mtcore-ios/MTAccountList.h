/**
 * @file
 * This file contains the definition of the protocol MTAccountList.
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id: MTAccountList.h 907 2011-08-30 21:28:27Z fchino@opencs.com.br $
#import <Foundation/Foundation.h>
#import <mtcore-ios/MTAccount.h>
#import <mtcore-ios/MTEnterprise.h>

/**
 * This is the protocol implemented by the list of accounts.
 *
 * <p>Instances of this protocol must be acquired from the application core by calling
 * the method MTAppCore::loadAccountListForEnterprise:.
 *
 * @since 5.0
 * @author Fabio Jun Takda Chino
 * @author Rafael Teixeira
 * @see MTAccount
 * @see MTToken
 */
@protocol MTAccountList <NSObject>
@required

/**
 * Returns the number of available accounts.
 */
@property (readonly) int count;

/**
 * Returns the account at a given index.
 *
 * @param[in] idx The index of the account.
 * @return A pointer to the account object or nil if the index is invalid.
 * @note Do not cache the object returned by this method.
 */
- (id <MTAccount>) accountAt: (int) idx;
@end

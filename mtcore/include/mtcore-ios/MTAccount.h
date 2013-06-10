/**
 * @file
 * This file contains the definition of the protocol MTAccount.
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id: MTAccount.h 907 2011-08-30 21:28:27Z fchino@opencs.com.br $
#import <Foundation/Foundation.h>
#import <mtcore-ios/MTEnterprise.h>

/**
 * This is the protocol implemented by the account objects.
 *
 * <p>In the @prodname, the account is the identifier of a token. It contains
 * the public information of a token, such as the name and the the parent 
 * enterprise and is used to load the token from the database.
 *
 * <p>Instances of this protocol must be acquired from the account lists returned by
 * the application core by calling MTAccountList::accountAt:.
 *
 * @since 5.0
 * @author Fabio Jun Takda Chino
 * @author Rafael Teixeira
 * @see MTEnterprise
 * @see MTAccountList
 * @see MTToken
 */
@protocol MTAccount <NSObject, NSCoding>
@required

/**
 * Returns the name of the account. 
 */
@property (readonly) NSString * name;

/**
 * Returns the enterprise that is the issuer of this account.
 */
@property (readonly) id <MTEnterprise> enterprise;

@end

/**
 * @file
 * This file contains the definition of the protocol MTToken.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id$

#import <Foundation/Foundation.h>

/**
 * This is the protocol implemented by the token objects.
 *
 * <p>On the @prodname, a token object is the OTP token itself. It
 * is used to generates the OTP.
 *
 * <p>Instances of this protocol must be loaded from the core using the
 * method MTAppCore::loadTokenForAccount:.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
@protocol MTToken <NSObject>

@required

/** 
 * @name Token properties
 * @{
 */

/**
 * Gets the name of the token.
 *
 * @return The name of the token.
 */
@property (readonly) NSString * name;

/** 
 * Verifies if this token has time based OTP.
 *
 * @return YES if the method is present or NO otherwise.
 */
@property (readonly) BOOL hasTime;

/** 
 * Verifies if this token has event based OTP.
 *
 * @return YES if the method is present or NO otherwise.
 */
@property (readonly) BOOL hasEvent;

/** 
 * Verifies if this token has challenge/response OTP.
 *
 * @return YES if the method is present or NO otherwise.
 */
@property (readonly) BOOL hasChallenge;

/** 
 * Verifies if this token has transaction signing.
 *
 * @return YES if the method is present or NO otherwise.
 */
@property (readonly) BOOL hasSigning;

/** 
 * Returns the last OTP calculated for this token.
 *
 * @return The OTP or nill if none is available.
 */
@property (readonly) NSString * otp;

/** @} */ //Token properties

/**
 * @name Time OTP
 * @{
 */

/**
 * Calculates the current time OTP.
 * 
 * <p>This method always calculates the OTP for each call. This 
 * means that this method is not suitable to keep the OTP
 * up-to-date on interactive interfaces.
 * 
 * @return YES for success or NO otherwise.
 * @see MTToken::updateTimeOTP:.
 * @warning The behavior of this method is undefined if the Time OTP is not
 * available.
 */
- (BOOL) calculateTimeOTP;

/**
 * Updates the time OTP calculated by MTToken::calculateTimeOTP:. 
 * 
 * <p>This method calculates the if, and only if, the previous OTP
 * is no longer valid. This makes this method suitable for interactive
 * interfaces.
 *
 * @return YES for success or NO otherwise.
 * @note The method MTToken::calculateTimeOTP: must be called at least
 * once before this method can be invoked.
 * @see MTToken::calculateTimeOTP:
 * @see MTToken::getCycleProgress:
 * @warning The behavior of this method is undefined if the Time OTP is not
 * available.
 */
- (BOOL) updateTimeOTP;

/**
 * This method calculates the fraction of the current time cycle. The main purpose
 * of this method the implementation of a gauge that keeps track of the current time
 * cycle.
 * 
 * @return The fraction of the current cycle (a value between 0.0 and 1.0).
 * @warning The behavior of this method is undefined if the Time OTP is not
 * available.
 */
- (float) getCycleProgress;

/** @} */ // Time OTP

/**
 * @name Event OTP
 * @{
 */

/**
 * Calculates the next event OTP.
 * 
 * @return YES for success or NO otherwise.
 * @warning Each call to this method increments the event counter, thus
 * multiple calls to this method without a successfull authentication will
 * make the token out of synchronization.
 * @warning The behavior of this method is undefined if the event OTP is not
 * available.
 */
- (BOOL) calculateNextEventOTP;

/** @} */ // Event OTP

/**
 * @name Challenge/Response
 * @{
 */

/**
 * Calculates the response for a challenge. 
 * 
 * @param[in] challenge The challenge.
 * @return YES for success or NO otherwise.
 * @note This method is also used to calculate the signing of a given transaction.
 * @warning The behavior of this method is undefined if the challenge/response is not
 * available.
 * @see MTTransactionSigning::getChallenge:
 */
- (BOOL) calculateResponseForChallenge: (NSString *) challenge;


/**
 * Calculates the response for a transaction signing. 
 * 
 * @param[in] challenge The challenge.
 * @return YES for success or NO otherwise.
 * @note This method is also used to calculate the signing of a given transaction.
 * @warning The behavior of this method is undefined if the challenge/response is not
 * available.
 * @see MTTransactionSigning::getChallenge: 
 * @since 2012.06.11
 */
- (BOOL) calculateResponseForTS: (NSString *) challenge;


/**
 * Returns the maximum length of the challenge allowed by this token.
 * 
 * @return The maximum length of the challenge.
 * @warning The behavior of this method is undefined if the challenge/response is not
 * available.
 */
- (int) getChallengeLength;

/** @} */ // Challenge/Response
@end

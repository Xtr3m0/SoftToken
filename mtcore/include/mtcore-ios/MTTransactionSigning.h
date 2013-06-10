/**
 * @file
 * This file contains the definition of the protocol MTTransactionSigning.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
// Copyright (c) 2011 Open Communications Security S/A. All rights reserved.
// $Id: MTTransactionSigning.h 907 2011-08-30 21:28:27Z fchino@opencs.com.br $
#import <Foundation/Foundation.h>

/**
 * This enumeration defines all the know signing parameter
 * supported by this library.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
typedef enum _MTTSParam {
    /**
     * This type represents an invalid/unknown parameter.
     */
    MTTS_PARAM_INVALID,
    /**
     * This type represents the currency.
     */
    MTTS_PARAM_CURRENCY,
    /**
     * This type represents the amount.
     */
    MTTS_PARAM_AMOUNT,
    /**
     * This type represents the account.
     */
    MTTS_PARAM_ACCOUNT,
    /**
     * This type represents the source account.
     */
    MTTS_PARAM_FROM_ACCOUNT,
    /**
     * This type represents the destination account.
     */
    MTTS_PARAM_TO_ACCOUNT,
    /**
     * This type represents a quantity.
     */
    MTTS_PARAM_QUANTITY,
    /**
     * This type represents a timestame defined by the server.
     */
    MTTS_PARAM_TIMESTAMP,
    /**
     * This type represents a reference value.
     */
    MTTS_PARAM_REFERENCE,
    /**
     * This type represents the folio identification.
     */
    MTTS_PARAM_FOLIO
} MTTSParam;

/**
 * This is the protocol implemented by a transaction signing object.
 *
 * <p>On the @prodname, the transaction signing is a special form of
 * challenge response. It uses well defined stardard to compose a
 * challenge based on the transaction parameters.
 *
 * <p>This transaction signing standard uses a special value called
 * start code in order to define the arguments will be used and what
 * will be the order used.
 *
 * <p>Instances of this protocol must be created by the method
 * MTCoreFactory::createTransactionSigningForStartCode:.
 *
 * <p>For further details about the transaction signing, see the
 * programmer's guide.
 *
 * @since 5.0
 * @author Fabio Jun Takada Chino
 */
@protocol MTTransactionSigning  <NSObject>
@required

/**
 * Moves the cursor to the next parameter.
 *
 * @return YES on success or NO otherwise.
 * @note It always returns NO when called after the last parameter.
 */
- (BOOL) nextParam;

/**
 * Returns the type of the current parameter.
 *
 * @return The type of the current parameter.
 */
- (MTTSParam) getParamType;

/**
 * Sets the value of the current parameter.
 *
 * @param[in] value The parameter value.
 * @return YES for success or NO otherwise.
 * @note When called more than once for the same parameter, this method replaces the old value.
 */
- (BOOL) setValue: (NSString *) value;

/**
 * Formats and sets the value of the current parameter using the rules imposed by
 * the amount parameter.
 *
 * <p>The amount format states that the decimal places, if any, must always be present. For instance,
 * if the currency defines 2 decimal places the typed values and the actual values will be:
 *
 * <table>
 * <tr><td>Typed value</td><td>Actual value</td></tr>
 * <tr><td>1</td><td>100</td></tr>
 * <tr><td>1.2</td><td>120</td></tr>
 * <tr><td>1.23</td><td>123</td></tr>
 * <tr><td>1.234</td><td>Invalid</td></tr>
 * <tr><td>.1</td><td>Invalid</td></tr>
 * </table>
 *
 * <p>This method verifies the typed value and format it according to the specified number of
 * decimal places or returns NO if the format is unacceptable.
 *
 * @param[in] value The parameter value.
 * @param[in] n The number of decimal places defined by the currency.
 * @param[in] sep The character used to separate the decimal places.
 * @return YES for success or NO otherwise.
 * @note When called more than once for the same parameter, this method replaces the old value.
 */
- (BOOL) setValueAsAmount: (NSString *) value withDecimalPlaces: (int) n andDecimalSeparator: (unichar) sep;

/**
 * Returns the challenge composed by the transaction parameters.
 *
 * @return The challenge to be used to calculate the response for this
 * transaction signing.
 */
- (NSString *) getChallenge;
@end

/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1IntegerEncoderPrivate.h
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsn1IntegerEncoderPrivate_h
#define BQSnmp_BQAsn1IntegerEncoderPrivate_h

/*------------------------------- Includes -----------------------------------*/
#include "BQAsn1EncoderPrivate.h"
#include "BQAsn1IntegerEncoder.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQAsn1IntegerEncoderMethods
    {
    BQUint32 (*EncodeValue)(BQAsn1IntegerEncoder self, BQUint8 *contentBuffer, BQInt64 value);
    BQInt64 (*DecodeValue)(BQAsn1IntegerEncoder self, BQUint8 *contentBuffer, BQUint32 contentSize);
    }tBQAsn1IntegerEncoderMethods;

typedef struct tBQAsn1IntegerEncoder
    {
    tBQAsn1Encoder super;
    const tBQAsn1IntegerEncoderMethods *methods;
    
    /* Private data */
    BQInt64 value;
    }tBQAsn1IntegerEncoder;

/*------------------------------- Prototypes ---------------------------------*/
BQAsn1IntegerEncoder BQAsn1IntegerEncoder_ObjectInit(BQAsn1IntegerEncoder self, BQUint8 *buffer, BQUint32 bufferSize);
BQInt64 BQAsn1IntegerEncoder_GetEncodedValue(BQAsn1IntegerEncoder self);

#endif

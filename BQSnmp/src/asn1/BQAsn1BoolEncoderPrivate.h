/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1BoolEncoderPrivate.h
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsn1BoolEncoderPrivate_h
#define BQSnmp_BQAsn1BoolEncoderPrivate_h

/*------------------------------- Includes -----------------------------------*/
#include "BQAsn1EncoderPrivate.h"
#include "BQAsn1BoolEncoder.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQAsn1BoolEncoderMethods
    {
    BQUint8 (*EncodeBool)(BQAsn1BoolEncoder self, BQBool value);
    BQBool (*DecodeBool)(BQAsn1BoolEncoder self, BQUint8 byteValue);
    }tBQAsn1BoolEncoderMethods;

typedef struct tBQAsn1BoolEncoder
    {
    tBQAsn1Encoder super;
    const tBQAsn1BoolEncoderMethods *methods;
    
    /* Private data */
    BQBool value;
    }tBQAsn1BoolEncoder;

/*------------------------------- Prototypes ---------------------------------*/
BQAsn1BoolEncoder BQAsn1BoolEncoder_ObjectInit(BQAsn1BoolEncoder self, BQUint8 *buffer, BQUint32 bufferSize);

#endif

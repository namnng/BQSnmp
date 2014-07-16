/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1EncoderPrivate.h
 *
 * Date        : 7/9/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsn1EncoderPrivate_h
#define BQSnmp_BQAsn1EncoderPrivate_h

/*------------------------------- Includes -----------------------------------*/
#include "asn1/BQAsn1Encoder.h"
#include "common/BQBitMasks.h"
#include "../common/BQObjectPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef enum eBQAsn1IdentifierTagClass
    {
    cBQAsn1IdentifierTagClassUniversal,
    cBQAsn1IdentifierTagClassApplication,
    cBQAsn1IdentifierTagClassContextSpecific,
    cBQAsn1IdentifierTagClassPrivate
    }eBQAsn1IdentifierTagClass;

typedef struct tBQAsn1EncoderMethods
    {
    eBQAsn1EncoderRet (*Encode)(BQAsn1Encoder self);
    eBQAsn1EncoderRet (*Decode)(BQAsn1Encoder self);
    
    BQBool (*DefiniteLength)(BQAsn1Encoder self);
    BQBool (*IsPrimative)(BQAsn1Encoder self);
    eBQAsn1IdentifierTagClass (*Class)(BQAsn1Encoder self);
    BQUint32 (*TagNumber)(BQAsn1Encoder self);
    BQUint32 (*Length)(BQAsn1Encoder self);
    BQUint32 (*ContentEncode)(BQAsn1Encoder self, BQUint8 *contentBuffer);
    BQUint32 (*ContentDecode)(BQAsn1Encoder self, BQUint8 *contentBuffer, BQUint32 contentSize);
    }tBQAsn1EncoderMethods;

typedef struct tBQAsn1Encoder
    {
    tBQObject super;
    const tBQAsn1EncoderMethods *methods;
    
    /* Private data */
    BQUint8 *buffer;
    BQUint32 bufferSize;
    BQUint32 encodedLength;
    BQBool encoded;
    BQBool decoded;
    
    /* Decoded identifier */
    BQBool infiniteLength;
    BQUint32 length;
    }tBQAsn1Encoder;

/*------------------------------- Prototypes ---------------------------------*/
BQAsn1Encoder BQAsn1Encoder_ObjectInit(BQAsn1Encoder self, BQUint8 *buffer, BQUint32 bufferSize);

/* Access private data */
void BQAsn1Encoder_SetEncoded(BQAsn1Encoder self, BQBool encoded);
BQBool BQAsn1Encoder_GetEncoded(BQAsn1Encoder self);
void BQAsn1Encoder_SetDecoded(BQAsn1Encoder self, BQBool decoded);
BQBool BQAsn1Encoder_GetDecoded(BQAsn1Encoder self);

#endif

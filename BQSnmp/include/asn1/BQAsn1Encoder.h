/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1Encoder.h
 *
 * Date        : 7/9/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsn1Encoder_h
#define BQSnmp_BQAsn1Encoder_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h" /* Super class */

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQAsn1Encoder * BQAsn1Encoder;

typedef enum eBQAsn1EncoderRet
    {
    cBQAsn1EncoderOk,
    cBQAsn1EncoderBufferIsNotEnough,
    cBQAsn1EncoderObjectNotExist,
    cBQAsn1EncoderError
    }eBQAsn1EncoderRet;

/*------------------------------- Prototypes ---------------------------------*/
/* Buffer */
void BQAsn1Encoder_SetBuffer(BQAsn1Encoder self, BQUint8 *buffer, BQUint32 bufferSize);
BQUint8 *BQAsn1Encoder_GetBuffer(BQAsn1Encoder self);
BQUint32 BQAsn1Encoder_GetBufferSize(BQAsn1Encoder self);

/* Encode/decode */
eBQAsn1EncoderRet BQAsn1Encoder_Encode(BQAsn1Encoder self);
eBQAsn1EncoderRet BQAsn1Encoder_Decode(BQAsn1Encoder self);
BQUint32 BQAsn1Encoder_EncodedLength(BQAsn1Encoder self);

#endif

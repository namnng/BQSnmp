/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1IntegerBerEncoder.c
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

/*------------------------------- Includes -----------------------------------*/
#include "BQAsnBer.h"
#include "../BQAsn1IntegerEncoderPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/
typedef struct tBQAsn1IntegerBerEncoder
    {
    tBQAsn1IntegerEncoder super;
    }tBQAsn1IntegerBerEncoder;

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;

/* Override */
static tBQAsn1EncoderMethods        m_BQAsn1EncoderOverride;
static tBQAsn1IntegerEncoderMethods m_BQAsn1IntegerEncoderOverride;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static BQUint8 NumBytesToRepresent(BQAsn1Encoder self, BQInt64 value)
    {
    BQUint64 byteMask  = cBit7_0 << 56;
    BQUint64 signBit   = cBit0   << 63;
    BQUint8 numBytes = 8;
    BQInt8 sign = 0;
    
    if ((value == 0) || (value == -1))
        return 1;
    
    while (byteMask)
        {
        BQInt64 byteValue = (value & byteMask);
        BQBool allOne  = (byteValue == byteMask) ? BQTrue : BQFalse;
        BQBool allZero = (byteValue == 0) ? BQTrue : BQFalse;
        BQBool ignore = BQFalse;
        BQInt8 thisSign = (byteValue & signBit) ? -1 : 1;
        
        /* Not determine sign yet */
        if (sign == 0)
            {
            if (allOne)
                sign = -1;
            if (allZero)
                sign = 1;
            ignore = BQTrue;
            }
        
        /* Same sign, ignore this byte */
        if ((allOne || allZero) && (sign == thisSign))
            ignore = BQTrue;
        
        /* Ignore this byte */
        if (ignore)
            {
            numBytes = numBytes - 1;
            byteMask = byteMask >> 8;
            signBit  = signBit >> 8;
            continue;
            }
        
        return (sign == thisSign) ? numBytes : (numBytes + 1);
        }
    
    /* This may be full words are used to encode */
    if (numBytes == 0)
        numBytes = 8;
    
    return numBytes;
    }

static BQUint32 Length(BQAsn1Encoder self)
    {
    BQInt64 value = BQAsn1IntegerEncoder_GetEncodedValue((BQAsn1IntegerEncoder)self);
    return NumBytesToRepresent(self, value);
    }

static BQUint32 EncodeValue(BQAsn1IntegerEncoder self, BQUint8 *contentBuffer, BQInt64 value)
    {
    BQAsn1Encoder encoder = (BQAsn1Encoder)self;
    BQUint8 numBytes = mMethodsGet(encoder)->Length(encoder);
    BQUint8 byte_i;
    
    /* Encode */
    for (byte_i = 0; byte_i < numBytes; byte_i++)
        {
        contentBuffer[numBytes - byte_i - 1] = (BQUint8)(value & cBit7_0);
        value = value >> 8;
        }
    
    /* Make sure if this encoding is minumum */
    if (numBytes > 1)
        {
        BQBool minimumEncode;
        
        minimumEncode = ((contentBuffer[0] == cBit7_0) && (contentBuffer[1] & cBit7)) ? BQFalse : BQTrue;
        assert(minimumEncode);
        minimumEncode = (((contentBuffer[0] & cBit7_0) == 0) && ((contentBuffer[1] & cBit7) == 0)) ? BQFalse : BQTrue;
        assert(minimumEncode);
        }
    
    return numBytes;
    }

static BQInt64 DecodeValue(BQAsn1IntegerEncoder self, BQUint8 *contentBuffer, BQUint32 contentSize)
    {
    BQUint8 byte_i;
    BQBool isNegative = (contentBuffer[0] & cBit7) ? BQTrue : BQFalse;
    BQInt64 value = isNegative ? -1 : 0;
    BQUint8 bitPosition = 0;
    
    /* Start from the last byte */
    for (byte_i = 0; byte_i < contentSize; byte_i++)
        {
        BQUint8 byteValue = contentBuffer[contentSize - byte_i - 1];
        BQUint64 mask = ((BQUint64)cBit7_0) << bitPosition;
        value = (value & (~mask)) | ((BQUint64)byteValue << bitPosition);
        bitPosition += 8;
        }
    
    return value;
    }

static void OverrideBQAsn1IntegerEncoder(BQAsn1IntegerEncoder self)
    {
    if (!m_methodsInit)
        {
        BQMemCopy(&m_BQAsn1IntegerEncoderOverride, (void *)self->methods, sizeof(m_BQAsn1IntegerEncoderOverride));
        
        mMethodSet(m_BQAsn1IntegerEncoderOverride, EncodeValue);
        mMethodSet(m_BQAsn1IntegerEncoderOverride, DecodeValue);
        }
    
    mMethodsSet(self, m_BQAsn1IntegerEncoderOverride);
    }

static void OverrideBQAsn1Encoder(BQAsn1IntegerEncoder self)
    {
    BQAsn1Encoder encoder = (BQAsn1Encoder)self;
    
    if (!m_methodsInit)
        {
        BQMemCopy(&m_BQAsn1EncoderOverride, (void *)mMethodsGet(encoder), sizeof(m_BQAsn1EncoderOverride));
        
        mMethodSet(m_BQAsn1EncoderOverride, Length);
        }
    
    mMethodsSet(encoder, m_BQAsn1EncoderOverride);
    }

static void Override(BQAsn1IntegerEncoder self)
    {
    OverrideBQAsn1Encoder(self);
    OverrideBQAsn1IntegerEncoder(self);
    }

static BQUint32 ObjectSize(void)
    {
    return sizeof(tBQAsn1IntegerBerEncoder);
    }

BQAsn1IntegerEncoder BQAsn1IntegerBerEncoder_ObjectInit(BQAsn1IntegerEncoder self, BQUint8 *buffer, BQUint32 bufferSize)
    {
    BQMemInit(self, 0, ObjectSize());
    
    /* Super constructor */
    if (BQAsn1IntegerEncoder_ObjectInit(self, buffer, bufferSize) == BQNULL)
        return BQNULL;
    
    /* Setup class */
    Override(self);
    m_methodsInit = 1;
    
    return self;
    }

BQAsn1IntegerEncoder BQAsn1IntegerBerEncoder_New(BQUint8 *buffer, BQUint32 bufferSize)
    {
    return BQAsn1IntegerBerEncoder_ObjectInit(BQMemAlloc(ObjectSize()), buffer, bufferSize);
    }

/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1IntegerEncoder.c
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
#include "BQAsn1IntegerEncoderPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/
#define mThis(self) ((BQAsn1IntegerEncoder)self)

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;
static tBQAsn1IntegerEncoderMethods m_methods;

/* Override */
static tBQAsn1EncoderMethods m_BQAsn1EncoderOverride;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static BQBool DefiniteLength(BQAsn1Encoder self)
    {
    return BQTrue;
    }

static BQBool IsPrimative(BQAsn1Encoder self)
    {
    return BQTrue;
    }

static eBQAsn1IdentifierTagClass Class(BQAsn1Encoder self)
    {
    return cBQAsn1IdentifierTagClassUniversal;
    }

static BQUint32 TagNumber(BQAsn1Encoder self)
    {
    return 2;
    }

static BQUint32 EncodeValue(BQAsn1IntegerEncoder self, BQUint8 *contentBuffer, BQInt64 value)
    {
    /* Sub class must know */
    return 0;
    }

static BQInt64 DecodeValue(BQAsn1IntegerEncoder self, BQUint8 *contentBuffer, BQUint32 contentSize)
    {
    /* Sub class must know */
    return 0;
    }

static BQUint32 ContentEncode(BQAsn1Encoder self, BQUint8 *contentBuffer)
    {
    return mMethodsGet(mThis(self))->EncodeValue(mThis(self), contentBuffer, mThis(self)->value);
    }

static BQUint32 ContentDecode(BQAsn1Encoder self, BQUint8 *contentBuffer, BQUint32 contentSize)
    {
    if (contentSize == 0)
        return 0;
    assert(contentSize <= 8);
    
    mThis(self)->value = mMethodsGet(mThis(self))->DecodeValue(mThis(self), contentBuffer, contentSize);
    
    return contentSize;
    }

static void MethodsInit(BQAsn1IntegerEncoder self)
    {
    if (!m_methodsInit)
        {
        BQMemInit(&m_methods, 0, sizeof(m_methods));
        
        mMethodSet(m_methods, EncodeValue);
        mMethodSet(m_methods, DecodeValue);
        }
    
    mMethodsSet(self, m_methods);
    }

static void OverrideBQAsn1Encoder(BQAsn1IntegerEncoder self)
    {
    BQAsn1Encoder encoder = (BQAsn1Encoder)self;
    
    if (!m_methodsInit)
        {
        BQMemCopy(&m_BQAsn1EncoderOverride, (void *)mMethodsGet(encoder), sizeof(m_BQAsn1EncoderOverride));
        
        mMethodSet(m_BQAsn1EncoderOverride, DefiniteLength);
        mMethodSet(m_BQAsn1EncoderOverride, IsPrimative);
        mMethodSet(m_BQAsn1EncoderOverride, Class);
        mMethodSet(m_BQAsn1EncoderOverride, TagNumber);
        mMethodSet(m_BQAsn1EncoderOverride, ContentEncode);
        mMethodSet(m_BQAsn1EncoderOverride, ContentDecode);
        }
    
    mMethodsSet(encoder, m_BQAsn1EncoderOverride);
    }

static void Override(BQAsn1IntegerEncoder self)
    {
    OverrideBQAsn1Encoder(self);
    }

static BQUint32 ObjectSize(void)
    {
    return sizeof(tBQAsn1IntegerEncoder);
    }

BQAsn1IntegerEncoder BQAsn1IntegerEncoder_ObjectInit(BQAsn1IntegerEncoder self, BQUint8 *buffer, BQUint32 bufferSize)
    {
    BQMemInit(self, 0, ObjectSize());
    
    /* Super constructor */
    if (BQAsn1Encoder_ObjectInit((BQAsn1Encoder)self, buffer, bufferSize) == BQNULL)
        return BQNULL;
    
    /* Setup class */
    Override(self);
    MethodsInit(self);
    m_methodsInit = 1;
    
    return self;
    }

BQInt64 BQAsn1IntegerEncoder_GetEncodedValue(BQAsn1IntegerEncoder self)
    {
    return self ? self->value : 0x0;
    }

eBQAsn1EncoderRet BQAsn1IntegerEncoder_SetValue(BQAsn1IntegerEncoder self, BQInt64 value)
    {
    if (self == BQNULL)
        return cBQAsn1EncoderObjectNotExist;
    
    BQAsn1Encoder_SetEncoded((BQAsn1Encoder)self, BQFalse);
    self->value = value;
    return cBQAsn1EncoderOk;
    }

BQInt64 BQAsn1IntegerEncoder_GetValue(BQAsn1IntegerEncoder self)
    {
    return BQAsn1Encoder_GetEncoded((BQAsn1Encoder)self) ? self->value : 0x0;
    }

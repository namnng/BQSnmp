/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1BoolEncoder.c
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
#include "BQAsn1BoolEncoderPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/
#define mThis(self) ((BQAsn1BoolEncoder)self)

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;
static tBQAsn1BoolEncoderMethods m_methods;

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
    return 1;
    }

static BQUint8 EncodeBool(BQAsn1BoolEncoder self, BQBool value)
    {
    return value ? 1 : 0;
    }

static BQBool DecodeBool(BQAsn1BoolEncoder self, BQUint8 byteValue)
    {
    return byteValue ? BQTrue : BQFalse;
    }

static BQUint32 ContentEncode(BQAsn1Encoder self, BQUint8 *contentBuffer)
    {
    if ((contentBuffer - self->buffer) >= self->bufferSize)
        return 0;
    
    *contentBuffer = mMethodsGet(mThis(self))->EncodeBool(mThis(self), mThis(self)->value);
    return 1;
    }

static BQUint32 ContentDecode(BQAsn1Encoder self, BQUint8 *contentBuffer, BQUint32 contentSize)
    {
    if (contentSize < 1)
        return 0;
    
    ((BQAsn1BoolEncoder)self)->value = mMethodsGet(mThis(self))->DecodeBool(mThis(self), *contentBuffer);
    return 1;
    }

static void OverrideBQAsn1Encoder(BQAsn1BoolEncoder self)
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

static void Override(BQAsn1BoolEncoder self)
    {
    OverrideBQAsn1Encoder(self);
    }

static void MethodsInit(BQAsn1BoolEncoder self)
    {
    if (!m_methodsInit)
        {
        BQMemInit(&m_methods, 0, sizeof(m_methods));
        
        mMethodSet(m_methods, EncodeBool);
        mMethodSet(m_methods, DecodeBool);
        }
    
    mMethodsSet(self, m_methods);
    }

static BQUint32 ObjectSize(void)
    {
    return sizeof(tBQAsn1BoolEncoder);
    }

BQAsn1BoolEncoder BQAsn1BoolEncoder_ObjectInit(BQAsn1BoolEncoder self, BQUint8 *buffer, BQUint32 bufferSize)
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

eBQAsn1EncoderRet BQAsn1BoolEncoder_SetBool(BQAsn1BoolEncoder self, BQBool value)
    {
    if (self == BQNULL)
        return cBQAsn1EncoderObjectNotExist;
    
    BQAsn1Encoder_SetEncoded((BQAsn1Encoder)self, BQFalse);
    self->value = value;
    
    return cBQAsn1EncoderOk;
    }

BQBool BQAsn1BoolEncoder_GetBool(BQAsn1BoolEncoder self)
    {
    if (BQAsn1Encoder_GetDecoded((BQAsn1Encoder)self))
        return self->value;
    return BQFalse;
    }

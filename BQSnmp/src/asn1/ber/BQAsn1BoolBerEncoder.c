/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1BoolBerEncoder.c
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
#include "../BQAsn1BoolEncoderPrivate.h"

/*------------------------------- Define--------------------------------------*/
#define cNumBytesToEncodeBool 3

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/
typedef struct tBQAsn1BoolBerEncoder
    {
    tBQAsn1BoolEncoder super;
    
    /* Private data */
    }tBQAsn1BoolBerEncoder;

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;

/* Override */
static tBQAsn1EncoderMethods     m_BQAsn1EncoderOverride;
static tBQAsn1BoolEncoderMethods m_BQAsn1BoolEncoderOverride;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static BQUint8 EncodeBool(BQAsn1BoolEncoder self, BQBool value)
    {
    return value ? 0xFF : 0;
    }

static BQUint32 Length(BQAsn1Encoder self)
    {
    return 1;
    }

static void OverrideBQAsn1BoolEncoder(BQAsn1BoolEncoder self)
    {
    if (!m_methodsInit)
        {
        BQMemCopy(&m_BQAsn1BoolEncoderOverride, (void *)self->methods, sizeof(m_BQAsn1BoolEncoderOverride));
        
        mMethodOverride(m_BQAsn1BoolEncoderOverride, EncodeBool);
        }
    
    mMethodsSet(self, m_BQAsn1BoolEncoderOverride);
    }

static void OverrideBQAsn1Encoder(BQAsn1BoolEncoder self)
    {
    BQAsn1Encoder encoder = (BQAsn1Encoder)self;
    
    if (!m_methodsInit)
        {
        BQMemCopy(&m_BQAsn1EncoderOverride, (void *)mMethodsGet(encoder), sizeof(m_BQAsn1EncoderOverride));
        
        mMethodSet(m_BQAsn1EncoderOverride, Length);
        }
    
    mMethodsSet(encoder, m_BQAsn1EncoderOverride);
    }

static void Override(BQAsn1BoolEncoder self)
    {
    OverrideBQAsn1Encoder(self);
    OverrideBQAsn1BoolEncoder(self);
    }

static BQUint32 ObjectSize(void)
    {
    return sizeof(tBQAsn1BoolBerEncoder);
    }

BQAsn1BoolEncoder BQAsn1BoolBerEncoder_ObjectInit(BQAsn1BoolEncoder self, BQUint8 *buffer, BQUint32 bufferSize)
    {
    BQMemInit(self, 0, ObjectSize());
    
    /* Super constructor */
    if (BQAsn1BoolEncoder_ObjectInit(self, buffer, bufferSize) == BQNULL)
        return BQNULL;
    
    /* Setup class */
    Override(self);
    m_methodsInit = 1;
    
    return self;
    }

BQAsn1BoolEncoder BQAsn1BoolBerEncoder_New(BQUint8 *buffer, BQUint32 bufferSize)
    {
    return BQAsn1BoolBerEncoder_ObjectInit(BQMemAlloc(ObjectSize()), buffer, bufferSize);
    }

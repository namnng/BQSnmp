/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1Encoder.c
 *
 * Date        : 7/9/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

/*------------------------------- Includes -----------------------------------*/
#include "BQAsn1EncoderPrivate.h"
#include "common/BQBitMasks.h"

/*------------------------------- Define--------------------------------------*/
/* Idenfifier */
#define cIdentifierClassMask        cBit7_6
#define cIdentifierClassShift       6
#define cIdentifierConstructedMask  cBit5
#define cIdentifierConstructedShift 5
#define cIdentifierTagNumberMask    cBit4_0
#define cIdentifierTagNumberShift   0

/* Length */
#define cShortLengthNumContentOctectsMask  cBit6_0
#define cShortLengthNumContentOctectsShift 0

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQBool m_methodsInit = 0;
static tBQAsn1EncoderMethods m_methods;

/* Override */
static tBQObjectMethods m_BQObjectOverride;

/* Super */
static const tBQObjectMethods *m_BQObjectMethods = BQNULL;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static eBQAsn1IdentifierTagClass Class(BQAsn1Encoder self)
    {
    return cBQAsn1IdentifierTagClassUniversal;
    }

static BQBool IsPrimative(BQAsn1Encoder self)
    {
    return BQTrue;
    }

static BQBool DefiniteLength(BQAsn1Encoder self)
    {
    return BQTrue;
    }

static BQUint32 TagNumber(BQAsn1Encoder self)
    {
    return 0;
    }

static BQUint32 Length(BQAsn1Encoder self)
    {
    return 0;
    }

static void PutPrimative(BQAsn1Encoder self, BQUint8 *identifier)
    {
    BQBool isPrimative = mMethodsGet(self)->IsPrimative(self);
    *identifier = FieldSet(*identifier, cIdentifierConstructedMask, cIdentifierConstructedShift, isPrimative ? 0 : 1);
    }

static void PutClass(BQAsn1Encoder self, BQUint8 *identifier)
    {
    BQUint8 class = mMethodsGet(self)->Class(self);
    *identifier = FieldSet(*identifier, cIdentifierClassMask, cIdentifierClassShift, class);
    }

static void PutShortTagNumber(BQAsn1Encoder self, BQUint8 *identifier, BQUint32 tagNumber)
    {
    *identifier = FieldSet(*identifier, cIdentifierTagNumberMask, cIdentifierTagNumberShift, tagNumber);
    }

static BQUint32 PutLongTagNumber(BQAsn1Encoder self, BQUint8 *identifer, BQUint32 tagNumber)
    {
    /* TODO: Implement this */
    assert(0);
    return 0;
    }

static BQUint32 IdentifierEncode(BQAsn1Encoder self, BQUint8 *identifierBuffer)
    {
    BQUint32 tagNumber;
    BQBool isShortTag;
    BQUint32 numBytesForTag;
    
    if ((identifierBuffer - self->buffer) >= self->bufferSize)
        return 0;
    
    *identifierBuffer = 0;
    PutClass(self, identifierBuffer);
    PutPrimative(self, identifierBuffer);
    
    tagNumber = mMethodsGet(self)->TagNumber(self);
    isShortTag = (tagNumber <= 30);
    if (isShortTag)
        {
        PutShortTagNumber(self, identifierBuffer, tagNumber);
        return 1;
        }
    
    numBytesForTag = PutLongTagNumber(self, identifierBuffer, tagNumber);
    if (numBytesForTag == 0)
        return 0;
    
    return 1 + numBytesForTag;
    }

static BQUint32 PutShortLength(BQAsn1Encoder self, BQUint8 *lengthBuffer, BQUint32 length)
    {
    if ((lengthBuffer - self->buffer) >= self->bufferSize)
        return 0;
    
    *lengthBuffer = length;
    return 1;
    }

static BQUint32 PutLongLength(BQAsn1Encoder self, BQUint8 *lengthBuffer, BQUint32 length)
    {
    /* TODO: Implement me */
    assert(0);
    return 0;
    }

static BQUint32 DefiniteLengthBuild(BQAsn1Encoder self, BQUint8 *lengthBuffer)
    {
    BQUint32 length = mMethodsGet(self)->Length(self);
    
    if (length < cBit6_0)
        return PutShortLength(self, lengthBuffer, length);
    else
        return PutLongLength(self, lengthBuffer, length);
    }

static BQUint32 InfiniteLengthBuild(BQAsn1Encoder self, BQUint8 *lengthBuffer)
    {
    /* TODO: Implement me */
    assert(0);
    return 0;
    }

static BQUint32 LengthEncode(BQAsn1Encoder self, BQUint8 *lengthBuffer)
    {
    if (DefiniteLength(self))
        return DefiniteLengthBuild(self, lengthBuffer);
    else
        return InfiniteLengthBuild(self, lengthBuffer);
    }

static BQUint32 ContentEncode(BQAsn1Encoder self, BQUint8 *contentBuffer)
    {
    /* Sub class should know */
    return 0;
    }

static eBQAsn1EncoderRet Encode(BQAsn1Encoder self)
    {
    BQUint32 numEncodedBytes = 0;
    BQUint8 *currentBuffer = self->buffer;
    
    /* Build Identifier */
    numEncodedBytes = IdentifierEncode(self, currentBuffer);
    if (numEncodedBytes == 0)
        return cBQAsn1EncoderBufferIsNotEnough;
    self->encodedLength += numEncodedBytes;
    
    /* Build Length field */
    currentBuffer += numEncodedBytes;
    numEncodedBytes = LengthEncode(self, currentBuffer);
    if (numEncodedBytes == 0)
        return cBQAsn1EncoderBufferIsNotEnough;
    self->encodedLength += numEncodedBytes;
    
    currentBuffer += numEncodedBytes;
    numEncodedBytes = mMethodsGet(self)->ContentEncode(self, currentBuffer);
    if (numEncodedBytes == 0)
        return cBQAsn1EncoderBufferIsNotEnough;
    self->encodedLength += numEncodedBytes;
    
    return cBQAsn1EncoderOk;
    }

static BQUint32 LongTagNumberDecode(BQAsn1Encoder self, BQUint8 *identifierBuffer)
    {
    /* Implement me */
    assert(0);
    return 0;
    }

static BQUint32 ShortTagNumberDecode(BQAsn1Encoder self, BQUint8 *identifierBuffer)
    {
    if ((identifierBuffer - self->buffer) >= self->bufferSize)
        return 0;
    
    assert((*identifierBuffer & cBit4_0) == mMethodsGet(self)->TagNumber(self));
    return 1;
    }

static BQUint32 IdentifierDecode(BQAsn1Encoder self, BQUint8 *identifierBuffer)
    {
    BQBool isLongTag;
    BQUint8 class = FieldGet(*identifierBuffer, cIdentifierClassMask, cIdentifierClassShift);
    BQBool isPrimative = (*identifierBuffer & cIdentifierConstructedMask) ? BQFalse : BQTrue;
    
    assert(class == mMethodsGet(self)->Class(self));
    assert(isPrimative == mMethodsGet(self)->IsPrimative(self));
    
    isLongTag = (*identifierBuffer & cBit5) ? BQTrue : BQFalse;
    if (isLongTag)
        {
        assert((*identifierBuffer & cBit4_0) == cBit4_0);
        return LongTagNumberDecode(self, identifierBuffer);
        }
    else
        return ShortTagNumberDecode(self, identifierBuffer);
    }

static BQUint32 LongLengthDecode(BQAsn1Encoder self, BQUint8 *lengthBuffer)
    {
    /* TODO: Implement me */
    assert(0);
    return 0;
    }

static BQUint32 ShortLengthDecode(BQAsn1Encoder self, BQUint8 *lengthBuffer)
    {
    if ((lengthBuffer - self->buffer) >= self->bufferSize)
        return 0;
    
    self->length = *lengthBuffer & cBit6_0;
    return 1;
    }

static BQUint32 LengthDecode(BQAsn1Encoder self, BQUint8 *lengthBuffer)
    {
    self->infiniteLength = (*lengthBuffer == cBit7) ? BQTrue : BQFalse;
    if (self->infiniteLength)
        return 1;

    if (*lengthBuffer & cBit7)
        return LongLengthDecode(self, lengthBuffer);
    else
        return ShortLengthDecode(self, lengthBuffer);
    }

static BQUint32 ContentDecode(BQAsn1Encoder self, BQUint8 *contentBuffer, BQUint32 contentSize)
    {
    /* Sub class should know */
    return 0;
    }

static eBQAsn1EncoderRet Decode(BQAsn1Encoder self)
    {
    BQUint32 numDecodedBytes = 0;
    BQUint8 *currentBuffer = self->buffer;
    BQUint32 remainingBytes;
    
    /* Build Identifier */
    numDecodedBytes = IdentifierDecode(self, currentBuffer);
    if (numDecodedBytes == 0)
        return cBQAsn1EncoderBufferIsNotEnough;
    self->encodedLength += numDecodedBytes;
    
    /* Build Length field */
    currentBuffer += numDecodedBytes;
    numDecodedBytes = LengthDecode(self, currentBuffer);
    if (numDecodedBytes == 0)
        return cBQAsn1EncoderBufferIsNotEnough;
    self->encodedLength += numDecodedBytes;
    
    /* Check if content buffer is enough to decode */
    currentBuffer += numDecodedBytes;
    remainingBytes  = (BQUint32)(self->bufferSize - (currentBuffer - self->buffer));
    if (remainingBytes < self->length)
        return cBQAsn1EncoderBufferIsNotEnough;
    
    /* Decode content */
    numDecodedBytes = mMethodsGet(self)->ContentDecode(self, currentBuffer, self->length);
    if (numDecodedBytes == 0)
        return cBQAsn1EncoderBufferIsNotEnough;
    self->encodedLength += numDecodedBytes;
    
    return cBQAsn1EncoderOk;
    }

static void MethodsInit(BQAsn1Encoder self)
    {
    if (!m_methodsInit)
        {
        BQMemInit(&m_methods, 0, sizeof(m_methods));
        
        mMethodSet(m_methods, Encode);
        mMethodSet(m_methods, Decode);
        mMethodSet(m_methods, DefiniteLength);
        mMethodSet(m_methods, IsPrimative);
        mMethodSet(m_methods, TagNumber);
        mMethodSet(m_methods, Length);
        mMethodSet(m_methods, ContentEncode);
        mMethodSet(m_methods, ContentDecode);
        mMethodSet(m_methods, Class);
        }
    
    mMethodsSet(self, m_methods);
    }

static void Delete(BQObject self)
    {
    m_BQObjectMethods->Delete(self);
    }

static BQUint32 ObjectSize(void)
    {
    return sizeof(tBQAsn1Encoder);
    }

static void OverrideBQObject(BQAsn1Encoder self)
    {
    BQObject object = (BQObject)self;
    
    if (!m_methodsInit)
        {
        m_BQObjectMethods = mMethodsGet(object);
        BQMemCopy(&m_BQObjectOverride, (void *)m_BQObjectMethods, sizeof(m_BQObjectOverride));
        
        mMethodSet(m_BQObjectOverride, Delete);
        }
    
    mMethodsSet(object, m_BQObjectOverride);
    }

static void Override(BQAsn1Encoder self)
    {
    OverrideBQObject(self);
    }

BQAsn1Encoder BQAsn1Encoder_ObjectInit(BQAsn1Encoder self, BQUint8 *buffer, BQUint32 bufferSize)
    {
    BQMemInit(self, 0, ObjectSize());
    
    /* Super constructor */
    if (BQObject_ObjectInit((BQObject)self) == BQNULL)
        return BQNULL;
    
    /* Setup class */
    Override(self);
    MethodsInit(self);
    m_methodsInit = 1;
    
    /* Private data */
    self->buffer     = buffer;
    self->bufferSize = bufferSize;
    
    return self;
    }

BQUint32 BQAsn1Encoder_EncodedLength(BQAsn1Encoder self)
    {
    return self ? self->encodedLength : 0;
    }

void BQAsn1Encoder_SetBuffer(BQAsn1Encoder self, BQUint8 *buffer, BQUint32 bufferSize)
    {
    if (self == BQNULL)
        return;
    
    self->buffer = buffer;
    self->bufferSize = bufferSize;
    }

eBQAsn1EncoderRet BQAsn1Encoder_Encode(BQAsn1Encoder self)
    {
    eBQAsn1EncoderRet ret;
    
    if (self == BQNULL)
        return cBQAsn1EncoderObjectNotExist;
    
    self->encodedLength = 0;
    self->encoded = BQFalse;
    ret = mMethodsGet(self)->Encode(self);
    if (ret == cBQAsn1EncoderOk)
        self->encoded = BQTrue;
    
    return ret;
    }

eBQAsn1EncoderRet BQAsn1Encoder_Decode(BQAsn1Encoder self)
    {
    eBQAsn1EncoderRet ret;
    
    if (self == BQNULL)
        return cBQAsn1EncoderObjectNotExist;
    
    self->encodedLength = 0;
    self->decoded = BQFalse;
    ret = mMethodsGet(self)->Decode(self);
    if (ret == cBQAsn1EncoderOk)
        self->decoded = BQTrue;
    
    return ret;
    }

void BQAsn1Encoder_SetEncoded(BQAsn1Encoder self, BQBool encoded)
    {
    if (self)
        self->encoded = encoded;
    }

BQBool BQAsn1Encoder_GetEncoded(BQAsn1Encoder self)
    {
    return self ? self->encoded : BQFalse;
    }

void BQAsn1Encoder_SetDecoded(BQAsn1Encoder self, BQBool decoded)
    {
    if (self)
        self->decoded = decoded;
    }

BQBool BQAsn1Encoder_GetDecoded(BQAsn1Encoder self)
    {
    return self ? self->decoded : BQFalse;
    }

BQUint8 *BQAsn1Encoder_GetBuffer(BQAsn1Encoder self)
    {
    return self ? self->buffer : BQNULL;
    }

BQUint32 BQAsn1Encoder_GetBufferSize(BQAsn1Encoder self)
    {
    return self ? self->bufferSize : 0;
    }


//
//  BQAsn1EncoderTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/9/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "asn1/BQAsn1EncoderManager.h"
#include "common/BQBitMasks.h"

static BQAsn1EncoderManager m_encodeManager = BQNULL;

@interface BQAsn1EncoderTests : BQSnmpTestCase

@property (nonatomic, assign) BQAsn1EncoderManager encoderManager;

@end

@implementation BQAsn1EncoderTests

+ (void)setUp{
    [super setUp];
    m_encodeManager = BQAsn1BerEncoderManager_New();
}

+ (void)tearDown{
    [super tearDown];
    BQObject_Delete((BQObject)m_encodeManager);
    assert(!BQMemLeak());
}

- (BQUint8 *)buffer: (BQUint32 *)size{
    static const BQUint32 cBufferSize = 128;
    static BQUint8 buffer[cBufferSize];
    static BQUint8 *pBuffer = BQNULL;
    
    if (pBuffer == BQNULL){
        BQMemInit(buffer, 0, sizeof(buffer));
        pBuffer = buffer;
    }
    
    if (size)
        *size = cBufferSize;
    
    return pBuffer;
}

#pragma mark - Encoders

- (BQAsn1EncoderManager)encoderManager{
    return m_encodeManager;
}

- (BQAsn1Encoder)setupEncoder: (BQAsn1Encoder)encoder{
    BQUint32 bufferSize;
    BQUint8 *buffer = [self buffer:&bufferSize];
    return [self setupEncoder:encoder withBuffer:buffer size:bufferSize];
}

- (BQAsn1Encoder)setupEncoder: (BQAsn1Encoder)encoder withBuffer: (BQUint8 *)buffer size: (BQUint32)bufferSize{
    BQAsn1Encoder_SetBuffer(encoder, buffer, bufferSize);
    return encoder;
}

#pragma mark - Bool encoder

- (BQAsn1Encoder)boolEncoder{
    return (BQAsn1Encoder)BQAsn1EncoderManager_BoolEncoder([self encoderManager]);
}

- (void)testEncodeBoolWithValue: (BQBool)value{
    BQAsn1BoolEncoder boolEncoder = (BQAsn1BoolEncoder)[self setupEncoder:[self boolEncoder]];
    BQAsn1Encoder encoder = (BQAsn1Encoder)boolEncoder;
    
    /* Encode */
    BQAsn1BoolEncoder_SetBool(boolEncoder, value);
    XCTAssert(BQAsn1Encoder_Encode(encoder) == cBQAsn1EncoderOk, @"Encode fail");
    XCTAssert(BQAsn1Encoder_EncodedLength(encoder) == 3, @"Size of decoded buffer is not right");
    
    /* Decode */
    XCTAssert(BQAsn1Encoder_Decode(encoder) == cBQAsn1EncoderOk, @"Decode fail");
    XCTAssert(BQAsn1Encoder_EncodedLength(encoder) == 3, @"Size of decoded buffer is not right");
    XCTAssertEqual(value, BQAsn1BoolEncoder_GetBool(boolEncoder), @"Decoded value does not match encoded value");
}

- (void)testEncodeBool{
    [self testEncodeBoolWithValue:BQTrue];
    [self testEncodeBoolWithValue:BQFalse];
}

- (void)testEncodeBoolWhenNotEnoughMemory{
    BQUint8 buffer[2];
    BQAsn1Encoder encoder = [self setupEncoder:[self boolEncoder] withBuffer:buffer size:sizeof(buffer)];
    BQAsn1BoolEncoder boolEncoder = (BQAsn1BoolEncoder)encoder;
    
    BQAsn1BoolEncoder_SetBool(boolEncoder, BQTrue);
    XCTAssertEqual(cBQAsn1EncoderBufferIsNotEnough, BQAsn1Encoder_Encode(encoder), @"Error should be returned when buffer is not enough");
    XCTAssertEqual(cBQAsn1EncoderBufferIsNotEnough, BQAsn1Encoder_Decode(encoder), @"Error should be returned when buffer is not enough");
}

#pragma mark - Integer encoder

- (BQAsn1Encoder)integerEncoder{
    return (BQAsn1Encoder)BQAsn1EncoderManager_IntegerEncoder(self.encoderManager);
}

- (void)testEncodeIntegerWithValue: (BQInt64)value expectedNumEncodedBytes: (BQUint32)expectedNumEncodedBytes{
    BQAsn1Encoder encoder = [self setupEncoder:[self integerEncoder]];
    BQAsn1IntegerEncoder integerEncoder = (BQAsn1IntegerEncoder)encoder;
    
    /* Encode */
    BQAsn1IntegerEncoder_SetValue(integerEncoder, value);
    XCTAssertEqual(BQAsn1Encoder_Encode(encoder), cBQAsn1EncoderOk, @"Encode integer fail");
    XCTAssertEqual(BQAsn1Encoder_EncodedLength(encoder), expectedNumEncodedBytes, @"Encoded buffer size is not minimum");
    
    /* Decode */
    XCTAssertEqual(BQAsn1Encoder_Decode(encoder), cBQAsn1EncoderOk, @"Decode integer fail");
    XCTAssertEqual(BQAsn1IntegerEncoder_GetValue(integerEncoder), value, @"Decoded value does not match");
}

- (BQInt64)minNegative: (BQUint8)bitWide{
    BQUint64 value = 2;
    return (value << (bitWide - 2)) * (-1);
}

- (BQInt64)maxPositive: (BQUint8)bitWide{
    BQUint64 value = 2;
    return (value << (bitWide - 2)) - 1;
}

- (void)testEncodeIntegerWithBitWide: (BQUint8)bitWide{
    BQUint8 numExpectedEncodedBytes = 2 + (bitWide / 8);
    [self testEncodeIntegerWithValue:[self maxPositive:bitWide] expectedNumEncodedBytes:numExpectedEncodedBytes];
    [self testEncodeIntegerWithValue:[self minNegative:bitWide] expectedNumEncodedBytes:numExpectedEncodedBytes];
}

- (void)testEncodeInteger{
    for (BQUint8 bitWide = 8; bitWide <= 64; bitWide += 8)
        [self testEncodeIntegerWithBitWide:bitWide];
}

@end

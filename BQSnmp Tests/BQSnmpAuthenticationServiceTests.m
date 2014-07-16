//
//  BQSnmpAuthenticationServiceTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "BQSnmpAuthenticationService.h"
#include "BQSnmpMessagePduFactory.h"

@interface BQSnmpAuthenticationServiceTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpAuthenticationService authenticationService;
@property (nonatomic, assign) BQSnmpMessagePduFactory messageFactory;

@end

@implementation BQSnmpAuthenticationServiceTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (BQSnmpTransportAddress)createAnyTransportAddress{
    /* TODO */
    return BQNULL;
}

- (BQSnmpAsn1)createValidAsn1Object{
    /* TODO */
    return BQNULL;
}

- (void)testCannotEncodeNullObject{
    BQSnmpAsn1 asn1Object = [self createValidAsn1Object];
    BQSnmpAsn1 encodedObject = BQSnmpAuthenticationService_Encode(self.authenticationService,
                                                                   asn1Object,
                                                                   [self createAnyTransportAddress],
                                                                   [self createAnyTransportAddress]);
    XCTAssert(encodedObject == BQNULL, @"Must not be able to encode a NULL object");
}

- (void)testCannotEncodeObjectWithNullTransportAddress{
    BQSnmpAsn1 asn1Object = [self createValidAsn1Object];
    BQSnmpAsn1 encodedObject = BQSnmpAuthenticationService_Encode(self.authenticationService,
                                                                  asn1Object,
                                                                  BQNULL,
                                                                  [self createAnyTransportAddress]);
    XCTAssert(encodedObject == nil, @"Must not be able to encode an object which NULL source transport address");
    
    encodedObject = BQSnmpAuthenticationService_Encode(self.authenticationService,
                                                       asn1Object,
                                                       [self createAnyTransportAddress],
                                                       BQNULL);
    XCTAssert(encodedObject == nil, @"Must not be able to encode a message which NULL destination transport address");
}

- (void)testCanEncodeMessage{
    BQSnmpAsn1 asn1Object = [self createValidAsn1Object];
    BQSnmpAsn1 encodedMessage = BQSnmpAuthenticationService_Encode(self.authenticationService,
                                                                   asn1Object,
                                                                   [self createAnyTransportAddress],
                                                                   [self createAnyTransportAddress]);
    XCTAssert(encodedMessage, @"Must be able to encoded an object");
}

@end

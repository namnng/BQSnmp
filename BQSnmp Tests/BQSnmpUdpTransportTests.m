//
//  BQSnmpUdpTransportTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTransportTests.h"
#include "BQSnmpUdpTransport.h"

@interface BQSnmpUdpTransportTests : BQSnmpTransportTests

@property (nonatomic, readonly) BQSnmpUdpTransport udpTransport;

@end

@implementation BQSnmpUdpTransportTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (BQSnmpUdpTransport)udpTransport{
    return (BQSnmpUdpTransport)self.transport;
}

- (void)testDefaultPortMustBeValid{
    XCTAssert(BQSnmpUdpTransport_MessageReceivePortGet(self.udpTransport) == 161, @"UDP transport must have default port number 161 for receiving message");
    XCTAssert(BQSnmpUdpTransport_TrapReceivePortGet(self.udpTransport) == 162, @"UDP transport must have default port number 162 for receiving trap");
}

- (void)testMaxPduSizeMustBeAcceptable{
    [super testMaxPduSizeMustBeAcceptable];
}

@end

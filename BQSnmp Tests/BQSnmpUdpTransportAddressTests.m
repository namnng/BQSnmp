//
//  BQSnmpUdpTransportAddressTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "BQSnmpUdpTransportAddress.h"

@interface BQSnmpUdpTransportAddressTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpUdpTransportAddress address;

@end

@implementation BQSnmpUdpTransportAddressTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testCanAccessProperties{
    BQSnmpUdpTransportAddress_Port(self.address);
    XCTAssert(BQSnmpUdpTransportAddress_IPAddress(self.address), @"Must have IP address");
}

@end

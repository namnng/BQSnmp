//
//  BQSnmpTransportTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTransportTests.h"

@implementation BQSnmpTransportTests

- (void)testMaxPduSizeMustBeAcceptable{
    XCTAssert(BQSnmpTransport_MaxMessageSize(self.transport) >= 484, @"Transport must support messages with size >= 484 octects");
}

- (void)testSourceAddressMustBeValid{
    XCTAssert(BQSnmpTransport_SourceAddress(self.transport), @"Source address must be valid");
}

@end

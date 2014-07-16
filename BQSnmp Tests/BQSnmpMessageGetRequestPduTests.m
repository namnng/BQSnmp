//
//  BQSnmpMessageGetRequestPduTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpMessagePduTests.h"

@interface BQSnmpMessageGetRequestPduTests : BQSnmpMessagePduTests

@end

@implementation BQSnmpMessageGetRequestPduTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testErrorStatusMustBeZero{
    XCTAssertEqual(BQSnmpMessagePdu_ErrorStatus(self.pdu), 0, @"Error status of GET request PDU must be 0");
}

- (void)testErrorIndexMustBeZero{
    XCTAssertEqual(BQSnmpMessagePdu_ErrorIndex(self.pdu), 0, @"Error index of GET request PDU must be 0");
}

@end

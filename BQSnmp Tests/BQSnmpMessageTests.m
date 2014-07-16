//
//  BQSnmpMessageTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "snmp/BQSnmpMessage.h"

@interface BQSnmpMessageTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpMessage message;

@end

@implementation BQSnmpMessageTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testCanAccessVersion{
    BQSnmpMessage_VersionGet(self.message);
}

- (void)testCanAccessCommunityName{
    BQString commumityName = BQSnmpMessage_CommunityNameGet(self.message);
    XCTAssert(BQString_Length(commumityName) > 0, @"Message must have community name");
}

- (void)testPduMustBeValid{
    XCTAssert(BQSnmpMessage_PduGet(self.message), @"Message must have PDU");
}

@end

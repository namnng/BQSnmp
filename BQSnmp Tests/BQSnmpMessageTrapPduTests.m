//
//  BQSnmpMessageTrapPduTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/8/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpMessagePduTests.h"
#include "BQSnmpMessageTrapPdu.h"

@interface BQSnmpMessageTrapPduTests : BQSnmpMessagePduTests

@property (nonatomic, assign) BQSnmpMessageTrapPdu trapPdu;

@end

@implementation BQSnmpMessageTrapPduTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (BQSnmpMessageTrapPdu)trapPdu{
    return (BQSnmpMessageTrapPdu)self.pdu;
}

- (void)testEnterpriseMustBeValid{
    XCTAssert(BQSnmpMessageTrapPdu_EnterpriseGet(self.trapPdu), @"Enterprise must be valid");
}

- (void)testAgentAddressMustBeValid{
    XCTAssert(BQSnmpMessageTrapPdu_AgentAddress(self.trapPdu), @"Agent address must be valid");
}

- (void)testGenericTypeMustBeValid{
    eBQSnmpMessageTrapPduGenericType genericType = BQSnmpMessageTrapPdu_GenericType(self.trapPdu);
    XCTAssert(BQSnmpMessageTrapPduGenericTypeIsValid(genericType), @"Invalid generic trap type");
}

- (void)testCanGetSpecificTrap{
    BQSnmpMessageTrapPdu_SpecificType(self.trapPdu);
}

- (void)testCanAccessTimeTicks{
    XCTAssert(BQSnmpMessageTrapPdu_TimeTicks(self.trapPdu), @"Time ticks must be valid");
}

@end

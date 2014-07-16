//
//  BQSnmpAccessPolicyTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "BQSnmpAccessPolicy.h"

@interface BQSnmpAccessPolicyTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpAccessPolicy policy;

@end

@implementation BQSnmpAccessPolicyTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testCanAccessCommunityProfile{
    XCTAssert(BQSnmpAccessPolicy_CommunityProfileGet(self.policy), @"No community profile");
}

- (void)testCanAccessCommunity{
    XCTAssert(BQSnmpAccessPolicy_CommunityGet(self.policy), @"No community");
}

@end

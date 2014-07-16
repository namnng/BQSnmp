//
//  BQSnmpMessagePduFactoryTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "BQSnmpMessagePduFactory.h"

@interface BQSnmpMessagePduFactoryTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpMessagePduFactory factory;

@end

@implementation BQSnmpMessagePduFactoryTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testMustBeAbleToCreateAllOfBasicMessageType{
    XCTAssert(BQSnmpMessageFactory_GetRequestPduCreate(self.factory), @"GET request must be able to be created");
    XCTAssert(BQSnmpMessageFactory_GetNextRequestPduCreate(self.factory), @"GET NEXT request must be able to be created");
    XCTAssert(BQSnmpMessageFactory_GetResponsePduCreate(self.factory), @"GET RESPONSE request must be able to be created");
    XCTAssert(BQSnmpMessageFactory_SetRequestPduCreate(self.factory), @"SET request must be able to be created");
    XCTAssert(BQSnmpMessageFactory_TrapPduCreate(self.factory), @"TRAP must be able to be created");
}

@end

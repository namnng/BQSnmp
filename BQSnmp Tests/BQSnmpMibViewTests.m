//
//  BQSnmpMibViewTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "BQSnmpMibView.h"

@interface BQSnmpMibViewTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpMibView mibView;

@end

@implementation BQSnmpMibViewTests

- (void)setUp{
    [super setUp];
}

- (void)tearDown{
    [super tearDown];
}

- (void)testCanIterateVariable{
    BQUint32 numVariables = 0;
    BQSnmpVariable variable;
    BQIterator variableIterator = BQSnmpMibView_VariableIteratorCreate(self.mibView);
    XCTAssert(variableIterator != BQNULL, @"No variable iterator");
    
    while ((variable = (BQSnmpVariable)BQIteratorNext(variableIterator)) != BQNULL)
        numVariables = numVariables + 1;
    
    XCTAssert(numVariables > 0, @"MIB view must have at least one variable");
    
    BQObject_Delete((BQObject)variableIterator);
}

- (void)testCanAccessVariableProperties{
    BQSnmpVariable variable;
    BQIterator variableIterator = BQSnmpMibView_VariableIteratorCreate(self.mibView);
    while ((variable = (BQSnmpVariable)BQIteratorNext(variableIterator)) != BQNULL){
        eBQSnmpAccessMode accessMode = BQSnmpVariable_AccessModeGet(variable);
        XCTAssert(BQSnmpAccessModeIsValid(accessMode), @"Invalid access mode");
        XCTAssert(BQSnmpVariable_Identifier(variable), @"Variable has no object identifier");
    }
    BQObject_Delete((BQObject)variableIterator);
}

@end

//
//  BQSnmpCommunityProfileTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "BQSnmpCommunityProfile.h"

@interface BQSnmpCommunityProfileTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpCommunityProfile profile;

@end

@implementation BQSnmpCommunityProfileTests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)_testChangeAccessMode: (eBQSnmpAccessMode)accessMode{
    XCTAssertEqual(BQSnmpCommunityProfile_AccessModeSet(self.profile, accessMode), cBQSnmpOk, @"Cannot change access mode");
    XCTAssertEqual(BQSnmpCommunityProfile_AccessModeGet(self.profile), accessMode, @"Cannot change access mode");
}

- (void)testCannotChangeNoneAccessMode{
    XCTAssert(BQSnmpCommunityProfile_AccessModeSet(self.profile, cBQSnmpAccessModeNone) != cBQSnmpOk, @"None access mode is not applicable for community profile");
}

- (void)testCannotChangeWriteOnlyAccessMode{
    XCTAssert(BQSnmpCommunityProfile_AccessModeSet(self.profile, cBQSnmpAccessModeWrite) != cBQSnmpOk, @"Write-only access mode is not applicable for community profile");
}

- (void)testCanAccessMode
{
    /* The default mode must be valid */
    eBQSnmpAccessMode accessMode = BQSnmpCommunityProfile_AccessModeGet(self.profile);
    XCTAssert(BQSnmpAccessModeIsValid(accessMode), @"Invalid access mode");
    
    /* Try to change */
    [self _testChangeAccessMode:cBQSnmpAccessModeRead];
    [self _testChangeAccessMode:cBQSnmpAccessModeWrite | cBQSnmpAccessModeWrite];
}

- (void)testMustHaveMibView{
    XCTAssert(BQSnmpCommunityProfile_MibViewGet(self.profile), @"No MIB view");
}

- (void)testCanGetVariableAccessMode{
    BQSnmpMibView mibView = BQSnmpCommunityProfile_MibViewGet(self.profile);
    BQIterator variableIterator = BQSnmpMibView_VariableIteratorCreate(mibView);
    BQSnmpVariable variable;
    while ((variable = (BQSnmpVariable)BQIteratorNext(variableIterator)) != BQNULL){
        eBQSnmpOperation operation = BQSnmpCommunityProfile_OperationsForVariable(self.profile, variable);
        XCTAssert(BQSnmpOperationIsValid(operation), @"Invalid operation");
    }
    BQObject_Delete((BQObject)variableIterator);
}

- (BQSnmpVariable)findVariableWithAccessMode: (eBQSnmpAccessMode)accessMode{
    BQSnmpMibView mibView = BQSnmpCommunityProfile_MibViewGet(self.profile);
    BQIterator variableIterator = BQSnmpMibView_VariableIteratorCreate(mibView);
    BQSnmpVariable variable = BQNULL;
    while ((variable = (BQSnmpVariable)BQIteratorNext(variableIterator)) != BQNULL){
        if (BQSnmpVariable_AccessModeGet(variable) == accessMode)
            break;
    }
    BQObject_Delete((BQObject)variableIterator);
    return variable;
}

- (void)_testVariable: (BQSnmpVariable)variable operationsMatch: (eBQSnmpOperation)expectedOperations{
    eBQSnmpOperation operations = BQSnmpCommunityProfile_OperationsForVariable(self.profile, variable);
    XCTAssert(operations & expectedOperations, @"Expect operations not fully match");
    XCTAssert(operations & (~expectedOperations), @"There should be no other operations");
}

- (void)testVariableAccessModeMustBeValid{
    /* if said variable is defined in the MIB with "Access:" of
     "none," it is unavailable as an operand for any operator */
    BQSnmpVariable variable = [self findVariableWithAccessMode:cBQSnmpAccessModeNone];
    XCTAssert(variable != BQNULL, @"No variable with None access mode");
    eBQSnmpOperation operations = BQSnmpCommunityProfile_OperationsForVariable(self.profile, variable);
    XCTAssertEqual(operations, cBQSnmpOperationNone, @"Variable operation is not right");
    
    /* if said variable is defined in the MIB with "Access:" of
     "read-write" or "write-only" and the access mode of the
     given profile is READ-WRITE, that variable is available
     as an operand for the get, set, and trap operations */
    variable = [self findVariableWithAccessMode:cBQSnmpAccessModeRead | cBQSnmpAccessModeWrite];
    XCTAssert(variable != BQNULL, @"No Read-Write variable");
    BQSnmpCommunityProfile_AccessModeSet(self.profile, cBQSnmpAccessModeRead | cBQSnmpAccessModeWrite);
    [self _testVariable:variable operationsMatch:cBQSnmpOperationGet | cBQSnmpOperationSet | cBQSnmpOperationTrap];
    
    /* otherwise, the variable is available as an operand for
     the get and trap operations. */
    BQSnmpCommunityProfile_AccessModeSet(self.profile, cBQSnmpAccessModeRead);
    [self _testVariable:variable operationsMatch:cBQSnmpOperationGet | cBQSnmpOperationTrap];
    
    /* In those cases where a "write-only" variable is an
     operand used for the get or trap operations, the value
     given for the variable is implementation-specific. */
    variable = [self findVariableWithAccessMode:cBQSnmpAccessModeWrite];
    XCTAssert(variable != BQNULL, @"No Write-Only variable");
    [self _testVariable:variable operationsMatch:cBQSnmpOperationGet | cBQSnmpOperationTrap];
}

@end

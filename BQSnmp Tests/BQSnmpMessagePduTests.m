//
//  BQSnmpMessagePduTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpMessagePduTests.h"

@implementation BQSnmpMessagePduTests

- (void)testCanGetRequestId{
    BQSnmpMessagePdu_RequestId(self.pdu);
}

- (void)testCanGetErrorStatus{
    BQSnmpMessagePdu_ErrorStatus(self.pdu);
}

- (void)testCanGetErrorIndex{
    BQSnmpMessagePdu_ErrorIndex(self.pdu);
}

- (void)testCanAccessVariableBinding{
    BQUint32 numVariables = BQSnmpMessagePdu_NumVariables(self.pdu);
    for (BQUint32 var_i; var_i < numVariables; var_i++){
        BQSnmpVariable variable = BQSnmpMessagePdu_VariableAtIndex(self.pdu, var_i);
        XCTAssert(variable, @"Variable binding at index %u must not be NULL", var_i);
        XCTAssert(BQSnmpVariable_Identifier(variable), @"Variable binding must have valid object name");
        XCTAssert(BQSnmpVariable_ValueGet(variable), @"Variable binding must have valid object syntax");
    }
}

- (void)testPduTypeMustBeValid{
    eBQSnmpMessagePduType pduType = BQSnmpMessagePdu_Type(self.pdu);
    XCTAssert(BQSnmpMessagePdu_TypeIsValid(pduType), @"PDU type must be valid");
}

@end

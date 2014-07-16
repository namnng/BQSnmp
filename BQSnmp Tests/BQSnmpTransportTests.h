//
//  BQSnmpTransportTests.h
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#include "BQSnmpTransport.h"

@interface BQSnmpTransportTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpTransport transport;

- (void)testMaxPduSizeMustBeAcceptable;

@end

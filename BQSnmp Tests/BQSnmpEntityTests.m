//
//  BQSnmpEntityTests.m
//  BQSnmp
//
//  Created by Nam Nguyen Ngoc on 7/6/14.
//  Copyright (c) 2014 BQ, Inc. All rights reserved.
//

#import "BQSnmpTestCase.h"
#import "BQSnmpEntity.h"

@interface BQSnmpEntityTests : BQSnmpTestCase

@property (nonatomic, assign) BQSnmpEntity entity;

@end

@implementation BQSnmpEntityTests

#pragma mark - Utils

- (BQSnmpTransportAddress)createAnyValidTransportAddress{
    /* TODO */
    return BQNULL;
}

- (BQSnmpMessage)createValidMessage{
    /* TODO */
    return BQNULL;
}

- (BQString)createValidCommunity{
    /* TODO */
    return BQNULL;
}

#pragma mark - Tests

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testColdStart{
    XCTAssert(BQSnmpEntity_ColdStart(self.entity) == cBQSnmpOk, @"Must be able to cold start entity");
    XCTAssert(0, @"Test if cold-start trap is sent");
}

- (void)testWarmStart{
    XCTAssert(BQSnmpEntity_WarmStart(self.entity), @"Must be able to warm start entity");
    XCTAssert(0, @"Test if warm-start trap is sent");
}

- (void)testCanGetVersion{
    BQSnmpEntity_Version(self.entity);
}

- (void)testMustHaveDefaultTransport{
    XCTAssert(BQSnmpEntity_TransportGet(self.entity), @"Default transport must exist");
}

- (void)testCanChangeTransport{
    XCTFail(@"%s has not implemented", __PRETTY_FUNCTION__);
}

- (void)testCannotSetTransportToNull{
    XCTAssert(BQSnmpEntity_TransportSet(self.entity, BQNULL), @"There must be a transport");
}

- (void)testCannotSetNullMessageFactory{
    XCTAssert(BQSnmpEntity_MessagePduFactorySet(self.entity, BQNULL), @"NULL factory must not be set to entiry");
}

- (void)testMustHaveMessageFactory{
    XCTAssert(BQSnmpEntity_MessagePduFactoryGet(self.entity), @"Entity must have message factory");
}

- (void)testCanChangeMessageFactory{
    BQUint32 any = 0;
    BQSnmpMessagePduFactory anyFactory = (BQSnmpMessagePduFactory)&any;
    XCTAssert(BQSnmpEntity_MessagePduFactorySet(self.entity, anyFactory) == cBQSnmpOk, @"Must be able to change message factory");
    XCTAssert(BQSnmpEntity_MessagePduFactoryGet(self.entity) == anyFactory, @"Cannot retrieve message factory");
}

- (void)testCannotSetNullAuthenticationService{
    XCTAssert(BQSnmpEntity_AuthenticationServiceSet(self.entity, BQNULL), @"NULL authentication service must not be able to be set to entity");
}

- (void)testMustHaveDefaultAuthenticationService{
    XCTAssert(BQSnmpEntity_AuthenticationServiceGet(self.entity), @"Entity must have default authentication service");
}

- (void)testCanChangeAuthenticationService{
    BQUint32 any = 0;
    BQSnmpAuthenticationService anyService = (BQSnmpAuthenticationService)&any;
    XCTAssert(BQSnmpEntity_AuthenticationServiceSet(self.entity, anyService) == cBQSnmpOk, @"Must be able to change authentication service");
    XCTAssert(BQSnmpEntity_AuthenticationServiceGet(self.entity) == anyService, @"Cannot retrieve authentication service");
}

- (void)testCannotSendANullMessage{
    XCTAssert(BQSnmpEntity_SendMessage(self.entity, BQNULL, [self createAnyValidTransportAddress], [self createValidCommunity]) != cBQSnmpOk, @"NULL message must not be able be sent");
}

- (void)testCannotSendMessageToNULLAddress{
    BQSnmpMessage message = [self createValidMessage];
    XCTAssert(BQSnmpEntity_SendMessage(self.entity, message, BQNULL, [self createValidCommunity]) != cBQSnmpOk, @"Message should not be send to NULL address");
}

- (void)testCannotSendMessageToNullCommunity{
    BQSnmpMessage message = [self createValidMessage];
    BQSnmpTransportAddress destination = [self createAnyValidTransportAddress];
    XCTAssert(BQSnmpEntity_SendMessage(self.entity, message, destination, BQNULL) == cBQSnmpOk, @"Message should not be send to NULL community");
}

- (void)testCanSendMessageToValidAddress{
    BQUint32 numSentMessages = BQSnmpEntity_NumSentMessages(self.entity);
    BQSnmpMessage message = [self createValidMessage];
    BQSnmpTransportAddress destination = [self createAnyValidTransportAddress];
    XCTAssert(BQSnmpEntity_SendMessage(self.entity, message, destination, [self createValidCommunity]) == cBQSnmpOk, @"Valid message can be send to valid destination");
    XCTAssert(BQSnmpEntity_NumSentMessages(self.entity) == (numSentMessages + 1), @"TX Counters have not been updated");
}

- (void)testCanGetStatistic{
    BQSnmpEntity_NumSentMessages(self.entity);
    BQSnmpEntity_NumReceivedMessages(self.entity);
    BQSnmpEntity_NumReceivedDiscardedMessages(self.entity);
}

- (void)testCannotReceiveNULLMessage{
    BQUint32 numReceivedMessage = BQSnmpEntity_NumReceivedMessages(self.entity);
    XCTAssert(BQSnmpEntity_ReceiveMessage(self.entity, BQNULL, [self createAnyValidTransportAddress], [self createAnyValidTransportAddress]) != cBQSnmpOk, @"NULL message must not be able to be processed");
    XCTAssertEqual(BQSnmpEntity_NumReceivedMessages(self.entity), numReceivedMessage, @"Invalid message must not be counted to num received messages counter");
}

- (void)testCannotReceiveMessageFromNullSource{
    BQUint32 numReceivedMessage = BQSnmpEntity_NumReceivedMessages(self.entity);
    BQSnmpMessage newMessage = [self createValidMessage];
    BQSnmpTransportAddress destination = [self createAnyValidTransportAddress];
    BQSnmpAsn1 encodedMessage = BQSnmpEntity_EncodeMessage(self.entity, newMessage, destination, [self createValidCommunity]);
    XCTAssert(BQSnmpEntity_ReceiveMessage(self.entity, encodedMessage, BQNULL, destination) != cBQSnmpOk, @"NULL message must not be able to be processed");
    XCTAssertEqual(BQSnmpEntity_NumReceivedMessages(self.entity), numReceivedMessage, @"Invalid message must not be counted to num received messages counter");
}

- (void)testCannotReceiveMessageToNullDestination{
    BQUint32 numReceivedMessage = BQSnmpEntity_NumReceivedMessages(self.entity);
    BQSnmpMessage newMessage = [self createValidMessage];
    BQSnmpTransportAddress source = [self createAnyValidTransportAddress];
    BQSnmpTransportAddress destination = [self createAnyValidTransportAddress];
    BQSnmpAsn1 encodedMessage = BQSnmpEntity_EncodeMessage(self.entity, newMessage, destination, [self createValidCommunity]);
    XCTAssert(BQSnmpEntity_ReceiveMessage(self.entity, encodedMessage, source, BQNULL) != cBQSnmpOk, @"NULL message must not be able to be processed");
    XCTAssertEqual(BQSnmpEntity_NumReceivedMessages(self.entity), numReceivedMessage, @"Invalid message must not be counted to num received messages counter");
}

- (void)testReceiveMessage{
    BQUint32 numReceivedMessage = BQSnmpEntity_NumReceivedMessages(self.entity);
    BQSnmpMessage newMessage = [self createValidMessage];
    BQSnmpTransportAddress source = [self createAnyValidTransportAddress];
    BQSnmpTransportAddress destination = [self createAnyValidTransportAddress];
    BQSnmpAsn1 encodedMessage = BQSnmpEntity_EncodeMessage(self.entity, newMessage, destination, [self createValidCommunity]);
    XCTAssert(BQSnmpEntity_ReceiveMessage(self.entity, encodedMessage, source, destination) == cBQSnmpOk, @"Must be able to receive valid message");
    XCTAssertEqual(BQSnmpEntity_NumReceivedMessages(self.entity), numReceivedMessage + 1, @"Number of receive messages counter must be updated");
}

- (void)testCountersMustBeHandledProperly{
    XCTAssert(0, @"Implement this");
}

- (void)testMibViewMustNotBeNULL{
    XCTAssert(BQSnmpEntity_MibView(self.entity), @"Entity must have MIB view");
}

- (void)testSendTraps{
    XCTAssert(BQSnmpEntity_SendColdStartTrap(self.entity) == cBQSnmpOk, @"Must be able to send cold-start trap");
    XCTAssert(BQSnmpEntity_SendWarmStartTrap(self.entity) == cBQSnmpOk, @"Must be able to send warm-start trap");
    XCTAssert(BQSnmpEntity_SendLinkDownTrap(self.entity) == cBQSnmpOk, @"Must be able to send link down trap");
    XCTAssert(BQSnmpEntity_SendLinkUpTrap(self.entity) == cBQSnmpOk, @"Must be able to send link up trap");
    XCTAssert(BQSnmpEntity_SendAuthenticationFailureTrap(self.entity) == cBQSnmpOk, @"Must be able to send authentication failure trap");
    XCTAssert(BQSnmpEntity_SendEgpNeighborLossTrap(self.entity) == cBQSnmpOk, @"Must be able to send EGP neighbor loss  trap");
}

- (void)testSendEnterpriseSpecificTraps{
    XCTAssert(BQSnmpEntity_SendEnterpriseSpecificTrap(self.entity, BQNULL) == cBQSnmpOk, @"Not implement yet");
}

@end

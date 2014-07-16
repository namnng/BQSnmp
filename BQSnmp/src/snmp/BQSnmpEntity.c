/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpEntity.c
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

/*------------------------------- Includes -----------------------------------*/
#include <assert.h>
#include "BQSnmpEntityPrivate.h"
#include "collection/BQList.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static BQSnmpAsn1 Pdu2Asn1(BQSnmpEntity self, BQSnmpMessagePdu messagePdu)
    {
    /* TODO: implement me */
    return BQNULL;
    }

static BQSnmpAsn1 PduAsn1AndCommunity2Asn1(BQSnmpEntity self, BQSnmpAsn1 pduAsn1, BQString communityName)
    {
    /* TODO: Implement me */
    return BQNULL;
    }

static BQSnmpMessage Asn1Object2Message(BQSnmpEntity self, BQSnmpAsn1 asn1Object)
    {
    /* TODO: Implement me */
    return BQNULL;
    }

static eBQSnmpRet DecodedAsn1ToPdu(BQSnmpEntity self, BQSnmpAsn1 decodedObject, BQSnmpMessage message)
    {
    /* TODO: Implement me */
    return cBQSnmpError;
    }

static BQSnmpMessagePdu ConstructNoSuchNameGetResponsePdu(BQSnmpEntity self, BQSnmpVariable variable, BQUint32 variableIndex)
    {
    /* TODO */
    return BQNULL;
    }

static BQSnmpMessagePdu ConstructGenErrorGetResponsePdu(BQSnmpEntity self, BQSnmpVariable variable, BQUint32 variableIndex)
    {
    /* TODO */
    return BQNULL;
    }

static BQSnmpMessagePdu ConstructTooBigGetResponsePdu(BQSnmpEntity self)
    {
    /* TODO */
    return BQNULL;
    }

static BQSnmpMessagePdu ConstructGetResponsePdu(BQSnmpEntity self, BQList variables)
    {
    /* TODO */
    return BQNULL;
    }

static BQSnmpMessagePdu ConstructBadValueGetResponsePdu(BQSnmpEntity self, BQSnmpVariable variable, BQUint32 variableIndex)
    {
    /* TODO */
    return BQNULL;
    }

static BQList CreateList(BQSnmpEntity self)
    {
    /* TODO */
    return BQNULL;
    }

static BQUint32 CalculateGetResponsePduSize(BQSnmpEntity self, BQList variables)
    {
    /* TODO */
    return 0xFFFFFFFF;
    }

static BQSnmpMessage ProcessTrapMessage(BQSnmpEntity self, BQSnmpMessage message)
    {
    /* TODO: Implement me */
    return BQNULL;
    }

static BQSnmpVariable SearchVariableByObjectId(BQSnmpEntity self, BQSnmpObjectIdentifier objectId)
    {
    BQSnmpMibView mibView = BQSnmpEntity_MibView(self);
    return BQSnmpMibView_SearchVariableByObjectId(mibView, objectId);
    }

static BQSnmpVariable SearchSuccessorVariableByObjectId(BQSnmpEntity self, BQSnmpObjectIdentifier objectId)
    {
    BQSnmpMibView mibView = BQSnmpEntity_MibView(self);
    return BQSnmpMibView_SearchSuccessorVariableByObjectId(mibView, objectId);
    }

static BQSnmpMessage ProcessGetRequestMessage(BQSnmpEntity self, BQSnmpMessage message)
    {
    BQSnmpMessagePdu pdu = BQSnmpMessage_PduGet(message);
    BQUint32 numVariables = BQSnmpMessagePdu_NumVariables(pdu);
    BQUint32 var_i;
    BQSnmpMibView mibView = BQSnmpEntity_MibView(self);
    BQSnmpMessagePdu responsePdu = BQNULL;
    BQList variables = CreateList(self);
    
    /* Search for variables in MIB view */
    for (var_i = 0; var_i < numVariables; var_i++)
        {
        BQSnmpVariable variableBinding = BQSnmpMessagePdu_VariableAtIndex(pdu, var_i);
        BQSnmpVariable variable = SearchVariableByObjectId(self, BQSnmpVariable_Identifier((BQSnmpVariable)variableBinding));
        assert(variableBinding);
        
        if (variable == BQNULL)
            {
            responsePdu = ConstructNoSuchNameGetResponsePdu(self, variableBinding, var_i);
            break;
            }
        
        if (BQSnmpMibView_IsAggregateVariable(mibView, variable))
            {
            responsePdu = ConstructNoSuchNameGetResponsePdu(self, variableBinding, var_i);
            break;
            }
        
        if (BQSnmpVariable_ValueGet(variable) == BQNULL)
            {
            responsePdu = ConstructGenErrorGetResponsePdu(self, variableBinding, var_i);
            break;
            }
        
        assert(BQList_AddObject(variables, (BQObject)variable) == cBQSnmpOk);
        }
    
    /* Also need to check if GET-RESPONSE PDU size is too large */
    if (responsePdu == BQNULL)
        {
        BQUint32 size = CalculateGetResponsePduSize(self, variables);
        BQSnmpTransport transport = BQSnmpEntity_TransportGet(self);
        if (size > BQSnmpTransport_MaxMessageSize(transport))
            responsePdu = ConstructTooBigGetResponsePdu(self);
        }
    
    if (responsePdu == BQNULL)
        responsePdu = ConstructGetResponsePdu(self, variables);
    
    BQObject_Delete((BQObject)variables);
    
    return BQSnmpMessageNew(BQSnmpMessage_VersionGet(message),
                            BQSnmpMessage_CommunityNameGet(message),
                            responsePdu);
    }

static BQSnmpMessage ProcessGetNextRequestMessage(BQSnmpEntity self, BQSnmpMessage message)
    {
    BQSnmpMessagePdu pdu = BQSnmpMessage_PduGet(message);
    BQUint32 numVariables = BQSnmpMessagePdu_NumVariables(pdu);
    BQUint32 var_i;
    BQSnmpMessagePdu responsePdu = BQNULL;
    BQList variables = CreateList(self);
    
    /* Search for variables in MIB view */
    for (var_i = 0; var_i < numVariables; var_i++)
        {
        BQSnmpVariable variableBinding = BQSnmpMessagePdu_VariableAtIndex(pdu, var_i);
        BQSnmpVariable nextVariable = SearchSuccessorVariableByObjectId(self, BQSnmpVariable_Identifier((BQSnmpVariable)variableBinding));
        assert(variableBinding);
        
        if (nextVariable == BQNULL)
            {
            responsePdu = ConstructNoSuchNameGetResponsePdu(self, variableBinding, var_i);
            break;
            }
        
        if (BQSnmpVariable_ValueGet(nextVariable) == BQNULL)
            {
            responsePdu = ConstructGenErrorGetResponsePdu(self, variableBinding, var_i);
            break;
            }
        
        assert(BQList_AddObject(variables, (BQObject)nextVariable) == cBQSnmpOk);
        }
    
    /* Also need to check if GET-RESPONSE PDU size is too large */
    if (responsePdu == BQNULL)
        {
        BQUint32 size = CalculateGetResponsePduSize(self, variables);
        BQSnmpTransport transport = BQSnmpEntity_TransportGet(self);
        if (size > BQSnmpTransport_MaxMessageSize(transport))
            responsePdu = ConstructTooBigGetResponsePdu(self);
        }
    
    if (responsePdu == BQNULL)
        responsePdu = ConstructGetResponsePdu(self, variables);
    
    BQObject_Delete((BQObject)variables);
    
    return BQSnmpMessageNew(BQSnmpMessage_VersionGet(message),
                            BQSnmpMessage_CommunityNameGet(message),
                            responsePdu);
    }

static BQSnmpMessage ProcessSetRequestMessage(BQSnmpEntity self, BQSnmpMessage message)
    {
    BQSnmpMessagePdu pdu = BQSnmpMessage_PduGet(message);
    BQUint32 numVariables = BQSnmpMessagePdu_NumVariables(pdu);
    BQUint32 var_i;
    BQSnmpMibView mibView = BQSnmpEntity_MibView(self);
    BQSnmpMessagePdu responsePdu = BQNULL;
    BQList variables = CreateList(self);
    
    /* Search for variables in MIB view */
    for (var_i = 0; var_i < numVariables; var_i++)
        {
        BQSnmpVariable variableBinding = BQSnmpMessagePdu_VariableAtIndex(pdu, var_i);
        BQSnmpVariable variable = SearchVariableByObjectId(self, BQSnmpVariable_Identifier((BQSnmpVariable)variableBinding));
        assert(variableBinding);
        
        if (variable == BQNULL)
            {
            responsePdu = ConstructNoSuchNameGetResponsePdu(self, variableBinding, var_i);
            break;
            }
        
        if (BQSnmpMibView_IsAggregateVariable(mibView, variable))
            {
            responsePdu = ConstructNoSuchNameGetResponsePdu(self, variableBinding, var_i);
            break;
            }
        
        if (!BQSnmpVariable_ValueIsConsistent(variable, BQSnmpVariable_ValueGet(variableBinding)))
            {
            responsePdu = ConstructBadValueGetResponsePdu(self, variableBinding, var_i);
            break;
            }
        
        assert(BQList_AddObject(variables, (BQObject)variable) == cBQSnmpOk);
        }
    
    /* Also need to check if GET-RESPONSE PDU size is too large */
    if (responsePdu == BQNULL)
        {
        BQUint32 size = CalculateGetResponsePduSize(self, variables);
        BQSnmpTransport transport = BQSnmpEntity_TransportGet(self);
        if (size > BQSnmpTransport_MaxMessageSize(transport))
            responsePdu = ConstructTooBigGetResponsePdu(self);
        }
    
    /* No error has been found, apply new values */
    if (responsePdu == BQNULL)
        {
        for (var_i = 0; var_i < numVariables; var_i++)
            {
            BQSnmpVariable variableBinding = BQSnmpMessagePdu_VariableAtIndex(pdu, var_i);
            BQSnmpVariable variable = (BQSnmpVariable)BQList_GetObjectAtIndex(variables, var_i);
            if (BQSnmpVariable_ValueSet(variable, BQSnmpVariable_ValueGet(variableBinding)) != cBQSnmpOk)
                {
                responsePdu = ConstructGenErrorGetResponsePdu(self, variableBinding, var_i);
                break;
                }
            }
        }
    
    /* TODO: Need to consider revert previous data */
    if (responsePdu)
        {
        }
    
    if (responsePdu == BQNULL)
        responsePdu = ConstructGetResponsePdu(self, variables);
    
    BQObject_Delete((BQObject)variables);
    
    return BQSnmpMessageNew(BQSnmpMessage_VersionGet(message),
                            BQSnmpMessage_CommunityNameGet(message),
                            responsePdu);
    }

static BQSnmpMessage ProcessReceiveMessage(BQSnmpEntity self, BQSnmpMessage message)
    {
    switch (BQSnmpMessagePdu_Type(BQSnmpMessage_PduGet(message)))
        {
        case cBQSnmpMessagePduTypeGetRequest:
            return ProcessGetRequestMessage(self, message);
        case cBQSnmpMessagePduTypeGetNextRequest:
            return ProcessGetNextRequestMessage(self, message);
        case cBQSnmpMessagePduTypeSetRequest:
            return ProcessSetRequestMessage(self, message);
        case cBQSnmpMessagePduTypeTrap:
            return ProcessTrapMessage(self, message);
            
        default:
            assert(0);
            break;
        }
    
    return BQNULL;
    }

static void SendTrapWhenDecodeMessageFail(BQSnmpEntity self)
    {
    /* TODO: consider to implement this. This is just an optional */
    }

static BQSnmpAsn1 EncodePdu(BQSnmpEntity self, BQSnmpMessage message, BQSnmpTransportAddress destination)
    {
    BQSnmpAuthenticationService authService = BQSnmpEntity_AuthenticationServiceGet(self);
    BQSnmpTransport transport = BQSnmpEntity_TransportGet(self);
    BQSnmpTransportAddress sourceAddress = BQSnmpTransport_SourceAddress(transport);
    BQSnmpAsn1 pduAsn1 = Pdu2Asn1(self, BQSnmpMessage_PduGet(message));
    return BQSnmpAuthenticationService_Encode(authService, pduAsn1, sourceAddress, destination);
    }

static void IncreaseNumDiscardedMessages(BQSnmpEntity self)
    {
    self->numDiscardedMessages++;
    }

static void IncreaseNumMismatchedVersionMessages(BQSnmpEntity self)
    {
    IncreaseNumDiscardedMessages(self);
    self->numVersionMismatchedMessages++;
    }

static void IncreaseNumDecodedFailMessages(BQSnmpEntity self)
    {
    IncreaseNumDiscardedMessages(self);
    self->numDecodedFailMessages++;
    }

static void IncreaseNumReceivedMessages(BQSnmpEntity self)
    {
    self->numReceivedMessages++;
    }

BQSnmpAsn1 BQSnmpEntity_EncodeMessage(BQSnmpEntity self,
                                      BQSnmpMessage message,
                                      BQSnmpTransportAddress destination,
                                      BQString communityName)
    {
    BQSnmpAsn1 encodedPdu;
    
    if (self == BQNULL)
        return BQNULL;
    
    if ((message == BQNULL) || (destination == BQNULL) || (communityName == BQNULL))
        return BQNULL;
    
    /* Build data to send */
    encodedPdu  = EncodePdu(self, message, destination);
    return PduAsn1AndCommunity2Asn1(self, encodedPdu, communityName);
    }

eBQSnmpRet BQSnmpEntity_SendMessage(BQSnmpEntity self,
                                    BQSnmpMessage message,
                                    BQSnmpTransportAddress destination,
                                    BQString communityName)
    {
    BQSnmpAsn1 messageAsn1;
    BQSnmpTransport transport;
    eBQSnmpRet ret;
    
    if (self == BQNULL)
        return cBQSnmpErrorObjectNotExist;
    
    if ((message == BQNULL) || (destination == BQNULL) || (communityName == BQNULL))
        return BQNULL;
    
    /* Build data to send */
    messageAsn1 = BQSnmpEntity_EncodeMessage(self, message, destination, communityName);
    transport   = BQSnmpEntity_TransportGet(self);
    
    /* Send and update statistic counters */
    ret = BQSnmpTransport_Asn1Send(transport, messageAsn1, destination);
    if (ret == cBQSnmpOk)
        self->numSentMessages++;
    else
        self->numSentFailMessages++;
    
    return ret;
    }

eBQSnmpRet BQSnmpEntity_ReceiveMessage(BQSnmpEntity self,
                                       BQSnmpAsn1 asn1Object,
                                       BQSnmpTransportAddress source,
                                       BQSnmpTransportAddress destination)
    {
    BQSnmpMessage message;
    BQSnmpAsn1 decodedMessage;
    BQSnmpAuthenticationService authService;
    BQSnmpMessage responseMessage;
    eBQSnmpRet ret;
    
    if (self == BQNULL)
        return cBQSnmpErrorObjectNotExist;
    
    if (asn1Object == BQNULL)
        return cBQSnmpErrorObjectNotExist;
    
    /* Rudimentary parse of the incoming datagram */
    IncreaseNumReceivedMessages(self);
    message = Asn1Object2Message(self, asn1Object);
    if (message == BQNULL)
        {
        IncreaseNumDiscardedMessages(self);
        return cBQSnmpErrorParseAsn1ObjectFail;
        }
    
    /* Check if version mismatch */
    if (BQSnmpMessage_VersionGet(message) != BQSnmpEntity_Version(self))
        {
        IncreaseNumMismatchedVersionMessages(self);
        return cBQSnmpErrorVersionMismatch;
        }
    
    /* Decode */
    authService    = BQSnmpEntity_AuthenticationServiceGet(self);
    decodedMessage = BQSnmpAuthenticationService_Decode(authService,
                                                        BQSnmpMessage_CommunityNameGet(message),
                                                        BQSnmpMessage_UserDataGet(message),
                                                        source, destination);
    if (decodedMessage == BQNULL)
        {
        IncreaseNumDecodedFailMessages(self);
        SendTrapWhenDecodeMessageFail(self);
        return cBQSnmpErrorDecodeMessageFail;
        }
    
    /* Have message PDU from decoded ASN.1 */
    ret = DecodedAsn1ToPdu(self, decodedMessage, message);
    if (ret != cBQSnmpOk){
        IncreaseNumDecodedFailMessages(self);
        return ret;
    }
    
    /* Process message and send back response (if have) */
    responseMessage = ProcessReceiveMessage(self, message);
    if (responseMessage == BQNULL)
        return cBQSnmpOk;
    
    ret = BQSnmpEntity_SendMessage(self, responseMessage, source, BQSnmpMessage_CommunityNameGet(message));
    BQObject_Delete((BQObject)responseMessage);
    
    return ret;
    }

BQUint32 BQSnmpEntity_Version(BQSnmpEntity self)
    {
    return 1;
    }

eBQSnmpRet BQSnmpEntity_TransportSet(BQSnmpEntity self, BQSnmpTransport transport)
    {
    if ((self == BQNULL) || (transport == BQNULL))
        return cBQSnmpErrorObjectNotExist;
    self->transport = transport;
    
    return cBQSnmpOk;
    }

BQSnmpTransport BQSnmpEntity_TransportGet(BQSnmpEntity self)
    {
    return self ? self->transport : BQNULL;
    }

eBQSnmpRet BQSnmpEntity_AuthenticationServiceSet(BQSnmpEntity self, BQSnmpAuthenticationService authenticationService)
    {
    if ((self == BQNULL) || (authenticationService == BQNULL))
        return cBQSnmpErrorObjectNotExist;
    
    self->authService = authenticationService;
    return cBQSnmpOk;
    }

BQSnmpAuthenticationService BQSnmpEntity_AuthenticationServiceGet(BQSnmpEntity self)
    {
    return self ? self->authService : BQNULL;
    }

BQSnmpMibView BQSnmpEntity_MibView(BQSnmpEntity self)
    {
    return BQNULL;
    }

eBQSnmpRet BQSnmpEntity_ColdStart(BQSnmpEntity self)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQSnmpEntity_WarmStart(BQSnmpEntity self)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQSnmpEntity_MessagePduFactorySet(BQSnmpEntity self, BQSnmpMessagePduFactory factory)
    {
    return cBQSnmpErrorNotImplemented;
    }

BQSnmpMessagePduFactory BQSnmpEntity_MessagePduFactoryGet(BQSnmpEntity self)
    {
    return BQNULL;
    }

eBQSnmpRet BQSnmpEntity_SendColdStartTrap(BQSnmpEntity self)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQSnmpEntity_SendWarmStartTrap(BQSnmpEntity self)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQSnmpEntity_SendLinkDownTrap(BQSnmpEntity self)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQSnmpEntity_SendLinkUpTrap(BQSnmpEntity self)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQSnmpEntity_SendAuthenticationFailureTrap(BQSnmpEntity self)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQSnmpEntity_SendEgpNeighborLossTrap(BQSnmpEntity self)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQSnmpEntity_SendEnterpriseSpecificTrap(BQSnmpEntity self, BQList variableBindings)
    {
    return cBQSnmpErrorNotImplemented;
    }

BQUint32 BQSnmpEntity_NumSentMessages(BQSnmpEntity self)
    {
    return 0xDEADCAFE;
    }

BQUint32 BQSnmpEntity_NumSentFailMessages(BQSnmpEntity self)
    {
    return 0xDEADCAFE;
    }

BQUint32 BQSnmpEntity_NumReceivedMessages(BQSnmpEntity self)
    {
    return 0xDEADCAFE;
    }

BQUint32 BQSnmpEntity_NumReceivedDiscardedMessages(BQSnmpEntity self)
    {
    return 0xDEADCAFE;
    }

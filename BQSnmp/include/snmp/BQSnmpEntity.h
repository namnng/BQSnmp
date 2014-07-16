/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpEntity.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpEntity_h
#define BQSnmp_BQSnmpEntity_h

/*------------------------------- Includes -----------------------------------*/
#include "common/BQObject.h" /* Super class */
#include "snmp/BQSnmpEntity.h"
#include "snmp/BQSnmpMibView.h"
#include "transport/BQSnmpTransport.h"
#include "authentication/BQSnmpAuthenticationService.h"
#include "pdu/BQSnmpMessagePduFactory.h"
#include "asn1/BQSnmpAsn1.h"
#include "collection/BQList.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpEntity * BQSnmpEntity;

/*------------------------------- Prototypes ---------------------------------*/
eBQSnmpRet BQSnmpEntity_ColdStart(BQSnmpEntity self);
eBQSnmpRet BQSnmpEntity_WarmStart(BQSnmpEntity self);
BQUint32 BQSnmpEntity_Version(BQSnmpEntity self);
BQSnmpMibView BQSnmpEntity_MibView(BQSnmpEntity self);

/* Control transport layer */
eBQSnmpRet BQSnmpEntity_TransportSet(BQSnmpEntity self, BQSnmpTransport transport);
BQSnmpTransport BQSnmpEntity_TransportGet(BQSnmpEntity self);

/* Message factory */
eBQSnmpRet BQSnmpEntity_MessagePduFactorySet(BQSnmpEntity self, BQSnmpMessagePduFactory factory);
BQSnmpMessagePduFactory BQSnmpEntity_MessagePduFactoryGet(BQSnmpEntity self);

/* Authentication service */
eBQSnmpRet BQSnmpEntity_AuthenticationServiceSet(BQSnmpEntity self, BQSnmpAuthenticationService authenticationService);
BQSnmpAuthenticationService BQSnmpEntity_AuthenticationServiceGet(BQSnmpEntity self);

/* Message transmission */
BQSnmpAsn1 BQSnmpEntity_EncodeMessage(BQSnmpEntity self,
                                      BQSnmpMessage message,
                                      BQSnmpTransportAddress destination,
                                      BQString communityName);
eBQSnmpRet BQSnmpEntity_SendMessage(BQSnmpEntity self,
                                    BQSnmpMessage message,
                                    BQSnmpTransportAddress destination,
                                    BQString communityName);
eBQSnmpRet BQSnmpEntity_ReceiveMessage(BQSnmpEntity self,
                                       BQSnmpAsn1 asn1Object,
                                       BQSnmpTransportAddress source,
                                       BQSnmpTransportAddress destination);

/* Traps */
eBQSnmpRet BQSnmpEntity_SendColdStartTrap(BQSnmpEntity self);
eBQSnmpRet BQSnmpEntity_SendWarmStartTrap(BQSnmpEntity self);
eBQSnmpRet BQSnmpEntity_SendLinkDownTrap(BQSnmpEntity self);
eBQSnmpRet BQSnmpEntity_SendLinkUpTrap(BQSnmpEntity self);
eBQSnmpRet BQSnmpEntity_SendAuthenticationFailureTrap(BQSnmpEntity self);
eBQSnmpRet BQSnmpEntity_SendEgpNeighborLossTrap(BQSnmpEntity self);
eBQSnmpRet BQSnmpEntity_SendEnterpriseSpecificTrap(BQSnmpEntity self, BQList variableBindings);

/* Statistic counters */
BQUint32 BQSnmpEntity_NumSentMessages(BQSnmpEntity self);
BQUint32 BQSnmpEntity_NumSentFailMessages(BQSnmpEntity self);
BQUint32 BQSnmpEntity_NumReceivedMessages(BQSnmpEntity self);
BQUint32 BQSnmpEntity_NumReceivedDiscardedMessages(BQSnmpEntity self);

#endif

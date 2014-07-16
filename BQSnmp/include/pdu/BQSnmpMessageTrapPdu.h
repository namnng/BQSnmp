/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMessageTrapPdu.h
 *
 * Date        : 7/8/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpTrapPdu_h
#define BQSnmp_BQSnmpTrapPdu_h

/*------------------------------- Includes -----------------------------------*/
#include "pdu/BQSnmpMessagePdu.h" /* Super class */
#include "snmp/BQSnmpObjectIdentifier.h"
#include "snmp/BQSnmpNetworkAddress.h"
#include "snmp/BQSnmpTimeTicks.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpMessageTrapPdu * BQSnmpMessageTrapPdu;

typedef enum eBQSnmpMessageTrapPduGenericType
    {
    cBQSnmpMessageTrapPduGenericTypeColdStart,
    cBQSnmpMessageTrapPduGenericTypeWarmStart,
    cBQSnmpMessageTrapPduGenericTypeLinkDown,
    cBQSnmpMessageTrapPduGenericTypeLinkUp,
    cBQSnmpMessageTrapPduGenericTypeAuthenticationFailure,
    cBQSnmpMessageTrapPduGenericTypeEgpNeighborLoss,
    cBQSnmpMessageTrapPduGenericTypeEnterpriseSpecific,
    cBQSnmpMessageTrapPduGenericTypeUnknown
    }eBQSnmpMessageTrapPduGenericType;

/*------------------------------- Prototypes ---------------------------------*/
BQSnmpObjectIdentifier BQSnmpMessageTrapPdu_EnterpriseGet(BQSnmpMessageTrapPdu self);
BQSnmpNetworkAddress BQSnmpMessageTrapPdu_AgentAddress(BQSnmpMessageTrapPdu self);
eBQSnmpMessageTrapPduGenericType BQSnmpMessageTrapPdu_GenericType(BQSnmpMessageTrapPdu self);
BQUint32 BQSnmpMessageTrapPdu_SpecificType(BQSnmpMessageTrapPdu self);
BQSnmpTimeTicks BQSnmpMessageTrapPdu_TimeTicks(BQSnmpMessageTrapPdu self);

/* Util */
BQBool BQSnmpMessageTrapPduGenericTypeIsValid(eBQSnmpMessageTrapPduGenericType genericType);

#endif

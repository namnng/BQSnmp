/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMessageTrapPdu.c
 *
 * Date        : 7/8/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

/*------------------------------- Includes -----------------------------------*/
#include "pdu/BQSnmpMessageTrapPdu.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQSnmpObjectIdentifier BQSnmpMessageTrapPdu_EnterpriseGet(BQSnmpMessageTrapPdu self)
    {
    return BQNULL;
    }

BQSnmpNetworkAddress BQSnmpMessageTrapPdu_AgentAddress(BQSnmpMessageTrapPdu self)
    {
    return BQNULL;
    }

eBQSnmpMessageTrapPduGenericType BQSnmpMessageTrapPdu_GenericType(BQSnmpMessageTrapPdu self)
    {
    return cBQSnmpMessageTrapPduGenericTypeUnknown;
    }

BQUint32 BQSnmpMessageTrapPdu_SpecificType(BQSnmpMessageTrapPdu self)
    {
    return 0xDEADCAFE;
    }

BQSnmpTimeTicks BQSnmpMessageTrapPdu_TimeTicks(BQSnmpMessageTrapPdu self)
    {
    return BQNULL;
    }

BQBool BQSnmpMessageTrapPduGenericTypeIsValid(eBQSnmpMessageTrapPduGenericType genericType)
    {
    switch (genericType)
        {
        case cBQSnmpMessageTrapPduGenericTypeColdStart: return BQTrue;
        case cBQSnmpMessageTrapPduGenericTypeWarmStart: return BQTrue;
        case cBQSnmpMessageTrapPduGenericTypeLinkDown: return BQTrue;
        case cBQSnmpMessageTrapPduGenericTypeLinkUp: return BQTrue;
        case cBQSnmpMessageTrapPduGenericTypeAuthenticationFailure: return BQTrue;
        case cBQSnmpMessageTrapPduGenericTypeEgpNeighborLoss: return BQTrue;
        case cBQSnmpMessageTrapPduGenericTypeEnterpriseSpecific: return BQTrue;
        default:
            return BQFalse;
        }
    }

/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMessagePdu.c
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
#include "BQSnmpMessagePduPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
eBQSnmpMessagePduType BQSnmpMessagePdu_Type(BQSnmpMessagePdu self)
    {
    return cBQSnmpMessagePduTypeUnknown;
    }

BQUint32 BQSnmpMessagePdu_NumVariables(BQSnmpMessagePdu self)
    {
    return 0;
    }

BQSnmpVariable BQSnmpMessagePdu_VariableAtIndex(BQSnmpMessagePdu self, BQUint32 varIndex)
    {
    return BQNULL;
    }

BQUint32 BQSnmpMessagePdu_RequestId(BQSnmpMessagePdu self)
    {
    return 0xDEADCAFE;
    }

eBQSnmpMessagePduErrorStatus BQSnmpMessagePdu_ErrorStatus(BQSnmpMessagePdu self)
    {
    return cBQSnmpMessagePduErrorStatusUnknown;
    }

BQUint32 BQSnmpMessagePdu_ErrorIndex(BQSnmpMessagePdu self)
    {
    return 0xDEADCAFE;
    }

BQBool BQSnmpMessagePdu_TypeIsValid(eBQSnmpMessagePduType pduType)
    {
    switch (pduType)
        {
        case cBQSnmpMessagePduTypeGetRequest    : return BQTrue;
        case cBQSnmpMessagePduTypeGetNextRequest: return BQTrue;
        case cBQSnmpMessagePduTypeSetRequest    : return BQTrue;
        case cBQSnmpMessagePduTypeTrap          : return BQTrue;
            
        default:
            return BQFalse;
        }
    }

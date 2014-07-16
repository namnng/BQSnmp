/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMessagePdu.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpMessagePdu_h
#define BQSnmp_BQSnmpMessagePdu_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h" /* Super class */
#include "snmp/BQSnmpVariable.h"
#include "snmp/BQSnmpTimeTicks.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpMessagePdu * BQSnmpMessagePdu;

typedef enum eBQSnmpMessagePduType
    {
    cBQSnmpMessagePduTypeUnknown,
    cBQSnmpMessagePduTypeGetRequest,
    cBQSnmpMessagePduTypeGetNextRequest,
    cBQSnmpMessagePduTypeSetRequest,
    cBQSnmpMessagePduTypeTrap
    }eBQSnmpMessagePduType;

typedef enum eBQSnmpMessagePduErrorStatus
    {
    cBQSnmpMessagePduErrorStatusNoError,
    cBQSnmpMessagePduErrorStatusTooBig,
    cBQSnmpMessagePduErrorStatusNoSuchName,
    cBQSnmpMessagePduErrorStatusBadValue,
    cBQSnmpMessagePduErrorStatusReadOnly,
    cBQSnmpMessagePduErrorStatusGenError,
    cBQSnmpMessagePduErrorStatusUnknown
    }eBQSnmpMessagePduErrorStatus;

/*------------------------------- Prototypes ---------------------------------*/
/* General attributes */
eBQSnmpMessagePduType BQSnmpMessagePdu_Type(BQSnmpMessagePdu self);

/* Request ID */
BQUint32 BQSnmpMessagePdu_RequestId(BQSnmpMessagePdu self);

/* Error information */
eBQSnmpMessagePduErrorStatus BQSnmpMessagePdu_ErrorStatus(BQSnmpMessagePdu self);
BQUint32 BQSnmpMessagePdu_ErrorIndex(BQSnmpMessagePdu self);

/* Variables binding */
BQUint32 BQSnmpMessagePdu_NumVariables(BQSnmpMessagePdu self);
BQSnmpVariable BQSnmpMessagePdu_VariableAtIndex(BQSnmpMessagePdu self, BQUint32 varIndex);

/* Utils */
BQBool BQSnmpMessagePdu_TypeIsValid(eBQSnmpMessagePduType pduType);

#endif

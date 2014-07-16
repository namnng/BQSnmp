/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpEntityPrivate.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpEntityPrivate_h
#define BQSnmp_BQSnmpEntityPrivate_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmpEntity.h"
#include "BQObjectPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpEntityMethods
    {
    BQUint32 dummy;
    }tBQSnmpEntityMethods;

typedef struct tBQSnmpEntity
    {
    tBQObject super;
    const tBQSnmpEntityMethods *methods;
    
    /* Private data */
    BQSnmpTransport transport;
    BQSnmpAuthenticationService authService;
    
    /* Counters */
    BQUint32 numSentMessages;
    BQUint32 numSentFailMessages;
    BQUint32 numReceivedMessages;
    BQUint32 numDiscardedMessages;
    BQUint32 numVersionMismatchedMessages;
    BQUint32 numDecodedFailMessages;
    }tBQSnmpEntity;

/*------------------------------- Prototypes ---------------------------------*/

#endif

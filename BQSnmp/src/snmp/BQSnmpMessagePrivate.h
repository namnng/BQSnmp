/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMessagePrivate.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpMessagePrivate_h
#define BQSnmp_BQSnmpMessagePrivate_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObjectPrivate.h"
#include "BQSnmpMessage.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpMessage
    {
    tBQObject super;
    
    /* Private data */
    BQUint32 version;
    BQString communityName;
    BQSnmpMessagePdu pdu;
    BQData userData;
    }tBQSnmpMessage;

/*------------------------------- Prototypes ---------------------------------*/

#endif

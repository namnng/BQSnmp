/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMessage.c
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
#include "BQSnmpMessagePrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQSnmpMessage BQSnmpMessageNew(BQUint32 version, BQString communityName, BQSnmpMessagePdu pdu)
    {
    return BQNULL;
    }

BQUint32 BQSnmpMessage_VersionGet(BQSnmpMessage self)
    {
    return self ? self->version : 0xFFFFFFFF;
    }

BQString BQSnmpMessage_CommunityNameGet(BQSnmpMessage self)
    {
    return self ? self->communityName : BQNULL;
    }

BQSnmpMessagePdu BQSnmpMessage_PduGet(BQSnmpMessage self)
    {
    return self ? self->pdu : BQNULL;
    }

BQData BQSnmpMessage_UserDataGet(BQSnmpMessage self)
    {
    return self ? self->userData : BQNULL;
    }



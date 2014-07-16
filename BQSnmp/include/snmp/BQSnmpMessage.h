/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMessage.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpMessage_h
#define BQSnmp_BQSnmpMessage_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h" /* Super class */
#include "BQSnmpMessagePdu.h"
#include "BQSnmpAsn1.h"
#include "BQString.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpMessage * BQSnmpMessage;

/*------------------------------- Prototypes ---------------------------------*/
BQSnmpMessage BQSnmpMessageNew(BQUint32 version, BQString communityName, BQSnmpMessagePdu pdu);

BQUint32 BQSnmpMessage_VersionGet(BQSnmpMessage self);
eBQSnmpRet BQSnmpMessage_VersionSet(BQSnmpMessage self, BQUint32 version);

BQString BQSnmpMessage_CommunityNameGet(BQSnmpMessage self);
eBQSnmpRet BQSnmpMessage_CommunityNameSet(BQSnmpMessage self, BQString name);

BQSnmpMessagePdu BQSnmpMessage_PduGet(BQSnmpMessage self);
eBQSnmpRet BQSnmpMessage_PduSet(BQSnmpMessage self, BQSnmpMessagePdu pdu);

BQData BQSnmpMessage_UserDataGet(BQSnmpMessage self);
eBQSnmpRet BQSnmpMessage_UserDataSet(BQSnmpMessage self, BQData userData);

#endif

/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpTransport.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpTransport_h
#define BQSnmp_BQSnmpTransport_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmp.h"
#include "BQObject.h" /* Super class */
#include "BQSnmpTransportAddress.h"
#include "BQSnmpAsn1.h"
#include "BQSnmpTransportAddress.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpTransport * BQSnmpTransport;

/*------------------------------- Prototypes ---------------------------------*/
BQUint32 BQSnmpTransport_MaxMessageSize(BQSnmpTransport self);
BQSnmpTransportAddress BQSnmpTransport_SourceAddress(BQSnmpTransport self);
eBQSnmpRet BQSnmpTransport_Asn1Send(BQSnmpTransport self, BQSnmpAsn1 asn1Object, BQSnmpTransportAddress destination);

/*------------------------------- Sub classes --------------------------------*/
#include "BQSnmpTransportAddress.h"
#include "BQSnmpUdpTransport.h"

#endif

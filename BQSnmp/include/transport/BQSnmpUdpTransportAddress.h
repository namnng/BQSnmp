/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpUdpTransportAddress.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpUdpTransportAddress_h
#define BQSnmp_BQSnmpUdpTransportAddress_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmpTransportAddress.h" /* Super class */
#include "BQSnmpIpAddress.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpUdpTransportAddress * BQSnmpUdpTransportAddress;

/*------------------------------- Prototypes ---------------------------------*/
BQUint32 BQSnmpUdpTransportAddress_Port(BQSnmpUdpTransportAddress self);
BQSnmpIpAddress BQSnmpUdpTransportAddress_IPAddress(BQSnmpUdpTransportAddress self);

#endif

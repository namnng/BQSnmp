/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpUdpTransport.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpUdpTransport_h
#define BQSnmp_BQSnmpUdpTransport_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmpTransport.h" /* Super class */

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpUdpTransport * BQSnmpUdpTransport;

/*------------------------------- Prototypes ---------------------------------*/
BQUint32 BQSnmpUdpTransport_MessageReceivePortGet(BQSnmpUdpTransport self);
BQUint32 BQSnmpUdpTransport_TrapReceivePortGet(BQSnmpUdpTransport self);

#endif

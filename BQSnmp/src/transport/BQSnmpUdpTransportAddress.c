/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpUdpTransportAddress.c
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
#include "transport/BQSnmpUdpTransportAddress.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQUint32 BQSnmpUdpTransportAddress_Port(BQSnmpUdpTransportAddress self)
    {
    return 0xDEADCAFE;
    }

BQSnmpIpAddress BQSnmpUdpTransportAddress_IPAddress(BQSnmpUdpTransportAddress self)
    {
    return BQNULL;
    }

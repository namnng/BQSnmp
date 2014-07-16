/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpTransport.c
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
#include "BQSnmpTransport.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
eBQSnmpRet BQSnmpTransport_Asn1Send(BQSnmpTransport self, BQSnmpAsn1 asn1Object, BQSnmpTransportAddress destination)
    {
    return cBQSnmpErrorNotImplemented;
    }

BQSnmpTransportAddress BQSnmpTransport_SourceAddress(BQSnmpTransport self)
    {
    return BQNULL;
    }

BQUint32 BQSnmpTransport_MaxMessageSize(BQSnmpTransport self)
    {
    return 0x0;
    }

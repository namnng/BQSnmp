/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpAuthenticationService.c
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
#include "BQSnmpAuthenticationService.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQSnmpAsn1 BQSnmpAuthenticationService_Encode(BQSnmpAuthenticationService self,
                                              BQSnmpAsn1 asn1Object,
                                              BQSnmpTransportAddress sourceAddress,
                                              BQSnmpTransportAddress destAddress)
    {
    return BQNULL;
    }

BQSnmpAsn1 BQSnmpAuthenticationService_Decode(BQSnmpAuthenticationService self,
                                              BQString communityName,
                                              BQData data,
                                              BQSnmpTransportAddress source,
                                              BQSnmpTransportAddress destination)
    {
    return BQNULL;
    }

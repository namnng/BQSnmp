/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpAuthenticationService.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpAuthenticationService_h
#define BQSnmp_BQSnmpAuthenticationService_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h"
#include "BQSnmpAsn1.h"
#include "BQSnmpTransportAddress.h"
#include "common/BQString.h"
#include "common/BQData.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpAuthenticationService * BQSnmpAuthenticationService;

/*------------------------------- Prototypes ---------------------------------*/
/* Message encoding/decoding */
BQSnmpAsn1 BQSnmpAuthenticationService_Encode(BQSnmpAuthenticationService self,
                                              BQSnmpAsn1 asn1Object,
                                              BQSnmpTransportAddress sourceAddress,
                                              BQSnmpTransportAddress destAddress);
BQSnmpAsn1 BQSnmpAuthenticationService_Decode(BQSnmpAuthenticationService self,
                                              BQString communityName,
                                              BQData data,
                                              BQSnmpTransportAddress source,
                                              BQSnmpTransportAddress destination);

#endif

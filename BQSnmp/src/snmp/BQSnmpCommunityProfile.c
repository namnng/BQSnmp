/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpCommunityProfile.c
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
#include "BQSnmp.h"
#include "BQSnmpCommunityProfilePrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
eBQSnmpOperation BQSnmpCommunityProfile_OperationsForVariable(BQSnmpCommunityProfile self, BQSnmpVariable variable)
    {
    return cBQSnmpOperationUnknown;
    }

eBQSnmpAccessMode BQSnmpCommunityProfile_AccessModeGet(BQSnmpCommunityProfile self)
    {
    return cBQSnmpAccessModeUnknown;
    }

eBQSnmpRet BQSnmpCommunityProfile_AccessModeSet(BQSnmpCommunityProfile self, eBQSnmpAccessMode accessMode)
    {
    return cBQSnmpErrorNotImplemented;
    }

BQSnmpMibView BQSnmpCommunityProfile_MibViewGet(BQSnmpCommunityProfile self)
    {
    return BQNULL;
    }

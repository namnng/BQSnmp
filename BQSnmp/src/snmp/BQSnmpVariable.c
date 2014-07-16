/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpVariable.c
 *
 * Date        : 7/7/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmpVariable.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQSnmpObjectIdentifier BQSnmpVariable_Identifier(BQSnmpVariable self)
    {
    return BQNULL;
    }

eBQSnmpAccessMode BQSnmpVariable_AccessModeGet(BQSnmpVariable self)
    {
    return cBQSnmpAccessModeUnknown;
    }

BQSnmpObjectValue BQSnmpVariable_ValueGet(BQSnmpVariable self)
    {
    return BQNULL;
    }

eBQSnmpRet BQSnmpVariable_ValueSet(BQSnmpVariable self, BQSnmpObjectValue value)
    {
    return cBQSnmpErrorNotImplemented;
    }

BQBool BQSnmpVariable_ValueIsConsistent(BQSnmpVariable self, BQSnmpObjectValue value)
    {
    return BQFalse;
    }

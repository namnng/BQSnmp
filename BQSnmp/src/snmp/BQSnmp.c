/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmp.c
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
#include "snmp/BQSnmp.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQBool BQSnmpAccessModeIsValid(eBQSnmpAccessMode accessMode)
    {
    BQUint32 allValidModes = cBQSnmpAccessModeNone | cBQSnmpAccessModeRead | cBQSnmpAccessModeWrite;
    return accessMode & (~allValidModes);
    }

BQBool BQSnmpOperationIsValid(eBQSnmpOperation operation)
    {
    BQUint32 validOperations = cBQSnmpOperationNone | cBQSnmpOperationGet | cBQSnmpOperationSet | cBQSnmpOperationTrap;
    return operation & (~validOperations);
    }

/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMibView.c
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
#include "BQSnmpMibView.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQSnmpVariable BQSnmpMibView_SearchVariableByObjectId(BQSnmpMibView self, BQSnmpObjectIdentifier objectId)
    {
    return BQNULL;
    }

BQSnmpVariable BQSnmpMibView_SearchSuccessorVariableByObjectId(BQSnmpMibView self, BQSnmpObjectIdentifier objectId)
    {
    return BQNULL;
    }

BQIterator BQSnmpMibView_VariableIteratorCreate(BQSnmpMibView self)
    {
    return BQNULL;
    }

BQBool BQSnmpMibView_IsAggregateVariable(BQSnmpMibView self, BQSnmpVariable variable)
    {
    return BQNULL;
    }

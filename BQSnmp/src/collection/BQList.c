/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQList.c
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
#include "BQList.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQUint32 BQList_Length(BQList self)
    {
    return 0;
    }

eBQSnmpRet BQList_AddObject(BQList self, BQObject object)
    {
    return cBQSnmpErrorNotImplemented;
    }

eBQSnmpRet BQList_AddObjectAtIndex(BQList self, BQObject object, BQUint32 objectIndex)
    {
    return cBQSnmpErrorNotImplemented;
    }

BQObject BQList_RemoveObjectAtIndex(BQList self, BQUint32 objectIndex)
    {
    return BQNULL;
    }

BQObject BQList_RemoveObject(BQList self, BQObject object)
    {
    return BQNULL;
    }

BQObject BQList_GetObjectAtIndex(BQList self, BQUint32 objectIndex)
    {
    return BQNULL;
    }

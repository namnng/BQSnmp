/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQList.h
 *
 * Date        : 7/7/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQList_h
#define BQSnmp_BQList_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmp.h"
#include "BQObject.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQList * BQList;

/*------------------------------- Prototypes ---------------------------------*/
BQUint32 BQList_Length(BQList self);

eBQSnmpRet BQList_AddObject(BQList self, BQObject object);
eBQSnmpRet BQList_AddObjectAtIndex(BQList self, BQObject object, BQUint32 objectIndex);
BQObject BQList_RemoveObjectAtIndex(BQList self, BQUint32 objectIndex);
BQObject BQList_RemoveObject(BQList self, BQObject object);

BQObject BQList_GetObjectAtIndex(BQList self, BQUint32 objectIndex);

#endif

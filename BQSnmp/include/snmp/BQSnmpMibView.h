/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMibView.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpMibView_h
#define BQSnmp_BQSnmpMibView_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h" /* Super class */
#include "BQIterator.h"
#include "BQSnmpVariable.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpMibView * BQSnmpMibView;

/*------------------------------- Prototypes ---------------------------------*/
BQIterator BQSnmpMibView_VariableIteratorCreate(BQSnmpMibView self);
BQSnmpVariable BQSnmpMibView_SearchVariableByObjectId(BQSnmpMibView self, BQSnmpObjectIdentifier objectId);
BQSnmpVariable BQSnmpMibView_SearchSuccessorVariableByObjectId(BQSnmpMibView self, BQSnmpObjectIdentifier objectId);
BQBool BQSnmpMibView_IsAggregateVariable(BQSnmpMibView self, BQSnmpVariable variable);

#endif

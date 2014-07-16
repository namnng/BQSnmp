/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpVariable.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpVariable_h
#define BQSnmp_BQSnmpVariable_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmp.h"
#include "common/BQObject.h" /* Super class */
#include "snmp/BQSnmpObjectIdentifier.h"
#include "snmp/BQSnmpObjectValue.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpVariable * BQSnmpVariable;

/*------------------------------- Prototypes ---------------------------------*/
eBQSnmpAccessMode BQSnmpVariable_AccessModeGet(BQSnmpVariable self);
BQSnmpObjectIdentifier BQSnmpVariable_Identifier(BQSnmpVariable self);

BQSnmpObjectValue BQSnmpVariable_ValueGet(BQSnmpVariable self);
eBQSnmpRet BQSnmpVariable_ValueSet(BQSnmpVariable self, BQSnmpObjectValue value);
BQBool BQSnmpVariable_ValueIsConsistent(BQSnmpVariable self, BQSnmpObjectValue value);

#endif

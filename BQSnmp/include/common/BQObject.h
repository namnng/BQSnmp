/*
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 * File        : BQObject.h
 * Date        : 7/4/14
 * Author      : Nam Nguyen Ngoc
 * Description : TODO
 */

#ifndef BQSnmp_BQObject_h
#define BQSnmp_BQObject_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmpTypes.h"
#include "BQMemoryManager.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/
#define mMethodsGet(self)          self->methods
#define mMethodsSet(self, _methods) self->methods = &_methods
#define mMethodSet(methods, method) methods.method = method
#define mMethodOverride(methods, method) mMethodSet(methods, method)

/*------------------------------- Typedefs------------------------------------*/
/** @brief SNMP root object class */
typedef struct tBQObject * BQObject;


/*------------------------------- Prototypes ---------------------------------*/
void BQObject_Delete(BQObject self);

#endif

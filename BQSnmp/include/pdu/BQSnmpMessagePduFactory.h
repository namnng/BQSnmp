/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpMessagePduFactory.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpMessagePduFactory_h
#define BQSnmp_BQSnmpMessagePduFactory_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h" /* Super class */
#include "BQSnmpMessage.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpMessageFactory * BQSnmpMessagePduFactory;

/*------------------------------- Prototypes ---------------------------------*/
BQSnmpMessagePdu BQSnmpMessageFactory_GetRequestPduCreate(BQSnmpMessagePduFactory self);
BQSnmpMessagePdu BQSnmpMessageFactory_GetNextRequestPduCreate(BQSnmpMessagePduFactory self);
BQSnmpMessagePdu BQSnmpMessageFactory_GetResponsePduCreate(BQSnmpMessagePduFactory self);
BQSnmpMessagePdu BQSnmpMessageFactory_SetRequestPduCreate(BQSnmpMessagePduFactory self);
BQSnmpMessagePdu BQSnmpMessageFactory_TrapPduCreate(BQSnmpMessagePduFactory self);

#endif

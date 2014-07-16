/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQData.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQData_h
#define BQSnmp_BQData_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h" /* Super class */

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQData * BQData;

/*------------------------------- Prototypes ---------------------------------*/
BQUint8 *BQData_Buffer(BQData self);
BQUint32 BQData_Size(BQData self);

#endif

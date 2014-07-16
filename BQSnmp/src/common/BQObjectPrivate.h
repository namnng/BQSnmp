/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQObjectPrivate.h
 *
 * Date        : 7/4/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQObjectPrivate_h
#define BQSnmp_BQObjectPrivate_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmp.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/
typedef struct tBQObjectMethods
    {
    void (*Delete)(BQObject self);
    }tBQObjectMethods;

typedef struct tBQObject
    {
    const tBQObjectMethods *methods;
    
    /* Private data */
    }tBQObject;

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
BQObject BQObject_ObjectInit(BQObject self);

#endif

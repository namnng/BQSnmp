/*
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 * File        : BQObject.c
 * Date        : 7/4/14
 * Author      : Nam Nguyen Ngoc
 * Description : TODO
 */

/*------------------------------- Includes -----------------------------------*/
#include "BQMemoryManager.h"
#include "BQObjectPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;
static tBQObjectMethods m_methods;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static void Delete(BQObject self)
    {
    BQMemFree(self);
    }

static void MethodsInit(BQObject self)
    {
    if (!m_methodsInit)
        {
        BQMemInit(&m_methods, 0, sizeof(m_methods));
        
        mMethodSet(m_methods, Delete);
        }
    
    mMethodsSet(self, m_methods);
    }

static BQUint32 ObjectSize()
    {
    return sizeof(tBQObject);
    }

BQObject BQObject_ObjectInit(BQObject self)
    {
    BQMemInit(self, 0, ObjectSize());
    
    /* Setup class */
    MethodsInit(self);
    m_methodsInit = 1;
    
    return self;
    }

void BQObject_Delete(BQObject self)
    {
    if (self)
        mMethodsGet(self)->Delete(self);
    }

/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1EncoderManager.c
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

/*------------------------------- Includes -----------------------------------*/
#include "BQAsn1EncoderManagerPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/
#define mThis(self) ((BQAsn1EncoderManager)self)

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;
static tBQAsn1EncoderManagerMethods m_methods;

/* Override */
static tBQObjectMethods m_BQObjectOverride;

/* Save super implementation */
static const tBQObjectMethods *m_BQObjectMethods = BQNULL;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static BQAsn1BoolEncoder CreateBoolEncoder(BQAsn1EncoderManager self)
    {
    /* Sub class should know */
    return BQNULL;
    }

static BQAsn1IntegerEncoder CreateIntegerEncoder(BQAsn1EncoderManager self)
    {
    /* Sub class should know */
    return BQNULL;
    }

static BQAsn1BoolEncoder BoolEncoder(BQAsn1EncoderManager self)
    {
    if (self->boolEncoder == BQNULL)
        self->boolEncoder = mMethodsGet(self)->CreateBoolEncoder(self);
    return self->boolEncoder;
    }

static BQAsn1IntegerEncoder IntegerEncoder(BQAsn1EncoderManager self)
    {
    if (self->integerEncoder == BQNULL)
        self->integerEncoder = mMethodsGet(self)->CreateIntegerEncoder(self);
    return self->integerEncoder;
    }

static void Delete(BQObject self)
    {
    BQObject_Delete((BQObject)mThis(self)->boolEncoder);
    BQObject_Delete((BQObject)mThis(self)->integerEncoder);
    
    m_BQObjectMethods->Delete(self);
    }

static void OverrideBQObject(BQAsn1EncoderManager self)
    {
    BQObject object = (BQObject)self;
    
    if (!m_methodsInit)
        {
        m_BQObjectMethods = mMethodsGet(object);
        BQMemCopy(&m_BQObjectOverride, (void *)m_BQObjectMethods, sizeof(m_BQObjectOverride));
        
        mMethodOverride(m_BQObjectOverride, Delete);
        }
    
    mMethodsSet(object, m_BQObjectOverride);
    }

static void Override(BQAsn1EncoderManager self)
    {
    OverrideBQObject(self);
    }

static void MethodsInit(BQAsn1EncoderManager self)
    {
    if (!m_methodsInit)
        {
        BQMemInit(&m_methods, 0, sizeof(m_methods));
        
        mMethodSet(m_methods, BoolEncoder);
        mMethodSet(m_methods, IntegerEncoder);
        
        mMethodSet(m_methods, CreateBoolEncoder);
        mMethodSet(m_methods, CreateIntegerEncoder);
        }
    
    mMethodsSet(self, m_methods);
    }

static BQUint32 ObjectSize(void)
    {
    return sizeof(tBQAsn1EncoderManager);
    }

BQAsn1EncoderManager BQAsn1EncoderManager_ObjectInit(BQAsn1EncoderManager self)
    {
    BQMemInit(self, 0, ObjectSize());
    
    /* Super constructor */
    if (BQObject_ObjectInit((BQObject)self) == BQNULL)
        return BQNULL;
    
    /* Setup class */
    Override(self);
    MethodsInit(self);
    m_methodsInit = 1;
    
    return self;
    }

BQAsn1BoolEncoder BQAsn1EncoderManager_BoolEncoder(BQAsn1EncoderManager self)
    {
    if (self)
        return mMethodsGet(self)->BoolEncoder(self);
    return BQNULL;
    }

BQAsn1IntegerEncoder BQAsn1EncoderManager_IntegerEncoder(BQAsn1EncoderManager self)
    {
    if (self)
        return mMethodsGet(self)->IntegerEncoder(self);
    return BQNULL;
    }

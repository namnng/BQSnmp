/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1BerEncoderManager.c
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
#include "BQAsnBer.h"
#include "../BQAsn1EncoderManagerPrivate.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/
typedef struct tBQAsn1BerEncoderManager
    {
    tBQAsn1EncoderManager super;
    }tBQAsn1BerEncoderManager;

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;

/* Overrdie */
static tBQAsn1EncoderManagerMethods m_BQAsn1EncoderManagerOverride;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static BQAsn1BoolEncoder CreateBoolEncoder(BQAsn1EncoderManager self)
    {
    return BQAsn1BoolBerEncoder_New(BQNULL, 0);
    }

static BQAsn1IntegerEncoder CreateIntegerEncoder(BQAsn1EncoderManager self)
    {
    return BQAsn1IntegerBerEncoder_New(BQNULL, 0);
    }

static void OverrideBQAsn1EncoderManager(BQAsn1EncoderManager self)
    {
    if (!m_methodsInit)
        {
        BQMemCopy(&m_BQAsn1EncoderManagerOverride, (void *)mMethodsGet(self), sizeof(m_BQAsn1EncoderManagerOverride));
        
        mMethodOverride(m_BQAsn1EncoderManagerOverride, CreateBoolEncoder);
        mMethodOverride(m_BQAsn1EncoderManagerOverride, CreateIntegerEncoder);
        }
    
    mMethodsSet(self, m_BQAsn1EncoderManagerOverride);
    }

static void Override(BQAsn1EncoderManager self)
    {
    OverrideBQAsn1EncoderManager(self);
    }

static BQUint32 ObjectSize(void)
    {
    return sizeof(tBQAsn1BerEncoderManager);
    }

BQAsn1EncoderManager BQAsn1BerEncoderManager_ObjectInit(BQAsn1EncoderManager self)
    {
    BQMemInit(self, 0, ObjectSize());
    
    /* Super constructor */
    if (BQAsn1EncoderManager_ObjectInit(self) == BQNULL)
        return BQNULL;
    
    /* Setup class */
    Override(self);
    m_methodsInit = 1;
    
    return self;
    }

BQAsn1EncoderManager BQAsn1BerEncoderManager_New(void)
    {
    return BQAsn1BerEncoderManager_ObjectInit(BQMemAlloc(ObjectSize()));
    }


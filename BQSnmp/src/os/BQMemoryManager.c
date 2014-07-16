/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQMemoryManager.c
 *
 * Date        : 7/4/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h"
#include "BQMemoryManager.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Local typedefs------------------------------*/

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;
static tBQMemoryManagerMethods m_methods;

static BQMemoryManager m_sharedManager = BQNULL;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static void *MemAlloc(BQMemoryManager self, BQUint32 size)
    {
    return BQNULL;
    }

static void MemFree(BQMemoryManager self, void *memory)
    {
    }

static void MemInit(BQMemoryManager self, void *memory, BQUint32 value, BQUint32 size)
    {
    }

static void MemCopy(BQMemoryManager self, void *dest, void *source, BQUint32 size)
    {
    }

static BQBool MemLeak(BQMemoryManager self)
    {
    return BQFalse;
    }

static void MethodsInit(BQMemoryManager self)
    {
    if (!m_methodsInit)
        {
        mMethodSet(m_methods, MemAlloc);
        mMethodSet(m_methods, MemFree);
        mMethodSet(m_methods, MemInit);
        mMethodSet(m_methods, MemCopy);
        mMethodSet(m_methods, MemLeak);
        }
    
    mMethodsSet(self, m_methods);
    }

BQMemoryManager BQMemoryManager_ObjectInit(BQMemoryManager self)
    {
    if (self == BQNULL)
        return BQNULL;
        
    MethodsInit(self);
    m_methodsInit = 1;
    
    return self;
    }

void *BQMemoryManager_MemAlloc(BQMemoryManager self, BQUint32 size)
    {
    if (self)
        return mMethodsGet(self)->MemAlloc(self, size);
    return BQNULL;
    }

void BQMemoryManager_MemFree(BQMemoryManager self, void *memory)
    {
    if (self)
        mMethodsGet(self)->MemFree(self, memory);
    }

void BQMemoryManager_MemInit(BQMemoryManager self, void *memory, BQUint32 value, BQUint32 size)
    {
    if (self)
        mMethodsGet(self)->MemInit(self, memory, value, size);
    }

void BQMemoryManager_MemCopy(BQMemoryManager self, void *dest, void *source, BQUint32 size)
    {
    if (self)
        mMethodsGet(self)->MemCopy(self, dest, source, size);
    }

BQBool BQMemoryManager_MemLeak(BQMemoryManager self)
    {
    if (self)
        return mMethodsGet(self)->MemLeak(self);
    return BQFalse;
    }

BQMemoryManager BQMemoryManager_SharedManager()
    {
    if (m_sharedManager)
        return m_sharedManager;
    return BQMemoryManager_DefaultManager();
    }

void BQMemoryManager_SharedManagerSet(BQMemoryManager sharedManager)
    {
    m_sharedManager = sharedManager;
    }

void *BQMemAlloc(BQUint32 size)
    {
    return BQMemoryManager_MemAlloc(BQMemoryManager_SharedManager(), size);
    }

void BQMemFree(void *memory)
    {
    BQMemoryManager_MemFree(BQMemoryManager_SharedManager(), memory);
    }

void BQMemInit(void *memory, BQUint32 value, BQUint32 size)
    {
    BQMemoryManager_MemInit(BQMemoryManager_SharedManager(), memory, value, size);
    }

void BQMemCopy(void *dest, void *source, BQUint32 size)
    {
    BQMemoryManager_MemCopy(BQMemoryManager_SharedManager(), dest, source, size);
    }

BQBool BQMemLeak(void)
    {
    return BQMemoryManager_MemLeak(BQMemoryManager_SharedManager());
    }

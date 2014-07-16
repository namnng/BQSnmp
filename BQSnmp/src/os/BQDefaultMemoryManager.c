/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQDefaultMemoryManager.c
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
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "BQObject.h"
#include "BQMemoryManager.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/
#define mThis(self) ((tBQDefaultMemoryManager *)self)

/*------------------------------- Local typedefs------------------------------*/
typedef struct tBQDefaultMemoryManager
    {
    tBQMemoryManager super;
    
    /* Private data */
    BQUint32 allocCount;
    BQUint32 freeCount;
    }tBQDefaultMemoryManager;

/*------------------------------- Global variables ---------------------------*/

/*------------------------------- Local variables ----------------------------*/
static BQUint8 m_methodsInit = 0;

/* Override */
static tBQMemoryManagerMethods m_BQMemoryManagerOverride;

/*------------------------------- Forward declarations -----------------------*/

/*------------------------------- Implementations ----------------------------*/
static void *MemAlloc(BQMemoryManager self, BQUint32 size)
    {
    assert(size > 0);
    mThis(self)->allocCount = mThis(self)->allocCount + 1;
    return malloc(size);
    }

static void MemFree(BQMemoryManager self, void *memory)
    {
    if (memory)
        {
        free(memory);
        mThis(self)->freeCount = mThis(self)->freeCount + 1;
        }
    }

static void MemInit(BQMemoryManager self, void *memory, BQUint32 value, BQUint32 size)
    {
    assert(size);
    memset(memory, value, size);
    }

static void MemCopy(BQMemoryManager self, void *dest, void *source, BQUint32 size)
    {
    assert(size);
    assert(dest);
    assert(source);
    memcpy(dest, source, size);
    }

static BQBool MemLeak(BQMemoryManager self)
    {
    return mThis(self)->allocCount != mThis(self)->freeCount;
    }

static void OverrideBQMemoryManager(BQMemoryManager self)
    {
    if (!m_methodsInit)
        {
        MemCopy(BQNULL, &m_BQMemoryManagerOverride, (void *)mMethodsGet(self), sizeof(m_BQMemoryManagerOverride));
        
        mMethodSet(m_BQMemoryManagerOverride, MemAlloc);
        mMethodSet(m_BQMemoryManagerOverride, MemFree);
        mMethodSet(m_BQMemoryManagerOverride, MemInit);
        mMethodSet(m_BQMemoryManagerOverride, MemCopy);
        mMethodSet(m_BQMemoryManagerOverride, MemLeak);
        }
    
    mMethodsSet(self, m_BQMemoryManagerOverride);
    }

static void Override(BQMemoryManager self)
    {
    OverrideBQMemoryManager(self);
    }

BQMemoryManager BQDefaultMemoryManagerObjectInit(BQMemoryManager self)
    {
    /* Super constructor */
    if (BQMemoryManager_ObjectInit(self) == BQNULL)
        return BQNULL;
    
    /* Setup class */
    Override(self);
    m_methodsInit = 1;
    
    return self;
    }

BQMemoryManager BQMemoryManager_DefaultManager()
    {
    static tBQDefaultMemoryManager m_manager;
    static BQMemoryManager manager = BQNULL;
    
    if (manager)
        return manager;
    
    manager = (BQMemoryManager)&m_manager;
    return (BQMemoryManager)BQDefaultMemoryManagerObjectInit(manager);
    }

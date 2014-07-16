/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQMemoryManager.h
 *
 * Date        : 7/4/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQMemoryManager_h
#define BQSnmp_BQMemoryManager_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmpTypes.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQMemoryManager * BQMemoryManager;

typedef struct tBQMemoryManagerMethods
    {
    void *(*MemAlloc)(BQMemoryManager self, BQUint32 size);
    void (*MemFree)(BQMemoryManager self, void *memory);
    void (*MemInit)(BQMemoryManager self, void *memory, BQUint32 value, BQUint32 size);
    void (*MemCopy)(BQMemoryManager self, void *dest, void *source, BQUint32 size);
    BQBool (*MemLeak)(BQMemoryManager self);
    }tBQMemoryManagerMethods;

typedef struct tBQMemoryManager
    {
    const tBQMemoryManagerMethods *methods;
    }tBQMemoryManager;

/*------------------------------- Prototypes ---------------------------------*/
/* Constructor */
BQMemoryManager BQMemoryManager_ObjectInit(BQMemoryManager self);

/* Concrete manager */
BQMemoryManager BQMemoryManager_DefaultManager();

/* Manage the shared memory manager */
BQMemoryManager BQMemoryManager_SharedManager();
void BQMemoryManager_SharedManagerSet(BQMemoryManager sharedManager);

/* Memory manager methods */
void *BQMemoryManager_MemAlloc(BQMemoryManager self, BQUint32 size);
void BQMemoryManager_MemFree(BQMemoryManager self, void *memory);
void BQMemoryManager_MemInit(BQMemoryManager self, void *memory, BQUint32 value, BQUint32 size);
void BQMemoryManager_MemCopy(BQMemoryManager self, void *dest, void *source, BQUint32 size);
BQBool BQMemoryManager_MemLeak(BQMemoryManager self);

/* Simple memory management methods */
void *BQMemAlloc(BQUint32 size);
void BQMemFree(void *memory);
void BQMemInit(void *memory, BQUint32 value, BQUint32 size);
void BQMemCopy(void *dest, void *source, BQUint32 size);
BQBool BQMemLeak(void);

#endif

/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1EncoderManagerPrivate.h
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsn1EncoderManagerPrivate_h
#define BQSnmp_BQAsn1EncoderManagerPrivate_h

/*------------------------------- Includes -----------------------------------*/
#include "../common/BQObjectPrivate.h"
#include "BQAsn1EncoderManager.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQAsn1EncoderManagerMethods
    {
    BQAsn1BoolEncoder (*BoolEncoder)(BQAsn1EncoderManager self);
    BQAsn1IntegerEncoder (*IntegerEncoder)(BQAsn1EncoderManager self);
    
    /* Factory methods */
    BQAsn1BoolEncoder (*CreateBoolEncoder)(BQAsn1EncoderManager self);
    BQAsn1IntegerEncoder (*CreateIntegerEncoder)(BQAsn1EncoderManager self);
    }tBQAsn1EncoderManagerMethods;

typedef struct tBQAsn1EncoderManager
    {
    tBQObject super;
    const tBQAsn1EncoderManagerMethods *methods;
    
    /* Private data */
    BQAsn1BoolEncoder boolEncoder;
    BQAsn1IntegerEncoder integerEncoder;
    }tBQAsn1EncoderManager;

/*------------------------------- Prototypes ---------------------------------*/
BQAsn1EncoderManager BQAsn1EncoderManager_ObjectInit(BQAsn1EncoderManager self);

#endif

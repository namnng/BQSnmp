/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQIterator.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQIterator_h
#define BQSnmp_BQIterator_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h" /* Super class */

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQIterator * BQIterator;

/*------------------------------- Prototypes ---------------------------------*/
BQBool BQIteratorHasNext(BQIterator self);
BQObject BQIteratorNext(BQIterator self);

#endif

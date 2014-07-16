/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQString.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQString_h
#define BQSnmp_BQString_h

/*------------------------------- Includes -----------------------------------*/

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQString * BQString;

/*------------------------------- Prototypes ---------------------------------*/
BQString BQStringNew(char *cString);
BQUint32 BQString_Length(BQString self);
char *BQString_cString(BQString self);

#endif

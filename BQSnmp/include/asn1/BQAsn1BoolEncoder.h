/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1BoolEncoder.h
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsn1BoolEncoder_h
#define BQSnmp_BQAsn1BoolEncoder_h

/*------------------------------- Includes -----------------------------------*/
#include "BQAsn1Encoder.h" /* Super class */

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQAsn1BoolEncoder * BQAsn1BoolEncoder;

/*------------------------------- Prototypes ---------------------------------*/
eBQAsn1EncoderRet BQAsn1BoolEncoder_SetBool(BQAsn1BoolEncoder self, BQBool value);
BQBool BQAsn1BoolEncoder_GetBool(BQAsn1BoolEncoder self);

#endif

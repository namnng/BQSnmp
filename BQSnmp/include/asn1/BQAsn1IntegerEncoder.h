/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1IntegerEncoder.h
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsn1IntegerEncoder_h
#define BQSnmp_BQAsn1IntegerEncoder_h

/*------------------------------- Includes -----------------------------------*/
#include "BQAsn1Encoder.h" /* Super class */

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQAsn1IntegerEncoder * BQAsn1IntegerEncoder;

/*------------------------------- Prototypes ---------------------------------*/
eBQAsn1EncoderRet BQAsn1IntegerEncoder_SetValue(BQAsn1IntegerEncoder self, BQInt64 value);
BQInt64 BQAsn1IntegerEncoder_GetValue(BQAsn1IntegerEncoder self);

#endif

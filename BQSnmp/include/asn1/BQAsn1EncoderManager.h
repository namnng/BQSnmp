/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsn1EncoderManager.h
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsn1EncoderManager_h
#define BQSnmp_BQAsn1EncoderManager_h

/*------------------------------- Includes -----------------------------------*/
#include "asn1/BQAsn1Encoder.h"
#include "asn1/BQAsn1BoolEncoder.h"
#include "asn1/BQAsn1IntegerEncoder.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQAsn1EncoderManager * BQAsn1EncoderManager;

/*------------------------------- Prototypes ---------------------------------*/
/* Concrete managers */
BQAsn1EncoderManager BQAsn1BerEncoderManager_New(void);

/* Encoders */
BQAsn1BoolEncoder BQAsn1EncoderManager_BoolEncoder(BQAsn1EncoderManager self);
BQAsn1IntegerEncoder BQAsn1EncoderManager_IntegerEncoder(BQAsn1EncoderManager self);

#endif

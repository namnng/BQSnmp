/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQAsnBer.h
 *
 * Date        : 7/13/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQAsnBer_h
#define BQSnmp_BQAsnBer_h

/*------------------------------- Includes -----------------------------------*/
#include "asn1/BQAsn1BoolEncoder.h"
#include "asn1/BQAsn1IntegerEncoder.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/

/*------------------------------- Prototypes ---------------------------------*/
BQAsn1BoolEncoder BQAsn1BoolBerEncoder_New(BQUint8 *buffer, BQUint32 bufferSize);
BQAsn1IntegerEncoder BQAsn1IntegerBerEncoder_New(BQUint8 *buffer, BQUint32 bufferSize);

#endif

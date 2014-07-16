/*
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 * File        : BQSnmpTypes.h
 * Date        : 7/4/14
 * Author      : Nam Nguyen Ngoc
 * Description : TODO
 */

#ifndef BQSnmp_BQSnmpTypes_h
#define BQSnmp_BQSnmpTypes_h

/*------------------------------- Includes -----------------------------------*/

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
/* Integer */
typedef unsigned long long  BQUint64;
typedef unsigned int        BQUint32;
typedef unsigned short      BQUint16;
typedef unsigned char       BQUint8;
typedef long long           BQInt64;
typedef signed long int     BQInt32;
typedef signed short        BQInt16;
typedef signed char         BQInt8;

/* Boolean */
enum __BQBool__
    {
    BQFalse,
    BQTrue
    };
typedef unsigned char BQBool;

/* Object */
#define BQNULL              '\0'

#endif

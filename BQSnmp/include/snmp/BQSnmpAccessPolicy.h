/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpAccessPolicy.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmpAccessPolicy_h
#define BQSnmp_BQSnmpAccessPolicy_h

/*------------------------------- Includes -----------------------------------*/
#include "BQObject.h" /* Super class */
#include "BQSnmpCommunityProfile.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpAccessPolicy * BQSnmpAccessPolicy;

/*------------------------------- Prototypes ---------------------------------*/
BQString BQSnmpAccessPolicy_CommunityGet(BQSnmpAccessPolicy self);
BQSnmpCommunityProfile BQSnmpAccessPolicy_CommunityProfileGet(BQSnmpAccessPolicy self);

#endif

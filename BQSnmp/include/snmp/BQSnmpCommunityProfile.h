/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmpCommunityProfile.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef PrototypesBQSnmp_BQSnmpCommunityProfile_h
#define PrototypesBQSnmp_BQSnmpCommunityProfile_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmp.h"
#include "BQSnmpMibView.h"
#include "BQSnmpVariable.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
typedef struct tBQSnmpCommunityProfile * BQSnmpCommunityProfile;

/*------------------------------- Prototypes ---------------------------------*/
/* Access mode */
eBQSnmpAccessMode BQSnmpCommunityProfile_AccessModeGet(BQSnmpCommunityProfile self);
eBQSnmpRet BQSnmpCommunityProfile_AccessModeSet(BQSnmpCommunityProfile self, eBQSnmpAccessMode accessMode);

/* MIB view */
BQSnmpMibView BQSnmpCommunityProfile_MibViewGet(BQSnmpCommunityProfile self);

/* Variable access mode */
eBQSnmpOperation BQSnmpCommunityProfile_OperationsForVariable(BQSnmpCommunityProfile self, BQSnmpVariable variable);

#endif

/*-----------------------------------------------------------------------------
 *   Copyright (c) 2014 BQ, Inc. All rights reserved.
 *
 * Project     : BQSnmp
 *
 * File        : BQSnmp.h
 *
 * Date        : 7/6/14
 *
 * Author      : Nam Nguyen Ngoc
 *
 * Description : TODO
 *
 * Notes       :
 *----------------------------------------------------------------------------*/

#ifndef BQSnmp_BQSnmp_h
#define BQSnmp_BQSnmp_h

/*------------------------------- Includes -----------------------------------*/
#include "BQSnmpTypes.h"
#include "BQString.h"
#include "BQData.h"

/*------------------------------- Define--------------------------------------*/

/*------------------------------- Macros--------------------------------------*/

/*------------------------------- Typedefs------------------------------------*/
/** @brief SNMP return code */
typedef enum eBQSnmpRet
    {
    cBQSnmpOk,    /**< Success */
    cBQSnmpErrorConstructAsn1ObjectFail, /**< Cannot construct ANS.1 object */
    cBQSnmpErrorParseAsn1ObjectFail,     /**< Cannot parse ANS.1 object */
    cBQSnmpErrorVersionMismatch,         /**< Version mismatch */
    cBQSnmpErrorObjectNotExist,          /**< Object does not exist */
    cBQSnmpErrorDecodeMessageFail,       /**< Cannot decode message */
    cBQSnmpErrorNotImplemented,          /**< Function has not been implemented */
    cBQSnmpError, /**< Generic error */
    }eBQSnmpRet;

typedef enum eBQSnmpAccessMode
    {
    cBQSnmpAccessModeNone,             /**< No read nor write */
    cBQSnmpAccessModeRead  = 1 << 0,   /**< Read access */
    cBQSnmpAccessModeWrite = 1 << 1,   /**< Write access */
    cBQSnmpAccessModeUnknown = 0xFF    /**< Unknown access mode */
    }eBQSnmpAccessMode;

typedef enum eBQSnmpOperation
    {
    cBQSnmpOperationNone,           /**< No operation */
    cBQSnmpOperationGet  = 1 << 0,  /**< SET */
    cBQSnmpOperationSet  = 1 << 1,  /**< GET */
    cBQSnmpOperationTrap = 1 << 2,  /**< TRAP */
    cBQSnmpOperationUnknown = 0xFF, /**< Invalid operation */
    }eBQSnmpOperation;

/*------------------------------- Prototypes ---------------------------------*/
BQBool BQSnmpAccessModeIsValid(eBQSnmpAccessMode accessMode);
BQBool BQSnmpOperationIsValid(eBQSnmpOperation operation);

/*------------------------------- Public classes -----------------------------*/

#endif

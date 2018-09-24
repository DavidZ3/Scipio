/*****************************************************************************
    The header file for the profile wrapper
    File:   profile.h
    Author: David Zhou
*****************************************************************************/

#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "stdutils.h"


/**************************** Constants ************************************/
/***************************************************************************/

/**************************** Typedef **************************************/
typedef uint8_T Feed;
struct profile{
    Time alarm1;
    Time alarm2;
    Time alarm3;
    
    uint8_T feed1;
    uint8_T feed2;
    uint8_T feed3;
    
    uint8_T alarmStatus1;
    uint8_T alarmStatus2;
    uint8_T alarmStatus3;
}
typedef struct profile Profile;
/***************************************************************************/


/**************************** Functions ************************************/
/***************************************************************************/

#endif

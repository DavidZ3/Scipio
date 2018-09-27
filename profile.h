/*****************************************************************************
    The header file for the profile wrapper
    File:   profile.h
    Author: David Zhou
*****************************************************************************/

#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "stdutils.h"
#include "rtc.h"
#include "eeprom.h" // Used for non-dynamic memory access


/**************************** Constants ************************************/
/***************************************************************************/

/**************************** Typedef **************************************/
typedef uint8_t Feed;
struct profile{
    Time alarm1;
    Time alarm2;
    Time alarm3;
    
    uint8_t feed1;
    uint8_t feed2;
    uint8_t feed3;
    
    uint8_t alarmStatus1;
    uint8_t alarmStatus2;
    uint8_t alarmStatus3;
};
typedef struct profile Profile;

struct profiles{
    Profile profile1;
    Profile profile2;
    Profile profile3;
};
typedef struct profiles Profiles;
/***************************************************************************/


/**************************** Functions ************************************/
void Profile_RESET(void);
void Profile_LOAD(Profiles* profiles);
/***************************************************************************/

#endif

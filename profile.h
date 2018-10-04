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
#define CLOCK       0
#define ALARM_1     1
#define ALARM_2     2
#define ALARM_3     3

#define TIME_MODE   0
#define FEED_MODE   1

/***************************************************************************/

/**************************** Typedef **************************************/
typedef uint8_t Feed;
struct profile{
    Time alarm[3];
    uint8_t feed[3];
    uint8_t alarmStatus[3];
};
typedef struct profile Profile;

struct profiles{
    Profile profile[3];
};
typedef struct profiles Profiles;
/***************************************************************************/


/**************************** Functions ************************************/
void Profile_RESET(void);
void Profile_LOAD(Profiles* profiles);
/***************************************************************************/

#endif

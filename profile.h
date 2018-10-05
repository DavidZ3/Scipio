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

#define PROFILE_1   0
#define PROFILE_2   1
#define PROFILE_3   2

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
void Profile_RESET(void);               // Used to initalise profiles in memory and set all the values to zero
void Profile_STORE(Profile* profiles);  // Used to store the input profile in memory
void Profile_LOAD(Profiles* profiles);  // Used to load the profile in memory to profiles
/***************************************************************************/

#endif

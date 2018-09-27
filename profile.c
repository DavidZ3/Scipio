/******************************************************************************
    File:   profiles.c
    Author: David Zhou
    Functions used for profile related operations. 
******************************************************************************/

#include "profile.h"
#include "eeprom.h"


void Profile_RESET(void){
     
    // Declares a Profile with 0 for everything
    Profile profile;
    profile.alarm1.hour = 0x00;
    profile.alarm1.min  = 0x00;
    profile.alarm1.sec  = 0x00;
    profile.alarm2.hour = 0x00;
    profile.alarm2.min  = 0x00;
    profile.alarm2.sec  = 0x00;
    profile.alarm3.hour = 0x00;
    profile.alarm3.min  = 0x00;
    profile.alarm3.sec  = 0x00;
    profile.alarmStatus1 = 0;
    profile.alarmStatus2 = 0;
    profile.alarmStatus3 = 0;
    profile.feed1 = 0;
    profile.feed2 = 0;
    profile.feed3 = 0;
    
    // Declare a Profiles with the zero Profile all three profiles
    Profiles profiles;
    profiles.profile1 = profile;
    profiles.profile2 = profile;
    profiles.profile3 = profile;

    // Write the profile to EEPROM memory
    char eeprom_address = 0x00;
    EEPROM_WriteNBytes(eeprom_address, &profiles, sizeof(Profiles));
} 

void Profile_LOAD(Profiles* profiles){
    char eeprom_address = 0x00;
    EEPROM_ReadNBytes(eeprom_address, profiles, sizeof(Profiles));
}



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
    for(uint8_t count = 0; count < 3; count++){
        profile.alarm[count].hour = 0x00;
        profile.alarm[count].min  = 0x00;
        profile.alarm[count].sec  = 0x00;
        profile.alarmStatus[count] = 0;
        profile.feed[count] = 0;
    }
    
    // Declare a Profiles with the zero Profile all three profiles
    Profiles profiles;
    profiles.profile[0] = profile;
    profiles.profile[1] = profile;
    profiles.profile[2] = profile;

    // Write the profile to EEPROM memory
    char eeprom_address = 0x00;
    EEPROM_WriteNBytes(eeprom_address, (uint8_t*) &profiles, sizeof(profiles));
    
}

void Profile_STORE(Profiles* profiles){
    // Write the profile to EEPROM memory
    char eeprom_address = 0x00;
    EEPROM_WriteNBytes(eeprom_address, (uint8_t*) profiles, sizeof(*profiles));
}



void Profile_LOAD(Profiles* profiles){                                                                                                                               
    char eeprom_address = 0x00;
    EEPROM_ReadNBytes(eeprom_address, (uint8_t*) profiles, sizeof(*profiles));
}



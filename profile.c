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

void Profile_Test_Values(Profiles* profiles){
    profiles->profile[0].alarm[0].hour   = 11;
    profiles->profile[0].alarm[0].min    = 11;
    profiles->profile[0].alarm[1].hour   = 12;
    profiles->profile[0].alarm[1].min    = 12;
    profiles->profile[0].alarm[2].hour   = 13;
    profiles->profile[0].alarm[2].min    = 13;
    
    
    profiles->profile[1].alarm[0].hour   = 21;
    profiles->profile[1].alarm[0].min    = 21;
    profiles->profile[1].alarm[1].hour   = 22;
    profiles->profile[1].alarm[1].min    = 22;
    profiles->profile[1].alarm[2].hour   = 23;
    profiles->profile[1].alarm[2].min    = 23;

    profiles->profile[2].alarm[0].hour   = 31;
    profiles->profile[2].alarm[0].min    = 31;
    profiles->profile[2].alarm[1].hour   = 32;
    profiles->profile[2].alarm[1].min    = 32;
    profiles->profile[2].alarm[2].hour   = 33;
    profiles->profile[2].alarm[2].min    = 33;
    
    profiles->profile[0].feed[0]         = 50;
    profiles->profile[0].feed[1]         = 12;
    profiles->profile[0].feed[2]         = 13;
    
    profiles->profile[1].feed[0]         = 21;
    profiles->profile[1].feed[1]         = 22;
    profiles->profile[1].feed[2]         = 23;
    
    profiles->profile[2].feed[0]         = 31;
    profiles->profile[2].feed[1]         = 32;
    profiles->profile[2].feed[2]         = 33;
    
    profiles->profile[0].alarmStatus[0]  = 1;
    profiles->profile[0].alarmStatus[1]  = 0;
    profiles->profile[0].alarmStatus[2]  = 0;
    
    profiles->profile[1].alarmStatus[0]  = 0;
    profiles->profile[1].alarmStatus[1]  = 0;
    profiles->profile[1].alarmStatus[2]  = 0;
    
    profiles->profile[2].alarmStatus[0]  = 0;
    profiles->profile[2].alarmStatus[1]  = 0;
    profiles->profile[2].alarmStatus[2]  = 0;
     
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



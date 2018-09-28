/***************************************************************************** 
* File: Feed Dispenser Backend.c
* Created: 28/08/2018 2:59:11 PM
* Author : David Zhou
*
* This file contains the operating instructions of the 
* Scipio system.
*****************************************************************************/

#define F_CPU 1000000UL

#include <avr/io.h>
#include "button.h"
#include "profile.h"

// The  following *.h are downloaded from the ExploreEmbedded Code Libraray
#include "eeprom.h" // The Enables are in eeprom.h
#include "delay.h"
#include "rtc.h"

void port_Init()
{
    DDRD &= ~(0b111111);     // Sets PORT_D(0-5) as inputs
    PORTD |= 0b111111;       // Sets PORT_D(0-5) as pull-up resistor inputs
    
    DDRB |= 0b111;          // Sets PORT_B(0-3) as 3 inputs to a 3:8 DeMUX
    PORTB &= ~(0b111);      // Sets the outputs as off
}


void Profile_RESET(void){
     
    // Declares a Profile with 0 for everything
    Profile profile;
    profile.alarm1  = 0x00;
    profile.alarm2  = 0x00;
    profile.alarm3  = 0x00;
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

int main(void)
{
    port_Init();
    RTC_Init();
   
    // Declares profiles and profile1, profile2 and profile3
    Profiles profiles;
    Profile profile1;
    Profile profile2;
    Profile profile3;
    profiles.profile1 = profile1;
    profiles.profile2 = profile2;
    profiles.profile3 = profile3;
    
    
    Profile_RESET();    // The reset is usesd to set all profiles to the zero profile
    Profile_LOAD(&profiles);
    
    // Sets the RTC Time
    Time t;     // Typedef in rtc.h
    t.hour  = 0x00;
    t.min   = 0x00;
    t.sec   = 0x00;
    
    RTC_SetTime(t.hour, t.min, t.sec);
    
    // note: the the bits are used individually
    // bit 0:   next_profile
    // bit 1:   next_clock
    // bit 2:   set_time
    // bit 3:   up
    // bit 4:   down
    // bit 5:   set_feed
    // bit 6:   manual dispense 
    // bit 7:   none 
    uint8_t previous = 0b0;  // Stores the previous state of the buttons for positive edge triggering    
  
    Buttons button_Pressed = None;
     
    uint8_t feed_Status = 0;
    while (1) 
    {
        button_Pressed = button_Get(&previous);
        button_Action(button_Pressed);
        RTC_GetTime(&t.hour, &t.min, &t.sec);
		// Check if the current times match alarm times
		// Check if there are button inputs
        DELAY_ms(500); // Wait 0.5 seconds after each loop cycle 
   }
    return 0;
}
           
        /*
         if((PINB & 0b10) != 0){
            DELAY_ms(500);
        }else{
            DELAY_ms(250);
        }
        PORTB = PORTB ^ 0b1;
       	PORTB = 0b1;
       	DELAY_ms(500);
        
        
        for(int i = 0; i < min; i++){
            DELAY_ms(500);
        }
        
                 
   		PORTB = 0b0;
        
        DELAY_ms(100);
        
        
        for(int i = 0; i < min; i++){
   		    DELAY_ms(500);
        }
        */     


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
#include "display.h"

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

int main(void)
{
    port_Init();
   
    // Declares profiles and profile1, profile2 and profile3
    Profiles profiles;
    
    /* Probably dont need this
    Profile profile0;
    Profile profile1;
    Profile profile2;

    profiles.profile[0] = profile0;
    profiles.profile[1] = profile1;
    profiles.profile[2] = profile2;
    */
    
    Profile_RESET();    // The reset is used to set all profiles to the zero profile
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
    uint8_t profile_Number = 1;
    Profile profile_Selected = profiles.profile[profile_Number];
    uint8_t clock_Current = CLOCK;
    uint8_t mode = TIME_MODE;
    uint8_t change_Flag = 0;
    uint8_t feed_Status = 0;
    

    while (1) 
    {
        button_Pressed = button_Get(&previous);
        button_Action(button_Pressed, &profiles, &profile_Number,
                &clock_Current, &change_Flag);
        
        disp_Set(t.min, t.sec);
        
        if(t.sec == 59){
            t.sec = 0;
            t.min++;
            RTC_GetTime(&t.hour, &t.min, &t.sec);   // Gets time from RTC once a minute
            // Reads hex as dec as rtc returns time in hex e.g. 45 min is 0x45
            t.hour = (t.hour/0x10)*10 + t.hour%0x10;
            t.min  = (t.min/0x10)*10  + t.min%0x10;
            t.sec  = (t.sec/0x10)*10  + t.sec%0x10;
        }
        else{
            t.sec++;   
        }
        if(t.min == 59){
            t.min = 0;
        }
        


        if(change_Flag == 1){
            // Do stuff
            // update time
            // check for current profile and current clock
            // check for set alarms (if set start blinking)
            // check if the current mode is time or feed
            // displayOnScreen(t) or dispOnScreen(feedMode)
            
            profile_Selected = profiles.profile[profile_Number]; // selected profile
            change_Flag = 0;
        }
		// Check if the current times match active alarm times; feed if it does
		// Check if there are button inputs
        DELAY_ms(1000); // Wait 1 seconds after each loop cycle 
   }
    return 0;
}

/***************************************************************************** 
* File: Feed Dispenser Backend.c
* Created: 28/08/2018 2:59:11 PM
* Author : David Zhou
*
* This file contains the operating instructions of the 
* Scipio system.
*****************************************************************************/

#define     F_CPU       1000000UL
#define     DELAY_TIME  200     // Sets the pause period (ms)

// AVR I/O Library
#include    <avr/io.h>

// The following *.h are written by David Zhou
#include    "button.h"
#include    "profile.h"
#include    "display.h"
#include    "logic.h"
#include    "LEDs.h"

// The following *.h are downloaded from the ExploreEmbedded Code Libraray
#include    "delay.h"
#include    "rtc.h"

int main(void)
{
    // Initialises the Inputs and Outputs
    port_Init();
    
    // Sets the initial LEDs
    profile_Number_LED(PROFILE_1);
    clock_Current_LED(CLOCK);
    
    // Declares profiles and load EEPROM into &profiles
    // The reset will no longer be used later
    Profiles profiles;
    //Profile_RESET();    // The reset is used to set all profiles to the zero profile
    Profile_LOAD(&profiles);
    
    Time t;     // Typedef in rtc.h
    t.hour  = 0;
    t.min   = 0;
    t.sec   = 0;
    
    // Sets the RTC Time
    toRTC(&t);      // Read time values as HEX before storing to the RTC
    RTC_SetTime(t.hour, t.min, t.sec);
    fromRTC(&t);    // Change back to DEC as time is stored in base 10 in this program
    
    // Loads RTC Time
    //RTC_GetTime(&t.hour, &t.min, &t.sec);
    //fromRTC(&t);

    // Start with no buttons pressed before reading in button inputs
    uint8_t previous = 0;   // Stores the previous state of the buttons for positive edge triggering    
    Buttons button_Pressed = None;
    
    // Set initial profile as profile 1
    uint8_t profile_Number = PROFILE_1;
    Profile* profile_Selected = &profiles.profile[profile_Number];
    
    // Sets initial clock/alarm displayed as CLOCK  
    uint8_t clock_Current = ALARM_1;
    
    // Sets the initial mode in TIME_MODE instead of FEED_MODE
    uint8_t mode = TIME_MODE;
    
    // Used to update the EEPROM and profile_Selected
    uint8_t change_Flag = 0;
    
    // Used to track feeding for the alarm(s)
    uint8_t feed_Status = 0;
    
    // Used to provide a 1 second delay 
    uint8_t cycle = 0;  // Used to perform certain actions once a second regardless of the actual delay
                        // assuming the delay is < 1sec and is a factor of 1 sec
    
    // Used to control the colon blink
    uint8_t colon_Status = 0;
    
    // Test Code /////////////////////////////////////////////////////////////
    /*
    profiles.profile[0].alarm[0].hour   = 05;
    profiles.profile[0].alarm[0].min    = 36;
    profiles.profile[0].alarm[0].sec    = 34;
    
    profiles.profile[0].alarm[1].hour   = 11;
    profiles.profile[0].alarm[1].min    = 12;
    profiles.profile[0].alarm[1].sec    = 55;
    Profile_STORE(&profiles);
    */
    //////////////////////////////////////////////////////////////////////////
     
    
    while (1) 
    {
        button_Pressed = button_Get(&previous);
        button_Action(button_Pressed, &profiles, &profile_Number,
                &clock_Current, &change_Flag, &mode);
        
        // See if button_Action has done anything
        if(change_Flag == 1){
            // Do stuff
            // check for set alarms (if set start blinking)
            // check if the current mode is time or feed
            // displayOnScreen(t) or dispOnScreen(feedMode)
                    
            profile_Selected = &profiles.profile[profile_Number]; // selected profile
            Profile_STORE(&profiles);   // Stores profiles in EEPROM
            change_Flag = 0;
        }
        // Used to display the correct clock/feed selection
        display_Selection(clock_Current, mode, *profile_Selected, t, colon_Status);
        
        // Tracks the time using the uC internal Oscillator, but fetches the RTC time once a minute for accuracy   
        if(cycle == (1000/DELAY_TIME - 1)){
            // Toggles the colon blink status once a second
            colon_Status ^= 1;
            // Increment t.sec once a second            
            internal_Clock_Increment(&t);        
            cycle = 0;
        }else{
            cycle++;
        }

		// Check if the current times match active alarm times; feed if it does
		// Check if there are button inputs
        DELAY_ms(DELAY_TIME); // Wait DELAY_TIME milliseconds after each loop cycle 
   }
    return 0;
}

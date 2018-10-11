/***************************************************************************** 
* File: Feed Dispenser Backend.c
* Created: 28/08/2018 2:59:11 PM
* Author : David Zhou
*
* This file contains the operating instructions of the 
* Scipio system.
*****************************************************************************/

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

// Debugging Settings
#define     SET_TIMER       0
#define     SET_PROFILE     1

int main(void)
{
    // Initialises the Inputs and Outputs
    port_Init();
    
    // Initialises the RTC
    RTC_Init();
    
    
    // Sets the initial LEDs
    profile_Number_LED(PROFILE_1);
    clock_Current_LED(CLOCK);
    
    // Declares profiles and load EEPROM into &profiles
    // The reset will no longer be used later
    Profiles profiles;
    
    // If Next_Profile and Set_Alarm and Down are held down 
    // when the uC is being powered on then enter reset mode
    if(PIND == 0b10000000){
        Profile_RESET();    // The reset is used to set all profiles to the zero profile
        RTC_SetTime(0x11, 0x10, 0x45);
        
        #if SET_PROFILE
        // Test Code for profiles /////////////////////////////////////////////////
        Profile_Test_Values(&profiles);
        Profile_STORE(&profiles);
        //////////////////////////////////////////////////////////////////////////
        #endif
        
    }
    
    Profile_LOAD(&profiles);
    
    Time t;     // Typedef in rtc.h

    // Sets and initial time if SET_TIMER is true
#if SET_TIMER
    t.hour  = 0x12;
    t.min   = 0x34;
    t.sec   = 0x00;
    
    // Sets the RTC Time
    RTC_SetTime(t.hour, t.min, t.sec);
    fromRTC(&t);    // Change back to DEC as time is stored in base 10 in this program
#endif
    
    // Loads RTC Time
    RTC_GetTime(&t.hour, &t.min, &t.sec);
    fromRTC(&t);

    // Start with no buttons pressed before reading in button inputs
    Buttons button_Pressed = None;
    
    // Stores the previous state of the buttons for positive edge triggering    
    uint8_t previous = 0;   
    
    // Set initial profile as profile 1
    uint8_t profile_Number = PROFILE_1;
    Profile* profile_Selected = &profiles.profile[profile_Number];
    
    // Sets initial clock/alarm displayed as CLOCK  
    uint8_t clock_Current = CLOCK;
    
    // Sets the initial mode in TIME_MODE instead of FEED_MODE
    uint8_t mode = TIME_MODE;
    
    // Used to update the EEPROM and profile_Selected
    uint8_t change_Flag = 0;
    
    // Used to track feeding for the alarm(s)
    uint8_t feed_Status = 0;
    
    // Used to perform certain actions once a second regardless of the actual delay
    // assuming the delay is < 1sec and is a factor of 1 sec
    uint8_t cycle = 0;      

    // Used to control the colon blink
    uint8_t colon_Status = 0;
    
    // Used to control the amount of feed cycles left
    int8_t feed_Cycles = 0;
    
    // Used to increment the time by 5 after 5 presses
    uint8_t up_Count = 0;
    
    // Used to decrement the time by 5 after 5 presses
    uint8_t down_Count = 0;
    
    
    while (1) 
    {
        // Turns off the motor at the start of each loop
        if(feed_Cycles <= 0){
            feed_Cycles = 0;
            PORTB &= ~(0b1100);
            //disp_Set(99,99);
            DELAY_ms(500);
        }        
        // Gets the button pressed
        button_Pressed = button_Get(&previous);
        
        // Resets the up/down count it stops being pressed
        if(button_Pressed != Up){
            up_Count = 0;
        }
        if(button_Pressed != Down){
            down_Count = 0;
        }


        // Determines the uC action based on the button pressed
        button_Action(button_Pressed, &profiles, &profile_Number,
                &clock_Current, &change_Flag, &mode, &feed_Cycles, &t,
                &up_Count, &down_Count);
        
        
        // Updates profile
        profile_Selected = &profiles.profile[profile_Number]; // selected profile
        
        // See if button_Action has done anything
        if(change_Flag == 1){
            Profile_STORE(&profiles);   // Stores profiles in EEPROM
            change_Flag = 0;
        }
        
        // Used to display the correct clock/feed selection
        // If feed_Cycles is not zero then display that instead later on.
        if(feed_Cycles <= 0){
            display_Selection(clock_Current, mode, *profile_Selected, t, colon_Status);
        }
                
        // Selects the correct profile/clock_Number
        profile_Number_LED(profile_Number);
        clock_Current_LED(clock_Current);
        
        // Tracks the time using the uC internal Oscillator, but fetches the RTC time once a 
        // minute for accuracy   
        if(cycle == (1000/DELAY_TIME - 1)){
            // Toggles the colon blink status once a second
            colon_Status ^= 1;
            // Increment t.sec once a second            
            internal_Clock_Increment(&t, &feed_Status);        
            cycle = 0;
        }else{
            cycle++;
        }

		// Check if the current times match active alarm times; feed if it does
        if(feed_Status == 0){
            alarm_Check(*profile_Selected, t, &feed_Status, &feed_Cycles);
        }     
           
        if(feed_Cycles > 0){
            // turns on motor
            PORTB |= 0b1100;
            
            // display the cycles left
            disp_Set(00, feed_Cycles*DELAY_TIME/200);
            
            // reduce cycles
            feed_Cycles = feed_Cycles -1;
        } 
        
		// Check if there are button inputs
        DELAY_ms(DELAY_TIME/SPEED); // Wait DELAY_TIME milliseconds after each loop cycle 
   }
    return 0;
}

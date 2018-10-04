/******************************************************************************
    File:   button.c
    Author: David Zhou
    Functions used to detect the button(s) pressed and perform funtions based
	on the buttons pressed.
******************************************************************************/

#include <avr/io.h>
#include "button.h"
#include "profile.h"    // Used for loading/writing profiles


// Note: The the bits are used individually
// Bit 0:   Next_Profile
// Bit 1:   Next_Clock
// Bit 2:   Set_Alarm
// Bit 3:   Up
// Bit 4:   Down
// Bit 5:   Set_Feed
// Bit 6:   None
// Bit 7:   (Not used/don't care)
Buttons button_Get(uint8_t* previous)
{
    // Reads the buttons for positive edge triggering
    for(int port_Num = 0; port_Num < NUM_OF_INPUTS; port_Num++)
	{
        // If an button is just pressed (rising edge), then return the button pressed
        if(((PINB & (0b1 << port_Num)) != 0) && 
			((*previous & (0b1 << port_Num)) != 0))
			{
                *previous |= (0b1 << port_Num);
                return (Buttons) port_Num;
            }
	}
    return None;   // If no buttons have been pressed return NO_INPUTS
}


void button_Action(
        Buttons button_Pressed, Profiles* profiles, 
        uint8_t* profile_Number, uint8_t* clock_Current,
        uint8_t* change_Flag)
{
	// A if statement is not used to check if the button is None as
	// a jump table directly solves this without the extra comparison

    // Load the profile
    
    Profiles profiles_Stored;
    Profile_LOAD(&profiles_Stored);

	switch(button_Pressed)
	{
		case Next_Profile:
			// Do stuff
			// next_Profile();
            if(*profile_Number == 3){
                *profile_Number = 2;
            }
            else{
                (*profile_Number)++;
            }
            *change_Flag = 1;
            break;
        case Next_Clock:
			// Do stuff
			// next_Clock();
            if(*clock_Current == ALARM_3){
                *clock_Current = CLOCK;
            }else{
                (*clock_Current)++;
            }

            *change_Flag = 1;
			break;
		case Set_Alarm:
			// Do stuff
			// set_Alarm();
            if(*clock_Current != CLOCK){
                (*profiles).profile[*profile_Number].alarmStatus[*clock_Current] ^= 1;
                // XORs the alarm status with 0b1  to toggle it
            }
			break;
		case Up:
			// Do stuff
			// time_Up();
			break;
		case Down:
			// Do stuff
			// time_Down();
			break;
		case Set_Feed:
			// Do stuff
			// set_Feed();
			break;
		case None:
			// Do nothing
			return;
	}
}

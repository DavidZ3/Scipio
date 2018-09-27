/******************************************************************************
    File:   button.c
    Author: David Zhou
    Functions used to detect the button(s) pressed and perform funtions based
	on the buttons pressed.
******************************************************************************/

#include <avr/io.h>
#include "button.h"


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



void button_Action(Buttons button_Pressed)
{
	// A if statement is not used to check if the button is None as
	// a jump table directly solves this without the extra comparison
	switch(button_Pressed)
	{
		case Next_Profile:
			// Do stuff
			// next_Profile();
			break;
		case Next_Clock:
			// Do stuff
			// next_Clock();
			break;
		case Set_Alarm:
			// Do stuff
			// set_Alarm();
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

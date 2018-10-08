/******************************************************************************
    File:   button.c
    Author: David Zhou
    Functions used to detect the button(s) pressed and perform functions based
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
// Bit 6:   Manual Dispense
// Bit 7:   None

// Rewrite button_Get to factor to get level triggering on the Up/Down/Manual_Dispense buttons
Buttons button_Get(uint8_t* previous)
{
    // Reads the buttons for positive edge triggering
    for(int port_Num = 0; port_Num < NUM_OF_INPUTS; port_Num++)
	{
        // If an button is just pressed (rising edge), then return the button pressed
        if((PIND & (1 << port_Num))){
            //*previous |= (1 << port_Num);
            return (Buttons) port_Num;
        //}else if((PIND & (1 << port_Num)) == 0){
          //  *previous &= ~(1 << port_Num);      
        }                
	}
    
    // Logic for level triggering instead of rising-edge triggering
    // this is used for continuous signals such as up/down/Manual_Dispense
    if(PIND & (0b1 << Up)){
        return Up;
    }
    if(PIND & (0b1 << Down)){
        return Down;
    }
    if(PIND & (0b1 << Manual_Dispense)){
        return Manual_Dispense;
    }       
    return None;   // If no buttons have been pressed return NO_INPUTS
}

// Local functions to increase/decrease the time/feed
void time_Up(Time* t){
    // If min == 59, then reset min; else min++
    if(t->min == 59){
        t->min = 0;
        // If hour = 23, then reset hour; else hour++
        if(t->hour == 23){
            t->hour = 0;
        }else{
            t->hour++;
        }
    }else{
        t->min++;
    }
}

void time_Down(Time* t){
    // If min is zero, then set to 59; else min--
    if(t->min == 0){
        t->min = 59;
        //If hour is zero, then set to 23; else hour--
        if(t->hour == 0){
            t->hour = 23;
        }else{
            t->hour--;
        }
    }else{
        t->min--;
    }
}



void feed_Up(uint8_t* feed){
    if(*feed < 99){
        (*feed)++;
    }
}
void feed_Down(uint8_t* feed){
    if(*feed > 0){
        (*feed)--;
    }
}



// NOTE: The *change_Flag is used to indicate when the profile needs to be changed or
//       when the profile in EEPROM needs to be updated
void button_Action(
        Buttons button_Pressed, Profiles* profiles, 
        uint8_t* profile_Number, uint8_t* clock_Current,
        uint8_t* change_Flag, uint8_t* mode,
        uint8_t* feed_Cycles, Time* t)
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
            *change_Flag = 0;
            PORTB |= 1;
            break;
        case Next_Clock:
			// Do stuff
			// next_Clock();
            if(*clock_Current == CLOCK){
                *clock_Current = ALARM_1;
            }else{
                (*clock_Current)++;
            }

            *change_Flag = 0;
			break;
		case Set_Alarm:
			// Do stuff
			// set_Alarm();
            if(*clock_Current != CLOCK){
                (*profiles).profile[*profile_Number].alarmStatus[*clock_Current] ^= 1;
                // XORs the alarm status with 0b1  to toggle it
            }
            *change_Flag = 1;
			break;
		case Up:
            // Store the updated time during the falling edge to avoid excessive EEPROM writes
			// Do stuff
            if(*mode == TIME_MODE){
                if(*clock_Current == CLOCK){
                    time_Up(t);
                }else{
                    time_Up(&(profiles->profile[*profile_Number].alarm[*clock_Current]));
                }
            }else{
                    feed_Up(feed_Cycles);
            }
			break;
		case Down:
			// Do stuff
            if(*mode == TIME_MODE){
                if(*clock_Current == CLOCK){
                    time_Down(t);
                }else{
                    time_Down(&(profiles->profile[*profile_Number].alarm[*clock_Current]));
                }
            }else{
                feed_Down(feed_Cycles);
            }
			break;
		case Set_Feed:
			// Do stuff
			// set_Feed();
            if(*mode == TIME_MODE){
                *mode = FEED_MODE;   
            }else if(*mode == FEED_MODE){
                *mode = TIME_MODE;   
            }
            *change_Flag = 0;
			break;
        case Manual_Dispense:
            // Dispense while the button is held down
            (*feed_Cycles)++;
            *change_Flag = 0;
            break;
		case None:
			// Do nothing
			return;
	}
}

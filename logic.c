/******************************************************************************
    File:   logic.c
    Author: David Zhou
    Functions used to for main function operations such as selecting which 
	time/alarm/feed to display.
******************************************************************************/

#include <avr/io.h>
#include "logic.h"
#include "profile.h"    // Used for profile related datatypes
#include "display.h"	// Used to control the 7-seg LED display
#include "rtc.h"		// Used for the Time datatype and RTC functions

// Used to convert the DEC time values to HEX before storing to the RTC
void toRTC(Time* t){
    t->hour = L_DEC2HEX(t->hour);
    t->min  = L_DEC2HEX(t->min);
    t->sec  = L_DEC2HEX(t->sec);
}

// Used to convert the HEX time values to DEC when reading from the RTC
void fromRTC(Time* t){
    t->hour = L_HEX2DEC(t->hour);
    t->min  = L_HEX2DEC(t->min);
    t->sec  = L_HEX2DEC(t->sec);
}

void display_Selection(uint8_t clock_Current, uint8_t mode, Profile profile_Selected, Time t, uint8_t colon_Status){
    
    // Toggles the colon blink status once a second

    
    switch(clock_Current)
    {
        // TODO: Write a blink function for the alarms and make sure to have the other alarms as off when the profile is switched
        case ALARM_1:
            if(mode == TIME_MODE){
                disp_Set(profile_Selected.alarm[ALARM_1].hour, profile_Selected.alarm[ALARM_1].min);    // displays alarm 1
            }else{
                disp_Set(00, profile_Selected.feed[ALARM_1]);
            }
            if(profile_Selected.alarmStatus[ALARM_1]){
                // blink Alarm1 led
            }
            break;
        case ALARM_2:
            if(mode == TIME_MODE){
                disp_Set(profile_Selected.alarm[ALARM_2].hour, profile_Selected.alarm[ALARM_2].min);    // displays alarm 2
            }else{
                disp_Set(00, profile_Selected.feed[ALARM_2]);
            }
            if(profile_Selected.alarmStatus[ALARM_2]){
                // blink Alarm2 led
            }
            break;
        case ALARM_3:
            if(mode == TIME_MODE){
                disp_Set(profile_Selected.alarm[ALARM_3].hour, profile_Selected.alarm[ALARM_3].min);    // displays alarm 3
            }else{
                disp_Set(00, profile_Selected.feed[ALARM_3]);
            }
            if(profile_Selected.alarmStatus[ALARM_3]){
                // blink Alarm3 led
            }
            break;
        case CLOCK:
            disp_Set(t.hour, t.min); // displays the time
            disp_Blink(colon_Status);
            break;
    }
}

void internal_Clock_Increment(Time* t, uint8_t* feed_Status){    
    // If sec = 59, reset sec and min++; else sec++
    if(t->sec == 59){
        t->sec = 0;
        // Once a minute reset feed status
        *feed_Status = 0;
        // If min = 59, reset min and hour++; else min++
        if(t->min == 59){
            t->min = 0;           
            // If hour = 23, reset hour; else hour++
            if(t->hour == 23){
                t->hour = 0;
            }else{
                (t->hour)++;
            }
        }else{
            (t->min)++;
        }
    }
    else{
        (t->sec)++;
    }    
     
    // Gets time from RTC once a minute at the 45sec mark to ensure the time
    // is relatively accurate at each minute
    if(RTC_STATUS && t->sec == 45){
        RTC_GetTime(&t->hour, &t->min, &t->sec);
        // Reads hex as dec as the RTC returns time in hex e.g. 45 min is 0x45
        fromRTC(t);
    }
}

uint8_t time_Equal(Time t1, Time t2){
    // Checks if the hours are equal
    if(t1.hour != t2.hour){
        return 0;
    } 
    // Checks if the minutes are equal
    if(t1.min != t2.min){
        return 0;
    }
    return 1;
}

void alarm_Check(Profile profile_Selected, Time t, uint8_t* feed_Status, uint8_t* feed_Cycles){
    for(uint8_t index = ALARM_1; index < NUM_OF_ALARMS; index++){
        // Check if the current alarm is armed
        if(profile_Selected.alarmStatus[index] == ARMED){
            // If the armed alarm's time matches the current time 
            if(time_Equal(profile_Selected.alarm[index], t)){
                // If the amount to dispense is not equal to zero
                if(profile_Selected.feed[index] != 0){
                    *feed_Status = 1;   // Indicates that an alarm has been triggered this minute
                    *feed_Cycles = profile_Selected.feed[index];
                    return;
                }
            }
        }
    } 

}

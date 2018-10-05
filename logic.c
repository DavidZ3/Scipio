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


void display_Selection(uint8_t clock_Current, uint8_t mode, Profile profile_Selected, Time t){
    switch(clock_Current)
    {
        // TODO: Write a blink function for the alarms and make sure to have the other alarms as off when the profile is switched
        case CLOCK:
        disp_Set(t.min, t.sec); // displays the time
        break;
        case ALARM_1:
        if(mode == FEED_MODE){
            disp_Set(profile_Selected.alarm[ALARM_1].hour, profile_Selected.alarm[ALARM_1].min);    // displays alarm 1
            }else{
            disp_Set(00, profile_Selected.feed[ALARM_1]);
        }
        if(profile_Selected.alarmStatus[ALARM_1]){
            // blink Alarm1 led
        }
        break;
        case ALARM_2:
        if(mode == FEED_MODE){
            disp_Set(profile_Selected.alarm[ALARM_2].hour, profile_Selected.alarm[ALARM_2].min);    // displays alarm 2
            }else{
            disp_Set(00, profile_Selected[ALARM_2]);
        }
        if(profile_Selected.alarmStatus[ALARM_2]){
            // blink Alarm2 led
        }
        break;
        case ALARM_3:
        if(mode == FEED_MODE){
            disp_Set(profile_Selected.alarm[ALARM_3].hour, profile_Selected.alarm[ALARM_3].min);    // displays alarm 3
            }else{
            disp_Set(00, profile_Selected.feed[ALARM_3]);
        }
        if(profile_Selected.alarmStatus[ALARM_3]){
            // blink Alarm3 led
        }
        break;
    }
}

void internal_Clock_Increment(Time* t){    
    // If sec = 59, reset sec and min++; else sec++
    if(t->sec == 59){
        t->sec = 0;
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
     
    // Gets time from RTC once a minute at the 30sec mark
    if(t->sec == 30){
        RTC_GetTime(&t.hour, &t.min, &t.sec);  
        // Reads hex as dec as the RTC returns time in hex e.g. 45 min is 0x45
        t->hour = HEX2DEC(t->hour);
        t->min  = HEX2DEC(t->min);
        t->sec  = HEX2DEC(t->sec);
    }
}
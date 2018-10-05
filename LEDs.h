/*****************************************************************************
    The header file for the functions used to manage the profile and 
    clock/alarm LEDs.
    File:   LEDs.h
    Author: David Zhou
*****************************************************************************/

#ifndef _LEDS_H_
#define _LEDS_H_

#include "stdutils.h"


/**************************** Constants ************************************/
// PORT_B(0:1) is used to display which profile is selected
// 00 = 0 = Profile 1 LED
// 01 = 1 = Profile 2 LED
// 10 = 2 = Profile 3 LED
// 11 = 3 = NOT USED


// PORT_B(5:6) is used to display which clock/alarm is selected
// 00 = 0 = CLOCK LED
// 01 = 1 = ALARM 1 LED
// 10 = 2 = ALARM 2 LED
// 11 = 3 = ALARM 3 LED

// These are already defined in profile.h
/***************************************************************************/


/**************************** Macros ***************************************/
#define SET_BIT(BYTE, BIT_NUM)      BYTE | (1 << BIT_NUM)
#define CLEAR_BIT(BYTE, BIT_NUM)    BYTE & (~(1 << BIT_NUM))
#define FETCH_BIT(BYTE, BIT_NUM)    (BYTE & (1 << BIT_NUM)) >> BIT_NUM  // Returns 1 if the selected bit is true; otherwise return 0
/***************************************************************************/


/**************************** Functions ************************************/
void port_Init();
void profile_Number_LED(uint8_t profile_Number);
void clock_Current_LED(uint8_t clock_Current);
/***************************************************************************/

#endif

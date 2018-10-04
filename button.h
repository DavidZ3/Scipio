/*****************************************************************************
    The header file for the button related functions
    File:   button.h
    Author: David Zhou
*****************************************************************************/

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "stdutils.h"
#include "profile.h"


/**************************** Constants ************************************/
#define NUM_OF_INPUTS   6
// Allocate numbers to buttons
enum buttons{Next_Profile, Next_Clock, Set_Alarm, Up, Down, Set_Feed, None};
/***************************************************************************/

/**************************** Typedef **************************************/
typedef enum buttons Buttons;
/***************************************************************************/


/**************************** Functions ************************************/
Buttons button_Get(uint8_t* previous);
void button_Action(Buttons button_Pressed, Profiles* profiles,
        uint8_t* profile_Number, uint8_t* clock_Current,
        uint8_t* change_FLag);
/***************************************************************************/

#endif

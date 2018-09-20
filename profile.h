/*****************************************************************************
    The header file for the profile wrapper
    File:   profile.h
    Author: David Zhou
*****************************************************************************/

#ifndef _PROFILE_H_
#define _PROFILE_H_

#include "stdutils.h"


/**************************** Constants ************************************/
#define NUM_OF_INPUTS   6
// Allocate numbers to buttons
enum buttons{Next_Profile, Next_Clock, Set_Alarm, Up, Down, Set_Feed, None};
/***************************************************************************/

/**************************** Typedef **************************************/
typedef enum buttons Buttons;
/***************************************************************************/


/**************************** Functions ************************************/
uint8_t button_Get(uint8_t* previous);
void button_Action();
/***************************************************************************/

#endif

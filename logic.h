/*****************************************************************************
    The header file for the functions used in the GUI logic used in main.c
    File:   logic.h
    Author: David Zhou
*****************************************************************************/

#ifndef _LOGIC_H_
#define _LOGIC_H_

#include "stdutils.h"
#include "rtc.h"        // Used for the Time datatype
#include "eeprom.h"     // Used for non-dynamic memory access
#include "profile.h"    // Used for the profile datatypes

/**************************** Constants ************************************/

/***************************************************************************/

/**************************** Macros ***************************************/
// Reads hex as dec without converting bases
#define L_HEX2DEC(X) (((X)/0x10)*10  + (X)%0x10)

// Reads dec as hex without converting bases
#define L_DEC2HEX(X) (((X)/10)*0x10  + (X)%10)
/***************************************************************************/

/**************************** Macros ***************************************/
#define SET_BIT(BYTE, BIT_NUM)      BYTE | (1 << BIT_NUM)
#define CLEAR_BIT(BYTE, BIT_NUM)    BYTE & (~(1 << BIT_NUM))
/***************************************************************************/


/**************************** Functions ************************************/
void toRTC(Time* t);
void fromRTC(Time* t);
void display_Selection(uint8_t clock_Current, uint8_t mode, Profile profile_Selected, Time t, uint8_t colon_Status);
void internal_Clock_Increment(Time* t);
/***************************************************************************/

#endif

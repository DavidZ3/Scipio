/*****************************************************************************
    The header file for the LED display functions
    File:   display.h
    Author: David Zhou
*****************************************************************************/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "stdutils.h"

/**************************** Constants ************************************/
#define C_DisplayReadMode_U8    0xE3
#define C_DisplayWriteMode_U8   0xE2
/***************************************************************************/



/**************************** Functions ************************************/
uint8_t button_Get(int previous);

/***************************************************************************/

#endif

/*****************************************************************************
    The header file for the LED display functions
    File:   display.h
    Author: David Zhou
*****************************************************************************/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "stdutils.h"

/**************************** Constants ************************************/
#define C_DisplayReadMode_U8        0xE3
#define C_DisplayWriteMode_U8       0xE2
#define C_LedControlRegAddress_U8   0xEB

//#define M_LedClearBit(x) util_BitClear((M_LedControlBus), (x));
//#define M_LedClearSet(x) util_BitSet((M_LedControlBus), (x));
/***************************************************************************/



/**************************** Functions ************************************/
void disp_Init();
void disp_Set(uint8_t hour, uint8_t min);
void disp_View(uint8_t* hour, uint8_t* min);

/***************************************************************************/

#endif

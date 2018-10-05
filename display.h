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

// Control Bytes
#define CLEAR_DISPLAY               0x76
#define DECIMAL_CONTROL             0x77    // 0-63, 1 bit per decimal
#define CURSOR_CONTROL              0x79    // 0-3, where 0 is the left most digit 
#define BRIGHTNESS_CONTROL          0x7A    // 0-100, brightness
#define DIGIT_1_CONTROL             0x7B    // 0-127, 1 bit per segment
#define DIGIT_2_CONTROL             0x7C    // 0-127, 1 bit per segment
#define DIGIT_3_CONTROL             0x7D    // 0-127, 1 bit per segment
#define DIGIT_4_CONTROL             0x7E    // 0-127, 1 bit per segment
#define BAUD_RATE_CONFIG            0x80    // 0-11
#define I2C_ADDRESS_CONFIG          0x80    // 0-126, Sets I2C data byte address
#define FACTORY_RESET               0x81

// Decimal Control
#define COLON                       0x04

// Digit Definitions
#define DIGIT_1                     0x00
#define DIGIT_2                     0x01
#define DIGIT_3                     0x02
#define DIGIT_4                     0x03

//#define M_LedClearBit(x) util_BitClear((M_LedControlBus), (x));
//#define M_LedClearSet(x) util_BitSet((M_LedControlBus), (x));
/***************************************************************************/



/**************************** Functions ************************************/
void disp_Init();
void disp_Cursor(uint8_t position);
void disp_Cusor_Digit(uint8_t position, uint8_t digit);
void disp_Clear(void);
void disp_Set(uint8_t hour, uint8_t min);
void disp_View(uint8_t* hour, uint8_t* min);

/***************************************************************************/

#endif

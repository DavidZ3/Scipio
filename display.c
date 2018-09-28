/******************************************************************************
    File:   display.c
    Author: David Zhou
    Functions used to set the SparkFun 4 Digit Seven Segment I2C LED Display
    written using the i2c.h functions from ExploreEmbedded 
******************************************************************************/

#include "display.h"
#include "i2c.h"

void disp_Init()
{
    I2C_Init();         // Initalise the I2C module.
    I2C_Start();        // Start the I2C communications.
    
    I2C_Write(C_DisplayWriteMode_U8);
    I2C_Write(C_LedControlRegAddress_U8);	
    I2C_Write(0x00);
    I2C_Write(0x00);
    I2C_Write(0x00);
    I2C_Write(0x00);
	// Do stuff
	
	I2C_Stop();
}

void disp_Set(uint8_t hour, uint8_t min)
{
	
}

void disp_View(uint8_t* hour, uint8_t* min){
	I2C_Write(C_DisplayReadMode_U8);
}

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
    I2C_Init();         // Initalises the I2C module.
    I2C_Start();        // Start the I2C communications.
    
    I2C_Write(C_DisplayWriteMode_U8);   // Selects the I2C LED Display
    // I2C_Write(CLEAR_DISPLAY);           // Clears the display
    // I2C_Write(DECIMAL_CONTROL);
    // I2C_Write(COLON);
}

void disp_Stop()
{
    I2C_Stop();
}

void disp_Cursor(uint8_t position)
{
    // Checks if the position is invalid
    if((position < DIGIT_1) || (position > DIGIT_4)){
        return;
    }
    I2C_Write(CURSOR_CONTROL);
    I2C_Write(position);
}

void disp_Cusor_Digit(uint8_t position, uint8_t digit)
{
    disp_Cursor(position);
    I2C_Write(digit);
}

void disp_Clear(void)
{
    I2C_Write(CLEAR_DISPLAY);   // Clear display command, and resets the cursor    
}

void disp_Set_Decimal(uint8_t decimal_Byte){
    disp_Init();
    I2C_Write(DECIMAL_CONTROL);
    I2C_Write(decimal_Byte);
    disp_Stop();
}

void disp_Blink(uint8_t colon_Status){    
    disp_Init();
    
    I2C_Write(DECIMAL_CONTROL);
    if(BLINK_MODE && (colon_Status == 0)){
        I2C_Write(0);   
    }else{
        I2C_Write(COLON);   
    }        

    disp_Stop();
}

void disp_Set(uint8_t hour, uint8_t min)
{
    disp_Init();
       
	// Splits the hours/min into their corresponding digits
    uint8_t digit1 = hour/10;
    uint8_t digit2 = hour%10;
    uint8_t digit3 = min/10;
    uint8_t digit4 = min%10;
    
    // Clears display and write time
    disp_Cursor(DIGIT_1);
    I2C_Write(digit1);
    I2C_Write(digit2);
    I2C_Write(digit3);
    I2C_Write(digit4);
    
    disp_Stop();
}

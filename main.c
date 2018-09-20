/***************************************************************************** 
* File: Feed Dispenser Backend.c
* Created: 28/08/2018 2:59:11 PM
* Author : David Zhou
*
* This file contains the operating instructions of the 
* Scipio system.
*****************************************************************************/

#define F_CPU 1000000UL

#include <avr/io.h>
#include "delay.h"
#include "rtc.h"
#include "button.h"

void port_Init()
{
    DDRD &= ~(0b111111);     // Sets PORT_D(0-5) as inputs
    PORTD |= 0b111111;       // Sets PORT_D(0-5) as pull-up resistor inputs
    
    DDRB |= 0b111;          // Sets PORT_B(0-3) as 3 inputs to a 3:8 DeMUX
    PORTB &= ~(0b111);      // Sets the outputs as off
}

int main(void)
{
    port_Init();
    RTC_Init();
    
    // Sets the RTC Time
    Time t;     // Typedef in rtc.h
    t.hour  = 0x00;
    t.min   = 0x00;
    t.sec   = 0x00;   
    RTC_SetTime(t.hour, t.min, t.sec);
    
    // Note: The the bits are used individually
    // Bit 0:   Next_Profile
    // Bit 1:   Next_Clock
    // Bit 2:   Set_Alarm
    // Bit 3:   Up
    // Bit 4:   Down
    // Bit 5:   Set_Feed
    // Bit 6:   None
    // Bit 7:   (Not used/don't care)
    uint8_t previous = 0b0;  // Stores the previous state of the buttons for positive edge triggering    
  
    Buttons button_Pressed = None;
    while (1) 
    {
        button_Pressed = button_Get(&previous);
        RTC_GetTime(&t.hour, &t.min, &t.sec);
		// Check if the current times match alarm times
		// Check if there are button inputs
        if((PINB & 0b10) != 0){
            DELAY_ms(500);
        }else{
            DELAY_ms(250);
        }
        PORTB = PORTB ^ 0b1;
           
        /*
       	PORTB = 0b1;
       	DELAY_ms(500);
        
        
        for(int i = 0; i < min; i++){
            DELAY_ms(500);
        }
        
                 
   		PORTB = 0b0;
        
        DELAY_ms(100);
        
        
        for(int i = 0; i < min; i++){
   		    DELAY_ms(500);
        }
        */     
    }
    return 0;
}


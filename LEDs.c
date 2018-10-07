/******************************************************************************
    File:   LEDs.c
    Author: David Zhou
    Functions used to control the LEDs' status based on the selected profile 
    and alarm/clock
******************************************************************************/

#include <avr/io.h>     // AVR IO
#include "LEDs.h"


void port_Init()
{
    DDRD &= ~(0b1111111);   // Sets PORT_D(0-6) as inputs
    //DDRD = 0;       // sets all pins on PORTD to inputs
    
    //PORTD |= 0b1111111;     // Sets PORT_D(0-6) as pull-up resistor inputs
    
    DDRB |= 0b000011;       // Sets PORT_B(0-1) as 2 inputs to a 2:4 DeMUX to control the profile LEDs
    DDRB |= 0b001100;       // Sets PORT_B(2-3) as 2 inputs to a bi-direction motor driver IC
    DDRB |= 0b110000;       // Sets PORT_B(4-5) as 2 inputs to a 2:4 DeMUX to control the clock/alarm LEDs
    
    PORTB &= ~(0b110011);   // Sets the outputs as off
}

void profile_Number_LED(uint8_t profile_Number){
    PORTB &= ~(0b11);           // clears bit 1 and bit 0
    PORTB |= profile_Number;    // sets bit 1 and 0
}

void clock_Current_LED(uint8_t clock_Current){
    PORTB &= (~(0b11 << 4));        // clears bit 5 and bit 4
    PORTB |= (clock_Current << 4);  // sets bit 5 and bit 4
}
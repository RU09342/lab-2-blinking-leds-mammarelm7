/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430F5529 Button blink led
//Works, sometimes blinks led brighter rather than off

#include <msp430.h>

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;


    //resistor enabled
    P1REN |= BIT1;

    //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
    P1OUT = BIT1;

	//Enables port 1.0 as output, has to use = to initialize
	P1DIR = BIT0;


	//infinite while loop
	while(1)
	{
	    if((P1IN & BIT1) == BIT1){ //starts the led off, could do if(!P1IN & BIT1) to start as off
	        //Toggles P1.0 RED led
	        P1OUT ^= BIT0;
	    }


	}
}

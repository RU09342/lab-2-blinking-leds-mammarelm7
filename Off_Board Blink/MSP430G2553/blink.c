/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430G2553 Button Blink led
//sometimes pressing button makes led brighter instead of turning off

#include <msp430g2553.h>

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    //selects I/O function
    P1SEL = 0;

    //resistor enabled, input 1.3
    P1REN |= BIT3;

    //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
    P1OUT = BIT3;

	//Enables port 1.0 as output, any bits that are 0 are treated as inputs
	P1DIR =BIT0;



	while(1) //infinite while loop
	{

	    //checks to see if input p1.3 is low
	    if (!((P1IN & BIT3)==BIT3)){
	        //toggles p1.0 red led
	        P1OUT ^= BIT0;
	    }


	}
}

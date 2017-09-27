/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430G2553 Simple Blink led

#include <msp430.h>				

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	//Selects I/O function
	P1SEL = 0;
	
	//Enables port 1.0 as output
	P1DIR |= 0x01;

	//declared as volatile to indicate i can change at any time
	// volatile to prevent optimization.
	//c compiler optimization can automatically remove code that introduces intended delays
	volatile unsigned int i;

	while(1) //infinite while loop
	{
	    //P1OUT contains the value to be output
	    // Toggle P1.0 using exclusive-OR
	    // If the least significant bit is 0, the XOR with BIT0 will result in a change to 0
	    // If the least significant bit is 1, the XOR with BIT0 will result in a change to 1
		P1OUT ^= 0x01;

		//creates the delay between pulses, determines how fast it blinks
		for(i=50000; i>0; i--);
	}
}

/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430F5529 simple blink led

#include <msp430.h>				

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	
	
	//Enables port 1.0 as output
	P1DIR |= 0x01;

	//declared as volatile to indicate i can change at any time
	// volatile to prevent optimization.
	//c compiler optimization can automatically remove code that introduces intended delays
	volatile unsigned int i;

	//infinite while loop
	while(1)
	{
	    //P1OUT contains the value to be output
	    // Toggle P1.0 using exclusive-OR
	    // If the least significant bit is 0, the XOR with BIT0 will result in a change to 0
	    // If the least significant bit is 1, the XOR with BIT0 will result in a change to 1
		P1OUT ^= 0x01;
		// creates the delay based on i
		for(i=50000; i>0; i--);
	}
}

/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430F5529 multiple blink led

#include <msp430.h>				

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	
	
	//Enables port 1.0
	P1DIR |= BIT0;
	//Enables port 4.7
	P4DIR |= BIT7;

	//declared as volatile to indicate i can change at any time
	// volatile to prevent optimization.
	//c compiler optimization can automatically remove code that introduces intended delays
	volatile unsigned int i;

	//infinite while loop
	while(1)
	{
	    //Toggles P1.0 RED led
		P1OUT ^= BIT0;
		// creates the delay based on i
		for(i=50000; i>0; i--);

		//Toggles off P1.0 RED led makes asynchronous
		P1OUT ^= BIT0;
		//Toggles on P4.7 Green led
		P4OUT ^= BIT7;

		//delay
		for(i=10000; i>0; i--);

	}
}

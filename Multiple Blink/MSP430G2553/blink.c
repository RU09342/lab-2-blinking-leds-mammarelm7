/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430G2553 Multiple Blink led

#include <msp430.h>				

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	//Enables port 1.0 and port 1.6 as output
	P1DIR |= (BIT0|BIT6);


	//declared as volatile to indicate i can change at any time
	// volatile to prevent optimization.
	//c compiler optimization can automatically remove code that introduces intended delays
	volatile unsigned int i;

	while(1) //infinite while loop
	{
	    //Toggle P1.0 Red led
	    //Exclusive or toggles
	    P1OUT ^= BIT0;
	    //delay for red led
	    for(i=50000; i>0; i--);

	    //Toggle P1.6 Green Led
	    //Exclusive or with BIT0 and BIT6 will turn off the red led if on and turn on the green led, makes asynchronous
	    P1OUT ^= (BIT0|BIT6);
		//delay for green led
		for(i=10000; i>0; i--);

	}
}

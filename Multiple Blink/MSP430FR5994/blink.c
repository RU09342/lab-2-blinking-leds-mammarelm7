/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR5994 Multiple Blink Led

#include <msp430.h>

void main(void) {

    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    //PM5CTL0 = Power mode 5 control register 0
    //LOCKLPM5 = Locks I/O pin, bit is reset by a power cycle
    //~LOCKLPM5=8'b0 and by anding PM5CTL0 it clears the register
    PM5CTL0 &= ~LOCKLPM5;

	//Selects I/O function
	P1SEL = 0;
	
    //Enables port 1.0 and port 1.1 as output
    P1DIR |= (BIT0|BIT1);

    for(;;)//creates an infinite loop so blinks indefinitely
    {
        //declared as volatile to indicate i can change at any time
        // volatile to prevent optimization.
        //c compiler optimization can automatically remove code that introduces intended delays
        volatile unsigned int i;
        volatile unsigned int j;

        //Toggle P1.0 Red led
        //Exclusive or toggles
        P1OUT ^= BIT0;

        //red led delay
        i = 50000;
        do i--;
        while(i != 0);

        //Toggle P1.0 and P1.1, will turn off red led if on, turn on green led
        P1OUT ^= (BIT0|BIT1);

        //green led delay
        j = 10000;
        do j--;
        while(j!=0);
    }
}

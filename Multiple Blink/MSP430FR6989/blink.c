/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR6989 Multiple Blink LED

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
	P9SEL = 0;
	
    //Enables port 1.0 as output
    P1DIR |= BIT0;

    //Enables port 9.7 as output
    P9DIR |= BIT7;


    for(;;)//creates an infinite loop so blinks indefinitely
    {
        //declared as volatile to indicate i can change at any time
        // volatile to prevent optimization.
        //c compiler optimization can automatically remove code that introduces intended delays
        volatile unsigned int i;

        //Toggles P1.0 RED LED
        P1OUT ^= BIT0;

        //creates the delay between pulses, determines how fast it blinks
        i = 50000;
        //will decrement i unless i = 0
        do i--;
        while(i != 0);

        //Toggles P1.0 RED LED, turns it off if on, makes asynchronous with green
        P1OUT ^= BIT0;

        //Toggles P9.7 Green LED
        P9OUT ^= BIT7;

        //creates the delay between pulses, determines how fast it blinks
        i = 10000;
        //will decrement i unless i = 0
        do i--;
        while(i != 0);

    }
}

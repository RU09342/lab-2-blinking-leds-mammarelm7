/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR6989 Simple Blink LED

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

	
	
    //Enables port 1.0 as output
    P1DIR |= 0x01;

    for(;;)//creates an infinite loop so blinks indefinitely
    {
        //declared as volatile to indicate i can change at any time
        // volatile to prevent optimization.
        //c compiler optimization can automatically remove code that introduces intended delays
        volatile unsigned int i;

        //P1OUT contains the value to be output
        // Toggle P1.0 using exclusive-OR
        // If the least significant bit is 0, the XOR with BIT0 will result in a change to 0
        // If the least significant bit is 1, the XOR with BIT0 will result in a change to 1
        P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR

        //creates the delay between pulses, determines how fast it blinks
        i = 50000;
        //will decrement i unless i = 0
        do i--;
        while(i != 0);
    }
}

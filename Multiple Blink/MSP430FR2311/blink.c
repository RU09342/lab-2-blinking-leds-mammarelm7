/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR2311 Multiple Blink led

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
    P1DIR |= BIT0;
    //Enables Port 2.0 as output
    P2DIR |= BIT0;

    for(;;) //creates an infinite loop so blinks indefinitely
    {
        //declared as volatile to indicate i can change at any time
        // volatile to prevent optimization.
        //c compiler optimization can automatically remove code that introduces intended delays
        volatile unsigned int i;

        //Toggles P1.0 RED led
        P1OUT ^= BIT0;

        //red led delay
        i = 50000;
        //will decrement i unless i = 0
        do i--;
        while(i != 0);

        //Toggles P1.0 RED led, turns off if on, makes asynchronous
        P1OUT ^= BIT0;
        //Toggles P2.0 Green led
        P2OUT ^= BIT0;

        //red led delay
        i = 10000;
        //will decrement i unless i = 0
        do i--;
        while(i != 0);
    }
}

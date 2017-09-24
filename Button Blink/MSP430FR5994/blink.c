/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR5994 Button Blink Led
//sometimes pushing button increases intensity of already on led instead of toggling it

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

    //resistor enabled input P5.6
    P5REN |= BIT6;

    //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
    P1OUT = BIT6;

    //Enables port 1.0 as output
    P1DIR = BIT0;



    for(;;)//creates an infinite loop so blinks indefinitely
    {
        //checks button input
        if(!(P5IN & BIT6)){ //starts led off
            //Toggle P1.0 Red led
            P1OUT ^= BIT0;
        }

    }
}

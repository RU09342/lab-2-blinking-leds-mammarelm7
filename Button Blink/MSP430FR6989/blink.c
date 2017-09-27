/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR6989 Button Blink LED
//Works sometimes makes led brighter instead of off
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


	
   //resistor enabled
    P1REN |= BIT1;

    //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
    P1OUT = BIT1;

    //Enables port 1.0 as output, has to use = to initialize
    P1DIR = BIT0;



    for(;;)//creates an infinite loop that checks for input
    {
		//checks to see if input 1.1 is low
        if(!((P1IN & BIT1)==BIT1)){

            //Toggles P1.0 RED LED
              P1OUT ^= BIT0;
        }

    }


}

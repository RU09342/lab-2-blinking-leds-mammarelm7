# Lab 2: Button Blink
The code for each of the boards were pretty similar, the main differences where the pinouts for the input buttons used. The code just checks for the button input and then toggles the onboard P1.0 led

## MSP430F5529 
Button: P1.1

```c
/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430F5529 Button blink led
//Works, sometimes blinks led brighter rather than off

#include <msp430.h>

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
	WDTCTL = WDTPW | WDTHOLD;

	
	
    //resistor enabled
    P1REN |= BIT1;

    //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
    P1OUT = BIT1;

	//Enables port 1.0 as output, has to use = to initialize
	P1DIR = BIT0;


	//infinite while loop
	while(1)
	{
		//checks to see if input p1.1 is low
	    if(!((P1IN & BIT1) == BIT1)){ 
	        //Toggles P1.0 RED led
	        P1OUT ^= BIT0;
	    }


	}
}
```

## MSP430FR2311 
Button: P1.1

```c
/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430FR2311 Button Blink led
//sometimes pressing button makes led brighter instead of turning off

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

    //Enables port 1.0 as output
    P1DIR = BIT0;





    for(;;) //creates an infinite loop so blinks indefinitely
    {
        //checks to see if p1.1 is low
        if (!((P1IN & BIT1) == BIT1)){
           //toggles p1.0 red led
           P1OUT ^= BIT0;
        }



    }
}

```

## MSP430FR5994 
Button: P5.6

```c
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
        if(!((P5IN & BIT6)==BIT6)){ //starts led off
            //Toggle P1.0 Red led
            P1OUT ^= BIT0;
        }

    }
}
```

## MSP430FR6989 
Button: P1.1

```c
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
```

## MSP430G2553 
Button: P1.3 

```c
/*
Matt Mammarelli
9/18/17
ECE 09342-2
*/

//MSP430G2553 Button Blink led
//sometimes pressing button makes led brighter instead of turning off

#include <msp430g2553.h>

void main(void)
{
    //WDTCTL is watchdog timer control
    //WDTPW watchdog timer + password, is an interrupt
    //WDTHOLD watchdog timer +hold, if 1 watchdog timer is stopped
    // Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

   

    //resistor enabled, input 1.3
    P1REN |= BIT3;

    //Sets Resistor to pullup, 1.0 is low, has to use = to initialize
    P1OUT = BIT3;

	//Enables port 1.0 as output, any bits that are 0 are treated as inputs
	P1DIR =BIT0;



	while(1) //infinite while loop
	{

	    //checks to see if input p1.3 is low
	    if (!((P1IN & BIT3)==BIT3)){
	        //toggles p1.0 red led
	        P1OUT ^= BIT0;
	    }


	}
}
```

## Huge Distinction of MSP430FR6989 and MSP430F5529
For these two boards you have to initialize P1OUT and P1DIR with an assignment operator (=). If you try to do something normal like a |= it will work with the other boards but will not work with these two for some reason.

## Toggling doesn't always work
For all of these boards, sometimes pressing the button increases the intensity of the output led instead of turning it off. This might be a problem with the P1REN statement for each of these boards since this is done with a |= instead of an =



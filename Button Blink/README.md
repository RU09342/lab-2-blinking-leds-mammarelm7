# Lab 2: Button Blink
The code for each of the boards were pretty similar, the main differences where the pinouts for the input buttons used. The code just checks for the button input and then toggles the onboard P1.0 led

## MSP430F5529 
Button: P1.1
## MSP430FR2311 
Button: P1.1
## MSP430FR5994 
Button: P5.6
## MSP430FR6989 
Button: P1.1
## MSP430G2553 
Button: P1.3 

## Huge Distinction of MSP430FR6989 and MSP430F5529
For these two boards you have to initialize P1OUT and P1DIR with an assignment operator (=). If you try to do something normal like a |= it will work with the other boards but will not work with these two for some reason.

## Toggling doesn't always work
For all of these boards, sometimes pressing the button increases the intensity of the output led instead of turning it off. This might be a problem with the P1REN statement for each of these boards since this is done with a |= instead of an =



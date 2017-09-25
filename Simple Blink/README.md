# Lab2: Simple Blink
For each of the boards, there is a blink.c file that will blink the onboard led with a 50% duty cycle

# Code Differences
There are two main blink.c files that were created for these boards. One blink.c file applies for the MSP430FR2311,MSP430FR5994,MSP430FR6989. The other blink.c file applies to the MSP430F5529, MSP430G2553. 

## MSP430FR2311, MSP430FR5994,  MSP430FR6989
These three boards have exactly the same blink.c file. 
First the watchdog timer is stopped.
Then the GPIO power-on default high-impedance mode is disabled so that the default port settings are loaded. 
Then port 1 is set as the output. 
Finally there is an infinite for loop where a delay is created and the led blinks indefinitely.

## MSP430F5529,  MSP430G2553
These two boards have the same blink.c file. 
First the watchdog timer is stopped. 
Then port 1 is enabled as output. 
Then there is an infinte while loop where a delay is created and the led blinks.

##Extra Work UART MSP430FR2311
For this board I included a msp430fr231x_euscia0_uart_01.c file which implements uart. It allows you to type in ascii characters to control the speed of the blinking led. You can send 's' or 'S' for slow, 'm' or 'M' for medium, and 'f' or 'F' for fast.


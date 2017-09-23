# Lab 2: Multiple Blink

## For each of the respective boards, a similar coding structure was used, but with different pinouts for the leds.

## MSP430F5529 
GREEN LED: P4.7
## MSP430FR2311 
GREEN LED: P2.0
## MSP430FR5994 
GREEN LED: P1.1
## MSP430FR6989 
GREEN LED: P9.7
## MSP430G2553 
GREEN LED: P1.6

### Each new blink.c file contains a different delay loop for the red and green leds and includes an extra toggle for the red led to ensure that both leds are asynchronous
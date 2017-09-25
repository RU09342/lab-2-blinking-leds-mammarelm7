/*
Matt Mammarelli
9/24/17
ECE 09342-2
*/

//MSP430FR2311 Simple Blink UART
//s or S for slow, m or M for medium, f or F for fast
//added code within the /***********

#include <msp430.h>

void Init_GPIO();
void Software_Trim();                       // Software Trim to get the best DCOFTRIM value
#define MCLK_FREQ_MHZ 8                     // MCLK = 8MHz

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;                // Stop watchdog timer

  // Configure GPIO
  Init_GPIO();

  PM5CTL0 &= ~LOCKLPM5;                    // Disable the GPIO power-on default high-impedance mode
                                           // to activate 1previously configured port settings

  __bis_SR_register(SCG0);                 // disable FLL
  CSCTL3 |= SELREF__REFOCLK;               // Set REFO as FLL reference source
  CSCTL1 = DCOFTRIMEN_1 | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_3;// DCOFTRIM=3, DCO Range = 8MHz
  CSCTL2 = FLLD_0 + 243;                  // DCODIV = 8MHz
  __delay_cycles(3);
  __bic_SR_register(SCG0);                // enable FLL
  Software_Trim();                        // Software Trim to get the best DCOFTRIM value

  CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK; // set default REFO(~32768Hz) as ACLK source, ACLK = 32768Hz
                                           // default DCODIV as MCLK and SMCLK source

  // Configure UART pins
  P1SEL0 |= BIT6 | BIT7;                    // set 2-UART pin as second function

  // Configure UART
  UCA0CTLW0 |= UCSWRST;
  UCA0CTLW0 |= UCSSEL__SMCLK;

  // Baud Rate calculation
  // 8000000/(16*9600) = 52.083
  // Fractional portion = 0.083
  // User's Guide Table 17-4: UCBRSx = 0x49
  // UCBRFx = int ( (52.083-52)*16) = 1
  UCA0BR0 = 52;                             // 8000000/16/9600
  UCA0BR1 = 0x00;
  UCA0MCTLW = 0x4900 | UCOS16 | UCBRF_1;

  UCA0CTLW0 &= ~UCSWRST;                    // Initialize eUSCI
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

  __bis_SR_register(LPM3_bits|GIE);         // Enter LPM3, interrupts enabled
  __no_operation();                         // For debugger
}

void Software_Trim()
{
    unsigned int oldDcoTap = 0xffff;
    unsigned int newDcoTap = 0xffff;
    unsigned int newDcoDelta = 0xffff;
    unsigned int bestDcoDelta = 0xffff;
    unsigned int csCtl0Copy = 0;
    unsigned int csCtl1Copy = 0;
    unsigned int csCtl0Read = 0;
    unsigned int csCtl1Read = 0;
    unsigned int dcoFreqTrim = 3;
    unsigned char endLoop = 0;

    do
    {
        CSCTL0 = 0x100;                         // DCO Tap = 256
        do
        {
            CSCTL7 &= ~DCOFFG;                  // Clear DCO fault flag
        }while (CSCTL7 & DCOFFG);               // Test DCO fault flag

        __delay_cycles((unsigned int)3000 * MCLK_FREQ_MHZ);// Wait FLL lock status (FLLUNLOCK) to be stable
                                                           // Suggest to wait 24 cycles of divided FLL reference clock
        while((CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)) && ((CSCTL7 & DCOFFG) == 0));

        csCtl0Read = CSCTL0;                   // Read CSCTL0
        csCtl1Read = CSCTL1;                   // Read CSCTL1

        oldDcoTap = newDcoTap;                 // Record DCOTAP value of last time
        newDcoTap = csCtl0Read & 0x01ff;       // Get DCOTAP value of this time
        dcoFreqTrim = (csCtl1Read & 0x0070)>>4;// Get DCOFTRIM value

        if(newDcoTap < 256)                    // DCOTAP < 256
        {
            newDcoDelta = 256 - newDcoTap;     // Delta value between DCPTAP and 256
            if((oldDcoTap != 0xffff) && (oldDcoTap >= 256)) // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim--;
                CSCTL1 = (csCtl1Read & (~DCOFTRIM)) | (dcoFreqTrim<<4);
            }
        }
        else                                   // DCOTAP >= 256
        {
            newDcoDelta = newDcoTap - 256;     // Delta value between DCPTAP and 256
            if(oldDcoTap < 256)                // DCOTAP cross 256
                endLoop = 1;                   // Stop while loop
            else
            {
                dcoFreqTrim++;
                CSCTL1 = (csCtl1Read & (~DCOFTRIM)) | (dcoFreqTrim<<4);
            }
        }

        if(newDcoDelta < bestDcoDelta)         // Record DCOTAP closest to 256
        {
            csCtl0Copy = csCtl0Read;
            csCtl1Copy = csCtl1Read;
            bestDcoDelta = newDcoDelta;
        }

    }while(endLoop == 0);                      // Poll until endLoop == 1

    CSCTL0 = csCtl0Copy;                       // Reload locked DCOTAP
    CSCTL1 = csCtl1Copy;                       // Reload locked DCOFTRIM
    while(CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Poll until FLL is locked
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCI_A0_VECTOR))) USCI_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCA0IV,USCI_UART_UCTXCPTIFG))
  {
    case USCI_NONE: break;
    case USCI_UART_UCRXIFG:
      while(!(UCA0IFG&UCTXIFG));//***************************************************************************************************************************************************
      if((UCA0RXBUF == 83) | (UCA0RXBUF==115)){      //S or s
          UCA0TXBUF = UCA0RXBUF;

          int j;
      for(j=0;j<=100;j++) //creates a finite loop so blinks
          {

              //declared as volatile to indicate i can change at any time
              // volatile to prevent optimization.
              //c compiler optimization can automatically remove code that introduces intended delays
              volatile unsigned int i;

              //P1OUT contains the value to be output
              // Toggle P1.0 using exclusive-OR
              // If the least significant bit is 0, the XOR with BIT0 will result in a change to 0
              // If the least significant bit is 1, the XOR with BIT0 will result in a change to 1
              P1OUT ^= 0x01;

              //creates the delay between pulses, determines how fast it blinks
              i = 65000;
              //will decrement i unless i = 0
              do i--;
              while(i != 0);
          }

      }
      if ((UCA0RXBUF == 77) | (UCA0RXBUF==109)){ //M or m
          UCA0TXBUF = UCA0RXBUF;

          int j;
          for(j=0;j<=100;j++) //creates a finite loop so blinks
                    {

                        //declared as volatile to indicate i can change at any time
                        // volatile to prevent optimization.
                        //c compiler optimization can automatically remove code that introduces intended delays
                        volatile unsigned int i;

                        //P1OUT contains the value to be output
                        // Toggle P1.0 using exclusive-OR
                        // If the least significant bit is 0, the XOR with BIT0 will result in a change to 0
                        // If the least significant bit is 1, the XOR with BIT0 will result in a change to 1
                        P1OUT ^= 0x01;

                        //creates the delay between pulses, determines how fast it blinks
                        i = 40000;
                        //will decrement i unless i = 0
                        do i--;
                        while(i != 0);
                    }

        }
      if ((UCA0RXBUF == 70) | (UCA0RXBUF==102)){ //F or f
                UCA0TXBUF = UCA0RXBUF;

                int j;
                for(j=0;j<=100;j++) //creates a finite loop so blinks
                          {

                              //declared as volatile to indicate i can change at any time
                              // volatile to prevent optimization.
                              //c compiler optimization can automatically remove code that introduces intended delays
                              volatile unsigned int i;

                              //P1OUT contains the value to be output
                              // Toggle P1.0 using exclusive-OR
                              // If the least significant bit is 0, the XOR with BIT0 will result in a change to 0
                              // If the least significant bit is 1, the XOR with BIT0 will result in a change to 1
                              P1OUT ^= 0x01;

                              //creates the delay between pulses, determines how fast it blinks
                              i = 20000;
                              //will decrement i unless i = 0
                              do i--;
                              while(i != 0);
                          }

              }



//*********************************************************************************************************************************************************************************
      __no_operation();
      break;
    case USCI_UART_UCTXIFG: break;
    case USCI_UART_UCSTTIFG: break;
    case USCI_UART_UCTXCPTIFG: break;
    default: break;
  }
}

void Init_GPIO()
{
    P1DIR = 0xFF; P2DIR = 0xFF;
    P1REN = 0xFF; P2REN = 0xFF;
    P1OUT = 0x00; P2OUT = 0x00;
}

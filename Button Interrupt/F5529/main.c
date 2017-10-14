#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

      P1OUT &= 0x00;               // Shut down everything
      P1DIR &= 0x00;
      P4DIR |= BIT7;            // P1.0 and P1.6 pins output the rest are input
      P1REN |= BIT1;                   // Enable internal pull-up/down resistors
      P1OUT |= BIT1;                   //Select pull-up mode for P1.3
      P1IE |= BIT1;                       // P1.3 interrupt enabled
      P1IES |= BIT1;                     // P1.3 Hi/lo edge
      P1IFG &= ~BIT1;                  // P1.3 IFG cleared
      __enable_interrupt(); // enable global interupts
}


#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
   P4OUT ^= BIT7;                      // Toggle P1.6
   P1IFG &= ~BIT1;                     // P1.3 IFG cleared
}

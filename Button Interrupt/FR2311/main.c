#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

     P1OUT &= 0x00;               // Shut down everything
     P2OUT &= 0x00;

     P1DIR &= 0x00;
     P2DIR &= 0x00;

     P1DIR |= BIT0;
     P2DIR |= BIT0;

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
   P1OUT ^= BIT0;                      // Toggle P1.6
   P2OUT ^= BIT0;
   P1IFG &= ~BIT1;                     // P1.3 IFG cleared
}

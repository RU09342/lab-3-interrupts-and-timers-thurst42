#include <msp430.h>



int a = 1000000;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

      P1OUT &= 0x00;               // Shut down everything
      P1DIR &= 0x00;
      P1DIR |= BIT0 + BIT6;            // P1.0 and P1.6 pins output the rest are input
      P1REN |= BIT3;                   // Enable internal pull-up/down resistors
      P1OUT |= BIT3;                   //Select pull-up mode for P1.3
      P1IE |= BIT3;                       // P1.3 interrupt enabled
      P1IES |= BIT3;                     // P1.3 Hi/lo edge
      P1IFG &= ~BIT3;                  // P1.3 IFG cleared

      TACCTL0 = CCIE;
      TA0CTL = TASSEL_2 + MC_1 + ID_3;  // Use SMCLK in up mode, /8 divider
      TACCR0 = a; // set interupt value
      TA0CCTL0 &= 0x10; // set compare mode


      __enable_interrupt(); // enable global interupts

      while(1)
              {} // run loop}
}


#pragma vector=PORT1_VECTOR
__interrupt void button(void) {
P1OUT ^= (BIT6);
P1IFG &= ~BIT3;
int a = 100000;


}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void blink(void){ //interrupt function
    P1OUT ^= (BIT0);   // Toggle P1.6 (LED)
}





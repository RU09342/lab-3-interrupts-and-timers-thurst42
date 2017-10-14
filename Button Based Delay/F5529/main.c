#include <msp430.h>




int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

      P1OUT &= 0x00;               // Shut down everything
      P1DIR &= 0x00;
      P1DIR |= BIT0 ;            // P1.0 and P1.6 pins output the rest are input
      P1REN |= BIT1;                   // Enable internal pull-up/down resistors
      P1OUT |= BIT1;                   //Select pull-up mode for P1.3
      P1IE |= BIT1;                       // P1.3 interrupt enabled
      P1IES |= BIT1;                     // P1.3 Hi/lo edge
      P1IFG &= ~BIT1;                  // P1.3 IFG cleared

      TACCTL0 = CCIE;
      TA0CTL = TASSEL_2 + MC_1 + ID_3;  // Use SMCLK in up mode, /8 divider
      TACCR0 = 100000; // set interupt value
      TA0CCTL0 &= 0x10; // set compare mode


      __enable_interrupt(); // enable global interupts

      while(1)
              {} // run loop}
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void blink(void){ //interrupt function
    P1OUT ^= (BIT0);   // Toggle P1.6 (LED)
}


#pragma vector=PORT1_VECTOR
__interrupt void button(void) {

    if (!(P1IN & BIT1))
       {

           TA1CTL = TASSEL_2 + MC_2 + ID_3 + TACLR; // Start timer 2
           P1IES &= ~BIT1; // rising edge mode
       }
       else
       {
           TA1CTL = MC_0; // stop timer 1
           TA0CCR0 = TA1R; // set timer 1 value to timer 0 capture compare register
           TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR; // start timer 0 up mode
           TA1R = 0; // Set TA1R to 0

           P1IES |= BIT1; // Set falling interrupt
       }
       P1IFG &= ~BIT1; // Reset interrupt flag
   }








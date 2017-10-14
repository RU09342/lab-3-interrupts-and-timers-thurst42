#include <msp430.h>


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;  // Disable the GPIO power-on default high-impedance mode
    TBCCTL0 = CCIE; // enable capture control interupt
    TB0CTL = TBSSEL_2 + MC_1 + ID_3;  // Use SMCLK in up mode, /8 divider
    TBCCR0 = 10000; // set interupt value
    TB0CCTL0 &= 0x10; // set compare mode

    P1DIR |= BIT0; // set port 1 direction register
    P2DIR |= BIT0;
    P1OUT &= 0x00;
    P2OUT &= 0x00;

    __enable_interrupt(); // enable global interupts


    while(1)
        {} // run loop

}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Port_1(void){ //interrupt function
    P1OUT ^= (BIT0);   // Toggle P1.6 (LED)
    P2OUT ^= (BIT0);
}

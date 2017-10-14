#include <msp430.h>
#define LED1 BIT0
#define BUTTON BIT2

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Disable watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    P1DIR |= LED1;            // Set to output
    P1DIR &= ~BUTTON;            // Set to input
    P1REN |= BUTTON;            // resistor enable...
    P1OUT |= BUTTON;            // pullup resistor
    P1IE |= BUTTON;             // Set as interrupt pin

    __bis_SR_register(GIE);     // Enable interrupt
    while(1)
    {}              // run
}

#pragma vector=PORT1_VECTOR   // interrupt vector
__interrupt void Port_1(void)
{
    P1OUT ^= LED1;            // Toggle
    P1IFG = ~BUTTON;            // Disable interrupt flag
}

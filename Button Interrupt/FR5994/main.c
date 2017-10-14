#include <msp430.h>
#define LED1 BIT0
#define BUTTON BIT5

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Disable watchdog timer
    PM5CTL0 &= ~LOCKLPM5;           // Disable the GPIO power-on default high-impedance mode

    P1DIR |= LED1;            // Set to output
    P5DIR &= ~BUTTON;            // Set P5 to inout
    P5REN |= BUTTON;            // resistor enable...
    P5OUT |= BUTTON;
    P5IE |= BUTTON;             // interrupt pin

    __bis_SR_register(GIE);     // Enable interrupt code

    while(1)
    {}              // By default, do nothing continuously
}

#pragma vector=PORT5_VECTOR   // interrupt vector
__interrupt void Port_1(void){ // interrupt
    P1OUT ^= LED1;            // Toggle
    P5IFG = ~BUTTON;            // Disable interrupt flag / re-enable interrupt
}

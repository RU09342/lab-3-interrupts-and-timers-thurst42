#include <msp430.h>



void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Disable watchdog timer
    PM5CTL0 &= ~LOCKLPM5;  // Disable the GPIO power-on default high-impedance mode
    P1DIR |= (BIT0);   // set bit0 out
    P1OUT &= ~(BIT0);  // bit 0 off
    P1DIR &= ~BIT1;            // set bit 3 to input
    P1REN |= BIT1;            // pulll up enable
    P1OUT |= BIT1;            // pull up enable
    P1IE |= BIT1;             // set bit 3 to interupt
    P1IES |= BIT1;            // tet falling edge interrupt
    TB0CTL = TBSSEL_2 + MC_1 + ID_3 + TBCLR; // Use SMCLK in up mode


    TB0CCR0 = 10000;
    TB0CCTL0 = CCIE;          // enable cc interrupt
    TB0CCTL0 &= 0x10;          // compare mode

    TB1CTL = TBSSEL_2 + MC_0 + ID_3 + TBCLR; //  SMCLK continuous mode, divide 8
    __enable_interrupt();     // enable global interupts
    while(1)
    {}
}

#pragma vector=TIMER0_B0_VECTOR  // timer 0 interupt vector
__interrupt void led(void) // interupt function
{
    P1OUT ^= (BIT0);   // blink led
}

#pragma vector=PORT1_VECTOR   // button interupt vector
__interrupt void button(void){ // interupt function

    if (!(P1IN & BIT1)) //detect button press
    {

        TB1CTL = TBSSEL_2 + MC_2 + ID_3 + TBCLR; // timer 1 enable countious mode divide 8
        P1IES &= ~BIT1; // rising edge interrupt
    }
    else
    {
        TB1CTL = MC_0; // kill timer 1

        TB0CCR0 = TB1R; //timer 1 val = CCR0
        TB0CTL = TBSSEL_2 + MC_1 + ID_3 + TBCLR; // sTBrt timer 0 up mode
        TB1R = 0; // set TB1R to 0

        P1IES |= BIT1; // falling edge interrupt
    }
    P1IFG &= ~BIT1; // reset interrupt flag
}


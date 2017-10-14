#include <msp430g2553.h>



void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Disable watchdog timer
    P1DIR |= (BIT0);   // set bit0 out
    P1OUT &= ~(BIT0);  // bit 0 off
    P1DIR &= ~BIT3;            // set bit 3 to input
    P1REN |= BIT3;            // pulll up enable
    P1OUT |= BIT3;            // pull up enable
    P1IE |= BIT3;             // set bit 3 to interupt
    P1IES |= BIT3;            // tet falling edge interrupt
    TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR; // Use SMCLK in up mode


    TA0CCR0 = 10000;
    TA0CCTL0 = CCIE;          // enable cc interrupt
    TA0CCTL0 &= 0x10;          // compare mode

    TA1CTL = TASSEL_2 + MC_0 + ID_3 + TACLR; //  SMCLK continuous mode, divide 8
    __enable_interrupt();     // enable global interupts
    while(1)
    {}
}

#pragma vector=TIMER0_A0_VECTOR  // timer 0 interupt vector
__interrupt void led(void) // interupt function
{
    P1OUT ^= (BIT0);   // blink led
}

#pragma vector=PORT1_VECTOR   // button interupt vector
__interrupt void button(void){ // interupt function

    if (!(P1IN & BIT3)) //detect button press
    {

        TA1CTL = TASSEL_2 + MC_2 + ID_3 + TACLR; // timer 1 enable countious mode divide 8
        P1IES &= ~BIT3; // rising edge interrupt
    }
    else
    {
        TA1CTL = MC_0; // kill timer 1

        TA0CCR0 = TA1R; //timer 1 val = CCR0
        TA0CTL = TASSEL_2 + MC_1 + ID_3 + TACLR; // start timer 0 up mode
        TA1R = 0; // set TA1R to 0

        P1IES |= BIT3; // falling edge interrupt
    }
    P1IFG &= ~BIT3; // reset interrupt flag
}


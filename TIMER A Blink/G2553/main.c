#include <msp430g2553.h>


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	TACCTL0 = CCIE; // enable capture control interupt
	TA0CTL = TASSEL_2 + MC_1 + ID_3;  // Use SMCLK in up mode, /8 divider
	TACCR0 = 10000; // set interupt value
	TA0CCTL0 &= 0x10; // set compare mode

	P1DIR |= BIT0 + BIT6; // set port 1 direction register
	P1OUT &= 0x00;

	__enable_interrupt(); // enable global interupts

	
	while(1)
	    {} // run loop

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Port_1(void){ //interrupt function
    P1OUT ^= (BIT0 + BIT6);   // Toggle P1.6 (LED)
}

#include <msp430.h>

#define LED0 BIT0
#define LED1 BIT6 
#define BUTTON BIT3

#define TIMER_OFFSET 64000

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	// P1DIR &= ~BUTTON;
	P1DIR = (LED1|LED0);
	P1OUT = BUTTON|LED1;
	P1REN |= BUTTON;
	P1IE |= BUTTON;
	P1IES |= BUTTON;
	P1IFG &= ~BUTTON;

	CCTL0 |= CCIE;
	CCR0 = TIMER_OFFSET;
	TACTL = TASSEL_2 + MC_2 + TAIFG + TAIE;

	__enable_interrupt();

	while (1) {}
}

__attribute__((interrupt(TIMER0_A0_VECTOR)))
void timera_interrupt(void) {
	// P1OUT ^= LED1;
	P1OUT ^= (LED0 + LED1);
	CCR0 = TIMER_OFFSET;
}

__attribute__((interrupt(PORT1_VECTOR)))
void port1_interrupt(void)
{
	if (P1IN & BUTTON) {
		P1OUT ^= (LED0 + LED1);
	}
	// P1OUT &= ~BUTTON;

	P1IFG &= ~BUTTON;
	P1IES ^= BUTTON;
}
#include <msp430.h>

#include <manchicken_430.h>

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; 			// Stop watchdog timer
	P1DIR |= (REDLED | GREENLED);		// Set P1.0 and P1.6 to output direction


	manckn430_set_display(5);

	_BIS_SR(LPM0_bits + GIE);       // LPM0 (low power mode) with interrupts enabled

	return 0;
}

__attribute__((interrupt(TIMER0_A0_VECTOR)))
void Timer0_A0 (void) {
	manckn430_readout_timer_interrupt();
}
#include <msp430.h>

#include <manchicken_430.h>

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; 			// Stop watchdog timer
	P1DIR |= (REDLED | GREENLED | (!BUTTON));		// Set P1.0 and P1.6 to output direction

	manckn430_set_crystal_timer0_a0();
	manckn430_set_display(3);
	manckn430_enable_button_interrupt();

	_BIS_SR(LPM3_bits + GIE);       // LPM0 (low power mode) with interrupts enabled
	// _BIS_SR(LPM0_bits + GIE);       // LPM0 (low power mode) with interrupts enabled

	return 0;
}

__attribute__((interrupt(TIMER0_A0_VECTOR)))
void interrupt_timer0_a0 (void) {
	manckn430_readout_timer_interrupt();
}

__attribute__((interrupt(PORT1_VECTOR)))
void port1_interrupt(void) {
	if (manckn430_is_button_down() == YES) {
		manckn430_increment_display(1);
		manckn430_toggle_led(YES, GREENLED);
		manckn430_toggle_led(YES, REDLED);
	}

	P1IFG &= ~BUTTON;
	P1IES ^= BUTTON;
}
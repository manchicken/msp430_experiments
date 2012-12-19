#include <msp430.h>

#define CRYSTAL_kHz 32768

#define REDLED BIT0
#define GREENLED BIT6
#define BUTTON BIT3

#define READOUT_PADDING 2

typedef char byte;

int to_read_out = 0;
byte readout_reset = 0;
byte onoff = 0;

void display_next(void);
void set_display(int new_value);

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; 			// Stop watchdog timer
	P1DIR |= (REDLED | GREENLED);		// Set P1.0 and P1.6 to output direction

	CCR0 = (CRYSTAL_kHz-1)/3;           // Count limit
	CCTL0 = 0x10;                   // Enable counter interrupts, bit 4=1
	TACTL = TASSEL_1 + MC_1;        // Timer A with ACLK, count UP

	set_display(5);

	_BIS_SR(LPM0_bits + GIE);       // LPM0 (low power mode) with interrupts enabled

	return 0;
}

__attribute__((interrupt(TIMER0_A0_VECTOR)))
void Timer0_A0 (void) {
	if (onoff) {
		display_next();
		onoff = 0;
	} else {
		P1OUT &= !(REDLED | GREENLED);
		onoff = 1;
	}
}	

void display_next() {
	static int curr_item = 0;

	// If the readout_reset is set
	if (readout_reset) {
		curr_item = 0;
		readout_reset = 0;
	}

	// Reset if we're at the limit
	if (curr_item >= to_read_out) {
		curr_item = (READOUT_PADDING * -1);
	}

	if (curr_item < 0) {
		P1OUT |= (REDLED | (!GREENLED));
		onoff = 1;
	} else {
		P1OUT |= ((!REDLED) | GREENLED);
	}

	curr_item += 1;

	return;
}

void set_display(int new_value) {
	to_read_out = new_value;
	readout_reset = 1;
}
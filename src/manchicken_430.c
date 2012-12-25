#include <manchicken_430.h>

char *foo = "manchicken_430.c";

int to_read_out = 0;
byte readout_reset = 0;
byte onoff = 0;

void manckn430_display_next() {
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

void manckn430_set_display(int new_value) {
	to_read_out = new_value;
	readout_reset = 1;
}

void manckn430_readout_timer_interrupt (void) {
	if (onoff) {
		manckn430_display_next();
		onoff = 0;
	} else {
		P1OUT &= !(REDLED | GREENLED);
		onoff = 1;
	}
}	

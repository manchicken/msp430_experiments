#include <manchicken_430.h>

int to_read_out = 0;
int reading_out = 0;
byte readout_reset = NO;
byte onoff = NO;
byte __lock_readout_interrupt_handler = NO;
byte _pause_display = NO;

void manckn430_set_crystal_timer0_a0(void) {
	CCR0 = (CRYSTAL_kHz-1)/3;           // Count limit
	CCTL0 |= 0x10;                   // Enable counter interrupts, bit 4=1
	TACTL |= TASSEL_1 + MC_1;        // Timer A with ACLK, count UP

	return;
}

void manckn430_enable_button_interrupt (void) {
	P1OUT |= BUTTON;
	P1REN |= BUTTON;
	P1IE |= BUTTON;
	P1IES |= BUTTON;
	P1IFG &= ~BUTTON;

	return;
}

void manckn430_pause_display() {
	_pause_display = YES;
}

void manckn430_resume_display() {
	_pause_display = NO;
}

void _manckn430_display_next() {
	if (_pause_display == YES) {
		return;
	}

	if ((reading_out < (READOUT_PADDING * -1)) || readout_reset) {
		reading_out = to_read_out - 1;
		readout_reset = NO;
	}

	if (reading_out >= 10) {
		manckn430_toggle_led((!(reading_out < 0)), REDLED);
		reading_out -= 10;
	} else {
		manckn430_toggle_led((!(reading_out < 0)), GREENLED);
		reading_out -= 1;
	}

	return;
}

void _manckn430_lock_readout(byte is_on) {
	__lock_readout_interrupt_handler = is_on;
}

void manckn430_set_display(int new_value) {
	_manckn430_lock_readout(YES);
	to_read_out = new_value;
	readout_reset = 1;
	_manckn430_lock_readout(NO);
}

void manckn430_increment_display(int amount) {
	_manckn430_lock_readout(YES);
	manckn430_toggle_led(YES,REDLED);
	manckn430_toggle_led(YES,GREENLED);
	to_read_out += amount;
	readout_reset = 1;
	_manckn430_lock_readout(NO);
}

void manckn430_readout_timer_interrupt (void) {
	if (__lock_readout_interrupt_handler == YES) {
		return;
	}

	_manckn430_lock_readout(YES);

	if (onoff) {
		_manckn430_display_next();
		onoff = 0;
	} else {
		P1OUT &= !(REDLED | GREENLED);
		onoff = 1;
	}

	_manckn430_lock_readout(NO);
}	

byte manckn430_is_button_down(void) {
	if (P1IN & BUTTON) {
		return YES;
	}

	return NO;
}

void manckn430_toggle_led(byte is_on, byte which_led) {
	if (is_on == NO) {
		P1OUT |= (!which_led);
	} else {
		P1OUT |= which_led;
	}

	return;
}
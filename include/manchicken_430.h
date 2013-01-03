#ifndef __MANCHICKEN_430_H__
#define __MANCHICKEN_430_H__

#include <msp430.h>

#define REDLED BIT0
#define GREENLED BIT6
#define BUTTON BIT3

#define YES 1
#define NO 0

#define CRYSTAL_kHz 32768
#define READOUT_PADDING 1

typedef char byte;

// Initialization
extern void manckn430_set_crystal_timer0_a0(void);
extern void manckn430_enable_button_interrupt (void);

// For readout display setting
extern void manckn430_set_display(int new_value);
extern void manckn430_increment_display(int amount);

// Interrupt handlers
extern void manckn430_readout_timer_interrupt (void);

// Internal stuff
extern void _manckn430_display_next(void);
extern void _manckn430_lock_readout(byte is_on);

// Tests
extern byte manckn430_is_button_down(void);

// Controlling stuff
extern void manckn430_toggle_led(byte is_on, byte which_led);
extern void manckn430_pause_display();
extern void manckn430_resume_display();

#endif /* __MANCHICKEN_430_H__ */
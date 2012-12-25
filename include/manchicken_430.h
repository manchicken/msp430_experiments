#ifndef __MANCHICKEN_430_H__
#define __MANCHICKEN_430_H__

#include <msp430.h>

#define REDLED BIT0
#define GREENLED BIT6
#define BUTTON BIT3

#define CRYSTAL_kHz 32768

#define READOUT_PADDING 2

typedef char byte;

#ifdef MANCHICKEN_430

extern void manckn430_display_next(void);
extern void manckn430_set_display(int new_value);
extern void manckn430_readout_timer_interrupt (void);

#endif /* MANCHICKEN_430 */

#endif /* __MANCHICKEN_430_H__ */
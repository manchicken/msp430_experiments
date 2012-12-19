#include <msp430.h>

#define LED0 BIT0
#define REDLED LED0
#define LED1 BIT6 
#define GREENLED LED1
#define BUTTON BIT3

#define CRYSTAL_kHz 32768

int main(void) {
	WDTCTL = WDTPW + WDTHOLD; 			// Stop watchdog timer
	P1DIR |= (REDLED | GREENLED); 					// Set P1.0 and P1.6 to output direction
	// P1OUT = 0;
	P1OUT = REDLED; 					// Set the red LED on
	// P1OUT |= GREENLED; 					// Set the green LED off

	CCR0 = CRYSTAL_kHz-1;					// Count limit
	CCTL0 = 0x10;					// Enable counter interrupts, bit 4=1
	TACTL = TASSEL_1 + MC_1; 			// Timer A with ACLK, count UP

	_BIS_SR(LPM0_bits + GIE);       		           // LPM0 (low power mode) with interrupts enabled

	return 0;
}

__attribute__((interrupt(TIMER0_A0_VECTOR)))
void Timer0_A0 (void) { // Timer0 A0 interrupt service routine
	P1OUT ^= (REDLED + GREENLED);					// Toggle red/green LEDs
}	

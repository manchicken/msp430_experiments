msp430_experiments
==================

Here's where I'm teaching my self how to hack the MSP430 (currently for the MSP430G2553)

MSP430 Programs
===============
## toggle_leds_with_button.430 ##
This program toggles P1.0 and P1.6 with each push of P1.3.

## light_patterns.430 ##
The goal of this is to learn how to use the timer and make patterns of P1.0 and P1.6 appear.

## readout_demo.430 ##
The goal of this is to use the timer and the LEDs to give a readout. A red LED flash (1.0) is ten, a green LED flash (1.6) is one. RED, GREEN, GREEN would be twelve.

## temp_readout_demo.430 ##
Something to tell you the temperature, uses the same convention as readout_demo.430.

Other Stuff
===========
## bitmath.osx ##
A program I'm using to double-check my math and use of operators.

## scripts/gdbmsp ##
This script is just a shortcut for loading GDB with my program. (doesn't really work all that well, kinda broken)

## scripts/progmsp ##
This script is a quick shortcut for programming the MSP with your chosen binary.

Usage: `./scripts/progmsp ./bin/readout_demo.430`

SRCDIR = ./src
OBJDIR = ./obj
LIBDIR = ./lib
BINDIR = ./bin
INCDIR = ./include

MSPINC = /usr/local/msp430-toolchain/msp430/include

GCC = msp430-gcc -mmcu=msp430g2553
OSXCC = gcc

CFLAGS = -g -Os -I$(INCDIR) -Wall -I$(MSPINC)

PROGS = \
	$(BINDIR)/toggle_leds_with_button.430 \
	$(BINDIR)/light_patterns.430 \

PLAY = \
	$(BINDIR)/bitmath.osx \

.PHONY: all clean rebuild

all: $(PROGS) $(PLAY)

clean:
	rm -fr bin/* obj/*

rebuild: clean all

$(BINDIR)/%.430: $(SRCDIR)/%.c
	$(GCC) $(CFLAGS) -o $@ $<

$(BINDIR)/%.osx: $(SRCDIR)/%.c
	$(OSXCC) $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(GCC) $(CFLAGS) -c -o $@ $<

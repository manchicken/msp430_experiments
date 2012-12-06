#include <stdio.h>
#include <msp430.h>
#include <in430.h>


typedef unsigned char byte;

#define LED0 getbit(0)
#define LED1 getbit(6)
#define BUTTON getbit(3)

byte getbit(unsigned short which) {
	if (which >= 8) { printf("Overflow\n"); return 0x0; }
	return (0x01 << which);
}

// Just dump some bits
void binout(byte num){
  int size = sizeof(byte);
  int maxPow = 1<<(size*8-1);
  // printf("MAX POW : %u\n",maxPow);
  int i=0;
	for( ; i<size*8; ++i ) {
	  // print last bit and shift left.
		printf("%u", !!(num&maxPow));
    num = num << 1;

    if (!((i + 1) % 8)) {
    	printf(" ");
    }
	}
	printf("\n");
}

#define TEST(X) binout(X)

int main(void) {
	printf("5 + 4 = %d\n",5+4);
	printf("5 - 4 = %d\n",5-4);
	printf("5 * 4 = %d\n",5*4);
	printf("(float)5 / (float)4 = %f\n",(float)5/(float)4);
   printf("5 / 4 = %d\n",5/4);	
	printf("5 %% 4 = %d\n",5%4);
	printf("5 & 4 = %d\n",5&4);
	printf("5 | 4 = %d\n",5|4);
	printf("5 ^ 4 = %d\n",5^4);
	printf("~5 = (hex) %x\n",~5);

	byte test = LED0 | LED1 | !BUTTON;
	binout(test);

	test |= BUTTON;
	binout(test);

	test ^= BUTTON;
	binout(test);

	test ^= BUTTON;
	binout(test);

	return 0;
}

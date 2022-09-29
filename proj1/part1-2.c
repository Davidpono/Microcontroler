#include <msp430fr6989.h>
#include <stdint.h>
#define redLED BIT0 // Red LED at P1.0
#define greenLED BIT7
void main(void) {
//volatile unsigned int i;
volatile uint32_t i;
WDTCTL = WDTPW | WDTHOLD; // Stop the Watchdog timer
PM5CTL0 &=  ~LOCKLPM5; // Disable GPIO power-on default high-
//impedance mode
P1DIR |= redLED; // Direct pin as output
P1OUT &= ~redLED; // Turn LED Off
P9DIR |= greenLED;
P9OUT &= ~greenLED;
int n=0;
for(;;) {
for(i=0; i<90000; i++) {
     }
P1OUT ^= redLED; // Toggle the LED
 
}
}

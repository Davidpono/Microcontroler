#include <msp430fr6989.h>
#define redLED BIT0 // Red LED at P1.0
#define greenLED BIT7 // Green LED at P9.7
#define BUT1 BIT1 // Button S1 at P1.1
#define BUT2 BIT2
void main(void) {
WDTCTL = WDTPW | WDTHOLD; // Stop the Watchdog timer
PM5CTL0 &=  ~LOCKLPM5;// Enable the GPIO pins
// Configure and initialize LEDs
P1DIR |= redLED; // Direct pin as output
P9DIR |= greenLED; // Direct pin as output
P1OUT &=  ~redLED; // Turn LED Off
P9OUT &=  ~greenLED; // Turn LED Off
// Configure buttons
P1DIR &=  ~(BUT1|BUT2); // Direct pin as input
P1REN|=(BUT1|BUT2); // Enable built-in resistor
P1OUT|=(BUT1|BUT2); // Set resistor as pull-up
// Polling the button in an infinite loop
for(;;) {
 
// Rewrite the pseudocode below into C code
while ((P1IN& BUT1) == 0){
    while ((P1IN & BUT2) == 0 &&(P1IN & BUT1) == 0){
        P1OUT &= ~redLED;//
        P9OUT &= ~greenLED;
    }
    P1OUT |=  redLED;//on
    P9OUT &= ~greenLED;//off
 
    }
 
    //P1OUT |=  redLED;
while((P1IN & BUT2) == 0){
    while ((P1IN & BUT2) == 0 &&(P1IN & BUT1) == 0){
            P1OUT &= ~redLED;//
            P9OUT &= ~greenLED;
    }
    P9OUT |=  greenLED;//on
        P1OUT &= ~redLED;//off
 
        }
 
 
P1OUT &= ~redLED;//
P9OUT &= ~greenLED;
//if((P1IN & BUT2) == 0)
   // P9OUT|=greenLED;
//else P9OUT &= ~greenLED;
}
}


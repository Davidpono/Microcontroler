#include <msp430fr6989.h>
#define redLED BIT0 // Red LED at P1.0
#define greenLED BIT7 // Green LED at P9.7
#define BUT1 BIT1 // Button S1 at P1.1
#define BUT2 BIT2
//**********************************
// Configures ACLK to 32 KHz crystal
void config_ACLK_to_32KHz_crystal() {
// By default, ACLK runs on LFMODCLK at 5MHz/128 = 39 KHz
// Reroute pins to LFXIN/LFXOUT functionality
PJSEL1 &= ~BIT4;
PJSEL0 |= BIT4;
// Wait until the oscillator fault flags remain cleared
CSCTL0 = CSKEY; // Unlock CS registers
do {
CSCTL5 &= ~LFXTOFFG; // Local fault flag
SFRIFG1 &= ~OFIFG; // Global fault flag
} while((CSCTL5 & LFXTOFFG) != 0);
CSCTL0_H = 0; // Lock CS registers
return;
}
#include <msp430.h>
#define redLED BIT0
#define greenLED BIT7
void main(void) {
WDTCTL = WDTPW | WDTHOLD; // Stop the Watchdog timer
PM5CTL0 &= ~LOCKLPM5;// Enable the GPIO pins
// Configure and initialize LEDs
P1DIR |= redLED; // Direct pin as output
P9DIR |= greenLED; // Direct pin as output
P1OUT &= ~redLED; // Turn LED Off
P9OUT &= ~greenLED; // Turn LED Off
config_ACLK_to_32KHz_crystal();
P1DIR &= ~(BUT1|BUT2); // Direct pin as input
P1REN |=( BUT1|BUT2); // Enable built-in resistor
P1OUT |= (BUT1|BUT2); // Set resistor as pull-up
P1IES |= (BUT1|BUT2); // 1: interrupt on falling edge (0 for rising edge)
P1IFG  &= ~(BUT1|BUT2); // 0: clear the interrupt flags
P1IE |= (BUT1|BUT2); // 1: enable the interrupts
//TA0CTL = TASSEL_1 |ID_0| MC_1 | TACLR;
//TA0CTL &= ~TAIFG;
_enable_interrupts();
// Polling the button in an infinite loop
 
for(;;) {}
}
// P1OUT ^= redLED;
//P9OUT ^= greenLED;
    //******* Writing the ISR *******
    #pragma vector = PORT1_VECTOR
    __interrupt void PORT1_ISR(){
            //check botton flag
            if((P1IFG & BUT1 ) !=0){
    P1OUT ^= redLED;
    P1IFG &= ~BUT1;//clear butt flasg
            }
    //TA0CTL &= ~TAIFG;
     //hw clear flag
     }

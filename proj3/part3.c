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
l:
s3:
if((P1IN & BUT1) == 0){//press botton
    P1OUT &= ~redLED;
    TA0CTL =TASSEL_1 | ID_0 | MC_2| TACLR; //start timer clear, no divide, continonus mode
    TA0CTL &= ~TAIFG;   //reset flags
 
    }
 
if(TA0R==0){            //if loop to check if timer was start
goto l;}                //if not started check again if bottons pressed
l2:
s4:
while((TA0CTL & TAIFG) == 1){   //whioe the flag is detected
 
    P9OUT |= greenLED;              // green led on
        if((P1IN & BUT2) == 0){        //if button two is pressed
                    P9OUT &= ~greenLED; //turn green off
                    TA0CTL &= ~TAIFG;   //reset the flag
                    TA0CTL = TACLR;        //reset the timer
                    goto s3;            //check if button/timer was started again
                }
        goto s4;                        //keep checking if botton two is presed
 
    }
 
if((P1IN & BUT1) == 0){                 //if botton 1 is not released yet keep checking for a flag
goto l2;}
 
if((P1IN & BUT1) == BUT1 ){             //if botton 1 is relased but no flag than make the taocco equalt to time
        TA0CCR0 = TA0R -1;              
    }
 
    P1OUT |= redLED;                    //tunr red led on
    TA0CTL = TASSEL_1 | ID_0 | MC_1 | TACLR;    //start timer no divider up mode
    TA0CTL &= ~TAIFG;                   //clear any flags just in case
 
    while((TA0CTL & TAIFG) == 0){       //while no flagg do nothing
    }
    P1OUT &= ~redLED;                   //turn led off
    TA0CTL = MC_0;                         //stop timer
 
}
}
 
 
 


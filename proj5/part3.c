#include <msp430fr6989.h>
#include <stdint.h>
#define redLED BIT0 // Red at P1.0
#define greenLED BIT7 // Green at P9.7
#define BUT1 BIT1 // Button S1 at P1.1
#define BUT2 BIT2
#define FLAGS UCA1IFG // Contains the transmit & receive flags
#define RXFLAG UCRXIFG // Receive flag
#define TXFLAG UCTXIFG // Transmit flag
#define TXBUFFER UCA1TXBUF // Transmit buffer
#define RXBUFFER UCA1RXBUF // Receive buffer
volatile int runway2=0;
volatile int runway1=0;
volatile int x=0;
void Initialize_UART_2(void){
    // Configure pins to UART functionality
    P3SEL1 &=  ~(BIT4|BIT5);
    P3SEL0 |= (BIT4|BIT5);
    // Main configuration register
    UCA1CTLW0 = UCSWRST; // Engage reset; change all the fields to zero
    // Most fields in this register, when set to zero, correspond to the
    // popular configuration
    UCA1CTLW0 |= UCSSEL_1; // Set clock to SMCLK
    // Configure the clock dividers and modulators (and enable oversampling)
    UCA1BRW = 6; // divider
    // Modulators: UCBRF = 8 = 1000 --> UCBRF3 (bit #3)
    // UCBRS = 0x20 = 0010 0000 = UCBRS5 (bit #5)
    //
    UCA1MCTLW =  UCBRS1 | UCBRS2| UCBRS3| UCBRS5 | UCBRS6| UCBRS7;
    // Exit the reset state
    UCA1CTLW0 &=  ~UCSWRST;
 
 
}
void Initialize_UART(void){
// Configure pins to UART functionality
P3SEL1 &=  ~(BIT4|BIT5);
P3SEL0 |= (BIT4|BIT5);
// Main configuration register
UCA1CTLW0 = UCSWRST; // Engage reset; change all the fields to zero
// Most fields in this register, when set to zero, correspond to the
// popular configuration
UCA1CTLW0 |= UCSSEL_2; // Set clock to SMCLK
// Configure the clock dividers and modulators (and enable oversampling)
UCA1BRW = 6; // divider
// Modulators: UCBRF = 8 = 1000 --> UCBRF3 (bit #3)
// UCBRS = 0x20 = 0010 0000 = UCBRS5 (bit #5)
UCA1MCTLW = UCBRF3 | UCBRS5 | UCOS16;
// Exit the reset state
UCA1CTLW0 &=  ~UCSWRST;
}
void uart_write_stringgotoline(char * str);
void uart_write_stringorlando (char * str);
void uart_write_uint16 (unsigned int n);
void uart_write_stringinused(char * str);
void uart_write_char(unsigned char ch){
// Wait for any ongoing transmission to complete
while ( (FLAGS & TXFLAG)==0 ) {}
// Copy the byte to the transmit buffer
TXBUFFER = ch; // Tx flag goes to 0 and Tx begins!
return;
}
 
// The function returns the byte; if none received, returns null character
unsigned char uart_read_char(void){
unsigned char temp;
// Return null character (ASCII=0) if no byte was received
if( (FLAGS & RXFLAG) == 0)
return 0;
// Otherwise, copy the received byte (this clears the flag) and return it
temp = RXBUFFER;
return temp;
}
// The array has the shapes of the digits (0 to 9)
// Complete this array...
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
void uart_write_string (char * str);
int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Stop WDT
PM5CTL0 &=  ~LOCKLPM5; // Enable GPIO pins
P1DIR |= redLED; // Pins as output
P9DIR |= greenLED;
P1OUT &=  ~redLED; // Red on
P9OUT &=  ~greenLED; // Green off
P1DIR &= ~(BUT1|BUT2); // Direct pin as input
P1REN |=( BUT1|BUT2); // Enable built-in resistor
P1OUT |= (BUT1|BUT2); // Set resistor as pull-up
P1IES |= (BUT1|BUT2); // 1: interrupt on falling edge (0 for rising edge)
P1IFG  &= ~(BUT1|BUT2); // 0: clear the interrupt flags
P1IE |= (BUT1|BUT2); // 1: enable the interrupts
// Initializes the LCD_C module
config_ACLK_to_32KHz_crystal();
TA0CTL = TASSEL_1 |ID_0| MC_2 | TACLR;
TA0CTL &= ~TAIFG;
TA1CCR0 = 10000; // 1 second @ 32 KHz
TA1CCTL0 &= ~CCIFG; // Enable Channel 0 CCIE bit
TA1CCTL0|= CCIE; // Clear Channel 0 CCIFG bit
TA1CTL = TASSEL_1 |ID_0| MC_1 | TACLR;
 
//_enable_interrupts();
// Set timer period
// Configure Channel 0 for up mode with interrupts
 
// The line below can be used to clear all the segments
//LCDCMEMCTL = LCDCLRM; // Clears all the segmentsint
 
// Display 430 on the rightmost three digits
Initialize_UART_2();
int p = 45657;
//uart_write_uint16(p);
//uart_write_string("hello");
//Initialize_UART();
 
//uart_write_string(str1);
 
//uart_write_string(str2);
//uart_write_uint16 (p);
    //uart_read_char();*/
//unsigned char c= 'd';
//uart_write_char(c);
int i=0;
int a = 0;
for(;;) {
 
if(uart_read_char()=='c'){
    uart_write_uint16(p);
    uart_write_string("hello");
}
 
 
}
return 0;
}
void uart_write_stringdelete(char * str){
    int i=0;
        int l =4;
 
        while(i<l){
            uart_write_char(str[i]);
                    i++;
    }
        return;
}
void uart_write_stringinused(char * str){
    int i=0;
        int l =6;
 
        while(i<l){
            uart_write_char(str[i]);
                    i++;
    }
        return;
}
void uart_write_stringgotoline(char * str){
    int i=0;
        int l =8;
 
        while(i<l){
            uart_write_char(str[i]);
                    i++;
    }
        return;
}
void uart_write_string (char * str){
    int i=0;
    int l =9;
 
    while(i<l){
        uart_write_char(str[i]);
                i++;
}
    return;
}
void uart_write_stringorlando (char * str){
    int i=0;
    int l =224;
 
    while(i<l){
        uart_write_char(str[i]);
                i++;
}
    return;
}
void uart_write_uint16 (unsigned int n){
    int digit;
    if(n>9999){
                   digit= (n/10000);
                   uart_write_char('0'+ digit);
               }
    if(n>999){
        digit= (n % 10000)/1000;
                    uart_write_char('0'+ digit);
           }
        if(n>99){
            digit= (n % 1000)/100;
            uart_write_char('0'+ digit);
        }
        if(n>9){
            digit= (n % 100)/10;
                   uart_write_char('0'+ digit);
        }
        digit = n%10;
        uart_write_char('0'+ digit);
        return;
 
 
}
#pragma vector = TIMER1_A1_VECTOR
__interrupt void TA0_A0_ISR(){
P1OUT ^= redLED;
//TA0CTL &= ~TAIFG;
//hw clear flag
}

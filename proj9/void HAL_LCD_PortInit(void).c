void HAL_LCD_PortInit(void)
{
    /////////////////////////////////////
    // Configuring the SPI pins
    /////////////////////////////////////
    P1SEL1 &= ~BIT4;
    P1SEL0 |= BIT4;
    // Configure UCB0CLK/P1.4 pin to serial clock
    P1SEL1 &= ~BIT6;
    P1SEL0 |= BIT6;
    // Configure UCB0SIMO/P1.6 pin to SIMO
    P9DIR |= BIT4;
    // OK to ignore UCB0STE/P1.5 since we'll connect the display's enable bit to low (enabled all the time)
    // OK to ignore UCB0SOMI/P1.7 since the display doesn't give back any data
 
    ///////////////////////////////////////////////
    // Configuring the display's other pins
    ///////////////////////////////////////////////
    // Set reset pin as output
    P2DIR |= BIT3;
    // Set the data/command pin as output
    P2DIR |= BIT5;
    // Set the chip select pin as output
 
 
    return;
}
 
void HAL_LCD_SpiInit(void)
{
    //////////////////////////
    // SPI configuration
    //////////////////////////
    // Put eUSCI in reset state and set all fields in the register to 0
    UCB0CTLW0 = UCSWRST;
 
    // Fields that need to be nonzero are changed below
    // Set clock phase to "capture on 1st edge, change on following edge"
    // Set clock polarity to "inactive low"
    UCB0CTLW0=UCSWRST;
    // Set data order to "transmit MSB first"
    UCB0CTLW0 |= UCCKPH;
    // Set data size to 8-bit
    UCB0CTLW0 &= ~UCCKPL;
    // Set MCU to "SPI master"
    UCB0CTLW0 |= UCMSB;
    // Set SPI to "3-pin SPI" (we UCwon't use eUSCI's chip select)
            UCB0CTLW0 &= ~UC7BIT;
    // Set module to synchronous mode
    UCB0CTLW0 |= UCMST;
    // Set clock to SMCLK
    UCB0CTLW0 |= UCMODE_0;
    UCB0CTLW0 |= UCSYNC;
    UCB0CTLW0 |= UCSSEL_2;
    // Configure the clock divider (SMCLK is from DCO at 8 MHz; run SPI at 8 MHz using SMCLK)
    UCB0BRW = 1;
    // Exit the reset state at the end of the configuration
    UCB0CTLW0 &= ~UCSWRST;
 
    // Set CS' (chip select) bit to 0 (display always enabled)
    P2OUT &= ~BIT5;
    // Set DC' bit to 0 (assume data)
    P2OUT &=  ~BIT3;
    //*/
 
    return;
}
 

void SPI_Init(){
    TRISB6 = 0;     // set RB6 == SPI_CLK as output
    TRISB4 = 0;     // set RB4 == SPI_SDI not used
    TRISC7 = 0;     // set RC7 == SPI_SDO as output
    TRISC6 = 0;     // set RC6 == SPI_SS as output
    
    ANSC6 = 0;      // Digital I/O
    ANSC7 = 0;
    
    PIR1bits.SSP1IF = 0;        // Clear interrupt flag
    PIE1bits.SSP1IE = 0;        // Disable MSSP interrupt
    //INTCONbits.PEIE = 0;      // Disable peripheral interrupts

    SSPCON1bits.SSPEN = 1;      // enables serial port
    SSPCON1bits.CKP = 1;        // Clock Polarity Select bit - idle state for clock is a high level
    SSPSTATbits.CKE = 1;        // SPI Clock Edge Select bit - transmit occurs on transition from ACTIVE to IDLE clock state
    SSPCON1bits.SSPM = 0b0010;  // Master mode, clock = FOSC/64
    SSPSTATbits.SMP = 1;        // input data sampled at end of data output time
}

void SPI_Write(char data){
    unsigned char TempVar;
    TempVar = SSP1BUF;              // Clear buffer by reading
    PIR1bits.SSP1IF = 0;            // Clear interrupt flag
    SSP1BUF = data;                 // write byte to SSP1BUF register
    while(!PIR1bits.SSP1IF);        // wait until bus cycle complete
}

unsigned char SPI_Read(void){
   SSPBUF = 0x00;                  // initiate bus cycle
   while ( !SSPSTATbits.BF );      // wait until cycle complete, Buffer Full Status bit
   return ( SSPBUF );              // return with byte read 
}

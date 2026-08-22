// CONFIG1L
#pragma config FEXTOSC = OFF                                                                        // External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_64MHZ                                                              // Power-up default value for COSC bits (HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1)

// CONFIG1H
#pragma config CLKOUTEN = OFF                                                                       // Clock Out Enable bit (CLKOUT function is disabled)
#pragma config CSWEN = ON                                                                           // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = OFF                                                                          // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31                                                                   // WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF                                                                           // WDT operating mode (WDT Disabled)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7                                                                    // WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC                                                                          // WDT input clock selector (Software Control)

#include <xc.h>
#include <string.h>

char data;

void UART_Init()
{
    ANSELDbits.ANSELD0 = 0;          //RDO - TX PIN DIGITAL
    ANSELDbits.ANSELD1 = 0;          //RD1 - RX PIN DIGITAL

    TRISDbits.TRISD0 = 0;            //OUTPUT EUSART2 TX
    TRISDbits.TRISD1 = 1;            //INPUT EUSART2 RX

    //DEFINING RECEVIER 

    RD0PPS = 0x0B;                   //EUSART2 (TX/CK)           
    RX2PPS = 0x19;                   // PORT AND PIN OF RX  0x0F
    //to achieve the desired baud rate
    SP2BRGL = 103;
    SP2BRGH = 0;
    
    BAUD2CONbits.BRG16 = 0;
    TX2STAbits.BRGH = 0;

    //enable RX
    RC2STAbits.SPEN = 1;
    TX2STAbits.TXEN = 1;
    RC2STAbits.CREN = 1;      
}


void UART()
{   
    while(1)
    {
        while(!PIR3bits.RC2IF); 
        data = RC2REG;
        while(!TX2STAbits.TRMT);
        TX2REG = data;
    }
}

void main()
{
    UART_Init();
    UART();   
    while(1)
    {
        ;
    }
    
}

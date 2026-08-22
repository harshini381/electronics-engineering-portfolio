// CONFIG1L
#pragma config FEXTOSC = OFF    // External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_64MHZ// Power-up default value for COSC bits (HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1)

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // Master Clear Enable bit (MCLR pin (RE3) is MCLR)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power up timer disabled)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (Low power BOR is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled)

// CONFIG2H
#pragma config BORV = VBOR_190  // Brown Out Reset Voltage selection bits (Brown-out Reset Voltage (VBOR) set to 1.90V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

#include <xc.h>
#include <string.h>

//TX UART
void UART_Init()
{
    ANSELDbits.ANSELD0 = 0;          //RDO - TX PIN DIGITAL
    ANSELDbits.ANSELD1 = 0;          //RD1 - RX PIN DIGITAL

    TRISDbits.TRISD0 = 0;            //INPUT EUSART2 TX
    TRISDbits.TRISD1 = 1;            //OUTPUT EUSART2 RX

    //DEFINING RECEVIER 
    
    RD0PPS = 0x0B;                   //EUSART2 (TX/CK)           
    RX2PPS = 0x19;                   // PORT AND PIN OF RX
    //to achieve the desired baud rate
    SP2BRGL = 103;
    SP2BRGH = 0;
    // TO ENABLE THE TX MODE
    BAUD2CONbits.BRG16 = 0;
    TX2STAbits.BRGH = 0;

    RC2STAbits.SPEN = 1;
    TX2STAbits.TXEN = 1;
}
//LOGIC OF SENDING DATA
void UART(char *data)
{
    while(*data)
    {
        while(!TX2STAbits.TRMT);
        TX2REG = *data++;
    }
}

//MAIN
void main()
{
    UART_Init();
    
    UART("Hello ");
    
    while(1)
    {
    ;
    }
}
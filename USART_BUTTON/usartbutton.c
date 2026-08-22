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

#define MAX 10
char buffer[MAX];
char i = 0;
char count = 0;
char flag = 0;

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

void UARTbutton(char data)
{
    while(!TX2STAbits.TRMT);
    TX2REG = data;
}

void main()
{
    UART_Init();
   
     // button
    TRISEbits.TRISE2 = 1;         //input
    ANSELEbits.ANSELE2 = 0;       // Digital 
    WPUEbits.WPUE2 = 1;          // enable weak pull-up
    
    while(1)
    {
        if(PIR3bits.RC2IF)
        {
            char c = RC2REG;
            
            
            if(c == '\n') 
            {
                buffer[i] = '\0';                
                if (strcmp(buffer, "start") == 0)
                {
                    flag = 1;  
                }
                else if(strcmp(buffer, "stop") == 0)
                {
                    flag = 0;
                    count = 0;
                }
                i = 0;
            }
            else
            {
                if(i < MAX-1) 
                {
                    buffer[i++] = c;
                }
            }
        }
        if(flag == 1) 
        {
            if (PORTEbits.RE2 == 0) 
            {
                count++;
                UARTbutton(count);
                while(PORTEbits.RE2 == 0); 
            }    
        }
    }
}
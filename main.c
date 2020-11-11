
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital input, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 10000000 // 1 instruction cycle = 400ns

#include <xc.h>


void main(void) {
    // Set led pin as output
    TRISB0 = 0;
    
    // Enable USART
    TRISB1 = 1;
    TRISB2 = 1;
    SPBRG = 10;
    TXSTA = 0b00101100;
    RCSTA = 0b10000000;
    

    unsigned char c = 0x20;
    
     
   while (1) {
        RB0 = 1;
        __delay_ms(100);
        RB0 = 0;
        __delay_ms(100);
        TXREG = c;
        if(++c == 0x7f) c = 0x20;
    }
}

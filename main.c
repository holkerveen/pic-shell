
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


#include <xc.h>
#include <string.h>
#include <stdlib.h>

#include "prompt.h"
#include "serial.h"
#include "config.h"

_Bool streq(char *a, char *b) {
    return stricmp(a,b)== 0;
}


char mem[MEM_SIZE][LINE_LENGTH+1];

void main(void) {

    // Set led pin as output
    TRISB3 = 0;
    
    // Enable USART
    TRISB1 = 1;
    TRISB2 = 1;
    SPBRG = 10;
    TXSTA = 0b00100100;
    RCSTA = 0b10010000;
    
    memset(mem, 0, MEM_SIZE * (LINE_LENGTH+1));
    
    serialStr("\r\n");
    while (1) {
        char *line = prompt("PicShell> ");

//        serialStr("Rx: ");
//        writeLine(line);
        
        char *cmd = strtok(line," ");
        
        // Light control
        if(streq("light", cmd)) {
            char *mode = strtok(NULL," ");
            if(streq("on",mode)) RB3 = 1;
            else if(streq("off",mode)) RB3 = 0;
            else if(streq("toggle",mode)) RB3 = !RB3;
            else writeLine("Unknown parameter");
        }
        
        // Read from memory
        else if(streq("read", cmd)) {
            char *istr = strtok(NULL, " ");
            char i = (char)atoi(istr);
            if(i > 0 && i <= MEM_SIZE) {
                writeLine(mem[i-1]);
            }
        }
        
        // Write to memory
        else if (streq("write", cmd)) {
            char *istr = strtok(NULL, " ");
            char i = (char)atoi(istr);
            if(i > 0 && i <= MEM_SIZE) {
                char *data = strtok(NULL, NULL);
                strcpy(mem[i-1], data);
            }
        }
        
        // Command unknown
        else {
            writeLine("Unknown command");
        }

    }
}


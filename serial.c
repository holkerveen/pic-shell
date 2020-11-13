#include "serial.h"

#include <xc.h>

void serialChr(char chr) {
    while(!TXIF);
    TXREG = chr;
}

void serialStr(char str[]) {
    for(int i=0; str[i]!=0; i++)
        serialChr(str[i]);
}

void writeLine(char str[]) {
    serialStr(str);
    serialStr("\r\n");
}

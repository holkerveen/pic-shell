#include "prompt.h"

#include <string.h>
#include <xc.h>

#include "config.h"

char *prompt(char msg[]) {
    serialStr(msg);
    static char buf[PROMPT_BUFFER_LENGTH + 1];
    memset(buf,0,sizeof buf);
    char len = 0;
    
    while(1) {       
        if(RCIF) {
            if(OERR) {
                TXREG = 'E';
                CREN = 0;
                CREN = 1;
            }
            else if(FERR) {
                RCREG;
                serialStr("FERR");
            }
            char chr = RCREG;
            
            if(chr == '\r') {
                serialStr("\r\n");
                return buf;
            }
            if(chr >= 0x20 || chr < 0x7f) {
                if(strlen(buf) >= PROMPT_BUFFER_LENGTH) {
                    continue;
                }
                buf[len++] = chr;
                serialChr(chr);
            }
            // @todo multiple backspaces not working yet somehow
            if(chr == 0x7 && len > 0) {
                buf[--len] = 0;
            }            
        }
    }
};
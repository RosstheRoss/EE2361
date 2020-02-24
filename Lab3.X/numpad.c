#include "xc.h"
void initKeyPad(void) {
    TRISA = 0b0000000000011111;  //set port A to inputs, 
    LATA = 0x0000;               //Set all of port A to LOW
    CNPU1bits.CN11PUE = 1;
    CNPU1bits.CN12PUE = 1;
    CNPU1bits.CN13PUE = 1;
    CNPU1bits.CN14PUE = 1;
}
void padDelay(long n) {
    for (n=n; n>0; n--) {
            asm("nop");
        }
}
//  1   2   3   4   5       6       7       8
//  RA0 RA1 RA2 RA3 RB15    RB14    RB13    RB12
char readKeyPadRAW(void) {
    int i; 
    char num;
    num = '\0'
    LATB |= (0b1111 << 12);
    padDelay(5);
    for (i = 0; i < 4; i++) {
        LATB ^= 0b1 << (15 - i);
        padDelay(10);
        switch (i) {
            case 0:
                switch (num) {
                    case 0b1110:
                        return 'A';
                        break;
                    case 0b1101:
                        return '3';
                        break;
                    case 0b1011:
                        return '2';
                        break;
                    case 0b111:
                        return '1';
                        break;
                } break;
            case 1:
                switch (num) {
                    case 0b1110:
                        return 'b';
                        break;
                    case 0b1101:
                        return '6';
                        break;
                    case 0b1011:
                        return '5';
                        break;
                    case 0b111:
                        return '4';
                        break;
                } break;
            case 2:
                switch (num) {
                    case 0b1110:
                        return 'C';
                        break;
                    case 0b1101:
                        return '9';
                        break;
                    case 0b1011:
                        return '8';
                        break;
                    case 0b111:
                        return '7';
                        break;
                } break;
            case 3:
                switch (num) {
                    case 0b1110:
                        return 'd';
                        break;
                    case 0b1101:
                        return 'E';
                        break;
                    case 0b1011:
                        return '0';
                        break;
                    case 0b111:
                        return 'F';
                        break;
                } break;
        }   //END switch(i);
        LATB |= (0b1111 << 12);
    }
    return '\0';
}
/*
Outputs<8:5> = 0b0111;  // Set Row 1 output Low
delay(1us);             // this delay could be lower, probably 2-3 cycles
RowOne = Inputs<4:1>;   // returns 0b1111 (no buttons pressed in row 1)

Outputs<8:5> = 0b1011;  // Set Row 2 output Low
delay(1us);
RowTwo = Inputs<4:1>;   // returns 0b1101 (the ?6? key was pressed!)
...
Outputs<8:5> = 0b1110;  // Set Row 4 output Low
delay(1us);
RowFour = Inputs<4:1>;  // returns 0b1111 (no buttons pressed in row 4)

 */
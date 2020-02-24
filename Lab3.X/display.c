#include "xc.h"
#include "display.h"
//Functions used for Display

void init7seg(void) { 
    TRISB = 0b0000000000000011;  //and port B to outputs
    LATB = 0x0000;               //and all of port B to LOW
}

void showChar7seg(char myChar, enum DIGIT myDigit) {
    LATB &= 0x00;
    switch (myChar) {
        case '0':
            LATB ^= (0b11 << 2);
            break;
        case '1':
            LATB ^= (0b10011111 << 2);
            break;
        case '2':
            LATB ^= (0b00100101 << 2);
            break;
        case '3':
            LATB ^= (0b1101 << 2);
            break;
        case '4':
            LATB ^= (0b10011001 << 2);
            break;
        case '5':
            LATB ^= (0b1001001 << 2);
            break;
        case '6':
            LATB ^= (0b1000001 << 2);
            break;
        case '7':
            LATB ^= (0b11111 << 2);
            break;
        case '8':
            LATB ^= (0b1 << 2);
            break;
        case '9':
            LATB ^= (0b1001 << 2);
            break;
        case 'A':
            LATB ^= (0b10001 << 2);
            break;
        case 'b':
            LATB ^= (0b11000001 << 2);
            break;
        case 'C':
            LATB ^= (0b01100011 << 2);
            break;
        case 'd':
            LATB ^= (0b10000101 << 2);
            break;
        case 'E':
            LATB ^= (0b01100001 << 2);
            break;
        case 'F':
            LATB ^= (0b01110001 << 2);
            break;
        default:
            LATB ^= (0b11111111 << 2);
            break;
    }   //END OF SWITCH
    LATB |= myDigit;
}
#include "xc.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void init7seg(void);
void showChar7seg(char myChar, int myDigit);
//where myChar is the character being displayed
//where myDigit indicates LEFT (1) or RIGHT (0)


void setup(void) {
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    init7seg();
}

void init7seg(void) {
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0b0000000000011111;  //set port A to inputs, 
    TRISB = 0b0000000000000011;  //and port B to outputs
    LATA = 0x0000;               //Set all of port A to LOW
    LATB = 0xF000;               //and all of port B to LOW
}

int main(void) {
    setup();
    LATB |= (0b01 << 10);
    LATB ^= (0b001111111);
    while (1) {
        
    }
}

void showChar7seg(char myChar, int myDigit) {
    LATB |= 0xFF;
    switch (myChar) {
        case '0':
            LATB ^= (0b11 << 2);
            break;
        case '1':
            LATB ^= (0b11 << 6);
            break;
        case '2':
            //
            break;
        case '3':
            //
            break;
        case '4':
            //
            break;
        case '5':
            //
            break;
        case '6':
            //
            break;
        case '7':
            LATB ^= (0b001111110);
            break;
        case '8':
            //
            break;
        case '9':
            //
            break;
        case 'A':
            //
            break;
        case 'b':
            //
            break;
        case 'C':
            //
            break;
        case 'd':
            //
            break;
        case 'E':
            //
            break;
        case 'F':
            //
            break;
        default:
            break;
    }   //END OF SWITCH
    if (myDigit == 0) {
        //0 = left
        LATB ^= (0b10 << 10);
    } else if (myDigit == 1) {
        //0 = right
        LATB ^= (0b01 << 10);
    }
    
}
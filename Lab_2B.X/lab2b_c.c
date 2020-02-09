#include "xc.h"
#include "lab2b_header.h"
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
#define PERIOD 5


void setup(void) {
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;
    TRISA = 0b1111111111111110;
    TRISB = 0x0000;  
    wait_100us();
}
void writeColor(int r, int g, int b);
void loop(void);

int main(void) {
    setup();
    wait_100us();   
    loop();
    return 0;
}

void writeColor(int r, int g, int b) {
    int i = 0;
    LATA = 0x0000;
    wait_100us();
    while (i < 8) {
        if (r & 1) {
            write_1();
        } else {
            write_0();
        }
        r >> 1;
        ++i;
    }
    while (i > 0) {
        if (g & 1) {
            write_1();
        } else {
            write_0();
        }
        g >> 1; 
        --i;
    }
    while (i < 8){
        if (b & 1) {
            write_1();
        } else {
            write_0();
        }
        b >> 1;
        ++i;
    }
}

void loop(void) {
 while (1) {
//     LATA = 0x0000;
//     wait_100us();
//     
//     //RED
//     write_1();
//     write_1();
//     write_1();
//     write_1();
//     
//     write_1();
//     write_1();
//     write_1();
//     write_1();
//     
//     //GREEN
//     write_1();
//     write_0();
//     write_0();
//     write_1();
//     
//     write_1();
//     write_0();
//     write_1();
//     write_1();
//     
//     //BLUE
//     write_0();
//     write_0();
//     write_0();
//     write_0();
//     
//     write_0();
//     write_0();
//     write_0();
//     write_0();
     
    writeColor(255, 155, 0);
 }
}
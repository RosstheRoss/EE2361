#include "xc.h"
#include "display.h"
#include "numpad.h"
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

void delay(long n) {
    for (n = n; n > 0; n--) {
        asm("nop");
    }
}

void setup(void) {
    CLKDIVbits.RCDIV = 0; //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
    //    T1CON = 0;    
    //    PR1 = 15999;    
    //    TMR1 = 0;    
    //    IFS0bits.T1IF = 0;    
    //    T1CONbits.TON = 1;
    init7seg();
    initKeyPad();
}

int main(void) {
    setup();
    char right, left, temp;
    unsigned long debounce = 0;
    while (1) {
        if (debounce % 300 == 0)
            temp = readKeyPadRAW();
        else
            temp = '\0';
        if (temp != '\0') {
            left = right;
            right = temp;
        }
        showChar7seg(right, MSB);
        delay(200);
        showChar7seg(left, LSB);
        delay(200);
        debounce++;
    }
}



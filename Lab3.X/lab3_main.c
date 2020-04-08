#include "xc.h"
#include "numpad.h"
#include "display.h"

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

#define NOKEY 255

void delay(long d) {
    for (d=d; d > 0; d--) {
        asm("nop");
    }
}



//============================================================================//

int main(void) {
    init7seg();
    initKeyPad();
    char key='N';
    char right, left;
    int debounce=250;
    //RB<9:2> will drive the cathodes of the seven-segment display
    //RB<11:10> will drive the right and left anodes respectively
    //RA<3:0> will drive inputs of keypad
    //RB<15:12> will cycle to sense RA inputs
    while(1)
    {
        if (debounce==0)
        {
            key=cycle();
            if (key!='N')
            {
                left=right;
                right=key;
            }
            debounce=250;
        }
        showChar7seg(right,0);
        delay(500);
        showChar7seg(left,1);
        delay(200);
        debounce--;
        while (!IFS0bits.T1IF) ;    
        IFS0bits.T1IF = 0;
    }
}
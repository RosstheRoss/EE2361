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
char cycle();


//============================================================================//

int main(void) {
    init7seg();
    initKeyPad();
    char key = 'N';
    char right, left;
    int debounce = 250;
    //RB<9:2> will drive the cathodes of the seven-segment display
    //RB<11:10> will drive the right and left anodes respectively
    //RA<3:0> will drive inputs of keypad
    //RB<15:12> will cycle to sense RA inputs
    while (1) {
        if (debounce == 0) {
            key = cycle();
            if (key != 'N') {
                left = right;
                right = key;
            }
            debounce = 250;
        }
        
        showChar7seg(right, MSB);
        delay(500);
        showChar7seg(left, LSB);
        delay(200);
        
        debounce--;
//        while (!IFS0bits.T1IF);
//        IFS0bits.T1IF = 0;
    }
}

//============================================================================//


//void test7seg(void) {
//    long int wait = 500000;
//    showChar7seg('1', 0);
//    delay(wait);
//    showChar7seg('1', 1);
//    delay(wait);
//    showChar7seg('2', 0);
//    delay(wait);
//    showChar7seg('2', 1);
//    delay(wait);
//    showChar7seg('3', 0);
//    delay(wait);
//    showChar7seg('3', 1);
//    delay(wait);
//    showChar7seg('4', 0);
//    delay(wait);
//    showChar7seg('4', 1);
//    delay(wait);
//    showChar7seg('5', 0);
//    delay(wait);
//    showChar7seg('5', 1);
//    delay(wait);
//    showChar7seg('6', 0);
//    delay(wait);
//    showChar7seg('6', 1);
//    delay(wait);
//    showChar7seg('7', 0);
//    delay(wait);
//    showChar7seg('7', 1);
//    delay(wait);
//    showChar7seg('8', 0);
//    delay(wait);
//    showChar7seg('8', 1);
//    delay(wait);
//    showChar7seg('9', 0);
//    delay(wait);
//    showChar7seg('9', 1);
//    delay(wait);
//    showChar7seg('0', 0);
//    delay(wait);
//    showChar7seg('0', 1);
//    delay(wait);
//    showChar7seg('A', 0);
//    delay(wait);
//    showChar7seg('A', 1);
//    delay(wait);
//    showChar7seg('b', 0);
//    delay(wait);
//    showChar7seg('b', 1);
//    delay(wait);
//    showChar7seg('C', 0);
//    delay(wait);
//    showChar7seg('C', 1);
//    delay(wait);
//    showChar7seg('d', 0);
//    delay(wait);
//    showChar7seg('d', 1);
//    delay(wait);
//    showChar7seg('E', 0);
//    delay(wait);
//    showChar7seg('E', 1);
//    delay(wait);
//    showChar7seg('F', 0);
//    delay(wait);
//    showChar7seg('F', 1);
//    delay(wait);
//    return;
//}

//void showChar7seg(char myChar, int myDigit) {
//    //1,2,3,4,5,6,7,8,9,0,A,b,C,d,E, and F
//    LATB &= 0xF000;
//    if (myDigit == 1) {
//        if (myChar == '1') {
//            LATB |= 0x067F;
//        } else if (myChar == '2') {
//            LATB |= 0x0497;
//        } else if (myChar == '3') {
//            LATB |= 0x0437;
//        } else if (myChar == '4') {
//            LATB |= 0x0667;
//        } else if (myChar == '5') {
//            LATB |= 0x0527;
//        } else if (myChar == '6') {
//            LATB |= 0x0507;
//        } else if (myChar == '7') {
//            LATB |= 0x047F;
//        } else if (myChar == '8') {
//            LATB |= 0x0407;
//        } else if (myChar == '9') {
//            LATB |= 0x0427;
//        } else if (myChar == '0') {
//            LATB |= 0x040F;
//        } else if (myChar == 'A') {
//            LATB |= 0x0447;
//        } else if (myChar == 'b') {
//            LATB |= 0x0707;
//        } else if (myChar == 'C') {
//            LATB |= 0x058F;
//        } else if (myChar == 'd') {
//            LATB |= 0x0617;
//        } else if (myChar == 'E') {
//            LATB |= 0x0587;
//        } else if (myChar == 'F') {
//            LATB |= 0x05C7;
//        }
//    } else if (myDigit == 0) {
//        if (myChar == '1') {
//            LATB |= 0x0A7F;
//        } else if (myChar == '2') {
//            LATB |= 0x0897;
//        } else if (myChar == '3') {
//            LATB |= 0x0837;
//        } else if (myChar == '4') {
//            LATB |= 0x0A67;
//        } else if (myChar == '5') {
//            LATB |= 0x0927;
//        } else if (myChar == '6') {
//            LATB |= 0x0907;
//        } else if (myChar == '7') {
//            LATB |= 0x087F;
//        } else if (myChar == '8') {
//            LATB |= 0x0807;
//        } else if (myChar == '9') {
//            LATB |= 0x0827;
//        } else if (myChar == '0') {
//            LATB |= 0x080F;
//        } else if (myChar == 'A') {
//            LATB |= 0x0847;
//        } else if (myChar == 'b') {
//            LATB |= 0x0B07;
//        } else if (myChar == 'C') {
//            LATB |= 0x098F;
//        } else if (myChar == 'd') {
//            LATB |= 0x0A17;
//        } else if (myChar == 'E') {
//            LATB |= 0x0987;
//        } else if (myChar == 'F') {
//            LATB |= 0x09C7;
//        }
//    }
//    return;
//}



char cycle() {
    int i = 0;
    char key = 'N';
    while (i < 4) {
        if (i == 0) {
            LATBbits.LATB12 = 0;
            LATBbits.LATB13 = 1;
            LATBbits.LATB14 = 1;
            LATBbits.LATB15 = 1;
        } else if (i == 1) {
            LATBbits.LATB12 = 1;
            LATBbits.LATB13 = 0;
            LATBbits.LATB14 = 1;
            LATBbits.LATB15 = 1;
        } else if (i == 2) {
            LATBbits.LATB12 = 1;
            LATBbits.LATB13 = 1;
            LATBbits.LATB14 = 0;
            LATBbits.LATB15 = 1;
        } else if (i == 3) {
            LATBbits.LATB12 = 1;
            LATBbits.LATB13 = 1;
            LATBbits.LATB14 = 1;
            LATBbits.LATB15 = 0;
        }
        key = readKeyPadRAW();
        if (key != 'N') {
            return key;
        }
        i++;
    }
    return key;
}
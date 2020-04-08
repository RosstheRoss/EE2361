#include "xc.h"
#include "lab2b_header.h"
#include "stdint.h"
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
#define PERIOD 30

//DEFINTIONS
void writeColor(int r, int g, int b);
void loop(void);
void delay(int delay_in_ms);
uint32_t packColor(unsigned char Red, unsigned char Grn, unsigned char Blu);
unsigned char getR(uint32_t RGBval);
unsigned char getG(uint32_t RGBval);
unsigned char getB(uint32_t RGBval);
void writePacCol(uint32_t PackedColor);
uint32_t Wheel(unsigned char WheelPos);

void setup(void) {
    CLKDIVbits.RCDIV = 0;  //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff;
    TRISA = 0b1111111111111110;
    TRISB = 0x0000;  
    wait_1ms();
}

int main(void) {
    setup();
    wait_100us();   
    loop();
    return 0;
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
/*
    writeColor(255, 155, 000);
*/
     int byteFrameNumber = 0;
     while (byteFrameNumber <= 255) {
//       // COLOR GRADIENT
//       writeColor(byteFrameNumber, 0 , 255 - byteFrameNumber);
         
         //COLOR WHEEL
         writePacCol(Wheel(byteFrameNumber));
         delay(PERIOD);
         byteFrameNumber++;
     }
 }
}

void writeColor(int r, int g, int b) {
    write_0();
    wait_100us();
    int i;
    for(i = 7; i >= 0; i--) {
	r & (1 << i) ? write_1() : write_0();
    }
    for(i = 7; i >= 0; i--) {
	g & (1 << i) ? write_1() : write_0();
    }
    for(i = 7; i >= 0; i--) {
	b & (1 << i) ? write_1() : write_0();
    }
}

void delay(int delay_in_ms) {
    int i;
    for (i = 0; i < delay_in_ms; i++) {
        wait_1ms();
    }
}

uint32_t packColor(unsigned char Red, unsigned char Grn, unsigned char Blu) {
    return ((long) Red << 16) | ((long) Grn << 8) | ((long) Blu);
}

unsigned char getR(uint32_t RGBval) {
    return (unsigned char) (RGBval >> 16);
}
unsigned char getG(uint32_t RGBval) {
    return (unsigned char) (RGBval >> 8 );
}
unsigned char getB(uint32_t RGBval) {
    return (unsigned char) (RGBval >> 0 );
}

void writePacCol(uint32_t PackedColor) {
    writeColor(getR(PackedColor), getG(PackedColor), getB(PackedColor));
}

uint32_t Wheel(unsigned char WheelPos) {
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return packColor(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return packColor(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return packColor(WheelPos * 3, 255 - WheelPos * 3, 0);
}
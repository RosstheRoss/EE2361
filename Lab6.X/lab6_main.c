#include "xc.h"
#include "../Lab5.X/lab5_lcd.h"
#include "circBuffer.h"
#include <stdio.h>

#pragma config ICS = PGx1 // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)

// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,
                                // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void) {
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff; //all digital inputs and outputs
    initBuffer();
    lcd_init();
    lcd_setCursor(0,0);
    
    // -- I2C STUFF --
    I2C2BRG = 0x9D;
    I2C2CONbits.I2CEN = 1;
    _I2CSIDL = 0;
    IFS3bits.MI2C2IF=0;
    
    // -- ADC STUFF --
    AD1CON1 = 0;    // set all control to 0.
    AD1CON1bits.SSRC = 0b010;  //Rollover to conversion
    AD1CON1bits.ASAM = 1; // auto-sample
    AD1CON1bits.FORM = 0b00;
    AD1CON2 = 0;
    AD1CON2bits.CSCNA = 0; // no scan
    AD1CON2bits.SMPI = 0b0; // every conversion
    AD1CON2bits.BUFM = 0;  // two 8-word buffers
    AD1CON3bits.ADCS = 0b1;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 0b1;
    AD1CON1bits.ADON = 1; // ton
    AD1CHS = 0;
    AD1CHSbits.CH0NB = 0;
    AD1CHSbits.CH0SB = 0;
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SA = 0;
    
    // -- TIMER 2 STUFF -- 
    T2CON = 0;
    TMR2 = 0;
    T2CONbits.TCKPS = 0b10;
    PR2 = 25000;
    T2CONbits.TON = 1;
    
    // -- TIMER 3 STUFF --
    T3CON = 0;
    TMR3 = 0;
    T3CONbits.TCKPS = 0b10;
    PR3 = 1562;
    T3CONbits.TON = 1;
    
    // -- INTERRUPT ENABLES --
    IEC0bits.AD1IE = 1;
    IFS0bits.AD1IF = 0;
    //ADC Interrupt (Enabled)
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;
    // T2 Interrupt (Enabled)
}

volatile unsigned int *ADCpointer = &ADC1BUF0, ADCvalue = 0;
void __attribute__((__interrupt__, __auto_psv__)) _ADC1Interrupt(void) {
    IFS0bits.AD1IF = 0;
    
    
}
volatile unsigned char flag = 0;
void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(void) {
    //Allow writing to LCD
    _T2IF = 0;
    TMR2 = 0;
    flag = 1;
}

int main(void) {
    setup();
    while (1) {
        char adStr[20];
        unsigned long adValue;
        if (flag) {
            flag = 0;
            lcd_setCursor(0,0);
            adValue = getAvg();
            sprintf(adStr, "%6.4f V", (3.3/1024)*adValue);
            lcd_printStr(adStr);
        }
    }
    return -1;
}

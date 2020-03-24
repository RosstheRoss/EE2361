#include "xc.h"
#include "lab4_button.h"

void initPushButton(){
    //Configure Timer 2 (500ns / count, 25ms max).
    // note that resolution = 500ns = 8 x 62.5ns, max period = 25ms = Tcy * 8 * 50,000
    T2CONbits.TON = 0;
    T2CONbits.TCKPS = 0b11;
    T2CONbits.TCS = 0b0;
    T2CONbits.TGATE = 0b0;
    TMR2 = 0;
    PR2 = 0xf424; // Set period to be larger than max external sig duration
    T2CONbits.TON = 1; // Start 16-bit Timer2
    
    // Initialize the Input Capture Module
    IC1CONbits.ICTMR = 1; // Select Timer2 as the IC1 Time base
    IC1CONbits.ICI = 0b00; // Interrupt on every capture event
    IC1CONbits.ICM = 0b011; // Generate capture event on every Rising edge
    // Enable Capture Interrupt And Timer2
    
    IPC0bits.IC1IP = 1; // Setup IC1 interrupt priority level
    IFS0bits.IC1IF = 0; // Clear IC1 Interrupt Status Flag
    IEC0bits.IC1IE = 1; // Enable IC1 interrupt
    
    IFS0bits.T2IF = 1;
    IEC0bits.T2IE = 1;
}

volatile unsigned long overflow = 0;
//Timer 2 overflow interrupt
//Each overflow is one second
void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void) {
    _T2IF = 0;
    overflow++;
}

volatile long int curPeriod=0;  
//IC1 interrupt
void __attribute__((__interrupt__,__auto_psv__)) _IC1Interrupt(void) { 
   static unsigned int prevEdge=0;
   int curEdge;

   _IC1IF = 0;
   curEdge = IC1BUF + 62500L * overflow;
   curPeriod = curEdge - prevEdge;
   prevEdge = curEdge;
}

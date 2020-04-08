#include "xc.h"
#include "lab4_button.h"
#define circBuffSize 2

void initPushButton(){
    //Configure Timer 2 (500ns / count, 25ms max).
    // note that resolution = 500ns = 8 x 62.5ns, max period = 25ms = Tcy * 8 * 50,000
    T2CONbits.TON = 0;
    T2CONbits.TCKPS = 0b11;
    T2CONbits.TCS = 0b0;
    T2CONbits.TGATE = 0b0;
    TMR2 = 0;
    PR2 = 62500; // Set period to be larger than max external sig duration
    T2CONbits.TON = 1; // Start 16-bit Timer2
    
    // Initialize the Input Capture Module
    IC1CON = 0; // Turn off and reset internal state of IC1
    IC1CONbits.ICTMR = 1; // Use Timer 2 for capture source
    IC1CONbits.ICM = 0b011; // Turn on and capture every rising edge
    IC1CON = 1;

    _IC1IF = 0; // Clear IC1 Interrupt Status Flag
    _IC1IE = 1; // Enable IC1 interrupt
    
    _T2IF = 1;
    _T2IE = 1;
} 

volatile unsigned long overflow = 0;
//Timer 2 overflow interrupt
//Each overflow is one second
void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void) {
    _T2IF = 0;
    overflow++;
}

//Buffer functions
volatile unsigned long buffer[circBuffSize];
int buffSize = 0, write = 0, read = 0;
void addBuffer(unsigned long x) {
    if (buffSize < circBuffSize) {
          buffer[write++] = x;
          write %= circBuffSize;
          ++buffSize;
    }
    //Otherwise get rid of the data.
}
unsigned long getBuffer() {
    unsigned long returnValue = buffer[read++];
    read %= circBuffSize;
    --buffSize;
    return returnValue;
}
int emptyBuffer(void) {
    if (buffSize <= 0) {
        buffSize=0;
        return 1;
    } else {
        return 0;
    }
}

volatile unsigned long curPeriod = 0, prevPress = 0, currPress = 0;
//IC1 interrupt
void __attribute__((__interrupt__,__auto_psv__)) _IC1Interrupt(void) { 
   _IC1IF = 0;
   unsigned int time;
   currPress = (IC1BUF + 62500 * (long) overflow);
   curPeriod = currPress - prevPress;
   time = curPeriod / 62.5;
   if (time > 10) {
       addBuffer(time);
   }
   prevPress = currPress;
}
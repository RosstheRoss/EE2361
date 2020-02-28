#include "xc.h"

void initKeyPad(void) {
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
    TRISA = 0b0000000000011111; //set port A to inputs, 
    TRISB = 0b0000000000000011; //and port B to outputs
    LATA = 0xFFFF; //Set all of port A to HIGH
    LATB = 0xF000; //Set RB12-15 to high, no touch rest of RB
    CNPU1bits.CN2PUE = 1; //RA0
    CNPU1bits.CN3PUE = 1; //RA1
    CNPU2bits.CN30PUE = 1; //RA2
    CNPU2bits.CN29PUE = 1; //RA3
//    T1CON = 0;
//    PR1 = 15999;
//    TMR1 = 0;
//    IFS0bits.T1IF = 0;
//    T1CONbits.TON = 1;
}

void padDelay(long n) {
    for (n = n; n > 0; n--) {
        asm("nop");
    }
}
//  1   2   3   4   5       6       7       8
//  RA0 RA1 RA2 RA3 RB15    RB14    RB13    RB12

char readKeyPadRAW(void) {
    if ((PORTAbits.RA0 || LATBbits.LATB12) == 0) {
        return 'A';
    } else if ((PORTAbits.RA1 || LATBbits.LATB12) == 0) {
        return '3';
    } else if ((PORTAbits.RA2 || LATBbits.LATB12) == 0) {
        return '2';
    } else if ((PORTAbits.RA3 || LATBbits.LATB12) == 0) {
        return '1';
    } else if ((PORTAbits.RA0 || LATBbits.LATB13) == 0) {
        return 'b';
    } else if ((PORTAbits.RA1 || LATBbits.LATB13) == 0) {
        return '6';
    } else if ((PORTAbits.RA2 || LATBbits.LATB13) == 0) {
        return '5';
    } else if ((PORTAbits.RA3 || LATBbits.LATB13) == 0) {
        return '4';
    } else if ((PORTAbits.RA0 || LATBbits.LATB14) == 0) {
        return 'C';
    } else if ((PORTAbits.RA1 || LATBbits.LATB14) == 0) {
        return '9';
    } else if ((PORTAbits.RA2 || LATBbits.LATB14) == 0) {
        return '8';
    } else if ((PORTAbits.RA3 || LATBbits.LATB14) == 0) {
        return '7';
    } else if ((PORTAbits.RA0 || LATBbits.LATB15) == 0) {
        return 'd';
    } else if ((PORTAbits.RA1 || LATBbits.LATB15) == 0) {
        return 'F';
    } else if ((PORTAbits.RA2 || LATBbits.LATB15) == 0) {
        return '0';
    } else if ((PORTAbits.RA3 || LATBbits.LATB15) == 0) {
        return 'E';
    } else {
        return 'N';
    }
}

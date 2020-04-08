#include "xc.h"
#include "lab4_servo.h"
void setServo(int Val)
{
    OC1RS=Val;
}
void initServo() {
    TRISB &= 1111111111011111;
    //TIMER 3
    T3CON = 0x0010; //Stop Timer, Tcy clk source, PRE 1:8
    T3CONbits.TCKPS = 0b01;
    T3CONbits.TCS=0;
    TMR3 = 0;     // Initialize to zero
    PR3 = 39999; // Set period in order to make 20ms cycle
    T3CONbits.TON = 1;
    
    //OC1
    OC1CON = 0;
    OC1R = 1234;   // servo start position. We won?t touch OC1R again
    OC1RS = 1234;  // We will only change this once PWM is turned on
    OC1CONbits.OCM = 0b110;
    OC1CONbits.OCTSEL = 1;
}

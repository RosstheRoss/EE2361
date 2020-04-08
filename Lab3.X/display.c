#include "xc.h"
#include "display.h"
//Functions used for Display

void init7seg(void) {
    CLKDIVbits.RCDIV = 0; //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
    TRISA = 0b0000000000011111; //set port A to inputs, 
    TRISB = 0b0000000000000011; //and port B to outputs
    LATA = 0x0000; //Set all of port A to LOW
    LATB = 0x0000; //and all of port B to LOW
}

void showChar7seg(char myChar, int myDigit)
{
    //1,2,3,4,5,6,7,8,9,0,A,b,C,d,E, and F
    LATB&=0xF000;
    if (myDigit==1)
    {
        if (myChar=='1'){LATB|=0x067F;}
        else if (myChar=='2'){LATB|=0x0497;}
        else if (myChar=='3'){LATB|=0x0437;}
        else if (myChar=='4'){LATB|=0x0667;}
        else if (myChar=='5'){LATB|=0x0527;}
        else if (myChar=='6'){LATB|=0x0507;}
        else if (myChar=='7'){LATB|=0x047F;}
        else if (myChar=='8'){LATB|=0x0407;}
        else if (myChar=='9'){LATB|=0x0427;}
        else if (myChar=='0'){LATB|=0x040F;}
        else if (myChar=='A'){LATB|=0x0447;}
        else if (myChar=='b'){LATB|=0x0707;}
        else if (myChar=='C'){LATB|=0x058F;}
        else if (myChar=='d'){LATB|=0x0617;}
        else if (myChar=='E'){LATB|=0x0587;}
        else if (myChar=='F'){LATB|=0x05C7;}
    }
    else if (myDigit==0)
    {
        if (myChar=='1'){LATB|=0x0A7F;}
        else if (myChar=='2'){LATB|=0x0897;}
        else if (myChar=='3'){LATB|=0x0837;}
        else if (myChar=='4'){LATB|=0x0A67;}
        else if (myChar=='5'){LATB|=0x0927;}
        else if (myChar=='6'){LATB|=0x0907;}
        else if (myChar=='7'){LATB|=0x087F;}
        else if (myChar=='8'){LATB|=0x0807;}
        else if (myChar=='9'){LATB|=0x0827;}
        else if (myChar=='0'){LATB|=0x080F;}
        else if (myChar=='A'){LATB|=0x0847;}
        else if (myChar=='b'){LATB|=0x0B07;}
        else if (myChar=='C'){LATB|=0x098F;}
        else if (myChar=='d'){LATB|=0x0A17;}
        else if (myChar=='E'){LATB|=0x0987;}
        else if (myChar=='F'){LATB|=0x09C7;}
    }
    return;
}
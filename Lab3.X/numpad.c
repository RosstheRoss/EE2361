#include "xc.h"
void initKeyPad(void) {
    TRISA = 0b0000000000011111;  //set port A to inputs, 
    LATA = 0x0000;               //Set all of port A to LOW
    CNPU1bits.CN11PUE = 1;
    CNPU1bits.CN12PUE = 1;
    CNPU1bits.CN13PUE = 1;
    CNPU1bits.CN14PUE = 1;
}

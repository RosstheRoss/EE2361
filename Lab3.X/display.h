#ifndef DISPLAY_H
#define	DISPLAY_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // Insert declarations

    enum DIGIT {
        MSB = (0b1 << 11),
        LSB = (0b1 << 10)
    };
    void init7seg(void);
    void showChar7seg(char myChar, int myDigit);
    void delay(long num);

#ifdef	__cplusplus
}
#endif
#endif
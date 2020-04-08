#ifndef LAB4_SERVO_H
#define	LAB4_SERVO_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    void delay(long n);
    void initServo(void);
    void setServo(int Val);
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */


#ifndef LAB4_BUTTON_H
#define	LAB4_BUTTON_H

#include <xc.h> // include processor files - each processor file is guarded.  


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    void initPushButton(void);
    void addBuffer(unsigned long x);
    unsigned long getBuffer();
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* LAB4_BUTTON_H */


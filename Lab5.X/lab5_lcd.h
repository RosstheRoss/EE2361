#ifndef LCD_HEADER
#define	LCD_HEADER

#include <xc.h> // include processor files - each processor file is guarded.  
#ifdef	__cplusplus
extern "C" {
#endif
    void lcd_cmd(char command);
    void lcd_init(void);
    void lcd_setCursor(char x, char y);
    void lcd_printChar(char myChar);
    void lcd_printStr(const char s[]);
#ifdef	__cplusplus
}
#endif
#endif


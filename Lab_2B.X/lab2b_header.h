#ifndef LAB2B_ASM
#define LAB2B_ASM

#ifdef	__cplusplus
extern "C" {
#endif
    void wait_100us(void);
    void wait_1ms(void);
    void write_0(void);
    void write_1(void);
    //DEFINTIONS
    void writeColor(int r, int g, int b);
    void loop(void);
    void delay(int delay_in_ms);
    uint32_t packColor(unsigned char Red, unsigned char Grn, unsigned char Blu);
    unsigned char getR(uint32_t RGBval);
    unsigned char getG(uint32_t RGBval);
    unsigned char getB(uint32_t RGBval);
    void writePacCol(uint32_t PackedColor);
    uint32_t Wheel(unsigned char WheelPos);
#ifdef	__cplusplus
}
#endif

#endif	/* LAB2B_ASM */
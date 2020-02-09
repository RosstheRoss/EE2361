
.include "xc.inc"          ; required "boiler-plate" (BP)

;the next two lines set up the actual chip for operation - required
config __CONFIG2, POSCMOD_EC & I2C1SEL_SEC & IOL1WAY_OFF & OSCIOFNC_ON & FCKSM_CSECME & FNOSC_FRCPLL & SOSCSEL_LPSOSC & WUTSEL_FST & IESO_OFF
config __CONFIG1, WDTPS_PS1 & FWPSA_PR32 & WINDIS_OFF & FWDTEN_OFF & BKBUG_ON & GWRP_ON & GCP_ON & JTAGEN_OFF

    .bss        ; put the following labels in RAM
counter:
    .space 2    ; a variable that takes two bytes (we won?t use
                ; it for now, but put here to make this a generic
                ; template to be used later).
stack:
    .space  32  ; this will be our stack area, needed for func calls

.text           ; BP (put the following data in ROM(program memory))

;because we are using the C compiler to assemble our code, we need a "_main" label
;somewhere. (There's a link step that looks for it.)
.global _main               ;BP
;your functions go here

_main:

    bclr    CLKDIV,#8                 ;BP
    nop
    ;; --- Begin your main program below here ---
    
    
    mov     #0x9fff,w0  
    mov     w0,AD1PCFG            ; Set all pins to digital mode
    mov     #0b1111111111111110,w0  
    mov     w0,TRISA            ; set pin RA0 to output
    mov     #0x0000,w0  
    mov     w0,LATA            ; set pin RA0 low
    call delay_100us
    call setColor
    call foreverLoop
   
wait_24cycles:
                     ; 2 cycles for function call
    repeat #17        ; 1 cycle to load and prep
    nop              ; 17+1 cycles to execute NOP 18 times
    return           ; 3 cycles for the return
    
wait_32cycles: ; 2
    repeat #24 ; 1
    nop	       ; 25+1 cycles = 26
    return     ; 3
    
delay_100us:
    repeat #1593
    nop
    return
    
delay_1ms:
    repeat #15993
    nop
    return
    
write_bit_stream:
    call    wait_24cycles     ; 24 cycles
    clr     LATA              ; set pin RA0 low = 1 cycle
    call    wait_32cycles     ; 32 cycles
    inc    LATA               ; set pin RA0 high = 1 cycle
    return

write_0:      ;2 cycles for function call
    inc LATA  ;1
    repeat #3 ;1 for load
    nop	      ;3+1=4 nop
    clr LATA  ;1
    repeat #6 ;1 for load
    nop       ;1+6=7 nop
    return    ;3 return
    
    
write_1:      ;2 cycle call
    inc LATA  ;1
    repeat #10;1 load
    nop	      ;1+10=11 nop
    clr LATA  ;1
    nop       ;1
    return    ;3 return
    
setColor:
    ;Set R
    call write_1
    call write_1
    call write_1
    call write_1
    call write_1
    call write_1
    call write_1
    call write_1
    ;Set G
    call write_1
    call write_0
    call write_0
    call write_1
    call write_1
    call write_0
    call write_1
    call write_1
    ;Set B
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    call write_0
    
    return
    
foreverLoop:
;   call write_bit_stream
    nop
    bra foreverLoop
    

.end 

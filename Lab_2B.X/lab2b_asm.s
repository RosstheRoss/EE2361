.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.
.global _write_0, _write_1, _wait_100us, _wait_1ms
    
_delay_100us:
    repeat #1593
    nop
    return
    
_delay_1ms:
    repeat #15993
    nop
    return
 
_write_0:      ;2 cycles for function call
    inc LATA  ;1
    repeat #3 ;1 for load
    nop	      ;3+1=4 nop
    clr LATA  ;1
    repeat #6 ;1 for load
    nop       ;1+6=7 nop
    return    ;3 return
    
    
_write_1:      ;2 cycle call
    inc LATA  ;1
    repeat #10;1 load
    nop	      ;1+10=11 nop
    clr LATA  ;1
    nop       ;1
    return    ;3 return
    
.globl _start

_start:
    mov sp,#0x8000
    mov x3, #0x800000 //0b1 0000 0000 0000 000 0000 0000
    MSR VBAR_EL1, x3
    bl main

.func enable_irq
    /*Enable irq */
.endfunc

.func irq_handler
    /* Save register
    call subroutine
    restore register */
.endfunc

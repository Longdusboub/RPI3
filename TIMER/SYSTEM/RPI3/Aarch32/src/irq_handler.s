.extern interrupts_handler

exception_vector:
    b _start
    b undefined_handler
    b svc_handler
    b prefetch_handler
    b abort_handler
    NOP
    b irq_handler

irq_handler:
    ;@srsdb sp!, #0x12
    push {r0-r12, lr}
    bl interrupts_handler
    pop {r0-r12, lr}
    ;@CPSIE I
    ;@rfeia sp!
    subs pc, lr, #4

undefined_handler:
    b undefined_handler

svc_handler:
    mov sp, #0x2800
    movs pc, lr

prefetch_handler:
    b prefetch_handler

abort_handler:
    b abort_handler

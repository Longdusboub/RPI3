.global _start
_start:
    CPSID I
    mov sp, #0x8000
    mov r6, #0x10000
    mcr p15, 0, r6, c12, c0, 0 ;@ Set VBAR
    bl init_jtag

SVC:
    MRS r0, cpsr
    bic r0, r0, #0x1F
    orr r0, r0, #0x13
    msr spsr_cxfs, r0
    add r6, pc, #4
    msr elr_hyp, r6
    eret

irq_stack:
    mrs r0, cpsr
    bic r0, r0, #0x1F
    orr r0, r0, #0x12
    msr cpsr_cxfs, r0
    mov sp, #0x3000

    orr r0, r0, #0x13
    msr cpsr_cxfs, r0

    mov sp, #0x3000
    bl main
    b .


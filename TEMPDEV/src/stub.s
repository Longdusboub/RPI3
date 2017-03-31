.global _start
_start:
    MRC p15, 0, r0, c0, c0, 5
    AND r0, #0x000F
    CMP r0, #0x0
    BEQ master_boot
    B	slave_boot

readbox: .word 0x400000CC
freq: .word 19200000 /* 19.2 Mhz */

slave_boot:
    LDR r5, readbox
wait_loop:
    LDR r1, [r5, r0, lsl #4]
    CMP r1, #0
    BEQ wait_loop
    STR r1, [r5, r0, lsl #4]
    MOV sp, #0x2000
    BX r1

master_boot:
    /* Set up stack pointer and jtag */
    MOV sp, #0x3000
    BL init_jtag

    /* Enable data and instruction cache */
    MRC p15, 0, r0, c1, c0, 0
    ORR r0, r0, #0x4
    ORR r0, r0, #0x1000
    MCR p15, 0, r0, c1, c0, 0

    /* Enable SMP */
    MRRC p15, 1, r0, r1, c15
    ORR r0, r0, #0x80
    MCRR p15, 1, r0, r1, c15

    /* Enable CNTV *.
    MOV r0, #0x1
    MCR p15, 0, r0, c14, c3, 1

    /* Set CNT freq to 19.2 Mhz */
    LDR r1, freq
    MCR p15, 0, r1, c14, c0, 0

    /* Disable IRQ */
    CPSID I

    /* Set VBAR */
    MOV r6, #0x1000
    MCR p15, 0, r6, c12, c0, 0

    /* Set MVBAR */
    MCR p15, 0, r6, c12, c0, 1

    /* Switch to irq mode */
    MRS r0, cpsr
    BIC r0, r0, #0x1F
    ORR r0, r0, #0x12
    MSR cpsr_cxfs, r0

    /* Set irq stack pointer */
    MOV sp, #0x3800

    /* Switch to abort mode */
    BIC r0, r0, #0x1F
    ORR r0, r0, #0x17
    MSR cpsr_cxfs, r0

    /* Set abort mode stack pointer */
    MOV sp, #0x2800

    /* Get back to svc mode */
    BIC r0, r0, #0x1F
    ORR r0, r0, #0x13
    MSR cpsr_cxfs, r0

    BL main

    smc #0

    /* Enable IRQ */
    CPSIE I

    /* Wait */
    B .

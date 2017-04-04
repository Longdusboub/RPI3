.global _start
_start:
    MRC p15, 0, r0, c0, c0, 5
    AND r0, #0x000F
    CMP r0, #0x0
    BEQ master_boot
    B	slave_boot

readbox: .word 0x400000CC /* Mailbox 3 */
freq: .word 19200000 /* 19.2 Mhz */

/* Cores 1-2-3 wait for addr to jump from core 0
   Then execute the core located at the specified addr
   Then go back here and continues to wait for instruction
   This is fun every sentence is longer than the previous one */
slave_boot:
    LDR lr,=rearm_loop
    MOV r2, #0x2000
    MOV r3, #0x400
    MUL r4, r3, r0
    ADD r4, r4, r2
    MOV sp, r4
rearm_loop:
    MRC p15, 0, r0, c0, c0, 5
    AND r0, #0x000F
    LDR r5, readbox
wait_loop:
    LDR r1, [r5, r0, lsl #4]
    CMP r1, #0
    BEQ wait_loop
    STR r1, [r5, r0, lsl #4]
    BX r1


/* Core 0 boot
   => Set sp of different mode
   => Set irq vector
   => enable irq
   => init jtag
   => Some black magic
   => ?????
   => Profit */

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
    MOV sp, #0x3400

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

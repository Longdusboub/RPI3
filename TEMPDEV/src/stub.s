.global _start

/* Variable declaration */
readbox: .word 0x400000CC /* Mailbox 3 */
freq: .word 19200000 /* 19.2 Mhz */

/* Core boot
   => Set sp of different mode
   => Set irq vector
   => enable irq
   => init jtag
   => Some black magic
   => ?????
   => Profit */

_start:
    /* Get core ID */
    MRC p15, 0, r4, c0, c0, 5
    AND r4, #0x000F

    /* Get sp base address for current core */
    MOV r3, #0x8400
    MOV r2, #0x1000
    MUL r1, r2, r4
    ADD r3, r3, r1 

    /* Set base SP */
    MOV sp, r3

    /* Only core 0 init JTAG */
    CMP r4, #0x0
    BNE no_jtag
    PUSH {r3}
    BL init_jtag
    POP {r3}
no_jtag:

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
    ADD r3, #0x400
    MOV sp, r3

    /* Switch to abort mode */
    BIC r0, r0, #0x1F
    ORR r0, r0, #0x17
    MSR cpsr_cxfs, r0

    /* Set abort mode stack pointer */
    ADD r3, #0x400
    MOV sp, r3

    /* Get back to svc mode */
    BIC r0, r0, #0x1F
    ORR r0, r0, #0x13
    MSR cpsr_cxfs, r0


    CMP r4, #0x0
    BEQ master_boot
    B	slave_boot

master_boot:
    BL main
    B .



/* Cores 1-2-3 wait for addr to jump from core 0
   Then execute the core located at the specified addr
   Then go back here and continues to wait for instruction
   This is fun every sentence is longer than the previous one */
slave_boot:
    LDR lr,=rearm_loop
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

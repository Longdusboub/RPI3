OUTPUT_ARCH(arm)

MEMORY
{
	/* Trusted RAM */       ram      : org = 0x00008000, len = 0x00040000
	/* Irq handler */	irq	 : org = 0x00010000, len = 0x00001000
}

ENTRY(_start)

SECTIONS
{
    .irqhandler :
    {
	. = ALIGN(4);
	irq_handler.o(.text*)
	. = ALIGN(4);
    } > irq

    .text :
    {
	. = ALIGN(4);
	*(.text*)
	. = ALIGN(4);
    } > ram

    .bss :
    {
	. = ALIGN(4);
	*(.bss*)
	. = ALIGN(4);
    } > ram
}


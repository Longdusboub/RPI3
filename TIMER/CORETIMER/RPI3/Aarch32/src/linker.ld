
MEMORY
{
	/* Armstub     */	ars      : org = 0x00000000, len = 0x00000200
	/* Trusted RAM */       ram      : org = 0x00008000, len = 0x00040000
}

ENTRY(_start)

SECTIONS
{
    .boot :
    {
	. = ALIGN(4);
	stub.o(.text*)
	. = ALIGN(4);
    } > ars

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


/*
 * Authors : Alexandre "Dargor" Meunier
 * Descritption : Header for BCM2836-7 local timer management
 */

#define LT_BASE_ADDRESS	0x40000000

#define LT_CONTROL	LT_BASE_ADDRESS + 0x34
#define LT_RESET	LT_BASE_ADDRESS + 0x38
#define LT_INTERRUPT	LT_BASE_ADDRESS + 0x24

/*typedef union test
{
	int;
	struct bitfieldss
	{
		unsigned toto :32;
	}
} test_t; */

// Interrupt routing
#define IRQ_CPU0 0b000
#define IRQ_CPU1 0b001
#define IRQ_CPU2 0b010
#define IRQ_CPU3 0b011
#define FIQ_CPU0 0b100
#define FIQ_CPU1 0b101
#define FIQ_CPU2 0b110
#define FIQ_CPU3 0b111

#define TRY(X)	((X == 1) ? LT_CONTROL : (X == 2) ? LT_RESET : LT_INTERRUPT)

/* Local Timer Control register */

#define CAST_LT_CONTROL		(*(volatile int *)TRY(1))
#define INT_LT_CONTROL		(((CAST_LT_CONTROL) >> 31) & 1)
#define LT_ENABLE_IRQ		((CAST_LT_CONTROL)|=(1 << 29))
#define LT_ENABLE		((CAST_LT_CONTROL) |= (1 << 28))
#define LT_CLR_RELOAD		((CAST_LT_CONTROL) &= (0xF0000000))
#define LT_SET_RELOAD(V)	((CAST_LT_CONTROL) |= (V))

/* Local Timer Reset and clear register */

#define CAST_LT_RESET		(*(volatile int *)TRY(2))
#define LT_RESET_FLAGS		(CAST_LT_RESET = (0x80000000))
#define LT_RELOAD_TIMER		(CAST_LT_RESET = (0x40000000))
#define LT_RESET_ALL		(CAST_LT_RESET = (0xC0000000))

/* Local Timer interrupt routing register */

#define CAST_LT_INTERRUPT	(*(volatile int *)TRY(3))
#define LT_ROUTING_IRQ(V)	(CAST_LT_INTERRUPT = V)

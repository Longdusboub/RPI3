/*
 * Authors : Alexandre "Dargor" Meunier
 * Descritption : Header for BCM2836-7 local timer management
 */

#ifndef _LOCALTIMER_H_
 #define _LOCALTIMER_H_

#define LT_FREQ		38400000
#define LT_FREQ_MS	38400

#define LT_BASE_ADDRESS	0x40000000

#define LT_CONTROL_REG		(LT_BASE_ADDRESS + 0x34)
#define LT_RESET_REG		(LT_BASE_ADDRESS + 0x38)
#define LT_IRQ_ROUTING_REG	(LT_BASE_ADDRESS + 0x24)

#define LT_GET_REG(R)	    (*(int *)(R))
#define LT_SET_REG(R, V)    (*(int *)(R)) = (V)

// Interrupt routing
#define IRQ_CPU0 0b000
#define IRQ_CPU1 0b001
#define IRQ_CPU2 0b010
#define IRQ_CPU3 0b011
#define FIQ_CPU0 0b100
#define FIQ_CPU1 0b101
#define FIQ_CPU2 0b110
#define FIQ_CPU3 0b111


/* Local Timer Control register */

#define LT_IRQ			31
#define LT_ENABLE_IRQ	    	(1 << 29)
#define LT_ENABLE		(1 << 28)

/* Local Timer Reset and clear register */

#define LT_RESET_IRQ		(1 << 31)
#define LT_RELOAD		(1 << 30)

#endif /* _LOCALTIMER_H_ */

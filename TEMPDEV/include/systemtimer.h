/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Header for bcm2837 system timer
 * Sources : BCM2835 peripheral documentation
 */

#ifndef _SYSTEMTIMER_H_
 #define _SYSTEMTIMER_H_

#define ST_BASE_ADDRESS		0x3F003000

#define ST_CS_REG		ST_BASE_ADDRESS + 0x0	// System timer control register
#define ST_CLO_REG		ST_BASE_ADDRESS + 0x4	// 32 Less significant bits of the free running counter
#define ST_CHI_REG		ST_BASE_ADDRESS + 0x8	// 32 most significant bits of the free running counter
#define ST_C0_REG		ST_BASE_ADDRESS + 0xC	// Compare register 0
#define ST_C1_REG		ST_BASE_ADDRESS + 0x10	// Compare register 1
#define ST_C2_REG		ST_BASE_ADDRESS + 0x14	// Compare register 2
#define ST_C3_REG		ST_BASE_ADDRESS + 0x18	// Compare register 3

#define ST_SET_REG(R, V)	(*(unsigned int *)(R)) = (V)
#define ST_GET_REG(R)		(*(unsigned int *)(R))

#define ST_GET_COMPARE(X)	(X == 0 ? ST_C0_REG : X == 1 ? ST_C1_REG : X == 2 ? ST_C2_REG : ST_C3_REG)

#define ST_IRQ0			0x1
#define ST_IRQ1			0x2
#define ST_IRQ2			0x4
#define ST_IRQ3			0x8

#define ST_US			1
#define ST_MS			1000
#define ST_S			1000000

void st_set_timer(unsigned int value, unsigned int unit, unsigned int compare);
void st_clear_irq(unsigned int irq);

#endif /* _SYSTEMTIMER_H_ */

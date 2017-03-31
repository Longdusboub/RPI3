/*
 * Authors : Alexandre "Dargor" Meunier
 * Description : Useful macro for bcm2836/7 Aarch32bit
 * Last modification : 30/03/2017
 */

#ifndef _UTILS_H_
 #define _UTILS_H_

int cpu_id(void)
{
	register unsigned int ret asm("r0");
	asm("MRC p15, 0, r0, c0, c0, 5");
	asm("AND r0, #0x000F");
	return ret;
}

#define SET_REG(R, V)	(*(int *)(R)) = (V)
#define GET_REG(R)	(*(int *)(R))

#endif /* _UTILS_H_ */

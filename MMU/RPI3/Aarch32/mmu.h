/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Headers for raspberry pi 3 armv7 MMU
 */

#ifndef _MMU_H_
 #define _MMU_H_

#define MMU_BASE    0x00004000

/* Flags */
#define P   (1 << 9)
#define XN  (1 << 4) //Exceute never flag.
#define C   (1 << 3)
#define B   (1 << 2)


void set_mmu(void);

#endif /* _MMU_H_ */

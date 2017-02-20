/*
 * : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Descriptions : Utils functions for Raspberry pi 3 Mini Uart	
 */
 
#include "uart.h"
 
extern void PUTREG ( unsigned int, unsigned int );
extern unsigned int GETREG ( unsigned int );
 
 


int put_char(char c)
{
	while(1)
        {
            if(GETREG(AUX_MU_STAT_REG)&0x100) break;
        }

		PUTREG(AUX_MU_IO_REG, c);
		return 1;
}
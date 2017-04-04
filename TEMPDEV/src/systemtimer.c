/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : C file for bcm2837 system timer
 * Sources : BCM2835 peripheral documentation
 */

#include "systemtimer.h"

void st_set_timer(unsigned int value, unsigned int unit, unsigned int compare)
{
	unsigned int counter = value * unit;
	unsigned int low32 = ST_GET_REG(ST_CLO_REG);
	counter += low32;
	ST_SET_REG(ST_GET_COMPARE(compare), counter);
}

void st_clear_irq(unsigned int irq)
{
	ST_SET_REG(ST_CS_REG, irq);
}

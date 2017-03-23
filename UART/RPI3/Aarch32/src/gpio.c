/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Descriptions : Function to manipulate Raspberry pi 3 GPIO
 */

#include "../include/gpio.h"

#define ERR	-1


void gpio_set_mode(int pin, int mode)
{
	int shift = (pin % 10) * 3;
	int reg;

	reg= FSEL_GET_VALUE(pin / 10);
	reg&= ~(7 << shift);
	reg|= mode << shift;
	FSEL_SET_VALUE(pin / 10, reg);
}

int gpio_get_mode(int pin)
{
	int mask = 7 << ((pin % 10) * 3);

	return (FSEL_GET_VALUE(pin / 10) & mask) << ((pin % 10) * 3);
}

void gpio_set_high(int pin)
{
	int reg = 1 << (pin % 32);
	SET_SET_VALUE(pin / 32, reg);
}

void gpio_set_low(int pin)
{
	int reg = 1 << (pin % 32);
	CLR_SET_VALUE(pin / 32, reg);
}

int gpio_get_level(int pin)
{
	return (LEV_GET_VALUE(pin / 32) >> pin) & 1;
}

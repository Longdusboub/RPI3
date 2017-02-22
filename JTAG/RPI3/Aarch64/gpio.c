/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Descriptions : Function to manipulate Raspberry pi 3 GPIO
 */

#include "gpio.h"

#define ERR	-1


static int check_pin(int pin)
{
	return (pin < 0 || pin > 53) ? 0 : 1;
}

int gpio_set_mode(int pin, int mode)
{
	if (!check_pin(pin))
		return ERR;
	if ((mode < 0)| (mode > 7))
		return ERR;

	int shift = (pin % 10) * 3;
	int reg;

	reg= FSEL_GET_VALUE(pin / 10);
	reg&= ~(7 << shift);
	reg|= mode << shift;
	FSEL_SET_VALUE(pin / 10, reg);
	return 1;
}

int gpio_get_mode(int pin)
{
	if (!check_pin(pin))
		return ERR;

	int mask = 7 << ((pin % 10) * 3);

	return (FSEL_GET_VALUE(pin / 10) & mask) << ((pin % 10) * 3);
}

int gpio_set_high(int pin)
{
	if (!check_pin(pin))
		return ERR;

	int reg = SET_GET_VALUE(pin / 32);

	reg|=1 << (pin % 32);
	SET_SET_VALUE(pin / 32, reg);
	return 1;
}

int gpio_set_low(int pin)
{
	if (!check_pin(pin))
		return ERR;

	int reg = CLR_GET_VALUE(pin / 32);

	reg|=1 << (pin % 32);
	CLR_SET_VALUE(pin / 32, reg);
	return 1;
}

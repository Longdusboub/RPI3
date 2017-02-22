/*
 * Authors : Alexandre "Dargor" Meunier <alexandre.meunier@epita.fr>
 * Description : Simple LED blinking baremetal exemple for Raspberry pi 3
 */

#include "gpio.c"


int blink(void)
{
	int toto = 0;
	while(1)
	{
		gpio_set_high(6);
		for (toto = 0; toto < 100000; toto++)
			toto = toto;
		gpio_set_low(6);
		for (toto = 0; toto < 100000; toto++)
			toto = toto;
	}
	return 0;
}

int main( void )
{
	gpio_set_mode(6, 1);
	blink();
	return(0);
}

/*
 * Authors : Alexandre "Dargor" Meunier <alexandre.meunier@epita.fr>
 * Description : Simple led blinking bare metal exemple for raspberry pi 3
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
	gpio_set_mode(6, GPIO_FUNCTION_OUT);
	blink();
	return(0);
}

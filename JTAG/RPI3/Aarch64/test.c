/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple jtag init for raspberry pi 3
 */

#include "gpio.c"
#include "localtimer.c"

void switchLED(void)
{
	if (gpio_get_level(21) == 1)
		gpio_set_low(21);
	else
		gpio_set_high(21);
	local_timer_reset(2);
}

void init_jtag(void)
{
	gpio_set_mode(4, GPIO_FUNCTION_ALT5);
	gpio_set_mode(22, GPIO_FUNCTION_ALT4);
	gpio_set_mode(23, GPIO_FUNCTION_ALT4);
	gpio_set_mode(24, GPIO_FUNCTION_ALT4);
	gpio_set_mode(25, GPIO_FUNCTION_ALT4);
	gpio_set_mode(27, GPIO_FUNCTION_ALT4);
	gpio_set_high(21);
}



int main( void )
{
	gpio_set_mode(21, GPIO_FUNCTION_OUT);
	init_jtag();
	local_timer_init(0x000FFFFF);
	while (1) if (local_timer_interrupt() == 1)
	{
		switchLED();
	}
	return(0);
}



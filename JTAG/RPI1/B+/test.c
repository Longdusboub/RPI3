/*
 * Authors : Alexandre "Dargor" Meunier <alexandre.meunier@epita.fr>
 * Description : Simple JTAG initialization for raspberry pi B+
 */

#include "gpio.c"

static int init_jtag(void)
{
	gpio_set_mode(4, GPIO_FUNCTION_ALT5);
	gpio_set_mode(22, GPIO_FUNCTION_ALT4);
	gpio_set_mode(23, GPIO_FUNCTION_ALT4);
	gpio_set_mode(24, GPIO_FUNCTION_ALT4);
	gpio_set_mode(25, GPIO_FUNCTION_ALT4);
	gpio_set_mode(27, GPIO_FUNCTION_ALT4);
	gpio_set_high(21);
	return 0;
}

int main( void )
{
	gpio_set_mode(21, GPIO_FUNCTION_OUT);
	init_jtag();
	while (1) continue;
	return(0);
}

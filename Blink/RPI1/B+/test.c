
#include "gpio.c"


int blink(void)
{
	int toto = 0;
	while(1)
	{
		gpio_set_high(6);
		for (toto = 0; toto < 1000000; toto++)
			toto = toto;
		gpio_set_low(6);
		for (toto = 0; toto < 1000000; toto++)
			toto = toto;
	}
	return 0;
}

int init_jtag(void)
{
	gpio_set_mode(4, GPIO_FUNCTION_ALT5);
	gpio_set_mode(22, GPIO_FUNCTION_ALT4);
	gpio_set_mode(23, GPIO_FUNCTION_ALT4);
	gpio_set_mode(24, GPIO_FUNCTION_ALT4);
	gpio_set_mode(25, GPIO_FUNCTION_ALT4);
	gpio_set_mode(27, GPIO_FUNCTION_ALT4);
	gpio_set_high(16);
	return 0;
}

int main( void )
{
	gpio_set_mode(16, GPIO_FUNCTION_OUT);
	gpio_set_mode(6, GPIO_FUNCTION_OUT);

	if (init_jtag() != 0)
		return 1;
	blink();
	return(0);
}

//TODO : Init uart

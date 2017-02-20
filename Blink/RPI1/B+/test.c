
#include "gpio.c"


int blink(void)
{
	int toto = 0;
	while(1)
    {
        write_output_set_register(6, 1);
		for (toto = 0; toto < 1000000; toto++)
			toto = toto;
		write_output_clear_register(6, 1);
		for (toto = 0; toto < 1000000; toto++)
			toto = toto;
    }
	return 0;
}

int init_jtag(void)
{
	write_function_selector_register(4, GPIO_FUNCTION_ALT5);
	write_function_selector_register(22, GPIO_FUNCTION_ALT4);
	write_function_selector_register(23, GPIO_FUNCTION_ALT4);
	write_function_selector_register(24, GPIO_FUNCTION_ALT4);
	write_function_selector_register(25, GPIO_FUNCTION_ALT4);
	write_function_selector_register(27, GPIO_FUNCTION_ALT4);
	write_output_set_register(16, 1);
	return 0;
}

int main( void )
{
	write_function_selector_register(16, 1);
	write_function_selector_register(6, 1);

	if (init_jtag() != 0)
		return 1;
	blink();
    return(0);
}

//TODO : Init uart

/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple mmu example for raspberry pi 3 Aarch32
 */

#include "gpio.c"
#include "mmu.c"

void init_jtag(void)
{
	gpio_set_mode(4, GPIO_FUNCTION_ALT5);
	gpio_set_mode(22, GPIO_FUNCTION_ALT4);
	gpio_set_mode(23, GPIO_FUNCTION_ALT4);
	gpio_set_mode(24, GPIO_FUNCTION_ALT4);
	gpio_set_mode(25, GPIO_FUNCTION_ALT4);
	gpio_set_mode(27, GPIO_FUNCTION_ALT4);
	gpio_set_mode(19, GPIO_FUNCTION_OUT);
	gpio_set_high(19);
}

int main(void)
{
	gpio_set_mode(6, GPIO_FUNCTION_OUT);
	gpio_set_mode(21, GPIO_FUNCTION_OUT);
	gpio_set_high(6);
	set_mmu();
	enable_mmu(0x4000, 0x1003);
	gpio_set_high(21);
	while(1) continue;
	return 0;
}



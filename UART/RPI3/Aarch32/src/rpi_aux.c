/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Simple uart management for raspberry pi 3
 */

#include "../include/rpi_aux.h"

void aux_mu_putchar(char x)
{
	while (AUX_MU_FIFO_TX_EMPTY == 0)
		continue;
	AUX_MU_SEND(x);
}

void aux_mu_putstring(char tab[])
{
	int i = 0;
	while (tab[i] != '\0')
		aux_mu_putchar(tab[i++]);
}

void aux_mu_puthex(unsigned int hex)
{
	aux_mu_putchar('0');
	aux_mu_putchar('x');
	int current;
	for (int i = 0; i < 8; i++)
	{
	    current = (hex & 0xF0000000) >> 28;
	    if (current > 9)
		    aux_mu_putchar(current + 0x37);
	    else
		    aux_mu_putchar(current + 0x30);
	    hex = hex << 4;
	}
}

void aux_mu_enable(int baudrate)
{
	AUX_DISABLE_MU;
	gpio_set_mode(14, GPIO_FUNCTION_ALT5);
	gpio_set_mode(15, GPIO_FUNCTION_ALT5);
	AUX_MU_CLEAR_FIFO;
	AUX_MU_8BIT;
	AUX_MU_ENABLE_TX;
	AUX_MU_SET_BAUDRATE(baudrate);
	AUX_ENABLE_MU;
}

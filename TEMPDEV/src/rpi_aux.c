/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Simple uart management for raspberry pi 3
 */

#include "../include/rpi_aux.h"

void aux_mu_putchar(char x)
{
	while (AUX_MU_FIFO_TX_EMPTY == 0)
		continue;
	AUX_SET_REG(AUX_MU_IO_REG, x);
}

void aux_mu_putstring(char tab[])
{
	int i = 0;
	while (tab[i] != '\0')
		aux_mu_putchar(tab[i++]);
}

char aux_mu_getchar(void)
{
	char temp = (AUX_GET_REG(AUX_MU_IO_REG) & 0xFF);
	aux_mu_putchar(temp); //ECHO FOR USER
	return temp;
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
	AUX_SET_REG(AUX_ENABLES, AUX_GET_REG(AUX_ENABLES) & ~(AUX_ENABLE_MU));
	gpio_set_mode(14, GPIO_FUNCTION_ALT5);
	gpio_set_mode(15, GPIO_FUNCTION_ALT5);
	AUX_SET_REG(AUX_MU_IIR_REG, AUX_MU_CLEAR_FIFO);
	AUX_SET_REG(AUX_MU_IER_REG, AUX_MU_ENABLE_TX_IRQ | AUX_MU_ENABLE_RX_IRQ);
	AUX_SET_REG(AUX_MU_LCR_REG, AUX_MU_8BIT);
	AUX_SET_REG(AUX_MU_CNTL_REG, AUX_MU_ENABLE_TX | AUX_MU_ENABLE_RX);
	AUX_SET_REG(AUX_MU_BAUD_REG, baudrate);
	AUX_SET_REG(AUX_ENABLES, (AUX_GET_REG(AUX_ENABLES) | AUX_ENABLE_MU));
}

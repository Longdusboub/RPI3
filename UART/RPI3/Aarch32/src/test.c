/*
 * Authors : Alexandre "Dargor" Meunier <meunie_f@epita.fr>
 * Description : simple jtag init for raspberry pi 3
 */

#include "gpio.c"
#include "rpi_aux.c"

int main(void)
{

	aux_mu_enable(3254);

	aux_mu_putstring("Hello World !\n");
	aux_mu_puthex(0xDEADBEEF);
	return(0);
}


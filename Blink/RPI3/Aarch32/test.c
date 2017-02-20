
#include "gpio.c"
#include "uart.c"


int blink(void)
{
	int toto = 0;
	while(1)
    {
        
		for (toto = 0; toto < 1000000; toto++)
			toto = toto;
		write_output_clear_register(19, 1);
		for (toto = 0; toto < 1000000; toto++)
			toto = toto;
    }
	return 0;
}

void init_jtag(void)
{
	write_function_selector_register(4, GPIO_FUNCTION_ALT5);
	write_function_selector_register(22, GPIO_FUNCTION_ALT4);
	write_function_selector_register(23, GPIO_FUNCTION_ALT4);
	write_function_selector_register(24, GPIO_FUNCTION_ALT4);
	write_function_selector_register(25, GPIO_FUNCTION_ALT4);
	write_function_selector_register(27, GPIO_FUNCTION_ALT4);
	
}



void printaddr(int addr)
{
	for (int i = 0; i < 8; i++)
	{
		int tmp = addr & 0xF;
		if (tmp < 10)
		{
			put_char(0x30 + tmp);
		}
		else
		{
			put_char(0x41 + tmp - 10);
		}
		addr = addr >> 4;
	}
}

void read_uart(void)
{
	while(1)
    {
        while(1)
        {
            if(GETREG(AUX_MU_LSR_REG)&0x40) break;
        }
        printaddr(0xABCDEF12);
    }
}

void init_uart(int baud, int uart, int mode)
{
	
	PUTREG(AUX_ENABLES,1);
	write_output_clear_register(21, 1);
    PUTREG(AUX_MU_IER_REG,0);
	write_output_clear_register(16, 1);
    PUTREG(AUX_MU_CNTL_REG,0);
    PUTREG(AUX_MU_LCR_REG,1);
    PUTREG(AUX_MU_MCR_REG,0);
    PUTREG(AUX_MU_IIR_REG,0xC6); //Enable and clear fifo buffer
    PUTREG(AUX_MU_BAUD_REG,270);
	
    write_function_selector_register(14, uart = 0 ? GPIO_FUNCTION_ALT0 : GPIO_FUNCTION_ALT5); 
	
	PUTREG(AUX_MU_CNTL_REG,mode);
	write_output_clear_register(19, 1);
}


int main( void )
{
	write_function_selector_register(16, 1);
	write_function_selector_register(21, 1);
	write_function_selector_register(19, 1);
	write_output_set_register(19, 1);
	write_output_set_register(16, 1);
	write_output_set_register(21, 1);
	init_jtag();
	
	//init_uart(476, 1, 2);	
	
	//read_uart();
	int toto = 1;
	while (1)
	{toto++;
	toto--;}
	blink();
    return(0);
}

//TODO : Init uart

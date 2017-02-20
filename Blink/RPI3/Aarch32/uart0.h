/*
 * : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Descriptions : Header for Raspberry pi 3 Mini Uart	
 */
#define BASE_ADDRESS	0x3F215000
 
/* AUXIRQ Register
	Used tu check if any pending interrupts.
	0 : No interrupts
	1 : Pending interrupts
	
	0 Mini uart IRQ
	1 SPI 1 IRQ
	2 SPI 2 IRQ */
	
#define AUX_IRQ			BASE_ADDRESS + 0x00

/* AUXENB Register
	Used to enables the 3 modules
	0 : Disable
	1 : Enable
	
	0 : Mini uart
	1 : SPI 1
	2 : SPI2 */
	
#define AUX_ENABLES		BASE_ADDRESS + 0x04


#define AUX_MU_IO_REG	BASE_ADDRESS + 0x40
#define AUX_MU_IER_REG	BASE_ADDRESS + 0x44
#define AUX_MU_IIR_REG	BASE_ADDRESS + 0x48
#define AUX_MU_LCR_REG	BASE_ADDRESS + 0x4C
#define AUX_MU_MCR_REG	BASE_ADDRESS + 0x50
#define AUX_MU_LSR_REG	BASE_ADDRESS + 0x54
#define AUX_MU_MSR_REG	BASE_ADDRESS + 0x58
#define AUX_MU_SCRATCH	BASE_ADDRESS + 0x5C
#define AUX_MU_CNTL_REG	BASE_ADDRESS + 0x60
#define AUX_MU_STAT_REG	BASE_ADDRESS + 0x64
#define AUX_MU_BAUD_REG	BASE_ADDRESS + 0x68

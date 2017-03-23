/*
 * Authors : Alexandre "dargor" Meunier <psychonaniste@gmail.com>
 * Description : Header for rpi auxilliary peripheral management
 */

#ifndef _RPI_AUX_H_
 #define _RPI_AUX_H_

#define AUX_BASE	    0x3F215000

#define AUX_IRQ		    AUX_BASE + 0x0
#define AUX_ENABLES	    AUX_BASE + 0x4
#define AUX_MU_IO_REG	    AUX_BASE + 0x40
#define AUX_MU_IER_REG	    AUX_BASE + 0x44
#define AUX_MU_IIR_REG	    AUX_BASE + 0x48
#define AUX_MU_LCR_REG	    AUX_BASE + 0x4C
#define AUX_MU_MCR_REG	    AUX_BASE + 0x50
#define AUX_MU_LSR_REG	    AUX_BASE + 0x54
#define AUX_MU_MSR_REG	    AUX_BASE + 0x58
#define AUX_MU_SCRATCH	    AUX_BASE + 0x5C
#define AUX_MU_CNTL_REG	    AUX_BASE + 0x60
#define AUX_MU_STAT_REG	    AUX_BASE + 0x64
#define AUX_MU_BAUD_REG	    AUX_BASE + 0x68


#define AUX_IRQ_MU		((*(int *)(AUX_IRQ)) >> 0) & 1
#define AUX_IRQ_SPI1		((*(int *)(AUX_IRQ)) >> 1) & 1
#define AUX_IRQ_SPI2		((*(int *)(AUX_IRQ)) >> 2) & 1

#define AUX_ENABLE_MU		*(int *)(AUX_ENABLES) |= 0x1
#define AUX_ENABLE_SPI1		*(int *)(AUX_ENABLES) |= 0x2
#define AUX_ENABLE_SPI2		*(int *)(AUX_ENABLES) |= 0x4

#define AUX_DISABLE_MU		*(int *)(AUX_ENABLES) &= 0x6
#define AUX_DISABLE_SPI1	*(int *)(AUX_ENABLES) &= 0x5
#define AUX_DISABLE_SPI2	*(int *)(AUX_ENABLES) &= 0x3

#define AUX_MU_SEND(X)		*(int *)(AUX_MU_IO_REG) = (X & 0xFF)
#define AUX_MU_RECEIVE(X)	(*(int *)(AUX_MU_IO_REG) & 0xFF)

#define AUX_MU_ENABLE_TX_IRQ	*(int *)(AUX_MU_IER_REG) |= 0x1
#define AUX_MU_ENABLE_RX_IRQ	*(int *)(AUX_MU_IER_REG) |= 0x2
#define AUX_MU_DISABLE_TX_IRQ	*(int *)(AUX_MU_IER_REG) &= 0x2
#define AUX_MU_DISABLE_RX_IRQ	*(int *)(AUX_MU_IER_REG) &= 0x1

#define AUX_MU_CLEAR_RX_FIFO	*(int *)(AUX_MU_IIR_REG) |= 0x2
#define AUX_MU_CLEAR_TX_FIFO	*(int *)(AUX_MU_IIR_REG) |= 0x4
#define AUX_MU_CLEAR_FIFO	*(int *)(AUX_MU_IIR_REG) |= 0x6

#define AUX_MU_7BIT		*(int *)(AUX_MU_LCR_REG) &= 0xFFFFFFFC
#define AUX_MU_8BIT		*(int *)(AUX_MU_LCR_REG) |= 0x3

#define AUX_MU_FIFO_TX_EMPTY	((*(int *)(AUX_MU_LSR_REG) >> 5) & 0x1)
#define AUX_MU_FIFO_TX_IDLE	((*(int *)(AUX_MU_LSR_REG) >> 6) & 0x1)
#define AUX_MU_FIFO_RX_READY	(*(int *)(AUX_MU_LSR_REG) & 0x1)

#define AUX_MU_ENABLE_TX	*(int *)(AUX_MU_CNTL_REG) |= 0x2
#define AUX_MU_ENABLE_RX	*(int *)(AUX_MU_CNTL_REG) |= 0x1
#define AUX_MU_DISABLE_TX	*(int *)(AUX_MU_CNTL_REG) &= 0xFFFFFFFD
#define AUX_MU_DISABLE_RX	*(int *)(AUX_MU_CNTL_REG) &= 0xFFFFFFFE

/* Baudregister can be obtained by this formula : baudreg = (250 000 000 / (8 * baudrate)) - 1 */
#define AUX_MU_SET_BAUDRATE(X)	*(int *)(AUX_MU_BAUD_REG) = X

#endif /* _RPI_AUX_H_ */

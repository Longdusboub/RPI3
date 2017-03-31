/*
 * Authors : Alexandre "dargor" Meunier <psychonaniste@gmail.com>
 * Description : Header for rpi auxilliary peripheral management
 * Source : See BCM2835 peripheral documentation
 */

#ifndef _RPI_AUX_H_
 #define _RPI_AUX_H_

#define AUX_BASE		0x3F215000

#define AUX_IRQ			(AUX_BASE + 0x0)
#define AUX_ENABLES		(AUX_BASE + 0x4)
#define AUX_MU_IO_REG		(AUX_BASE + 0x40)
#define AUX_MU_IER_REG		(AUX_BASE + 0x44)
#define AUX_MU_IIR_REG		(AUX_BASE + 0x48)
#define AUX_MU_LCR_REG	        (AUX_BASE + 0x4C)
#define AUX_MU_MCR_REG		(AUX_BASE + 0x50)
#define AUX_MU_LSR_REG		(AUX_BASE + 0x54)
#define AUX_MU_MSR_REG		(AUX_BASE + 0x58)
#define AUX_MU_SCRATCH		(AUX_BASE + 0x5C)
#define AUX_MU_CNTL_REG		(AUX_BASE + 0x60)
#define AUX_MU_STAT_REG		(AUX_BASE + 0x64)
#define AUX_MU_BAUD_REG		(AUX_BASE + 0x68)

#define AUX_SET_REG(R, V)	(*(int *)(R)) = (V)
#define AUX_GET_REG(R)		(*(int *)(R))

#define AUX_IRQ_MU		((*(int *)(AUX_IRQ)) >> 0) & 1
#define AUX_IRQ_SPI1		((*(int *)(AUX_IRQ)) >> 1) & 1
#define AUX_IRQ_SPI2		((*(int *)(AUX_IRQ)) >> 2) & 1

#define AUX_ENABLE_MU		0x1
#define AUX_ENABLE_SPI1		0x2
#define AUX_ENABLE_SPI2		0x4

#define AUX_DISABLE_MU		0x6
#define AUX_DISABLE_SPI1	0x5
#define AUX_DISABLE_SPI2	0x3

#define AUX_MU_SEND(X)		*(int *)(AUX_MU_IO_REG) = (X & 0xFF)
#define AUX_MU_RECEIVE		(*(int *)(AUX_MU_IO_REG) & 0xFF)

#define AUX_MU_ENABLE_TX_IRQ	0x1
#define AUX_MU_ENABLE_RX_IRQ	0x2

#define AUX_MU_NO_IRQ		0x0
#define AUX_MU_TX_EMPTY_IRQ	0x1
#define AUX_MU_RX_HOLD_BYTE_IRQ	0x2
#define AUX_MU_IMPOSSIBLE_IRQ	0x3

#define AUX_MU_IRQ_PENDING	~((*(int *)(AUX_MU_IER_REG)) & 1)
#define AUX_MU_IRQ_ID		(((*(int *)(AUX_MU_IER_REG)) & 0x6) >> 1)
#define AUX_MU_CLEAR_RX_FIFO	0x2
#define AUX_MU_CLEAR_TX_FIFO	0x4
#define AUX_MU_CLEAR_FIFO	0x6

#define AUX_MU_BREAK		0x40
#define AUX_MU_7BIT		0x0
#define AUX_MU_8BIT		0x3

#define AUX_MU_RTS_LOW		0x2

#define AUX_MU_FIFO_TX_EMPTY	((*(int *)(AUX_MU_LSR_REG) >> 5) & 0x1)
#define AUX_MU_FIFO_TX_IDLE	((*(int *)(AUX_MU_LSR_REG) >> 6) & 0x1)
#define AUX_MU_FIFO_RX_READY	(*(int *)(AUX_MU_LSR_REG) & 0x1)

#define AUX_MU_CTS_LOW		0x20
#define AUX_MU_GET_CTS		((*(int *)(AUX_MU_MSR_REG)) >> 5)

#define AUX_MU_CTS_ASSERT_LOW	0x80
#define AUX_MU_RTS_ASSERT_LOW	0x40
#define AUX_MU_RTS_AUTO_1	0x20
#define AUX_MU_RTS_AUTO_2	0x10
#define AUX_MU_RTS_AUTO_3	0x00
#define AUX_MU_RTS_AUTO_4	0x30
#define AUX_MU_ENABLE_CTS	0x8
#define AUX_MU_ENABLE_RTS	0x4


#define AUX_MU_ENABLE_TX	0x2
#define AUX_MU_ENABLE_RX	0x1

#endif /* _RPI_AUX_H_ */

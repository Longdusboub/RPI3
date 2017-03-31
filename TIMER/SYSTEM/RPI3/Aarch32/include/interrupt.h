/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Function for interrupt sources register for raspberry pi 3
 */

#ifndef _INTERRUPT_H_
 #define _INTERRUPT_H_

#define IRQ_GET_REG(R)	    (*(int *)(R))
#define IRQ_SET_REG(R, V)   (*(int *)(R)) = (V)

#define IRQ_SRC_CORE0	0x40000060
#define IRQ_SRC_CORE1	0x40000064
#define IRQ_SRC_CORE2	0x40000068
#define IRQ_SRC_CORE3	0x4000006C

#define FIQ_SRC_CORE0	0x40000070
#define FIQ_SRC_CORE1	0x40000074
#define FIQ_SRC_CORE2	0x40000078
#define FIQ_SRC_CORE3	0x4000007C

#define IRQ_PER(X)  (11 + X)
#define IRQ_LT	    (11)
#define IRQ_AXI	    (10)
#define IRQ_PMU	    (9)
#define IRQ_GPU	    (8)
#define IRQ_MB3	    (7)
#define IRQ_MB2	    (6)
#define IRQ_MB1	    (5)
#define IRQ_MB0	    (4)
#define IRQ_CV	    (3)
#define IRQ_CHP	    (2)
#define IRQ_CPNS    (1)
#define IRQ_CPS	    (0)

#define IRQ_SRC_COREN(X)    ((X == 0) ? IRQ_SRC_CORE0 : (X == 1) ? IRQ_SRC_CORE1 : (X == 2) ? IRQ_SRC_CORE2 : IRQ_SRC_CORE3)

/* This define are only useful for GPU-side irq routing to core */

#define IRQ_BASE	0x3F00B200

#define IRQ_BASIC_PENDING   (IRQ_BASE + 0x0)
#define IRQ_PENDING_1	    (IRQ_BASE + 0x4)
#define IRQ_PENDING_2	    (IRQ_BASE + 0x8)
#define FIQ_CONTROL	    (IRQ_BASE + 0xC)
#define ENABLE_IRQ_1	    (IRQ_BASE + 0x10)
#define ENABLE_IRQ_2	    (IRQ_BASE + 0x14)
#define ENABLE_BASIC_IRQ    (IRQ_BASE + 0x18)
#define DISABLE_IRQ_1	    (IRQ_BASE + 0x1C)
#define DISABLE_IRQ_2	    (IRQ_BASE + 0x20)
#define DISABLE_BASIC_IRQ   (IRQ_BASE + 0x24)


#define GPU_ST0_IRQ		    0x0 //Reserved for GPU
#define GPU_ST1_IRQ		    0x1
#define GPU_ST2_IRQ	            0x2 //Reserved for GPU
#define GPU_ST3_IRQ		    0x3
#define GPU_CODEC0_IRQ		    0x4
#define GPU_CODEC1_IRQ		    0x5
#define GPU_CODEC2_IRQ		    0x6
#define GPU_JPEG_IRQ		    0x7
#define GPU_ISP_IRQ		    0x8
#define GPU_USB_IRQ		    0x9
#define GPU_3D_IRQ		    0xA
#define GPU_TRANSPOSER_IRQ	    0xB
#define GPU_MULTICORE_SYNC0_IRQ	    0xC
#define GPU_MULTICORE_SYNC1_IRQ	    0xD
#define GPU_MULTICORE_SYNC2_IRQ	    0xE
#define GPU_MULTICORE_SYNC3_IRQ	    0xF
#define GPU_DMA0_IRQ		    0x10
#define GPU_DMA1_IRQ		    0x11
#define GPU_DMA2_IRQ		    0x12
#define GPU_DMA3_IRQ		    0x13
#define GPU_DMA4_IRQ		    0x14
#define GPU_DMA5_IRQ		    0x15
#define GPU_DMA6_IRQ		    0x16
#define GPU_DMA7_IRQ		    0x17
#define GPU_DMA8_IRQ		    0x18
#define GPU_DMA9_IRQ		    0x19
#define GPU_DMA10_IRQ		    0x1A
#define GPU_DMA11_14_IRQ	    0x1B
#define GPU_DMA_ALL_IRQ		    0x1C
#define GPU_AUX_IRQ		    0x1D
#define GPU_ARM_IRQ		    0x1E
#define GPU_GPUDMA_IRQ		    0x1F
#define GPU_HOSTPORT_IRQ	    0x20
#define GPU_VIDEOSCALER_IRQ	    0x21
#define GPU_CCP2TX_IRQ		    0x22
#define GPU_SDC_IRQ		    0x23
#define GPU_DSIO_IRQ		    0x24
#define GPU_AVE_IRQ		    0x25
#define GPU_CAM0_IRQ		    0x26
#define GPU_CAM1_IRQ		    0x27
#define GPU_HDMI0_IRQ		    0x28
#define GPU_HDMI1_IRQ		    0x29
#define GPU_PIXELVALVE_IRQ	    0x2A
#define GPU_I2C_SPI_IRQ		    0x2B
#define GPU_DSI1_IRQ		    0x2C
#define GPU_PWA0_IRQ		    0x2D
#define GPU_PWA1_IRQ		    0x2E
#define GPU_CPR_IRQ		    0x2F
#define GPU_SMI_IRQ		    0x30
#define GPU_GPIO_0_IRQ		    0x31
#define GPU_GPIO_1_IRQ		    0x32
#define GPU_GPIO_2_IRQ		    0x33 //Not present on bcm2837
#define GPU_GPIO_ALL_IRQ	    0x34
#define GPU_I2C_IRQ		    0x35
#define GPU_SPI_IRQ		    0x36
#define GPU_I2SPCM_IRQ		    0x37
#define GPU_SDIO_IRQ		    0x38
#define GPU_PL011_IRQ		    0x39
#define GPU_SLIMBUS_IRQ		    0x3A
#define GPU_VEC_IRQ		    0x3B
#define GPU_CPG_IRQ		    0x3C
#define GPU_RNG_IRQ		    0x3D
#define GPU_SDHCI_IRQ		    0x3E
#define GPU_AVSPMON_IRQ		    0x3F
#define GPU_HALTED0_IRQ		    0x44
#define GPU_HALTED1_IRQ		    0x45
#define GPU_ILL_ACC0_IRQ	    0x46
#define GPU_ILL_ACC1_IRQ	    0x47
#define GPU_PENDING1_IRQ	    0x48
#define GPU_PENDING2_IRQ	    0x49

#define ENABLE_FIQ	    *(int *)FIQ_CONTROL |= 0x80;
#define CLEAR_FIQ	    *(int *)FIQ_CONTROL &= 0xFFFFFF80
#define SOURCE_FIQ(X)	    *(int *)FIQ_CONTROL |= X;

#define GET_ENABLE_REG(X)   (X < 32 ? ENABLE_IRQ_1 : X < 64 ? ENABLE_IRQ_2 : ENABLE_BASIC_IRQ)
#define GET_DISABLE_REG(x)  (X < 32 ? DISABLE_IRQ_1 : X < 64 ? DISABLE_IRQ_2 : DISABLE_BASIC_IRQ)

#define ENABLE_IRQ(X)	    *(int *)(GET_ENABLE_REG(X)) |= (1 << X % 32)
#define DISABLE_IRQ(X)	    *(int *)(GET_DISABLE_REG(X)) &= ~(1 << X % 32)

void (*interrupt_handler[16])();
void (*gpu_interrupt_handler[64])();


int ct_int(int core, int inte);
extern void interrupts_handler(void);
void add_handler(void (*hand)(void), int irqnum);

void gpu_irq_handler(void);
void gpu_irq_1_handler(void);
void gpu_irq_2_handler(void);
void add_gpu_handler(void (*hand)(void), int irqnum);
void enable_gpu_irq(int irqnum);

#endif /* _INTERRUPT_H_ */

/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Header for mailbox management for bcm 2836/7
 * Source : BCM 2836 peripheral documentation
 */

#ifndef _MAILBOX_H_
 #define _MAILBOX_H_

#define MB_BASE_ADDRESS	    0x40000080

/* Write-set mailbox
   |OLD|WRITE|NEW|
   | 0 |  0  | 0 |
   | 0 |  1  | 1 |
   | 1 |  0  | 1 |
   | 1 |  1  | 1 | 

#define MB_WRITE_CORE0_0    (MB_BASE_ADDRESS + 0x00)
#define MB_WRITE_CORE0_1    (MB_BASE_ADDRESS + 0x04)
#define MB_WRITE_CORE0_2    (MB_BASE_ADDRESS + 0x08)
#define MB_WRITE_CORE0_3    (MB_BASE_ADDRESS + 0x0C)
#define MB_WRITE_CORE1_0    (MB_BASE_ADDRESS + 0x10)
#define MB_WRITE_CORE1_1    (MB_BASE_ADDRESS + 0x14)
#define MB_WRITE_CORE1_2    (MB_BASE_ADDRESS + 0x18)
#define MB_WRITE_CORE1_3    (MB_BASE_ADDRESS + 0x1C)
#define MB_WRITE_CORE2_0    (MB_BASE_ADDRESS + 0x20)
#define MB_WRITE_CORE2_1    (MB_BASE_ADDRESS + 0x24)
#define MB_WRITE_CORE2_2    (MB_BASE_ADDRESS + 0x28)
#define MB_WRITE_CORE2_3    (MB_BASE_ADDRESS + 0x2C)
#define MB_WRITE_CORE3_0    (MB_BASE_ADDRESS + 0x30)
#define MB_WRITE_CORE3_1    (MB_BASE_ADDRESS + 0x34)
#define MB_WRITE_CORE3_2    (MB_BASE_ADDRESS + 0x38)
#define MB_WRITE_CORE3_3    (MB_BASE_ADDRESS + 0x3C)

   Read/Write-clear mailbox
   |OLD|WRITE|NEW|
   | 0 |  0  | 0 |
   | 0 |  1  | 0 |
   | 1 |  0  | 1 |
   | 1 |  1  | 0 | 

#define MB_READ_CORE0_0	    (MB_BASE_ADDRESS + 0x40)
#define MB_READ_CORE0_1	    (MB_BASE_ADDRESS + 0x44)
#define MB_READ_CORE0_2	    (MB_BASE_ADDRESS + 0x48)
#define MB_READ_CORE0_3	    (MB_BASE_ADDRESS + 0x4C)
#define MB_READ_CORE1_0	    (MB_BASE_ADDRESS + 0x50)
#define MB_READ_CORE1_1	    (MB_BASE_ADDRESS + 0x54)
#define MB_READ_CORE1_2	    (MB_BASE_ADDRESS + 0x58)
#define MB_READ_CORE1_3	    (MB_BASE_ADDRESS + 0x5C)
#define MB_READ_CORE2_0	    (MB_BASE_ADDRESS + 0x60)
#define MB_READ_CORE2_1	    (MB_BASE_ADDRESS + 0x64)
#define MB_READ_CORE2_2	    (MB_BASE_ADDRESS + 0x68)
#define MB_READ_CORE2_3	    (MB_BASE_ADDRESS + 0x6C)
#define MB_READ_CORE3_0	    (MB_BASE_ADDRESS + 0x70)
#define MB_READ_CORE3_1	    (MB_BASE_ADDRESS + 0x74)
#define MB_READ_CORE3_2	    (MB_BASE_ADDRESS + 0x78)
#define MB_READ_CORE3_3	    (MB_BASE_ADDRESS + 0x7C) */

#define MB_GET_REG(R)	    (*(int *)(R))
#define MB_SET_REG(R, V)    (*(int *)(R)) = (V)

#define MB_GET_WRITEO(C, M) (MB_BASE_ADDRESS + (C * 0x10) + (M * 0x4))
#define MB_GET_READO(C, M)  (MB_BASE_ADDRESS + 0x40 + (C * 0x10) + (M * 0x4))

/*
#define MB_GET_WRITE(C, M)  (C == 0 ? MB_GET_W0(M) : C == 1 ? MB_GET_W1(M) : C == 2 ? MB_GET_W2(M) : MB_GET_W3(M))
#define MB_GET_W0(M)	    (M == 0 ? MB_WRITE_CORE0_0 : M == 1 ? MB_WRITE_CORE0_1 : M == 2 ? MB_WRITE_CORE0_2 : MB_WRITE_CORE0_3)
#define MB_GET_W1(M)	    (M == 0 ? MB_WRITE_CORE1_0 : M == 1 ? MB_WRITE_CORE1_1 : M == 2 ? MB_WRITE_CORE1_2 : MB_WRITE_CORE1_3)
#define MB_GET_W2(M)	    (M == 0 ? MB_WRITE_CORE2_0 : M == 1 ? MB_WRITE_CORE2_1 : M == 2 ? MB_WRITE_CORE2_2 : MB_WRITE_CORE2_3)
#define MB_GET_W3(M)	    (M == 0 ? MB_WRITE_CORE3_0 : M == 1 ? MB_WRITE_CORE3_1 : M == 2 ? MB_WRITE_CORE3_2 : MB_WRITE_CORE3_3)

#define MB_GET_READ(C, M)  (C == 0 ? MB_GET_R0(M) : C == 1 ? MB_GET_R1(M) : C == 2 ? MB_GET_R2(M) : MB_GET_R3(M))
#define MB_GET_R0(M)	    (M == 0 ? MB_READ_CORE0_0 : M == 1 ? MB_READ_CORE0_1 : M == 2 ? MB_READ_CORE0_2 : MB_READ_CORE0_3)
#define MB_GET_R1(M)	    (M == 0 ? MB_READ_CORE1_0 : M == 1 ? MB_READ_CORE1_1 : M == 2 ? MB_READ_CORE1_2 : MB_READ_CORE1_3)
#define MB_GET_R2(M)	    (M == 0 ? MB_READ_CORE2_0 : M == 1 ? MB_READ_CORE2_1 : M == 2 ? MB_READ_CORE2_2 : MB_READ_CORE2_3)
#define MB_GET_R3(M)	    (M == 0 ? MB_READ_CORE3_0 : M == 1 ? MB_READ_CORE3_1 : M == 2 ? MB_READ_CORE3_2 : MB_READ_CORE3_3)
*/

void mailbox_write(int core, int mailbox, int message);
void mailbox_clear_bit(int mailbox, int bit);
void mailbox_full_clear(int mailbox);
int mailbox_read(int mailbox);
int mailbox_read_bit(int mailbox, int bit);

#endif /* _MAILBOX_H_ */

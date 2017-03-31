/*
 * Authors : Alexandre "Dargor" Meunier <psychonaniste@gmail.com>
 * Description : Headers for raspberry pi 3 armv7 MMU
 */

#ifndef _MMU_H_
 #define _MMU_H_

#define MMU_BASE    0x00004000
 

/* Section first level descriptor
|31                20| 19 |18|17|16|15|14 12|11 10| 9 |8    5| 4 |3|2|1| 0 |
|--------------------|----|--|--|--|--|-----|-----|---|------|---|-|-|-|---|
|Section base adresse| NS | 0|nG| S|AP| TEX | AP  |ID |Domain|XN |C|B|1|PXN|
*/

/* Flags */
#define NS		(1 << 19)//Non secure 
#define NG		(1 << 17)//Not global
#define S		(1 << 16)//Shareable
#define XN		(1 << 4) //Exceute never flag.

/* Domain permission */
#define NA		0b00    // Any access generate a domain fault
#define CLIENT		0b01    // Access are checked against permissions access bit
#define RESERVED	0b10    // Any access generate a domain fault
#define MANAGER		0b11    // Free porn

/* DOMAINS from 0 to 15 */
#define DOMAINS(X)	(X < 0 ? 0 : X > 15 ? (15 << 5) : (X << 5))

/* First level descriptor type */
#define SUPERSECTION	0x00040002
#define SECTION		0x00000002
#define PAGE		0x00000001
#define FAULT		0x00000000

/* access permissions bits PRIVILIGED_USER */
#define AP_NO_ACCESS	0x00000000
#define AP_RW_NA	0x00000400
#define AP_RW_RO	0x00000800
#define AP_FULL_ACCESS	0x00000C00
#define AP_RESERVED	0x00008000
#define AP_RO_NA	0x00008400
#define AP_RO_RO	0x00008800
#define AP_RO_RO2	0x00008C00

/* TEX C and B policy aka memory region type aka very long define streak aka hard to find short define name */
// O = Outer, I = Inner, WT = write through, WB = write back, NOA = No allocate, WR = write, RD = read
#define MRT_STR_ORD	    0x00000000 //Strongly ordered
#define MRT_SHA_DEV	    0x00000004 //Shared device
#define MRT_OI_WT_NOA_WR    0x00000008 //Outer and inner write through, no allocate on write
#define MRT_OI_WB_NOA_WR    0x0000000C //Outer and inner write back, no allocate on write
#define MRT_OI_NO_CACHEABLE 0x00001000 //Outer and inner non cacheable
#define MRT_OI_WB_WR_ALL    0x0000100C //Outer and inner WB, write allocate
#define MRT_NON_SHARED	    0x00002000 //Non shared device
/* Cached memory define */
//O = outer, CA = cachable, UNB = unbuffered, BU = buffered, WB = write back
#define TEX_CACHED		0x00004000 //Cached memory
#define	TEX_O_NO_CA_UNB		0x00000000 //Outer non cacheable, unbuffered
#define TEX_O_WB_CA_WA_BU	0x00001000 //Write back cached, write allocate, buffered	
#define TEX_O_WT_CA_NOA_WR_BU	0x00002000 //Write through cached, no allocate write, buffered
#define TEX_O_WB_CA_NOA_WR_BU	0x00003000 //Write back cached, no allocate on write, buffered
#define TEX_I_NO_CA_UNB		0x00000000
#define TEX_I_WB_CA_WA_BU	0x00000004
#define TEX_I_WT_CA_NOA_WR_BU	0x00000008
#define TEX_I_WB_CA_NOA_WR_BU	0x0000000C
void set_mmu(void);

#endif /* _MMU_H_ */

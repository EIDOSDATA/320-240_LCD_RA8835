/*
 * RA8835.h
 *
 *  Created on: 2024. 5. 12.
 *      Author: c6h6
 */

#ifndef RA8835_RA8835_H_
#define RA8835_RA8835_H_

#include <stdint.h>

#define RA8835_CMD_SYSTEM_SET       0x40
#define RA8835_CMD_SLEEP_IN         0x53
#define RA8835_CMD_DISPLAY_OFF      0x58
#define RA8835_CMD_DISPLAY_ON       0x59
#define RA8835_CMD_SCROLL           0x44
#define RA8835_CMD_CSRFORM          0x5D
#define RA8835_CMD_CGRAM_ADR        0x5C
#define RA8835_CMD_CSRDIR_RIGHT     0x4C
#define RA8835_CMD_CSRDIR_LEFT      0x4D
#define RA8835_CMD_CSRDIR_UP        0x4E
#define RA8835_CMD_CSRDIR_DOWN      0x4F
#define RA8835_CMD_HDOT_SCR         0x5A
#define RA8835_CMD_OVLAY            0x5B
#define RA8835_CMD_CSRW             0x46
#define RA8835_CMD_CSRR             0x47
#define RA8835_CMD_MWRITE           0x42
#define RA8835_CMD_MREAD            0x43

#define SED1335_SCR_WIDTH   	319
#define SED1335_M0   			0
#define SED1335_M1   			0
#define SED1335_M2   			0
#define SED1335_WS   			0
#define SED1335_IV   			1
#define SED1335_FX   			7
#define SED1335_FY   			7
#define SED1335_WF   			1
#define SED1335_CR   			39
#define SED1335_TCR   			43
#define SED1335_LF   			239
#define SED1335_APL   			40
#define SED1335_APH   			0
#define SED1335_LINES   			30
#define SED1335_SAD1L   			0
#define SED1335_SAD1H   			0
#define SED1335_SL1   			0xEF
#define SED1335_SAD2L   			0xB0
#define SED1335_SAD2H   			0x04
#define SED1335_SL2   			0xEF
#define SED1335_SAD3L   			0
#define SED1335_SAD3H  			0
#define SED1335_SAD4L   			0
#define SED1335_SAD4H   			0
#define SED1335_CRX   			0x04
#define SED1335_CRY   			0x07
#define SED1335_CM   			0
#define SED1335_MX0   			1
#define SED1335_MX1   			0
#define SED1335_DM1   			0
#define SED1335_DM2   			0
#define SED1335_OV   			0
#define SED1335_SAGL   			0
#define SED1335_SAGH   			0x70
#define SED1335_SCRD   			0
#define SED1335_FLASH   			0x16
#define SED1335_TEXTSIZE   		((SED1335_SAD2H << 8) + SED1335_SAD2L)
#define SED1335_GRAPHICSTART	((SED1335_SAD2H << 8) + SED1335_SAD2L)

#define SED1335_GRAPHICSIZE   	((SED1335_SL2+1) * (SED1335_SCR_WIDTH+1))>>3
#define SED1335_MEM_END   		10800
#define SED1335_SYS_P1   		0x10 | (SED1335_IV << 5) | (SED1335_WS << 3) | (SED1335_M2 << 2) | (SED1335_M1 << 1) | SED1335_M0
#define SED1335_SYS_P2   		0x00 | (SED1335_WF << 7) | SED1335_FX
#define SED1335_CSRF_P2   		0x00 | (SED1335_CM << 7) | SED1335_CRY
#define SED1335_OVLAY_P1   		0x00 | (SED1335_OV << 4) | (SED1335_DM2 << 3) | (SED1335_DM1 << 2) | (SED1335_MX1 << 1) | SED1335_MX0

void RA8835_Init();
void RA8835_Set_Cursor(uint16_t address);
void RA8835_Clear_Text_Area();
void RA8835_Clear_Graphic_Area();

// HW Specific

#include "iodefine.h"
#include "iodefine_ext.h"

#define RA8835_HW_SPECIFIC_DELAY_TUINIG 12

inline void RA8835_hw_set_RST(uint8_t rst)
{
	rst?(P5_bit.no0=1):(P5_bit.no0=0);
}

inline void RA8835_hw_set_A0(uint8_t A0)
{
	A0?(P5_bit.no1=1):(P5_bit.no1=0);
}

inline void RA8835_hw_set_CS(uint8_t CS)
{
	CS?(P5_bit.no2=1):(P5_bit.no2=0);
}
inline void RA8835_hw_set_RD(uint8_t RD)
{
	RD?(P5_bit.no3=1):(P5_bit.no3=0);
}
inline void RA8835_hw_set_WR(uint8_t WR)
{
	WR?(P5_bit.no4=1):(P5_bit.no4=0);
}

inline void RA8835_hw_delay_cyc(const uint32_t cycles)
{
	for(volatile uint32_t i=0;i<cycles;i++)
	{
		asm volatile("nop");
	}
}
inline void RA8835_hw_set_DATA(uint8_t DATA)
{
	P7=DATA;
}
inline void RA8835_hw_set_DATAMODE(uint8_t DATAMODE)
{
	DATAMODE?(PM7=0xFF):(PM7=0x00);
}
inline uint8_t RA8835_hw_get_DATA()
{
	return P7;
}

void RA8835_hw_init();


#endif /* RA8835_RA8835_H_ */

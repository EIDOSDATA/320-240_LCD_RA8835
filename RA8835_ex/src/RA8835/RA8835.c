/*
 * RA8835.c
 *
 *  Created on: 2024. 5. 13.
 *      Author: c6h6
 */

#include "RA8835.h"

void RA8835_write_cmd(uint8_t cmd);
void RA8835_write_data(uint8_t data);
uint8_t RA8835_read_data();

void RA8835_hw_init()
{
	PM7=0x00;
	PM5=0x00;

	RA8835_hw_set_DATA(0xFF);
	RA8835_hw_set_RST(1);

	RA8835_hw_set_A0(1);
	RA8835_hw_set_RD(1);
	RA8835_hw_set_WR(1);
	RA8835_hw_set_CS(1);
}

void RA8835_write_data(uint8_t data)
{
	//Prepare Data
	RA8835_hw_set_DATA(data);
	RA8835_hw_set_DATAMODE(0);

	RA8835_hw_set_A0(0);
	RA8835_hw_set_CS(0);
	RA8835_hw_set_WR(0);

	RA8835_hw_delay_cyc(RA8835_HW_SPECIFIC_DELAY_TUINIG);

	RA8835_hw_set_WR(1);
	RA8835_hw_set_A0(1);
	RA8835_hw_set_CS(1);

}

void RA8835_write_cmd(uint8_t cmd)
{
	//Prepare Data
	RA8835_hw_set_DATA(cmd);
	RA8835_hw_set_DATAMODE(0);

	RA8835_hw_set_CS(0);
	RA8835_hw_set_WR(0);

	RA8835_hw_delay_cyc(RA8835_HW_SPECIFIC_DELAY_TUINIG);

	RA8835_hw_set_WR(1);
	RA8835_hw_set_CS(1);
}


uint8_t RA8835_read_data()
{
	uint8_t result;
	//Prepare Port mode read
	RA8835_hw_set_DATAMODE(1);
	RA8835_hw_set_CS(0);
	//Read
	RA8835_hw_set_RD(0);
	RA8835_hw_set_WR(1);
	RA8835_hw_delay_cyc(RA8835_HW_SPECIFIC_DELAY_TUINIG);
	result=RA8835_hw_get_DATA();
	RA8835_hw_delay_cyc(RA8835_HW_SPECIFIC_DELAY_TUINIG);

	//Recover RD, WR Signal
	RA8835_hw_set_RD(1);
	RA8835_hw_set_WR(1);

	//Recover A0, CS Signal
	RA8835_hw_set_A0(1);
	RA8835_hw_set_CS(1);
	//Restore Port mode write
	RA8835_hw_set_DATAMODE(0);

	return result;
}
void RA8835_Set_Cursor(uint16_t address)
{
	RA8835_write_cmd(RA8835_CMD_CSRW);
	RA8835_write_data(address & 0x00FF);
	RA8835_write_data(address >> 8);
}
void RA8835_Clear_Text_Area(void)
{
	int i;

	RA8835_Set_Cursor(0);
	RA8835_write_cmd(RA8835_CMD_MWRITE);

	for(i = 0;i < 320 / 8 * 240 / 8;i++)
	{
		RA8835_write_data(0x20);
	}
	RA8835_Set_Cursor(0);
}

void RA8835_Clear_Graphic_Area(void)
{
	int i;

	RA8835_Set_Cursor(320 / 8 * 240 / 8);
	RA8835_write_cmd(RA8835_CMD_MWRITE);

	for(i = 0;i < 320 / 8 * 240;i++)
	{
		RA8835_write_data(0x00);
	}

	RA8835_Set_Cursor(320 / 8 * 240 / 8);
}

void RA8835_Init()
{
	RA8835_hw_init();

	RA8835_write_cmd(RA8835_CMD_SYSTEM_SET);
	RA8835_write_data(SED1335_SYS_P1);
	RA8835_write_data(SED1335_SYS_P2);
	RA8835_write_data(SED1335_FY);
	RA8835_write_data(SED1335_CR);
	RA8835_write_data(SED1335_TCR);
	RA8835_write_data(SED1335_LF);
	RA8835_write_data(SED1335_APL);
	RA8835_write_data(SED1335_APH);

	RA8835_write_cmd(RA8835_CMD_SCROLL);
	RA8835_write_data(SED1335_SAD1L);
	RA8835_write_data(SED1335_SAD1H);
	RA8835_write_data(SED1335_SL1);
	RA8835_write_data(SED1335_SAD2L);
	RA8835_write_data(SED1335_SAD2H);
	RA8835_write_data(SED1335_SL2);
	RA8835_write_data(SED1335_SAD3L);
	RA8835_write_data(SED1335_SAD3H);
	RA8835_write_data(SED1335_SAD4L);
	RA8835_write_data(SED1335_SAD4H);

	RA8835_write_cmd(RA8835_CMD_CSRFORM);
	RA8835_write_data(SED1335_CRX);
	RA8835_write_data(SED1335_CSRF_P2);

	RA8835_write_cmd(RA8835_CMD_CGRAM_ADR);
	RA8835_write_data(SED1335_SAGL);
	RA8835_write_data(SED1335_SAGH);

	RA8835_write_cmd(RA8835_CMD_CSRDIR_RIGHT);

	RA8835_write_cmd(RA8835_CMD_HDOT_SCR);
	RA8835_write_data(SED1335_SCRD);

	RA8835_write_cmd(RA8835_CMD_OVLAY);
	RA8835_write_data(SED1335_OVLAY_P1);

	//Clear Display

	RA8835_Clear_Graphic_Area();
	RA8835_Clear_Text_Area();

	RA8835_write_cmd(RA8835_CMD_DISPLAY_ON);
	RA8835_write_data(SED1335_FLASH);
}


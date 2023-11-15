/*****************HORSE Program******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:03/09/2023.****************/
/************************************************/

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "HORSE_private.h"
#include "HORSE_config.h"
#include "HORSE_interface.h"
#include <util/delay.h>

/*Stolen from the Internet with minor modifications
 *Credit to YouTube channel: Teach Me Something
 *Link: https://www.youtube.com/@TeachMeSomething*/
void HORSE_Animation(void)
{

	u8 Local_u8HorseCustomChar[2][8][8] =
		{
			{{0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x0E},
			 {0x00, 0x00, 0x00, 0x00, 0x0F, 0x1F, 0x1F, 0x1F},
			 {0x00, 0x00, 0x00, 0x03, 0x07, 0x1F, 0x1F, 0x1F},
			 {0x00, 0x00, 0x05, 0x1F, 0x1D, 0x1F, 0x16, 0x06},
			 {0x0C, 0x18, 0x10, 0x00, 0x01, 0x01, 0x01, 0x00},
			 {0x1F, 0x1F, 0x1E, 0x17, 0x00, 0x00, 0x10, 0x00},
			 {0x1F, 0x1F, 0x03, 0x02, 0x14, 0x04, 0x02, 0x00},
			 {0x1C, 0x1C, 0x04, 0x04, 0x08, 0x00, 0x00, 0x00}},
			{{0x00, 0x00, 0x00, 0x07, 0x0F, 0x0E, 0x1C, 0x18},
			 {0x00, 0x00, 0x00, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F},
			 {0x00, 0x00, 0x01, 0x03, 0x1F, 0x1F, 0x1F, 0x1F},
			 {0x14, 0x1C, 0x1A, 0x1E, 0x1F, 0x13, 0x10, 0x10},
			 {0x13, 0x13, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00},
			 {0x1F, 0x07, 0x0E, 0x06, 0x01, 0x00, 0x00, 0x00},
			 {0x0F, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00},
			 {0x10, 0x18, 0x0C, 0x02, 0x02, 0x11, 0x00, 0x00}}};

	s8 Local_u8HorseMoving = HORSE_STARTING_POINT;

	for (u8 Local_u8Iterator = 0; Local_u8Iterator < HORSE_STOPING_POINT; Local_u8Iterator++)
	{
		for (u8 Local_u8LineSelection = FIRST_LINE; Local_u8LineSelection <= SECOND_LINE; Local_u8LineSelection++)
		{
			CLCD_voidSendCommand(DISPLAY_CLEAR);
			for (u8 Local_u8LcdBlock = 0; Local_u8LcdBlock < 8; Local_u8LcdBlock++)
			{
				CLCD_voidDrawSpecialChar(Local_u8LcdBlock, Local_u8HorseCustomChar[Local_u8LineSelection][Local_u8LcdBlock]);
			}
			for (u8 Local_u8HorseDraw = 0; Local_u8HorseDraw < FULL_HORSE; Local_u8HorseDraw++)
			{
				if ((Local_u8HorseMoving >= HORSE_STARTING_POINT) && (Local_u8HorseMoving <= LCD_BORDER))
				{
					CLCD_voidSetPostion(FIRST_LINE, Local_u8HorseDraw + Local_u8HorseMoving);
					CLCD_voidSendData(Local_u8HorseDraw);
					CLCD_voidSetPostion(SECOND_LINE, Local_u8HorseDraw + Local_u8HorseMoving);
					CLCD_voidSendData(Local_u8HorseDraw + FULL_HORSE);
				}
				else
				{
					Local_u8HorseMoving = HORSE_STARTING_POINT;
				}
			}
			Local_u8HorseMoving++;
			_delay_ms(200);
		}
	}

	CLCD_voidSetPostion(FIRST_LINE, 0);
	CLCD_voidSendString("Horse");
	CLCD_voidSetPostion(SECOND_LINE, 0);
	CLCD_voidSendString("Animation...");
	_delay_ms(3000);
}

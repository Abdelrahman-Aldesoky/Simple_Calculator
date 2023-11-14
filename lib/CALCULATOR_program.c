/***************Calculator Program***************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 03********************/
/****************Date:02/09/2023.****************/
/************************************************/

#include "../inc/BIT_MATH.h"
#include "../inc/STD_TYPES.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "HORSE_interface.h"
#include "CALCULATOR_interface.h"
#include <util/delay.h>


/*CALC_voidInit
 * 1-initializes the keypad
 * 2-initializes the LCD
 * Display useless horse running from left to right
 * Display Calculator on the LCD
 * the array in there to make custom useless char
 * to display useless loading bar ignore them
 * input for the function is void
 * output is also void
 */
void CALC_voidInit(void)
{

	/*Initialize KeyPad*/
	KPD_voidInit();
	_delay_ms(5);
	/*Initialize LCD*/
	CLCD_voidInit();
	_delay_ms(5);

	/*********************************Useless ignore just displaying some stuff*********************************/

	/*Horse running xD*/
	HORSE_Animation();

	/*Custom Char for the LCD "Loading Bar" Useless ignore*/
	u8 Custom_Char_Loading[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF , 0xFF, 0xFF, 0xFF };
	_delay_ms(5);

	/*Clear LCD*/
	CLCD_voidSendCommand(DISPLAY_CLEAR);
	_delay_ms(5);

	/*Go Back To DDRAM Addresses To Display Can't Display From CGRAM*/
	CLCD_voidSendCommand(SET_DDRAM_ADDRESS);
	_delay_ms(5);

	/*Display Calculator on the LCD */
	CLCD_voidSendString("   Calculator   ");
	_delay_ms(500);

	/*Make Custom Char in CGRAM Position 0*/
	CLCD_voidDrawSpecialChar(0, Custom_Char_Loading);
	_delay_ms(5);

	/*Go Back To DDRAM Addresses To Display Can't Display From CGRAM*/
	CLCD_voidSendCommand(SET_DDRAM_ADDRESS);
	_delay_ms(5);

	/*Go to Line 2 to display under word Calculator*/
	CLCD_voidSetPostion(SECOND_LINE, 0);

	/*Loop to display loading bars 16 of them till the end of LCD*/
	for(u8 Local_Iterator=0;Local_Iterator<16;Local_Iterator++)
	{
		/*Display custom char stored in the RAM at position 0 which is a Loading Bar*/
		CLCD_voidSendData(0x00);
		_delay_ms(100);
	}

	/*CLear LCD*/
	CLCD_voidSendCommand(DISPLAY_CLEAR);
	_delay_ms(2);

	/**********************************************End of Useless**********************************************/
}

/*S32 CALC_GetNumber
 * function to calculate the numbers entered by the user
 * if the user only entered single digit number it will just return it as is
 * if the user entered a multiple digit number it multiplies by 10 and add to it the last input by the user
 * function takes copy of s32Number from my main function and copy of s8 ReceivedKey "last input by the user from keypad
 *input of the function is copy of s32number and copy of s8recievedkey from the user
 *function returns s32Number to be captured by s32Number variable in main.
 */
s32 CALC_GetNumber(s32 Copy_s32Number,s8 Copy_s8ReceivedKey)
{
	s32 Local_s32Number=Copy_s32Number;
	if(Local_s32Number)
	{
		Local_s32Number=(Local_s32Number*10)+Copy_s8ReceivedKey;
	}
	else
	{
		Local_s32Number=Copy_s8ReceivedKey;
	}
	return Local_s32Number;
}

/*Display stuff in specific format
 * this took more time than i care to admit
 * way more time than the actual calculator program :(*/
void CALC_Display(s64 Copy_s64Result,s32 Copy_s32Number,s8 Copy_s8LastOPeration,s8 Copy_s8ReceivedKey)
{
		CLCD_voidSendCommand(DISPLAY_CLEAR);
		if(Copy_s64Result || Copy_s8LastOPeration)
		{
			CLCD_voidSendNumber(Copy_s64Result);
		}
		if((DISPLAY_CALCULATION)||(DIS_CALC))
		{
			CLCD_voidSendData(Copy_s8LastOPeration);
		}
		if(Copy_s32Number)
		{
			CLCD_voidSendNumber(Copy_s32Number);
		}
		else if(DISPLAY_NUMBER && Copy_s8LastOPeration!=EQUAL)
		{
			CLCD_voidSendNumber(Copy_s8ReceivedKey);
		}
		GO_TO_SECOND_LINE;
		CLCD_voidSendData(EQUAL);
		CLCD_voidSendNumber(Copy_s64Result);
}

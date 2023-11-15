/******************KPD Program*******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:23/08/2023.****************/
/************************************************/

#include "../inc/STD_TYPES.h"
#include "../inc/BIT_MATH.h"
#include "DIO_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"
#include "KPD_interface.h"
#include <util/delay.h>

/*KPD INITIALIZING
 * setting up the directions of keypad pins as an input or output
 * setting they keypad port to high "pull up mode" for input pins
 * and detect on low for output */
void KPD_voidInit(void)
{
	/*Initializing my KPD COLS as outputs*/
	DIO_voidSetPinDirection(KPD_PORT, KPD_COL1, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_COL2, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_COL3, PIN_DIRECTION_OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_COL4, PIN_DIRECTION_OUTPUT);

	/*Initializing my KPD ROWS as inputs*/
	DIO_voidSetPinDirection(KPD_PORT, KPD_ROWA, PIN_DIRECTION_INPUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_ROWB, PIN_DIRECTION_INPUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_ROWC, PIN_DIRECTION_INPUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_ROWD, PIN_DIRECTION_INPUT);

	/*Setting my KPD PORT to high for pull up and detecting on low*/
	DIO_voidSetPortValue(KPD_PORT, PORT_VALUE_HIGH);
}

s8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8Col = 0, Local_u8Row = 0;
	u8 Local_u8Reading = 0;
	s8 Local_u8Key = DEFAULT_VALUE; // just any value since i need to use zero in my keypad
	u8 KPD_u8Values[MAX_ROW][MAX_COL] = KPD_VALUES;

	for (Local_u8Col = COL_INIT; Local_u8Col < COL_FIN; Local_u8Col++)
	{
		DIO_voidSetPinValue(KPD_PORT, Local_u8Col, PIN_VALUE_LOW);
		for (Local_u8Row = ROW_INIT; Local_u8Row < ROW_FIN; Local_u8Row++)
		{
			Local_u8Reading = DIO_u8GetPinValue(KPD_PORT, Local_u8Row + MAX_COL);
			if (Local_u8Reading == PIN_VALUE_LOW)
			{
				_delay_ms(5);
				Local_u8Key = KPD_u8Values[Local_u8Row][Local_u8Col];
			}
			while (DIO_u8GetPinValue(KPD_PORT, Local_u8Row + 4) == PIN_VALUE_LOW) // stay here till the user let go of the button
			{
			}
		}
		DIO_voidSetPinValue(KPD_PORT, Local_u8Col, PIN_VALUE_HIGH);
	}
	return Local_u8Key;
}

/*
 * main.c
 *  Created on: 02/09/2023
 *      Author: Abdelrahman Mohamed.
 */

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <util/delay.h>
#include "KPD_interface.h"
#include "CLCD_interface.h"
#include "CALCULATOR_interface.h"

int main(void)
{
	CALC_voidInit();					/*Initialize calculator by initializing LCD,Keypad and doing some animations*/
	s8 s8ReceivedKey=DEFAULT;			/*variable to store the user input from keypad*/
	s8 s8EqualFlag=FALSE;				/*Flag to check if the last operation is Equal*/
	s8 s8OperationCount=0;				/*Variable to keep track if the user entered multiple operations in row "error"*/
	s8 s8LastOperation=FALSE;			/*Variable to store last operation input by the user*/
	s64 s64Result=0;					/*Signed long long INT variable to hold my result from the operations*/
	s32 s32Number=0;    				/*Signed long INT variable to hold the number entered from keypad*/

	while(1)
	{
		/*Calling KPD_u8GetPressedKey storing its value in s8ReceivedKey variable
		 * KPD_u8GetPressedKey() returns the value of the key pressed on the keypad
		 * as per the matrix in the KPD_config.h file
		 * if no key is pressed it returns a default value "-1" */
		s8ReceivedKey=KPD_u8GetPressedKey();

		/*Added a condition here for smoother operation and efficiency*/
		if(s8ReceivedKey!=DEFAULT)		/*if the pressed key from the keypad is an actual key and not just the default value*/
		{
			/*if user pressed a number and equal flag is down. "equal must be followed with an operation can't press equal then start inputing a number"*/
			if(NUMBER && EQUAL_FLAG_IS_DOWN)
			{
				s8OperationCount=0;										/*reset operation count since the user started entering numbers so he can select an operation next*/

				switch (s8ReceivedKey)									/*switch based on user input of number from 0-9*/
				{
				case 0:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);	/*Function: CALC_GetNumber for doing multiple digits if entered by the user*/
					break;
				case 1:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				case 2:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				case 3:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				case 4:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				case 5:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				case 6:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				case 7:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				case 8:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				case 9:
					s32Number=CALC_GetNumber(s32Number, s8ReceivedKey);
					break;
				}
			}
			else if((CALCULATION_CURRENT) && MULTIPLE_OPERATIONS)  /*if the user changed his operation by pressing multiple operations in row take the last operation input by the user*/
			{
				s8LastOperation=s8ReceivedKey;			/*change operation to the current input by the user*/
			}
			else if((OPERATION) && NOT_MULTIPLE_OPERATIONS)
			{
				s8EqualFlag=FALSE;						/*lower equal flag so user can enter a number next time if it was raised*/
				s8OperationCount++;						/*increase operation by one to prevent user from entering two operations in row only one operation allowed*/

				if(s8ReceivedKey==EQUAL)				/*if user input is equal, raise equal flag to prevent the user from entering numbers must enter an operation*/
				{
					s8EqualFlag=TRUE;
					s8OperationCount=0;					/*reseting operation count so the user can select an operation*/
				}
				if((CALCULATION) && (NOT_CLEAR))		/*if received key is ADD SUBTRACT MULTIPLY DIVIDE do the calculations it checks against last operation */
				{
					switch (s8LastOperation)			/*switch on last operation since first operation means only one number in memory*/
					{
					case ADD:
						s64Result+=s32Number;			/*Addition Operation*/
						break;
					case SUBTRACT:
						s64Result-=s32Number;			/*Subtraction Operation*/
						break;
					case MULTIPLY:
						s64Result*=s32Number;			/*Multiplication Operation*/
						break;
					case DIVIDE:
						if(s32Number)
						{
							s64Result/=s32Number;		/*Division Operation*/
						}
						else
						{
							/*if division by zero show some error and clear everything by changing the received key to clear*/
							CLCD_voidSendCommand(DISPLAY_CLEAR);
							CLCD_voidSendString("     ERROR.     ");
							CLCD_voidSetPostion(SECOND_LINE, 0);
							CLCD_voidSendString("DIVIDING BY ZERO");
							_delay_ms(2000);
							s8ReceivedKey=CLEAR;
						}
						break;
					}
				}
				else if(s64Result==0)   		/*if result = zero*/
				{
					s64Result=s32Number;		/*take the number the user provided probably first input no result yet*/
				}
				s8LastOperation=s8ReceivedKey; 	/*always storing the last operation since the user can click multiple operations in row program only acts on the last one.*/
				s32Number=0;					/*Reset the number back to zero*/
				if(s8ReceivedKey == CLEAR)
				{	/*Clearing Everything to start over*/
					s32Number=0;
					s64Result=0;
					s8EqualFlag=FALSE;
					s8OperationCount=0;
					s8LastOperation=FALSE;
					s8ReceivedKey=DEFAULT;
					CLCD_voidSendCommand(DISPLAY_CLEAR);
					_delay_ms(5);
				}
			}
			else
			{
				/*Maybe an error do nothing*/
			}
			/*Function: CALC_Display for displaying on LCD based on my format and what numbers i have and operations*/
			CALC_Display(s64Result, s32Number, s8LastOperation, s8ReceivedKey);
		}
		else
		{
			/*Do Nothing since all i am getting is Default value from Keypad*/
		}
	}
	return 0;
}	/*150 lines :D*/

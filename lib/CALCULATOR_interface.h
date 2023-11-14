/***************Calculator Interface***************/
/***********Author: Abdelrahman Mohamed.***********/
/*********************Ver.: 03*********************/
/*****************Date:02/09/2023.*****************/
/**************************************************/

#ifndef CALCULATOR_INTERFACE_H_
#define CALCULATOR_INTERFACE_H_

/*Initializing CALCUlATOR*/
void CALC_voidInit(void);

/*Function: CALC_GetNumber for doing multiple digits if entered by the user*/
s32 CALC_GetNumber(s32 Copy_s32Number,s8 Copy_s8ReceivedKey);

/*Function: CALC_Display for displaying on LCD based on my format and what numbers it received and operations*/
void CALC_Display(s64 Copy_s64Result,s32 Copy_s32Number,s8 Copy_s8LastOPeration,s8 Copy_s8ReceivedKey);

/****************************************Start of Conditional Statements for the numbers or the operations*************************************/

/*Statement that verifies if a number is returned from keypad the other for display*/
#define NUMBER			s8ReceivedKey>=0 && s8ReceivedKey<=9
#define DISPLAY_NUMBER 	Copy_s8ReceivedKey>=0 && Copy_s8ReceivedKey<=9

/*Statement that verifies if an operation is returned from keypad */
#define OPERATION	s8ReceivedKey==ADD||s8ReceivedKey==SUBTRACT||s8ReceivedKey==MULTIPLY||s8ReceivedKey==DIVIDE||s8ReceivedKey==EQUAL||s8ReceivedKey==CLEAR
#define CALCULATION_CURRENT s8ReceivedKey==ADD||s8ReceivedKey==SUBTRACT||s8ReceivedKey==MULTIPLY||s8ReceivedKey==DIVIDE

/*Conditions for calculating or displaying*/
#define CALCULATION 		s8LastOperation==ADD||s8LastOperation==SUBTRACT||s8LastOperation==MULTIPLY||s8LastOperation==DIVIDE
#define NOT_CLEAR 			s8ReceivedKey!=CLEAR
#define DISPLAY_CALCULATION Copy_s8ReceivedKey==ADD||Copy_s8ReceivedKey==SUBTRACT||Copy_s8ReceivedKey==MULTIPLY||Copy_s8ReceivedKey==DIVIDE
#define DIS_CALC  			Copy_s8LastOPeration==ADD||Copy_s8LastOPeration==SUBTRACT||Copy_s8LastOPeration==MULTIPLY||Copy_s8LastOPeration==DIVIDE

/*Statement that verifies if the user is pressing multiple operations in row only CLEAR operation can get through*/
#define NOT_MULTIPLE_OPERATIONS ((!s8OperationCount)||(s8ReceivedKey==CLEAR))

/*Statement that Check if Multiple operations is pressed in row*/
#define MULTIPLE_OPERATIONS s8OperationCount

/*Statement that check if EqualFlag is down "check if the last operation the user clicked was equal" */
#define EQUAL_FLAG_IS_DOWN !s8EqualFlag

/*******************************************End of Conditional Statements for numbers and operations*****************************************/

/*Operations in my calculator*/
#define DIVIDE 		'/'
#define MULTIPLY 	'*'
#define SUBTRACT	'-'
#define ADD 		'+'
#define CLEAR 		'C'
#define EQUAL		'='

#define	GO_TO_FIRST_LINE 	CLCD_voidSetPostion(FIRST_LINE, 0)			/*Go to first line on LCD position 0*/
#define	GO_TO_SECOND_LINE 	CLCD_voidSetPostion(SECOND_LINE, 0)			/*Go to second line on LCD position 0*/
#define CLEAR_LCD_LINE 		CLCD_voidSendString("                ")		/*Clear Current LCD Line*/

/*Default number that get returned from my keypad based on my KPD_config file*/
#define DEFAULT -1

#define TRUE 1
#define FALSE 0

#endif

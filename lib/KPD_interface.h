/*****************KPD Interface.*****************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:23/08/2023.****************/
/************************************************/

#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

void KPD_voidInit(void);			/*Function to initialize Keypad ports and so on*/
s8 KPD_u8GetPressedKey(void);		/*Function that returns what key has been pressed on keypad*/

#endif

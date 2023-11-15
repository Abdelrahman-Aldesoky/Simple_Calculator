/******************KPD Config.*******************/
/**********Author: Abdelrahman Mohamed.**********/
/********************Ver.: 01********************/
/****************Date:23/08/2023.****************/
/************************************************/

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_
/*KEYPAD PORT OPTIONS
 * 1-PORTA_REG
 * 2-PORTB_REG
 * 3-PORTC_REG
 * 4-PORTD_REG */
#define KPD_PORT PORTB_REG

/*KEYPAD COLS INPUT PINS
 * you can choose any pin as long as you are in the same port for input and output
 * */
#define KPD_COL1 PIN0
#define KPD_COL2 PIN1
#define KPD_COL3 PIN2
#define KPD_COL4 PIN3

/*KEYPAD ROWS OUTPUT PINS
 * you can choose any pin as long as you are in the same port for input and output
 * */
#define KPD_ROWA PIN4
#define KPD_ROWB PIN5
#define KPD_ROWC PIN6
#define KPD_ROWD PIN7

#define COL_INIT 0
#define COL_FIN 4

#define ROW_INIT 0
#define ROW_FIN 4

#define MAX_ROW 4
#define MAX_COL 4

/*Default Value that is always returned from my function KPD_u8GetPressedKey
 * you can choose any number that is not present in your keypad matrix*/
#define DEFAULT_VALUE -1

/*MAPING MATRIX 4x4 FOR MY KPD BUTTONS
 * the ones here are mapped to my Keypad actual hardware
 * u can set it up same as your hardware
 * note don't use the default value in your matrix or it will keep returning said value */
#define KPD_VALUES                                                           \
    {                                                                        \
        {7, 8, 9, '/'}, {4, 5, 6, '*'}, {1, 2, 3, '-'}, { 'C', 0, '=', '+' } \
    }

#endif

/*
 * HLEDMATRIX_Program.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Legion
 */

/*****************LIB*************************/
#include "../include/BIT_MATH.h"
#include "../include/STD_Types.h"
/*****************MCAL***********************/
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/STK/MSTK_Interface.h"
/*****************HAL***********************/
#include "../include/LEDMATRIX/HLEDMATRIX_Interface.h"
#include "../include/LEDMATRIX/HLEDMATRIX_config.h"
#include "../include/LEDMATRIX/HLEDMATRIX_private.h"

/*********************function defentions **********/

void HLEDMATRIX_voidInit(void)
{
	/********************PORTA****************/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN11,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA, GPIO_PIN11,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN12,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA, GPIO_PIN12,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN14,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA, GPIO_PIN14,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN15,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTA, GPIO_PIN15,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN0,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN0,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN1,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN1,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN2,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN2,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN5,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN5,GPIO_PUSH_PULL, GPIO_LOW_SPEED);
		/*****************PORTB******************/

	MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN6,GPIO_OUTPUT);
	MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN6,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

		MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN7,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN7,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

		MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN8,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN8,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

		MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN9,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN9,GPIO_PUSH_PULL, GPIO_LOW_SPEED);


		MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN10,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN10,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

		MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN12,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN12,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

		MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN13,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN13,GPIO_PUSH_PULL, GPIO_LOW_SPEED);

		MGPIO_voidSetPinMode(GPIO_PORTB, GPIO_PIN14,GPIO_OUTPUT);
		MGPIO_voidSetPinOutputMode(GPIO_PORTB, GPIO_PIN14,GPIO_PUSH_PULL, GPIO_LOW_SPEED);


}
void HLEDMATRIX_voidDisableColoumns(void)
{
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN11,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN12,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN14,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN15,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN0,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN1,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN2,GPIO_PIN_LOW);
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN5,GPIO_PIN_LOW);

}
void HLEDMATRIX_voidSetRowValue(u8 copy_u8RowValue)
{
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN6,!GET_BIT(copy_u8RowValue,1));
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN7,!GET_BIT(copy_u8RowValue,2));
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN8,!GET_BIT(copy_u8RowValue,3));
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN9,!GET_BIT(copy_u8RowValue,4));
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN10,!GET_BIT(copy_u8RowValue,5));
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN12,!GET_BIT(copy_u8RowValue,6));
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN13,!GET_BIT(copy_u8RowValue,7));
	MGPIO_voidSetPinValue(GPIO_PORTB, GPIO_PIN14,!GET_BIT(copy_u8RowValue,7));


}
void HLEDMATRIX_voidDisplay(u8 *copy_u8array)
{
HLEDMATRIX_voidDisableColoumns();
HLEDMATRIX_voidSetRowValue(copy_u8array[1]);
MGPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN11,GPIO_PIN_HIGH);
MSTK_voidDelayus(2500);

HLEDMATRIX_voidDisableColoumns();
HLEDMATRIX_voidSetRowValue(copy_u8array[2]);
MGPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN12,GPIO_PIN_HIGH);
MSTK_voidDelayus(2500);

HLEDMATRIX_voidDisableColoumns();
HLEDMATRIX_voidSetRowValue(copy_u8array[3]);
MGPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN14,GPIO_PIN_HIGH);
MSTK_voidDelayus(2500);

HLEDMATRIX_voidDisableColoumns();
HLEDMATRIX_voidSetRowValue(copy_u8array[4]);
MGPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN15,GPIO_PIN_HIGH);
MSTK_voidDelayus(2500);

HLEDMATRIX_voidDisableColoumns();
HLEDMATRIX_voidSetRowValue(copy_u8array[5]);
MGPIO_voidSetPinValue(GPIO_PORTB , GPIO_PIN0,GPIO_PIN_HIGH);
MSTK_voidDelayus(2500);


HLEDMATRIX_voidDisableColoumns();
HLEDMATRIX_voidSetRowValue(copy_u8array[6]);
MGPIO_voidSetPinValue(GPIO_PORTB , GPIO_PIN1,GPIO_PIN_HIGH);
MSTK_voidDelayus(2500);

HLEDMATRIX_voidDisableColoumns();
HLEDMATRIX_voidSetRowValue(copy_u8array[7]);
MGPIO_voidSetPinValue(GPIO_PORTB , GPIO_PIN2,GPIO_PIN_HIGH);
MSTK_voidDelayus(2500);

HLEDMATRIX_voidDisableColoumns();
HLEDMATRIX_voidSetRowValue(copy_u8array[7]);
MGPIO_voidSetPinValue(GPIO_PORTB , GPIO_PIN5,GPIO_PIN_HIGH);
MSTK_voidDelayus(2500);


}

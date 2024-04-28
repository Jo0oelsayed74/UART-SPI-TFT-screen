/*
 * MSPI_Program.c
 *
 *  Created on: Apr 21, 2024
 *      Author: yoels
 */

#include "../include/BIT_MATH.h"
#include "../include/STD_Types.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/SPI/MSPI_Interface.h"
#include "../include/SPI/MSPI_Private.h"
#include "../include/SPI/MSPI_Config.h"

PtrToFunc_void SPI_CallBack[SPI_NUMBER];

void MSPI_voidInit (void)
{
	SPI1->CR1 = 0x0347;
}

u16 MSPI_voidSendReceiveData (u16 A_u16Data)
{
	MGPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN8 , GPIO_OUTPUT);
	MGPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN8 , GPIO_PIN_LOW);

	/* Send Data */
	SPI1 -> DR = A_u16Data;

	/* Wait Busy Flag to finish */
	while (GET_BIT(SPI1 -> SR, 7));
	MGPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN8 , GPIO_PIN_HIGH);

	return (u8)(SPI1 -> DR);
}

void MSPI_voidSetCallBack (PtrToFunc_void p_CallBackFunc)
{
	/*Set Call Back Function*/
	SPI_CallBack[0] = p_CallBackFunc;
}

void SPI1_IRQHandler (void)
{
	if (SPI_CallBack[0] != NULL)
	{
		SPI_CallBack[0]();
	}
}




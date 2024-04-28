/*
 * HTFT_Program.c
 *
 *  Created on: Apr 21, 2024
 *      Author: yoels
 */

#include "../include/BIT_MATH.h"
#include "../include/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/STK/MSTK_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/SPI/MSPI_Interface.h"

#include "../include/TFT/HTFT_Interface.h"
#include "../include/TFT/HTFT_Private.h"
#include "../include/TFT/HTFT_Config.h"
//#include "../include/HTFT/TFT_Monir.h"


void HTFT_voidReset (void)
{
	MGPIO_voidSetResetPin(TFT_RESET_PORT , TFT_RESET_PIN , GPIO_SET);
	MSTK_voidDelayms(100);
	MGPIO_voidSetResetPin(TFT_RESET_PORT , TFT_RESET_PIN , GPIO_RESET);
	MSTK_voidDelayms(1);
	MGPIO_voidSetResetPin(TFT_RESET_PORT , TFT_RESET_PIN , GPIO_SET);
	MSTK_voidDelayms(100);
	MGPIO_voidSetResetPin(TFT_RESET_PORT , TFT_RESET_PIN , GPIO_RESET);
	MSTK_voidDelayms(100);
	MGPIO_voidSetResetPin(TFT_RESET_PORT , TFT_RESET_PIN , GPIO_SET);
	MSTK_voidDelayms(120);
}

void HTFT_voidInit (void)
{
		/*Reset sequence*/
		HTFT_voidReset();

		/*Send command sleep out*/
		HTFT_voidSendCommand(0x11);

		/*wait 150 msec*/
		MSTK_voidDelayms(150);

		/*color mode command*/
		HTFT_voidSendCommand(0x3A);
		/*RGB565*/
		HTFT_voidSendData(0x05);

		/*Display command*/
		HTFT_voidSendCommand(0x29);
}

void HTFT_voidSendPicture (const u16 *p_Picture)
{
		u16 counter = 0;

		/*Set x*/
		HTFT_voidSendCommand(0x2A);

		/*start*/
		HTFT_voidSendData(0);
		HTFT_voidSendData(0);

		/*stop*/
		HTFT_voidSendData(0);
		HTFT_voidSendData(127);


		/*Set y*/
		HTFT_voidSendCommand(0x2B);

		/*start*/
		HTFT_voidSendData(0);
		HTFT_voidSendData(0);

		/*stop*/
		HTFT_voidSendData(0);
		HTFT_voidSendData(159);

		/*Display command*/
		HTFT_voidSendCommand(0x2c);

		for(counter = 0; counter < 20480 ; counter++)
		{
			/*Write data for high byte*/
			HTFT_voidSendData(p_Picture[counter] >> 8);

			/*Write data for low byte*/
			HTFT_voidSendData(p_Picture[counter] & 0x00ff);
		}
}

static void HTFT_voidSendCommand (u8 A_u8Command)
{
	MGPIO_voidSetResetPin(TFT_CONTROL_PORT , TFT_CONTROL_PIN , GPIO_RESET);
	(void)MSPI_voidSendReceiveData(A_u8Command);
}
static void HTFT_voidSendData (u8 A_u8Data)
{
	MGPIO_voidSetPinValue(GPIO_PORTA , GPIO_PIN2 , GPIO_PIN_HIGH);
	(void)MSPI_voidSendReceiveData(A_u8Data);
}


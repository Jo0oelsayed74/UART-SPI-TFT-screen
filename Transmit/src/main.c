#include "../include/BIT_MATH.h"
#include "../include/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/STK/MSTK_interface.h"
#include "../include/LCD/HLCD_Interface.h"
#include "../include/UART/MUSART_Interface.h"
#include "../include/TFT/HTFT_interface.h"
#include "../include/TFT/TFT_image.h"



void handler_USART(void);
u8 Global_u8RX;

int main(void)
{
    /* RCC initialization */
    MRCC_voidInit();
    MSTK_voidInit();

    /* Clock to GPIOB and GPIOA */
    MRCC_voidEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOB);
    MRCC_voidEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOA);
    MRCC_voidEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOC);

    /*Enable clock to USART1*/
    MRCC_voidEnablePeripheral(RCC_APB2, RCC_APB2_USART1);

    /*Configure Pins 9 & 10 as alternative function -> USART1*/
    MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN9, GPIO_ALT_FUN);
    MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN10, GPIO_ALT_FUN);
    /*Setup the pins of the alternative functions*/
    MGPIO_voidSetAltFunction(GPIO_PORTA, GPIO_PIN9, 0b0111);
    MGPIO_voidSetAltFunction(GPIO_PORTA, GPIO_PIN10, 0b0111);

    /*Enable Peripheral number of USART1*/
    MNVIC_voidEnablePeripheralInterrupt(37);

    MUSART_voidInit();
    MUSART_EnableUSART(MUSART_USART1);
    MSUART_voidSetCallBack(handler_USART);

    /* LCD initialization */
    LCD_voidInit();
    LCD_voidSetPosition(LCD_ROW0, LCD_COLUMN1);
    LCD_voidSendString((u8 *)"WELCOME TO");

    LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
    LCD_voidSendString((u8 *)"NOGOOM FM");

    MSTK_voidDelayus(1000000000);
    MSTK_voidDelayus(1000000000);

    LCD_voidClearScreen();
    MSTK_voidDelayus(100000000);


    LCD_voidSetPosition(LCD_ROW0, LCD_COLUMN1);
    LCD_voidSendString((u8 *)"CHOOSE SONG");

    LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
    LCD_voidSendString((u8 *)"AMR DIAB/MONIR");

    /* Push button setup */
    MGPIO_voidSetPinMode(GPIO_PORTC, GPIO_PIN13, GPIO_INPUT);
    MGPIO_voidSetPinInputMode(GPIO_PORTC, GPIO_PIN13, GPIO_PULLUP);
    MGPIO_voidSetPinMode(GPIO_PORTC, GPIO_PIN14, GPIO_INPUT);
    MGPIO_voidSetPinInputMode(GPIO_PORTC, GPIO_PIN14, GPIO_PULLUP);

    /* Previous button states */
    u8 prev_button1_state = 1;
    u8 prev_button2_state = 1;

    /* Infinite loop */
    while (1)
    {
        u8 button1_state, button2_state;

        /* Read current button states */
        MGPIO_voidGetPinValue(GPIO_PORTC, GPIO_PIN13, &button1_state);
        MGPIO_voidGetPinValue(GPIO_PORTC, GPIO_PIN14, &button2_state);

        /* Check if button 1 was pressed */
        if (button1_state == GPIO_PIN_LOW && prev_button1_state == GPIO_PIN_HIGH)
        {
        	MUSART_voidTransmit(MUSART_USART1, (u8*)"2", 1);
            LCD_voidClearScreen();
            MSTK_voidDelayus(100000);
            LCD_voidSetPosition(LCD_ROW0, LCD_COLUMN1);
            LCD_voidSendString((u8 *)"   ELKING");
            LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
            LCD_voidSendString((u8 *)"   MONIR");
            MSTK_voidDelayus(100000);
            // Wait until button is released
            while (button1_state == GPIO_PIN_LOW)
            {
                MGPIO_voidGetPinValue(GPIO_PORTC, GPIO_PIN13, &button1_state);
            }
            // Update previous button state
            prev_button1_state = GPIO_PIN_LOW;
        }
        else if (button1_state == GPIO_PIN_HIGH && prev_button1_state == GPIO_PIN_LOW)
        {
            prev_button1_state = GPIO_PIN_HIGH;
        }

        /* Check if button 2 was pressed */
        if (button2_state == GPIO_PIN_LOW && prev_button2_state == GPIO_PIN_HIGH)
        {
        	MUSART_voidTransmit(MUSART_USART1, (u8*)"1", 1);
            LCD_voidClearScreen();
            MSTK_voidDelayus(100000);
            LCD_voidSetPosition(LCD_ROW0, LCD_COLUMN1);
            LCD_voidSendString((u8 *)"   ELHADBA");
            LCD_voidSetPosition(LCD_ROW1, LCD_COLUMN1);
            LCD_voidSendString((u8 *)"   AMR DIAB");
            MSTK_voidDelayus(100000); // Delay to avoid flickering
            // Wait until button is released
            while (button2_state == GPIO_PIN_LOW)
            {
                MGPIO_voidGetPinValue(GPIO_PORTC, GPIO_PIN14, &button2_state);
            }
            // Update previous button state
            prev_button2_state = GPIO_PIN_LOW;
        }
        else if (button2_state == GPIO_PIN_HIGH && prev_button2_state == GPIO_PIN_LOW)
        {
            prev_button2_state = GPIO_PIN_HIGH;
        }
    }
    return 0;
}
void handler_USART(void)
{
    // Receive initial command from USART
    MUSART_voidReceive(MUSART_USART1, &Global_u8RX);
    if (Global_u8RX == '1')
    {
    	HTFT_voidSendPicture(AMRDIAB);

    }
    else if (Global_u8RX == '2')
    {
    	HTFT_voidSendPicture(Monir);
    }
}

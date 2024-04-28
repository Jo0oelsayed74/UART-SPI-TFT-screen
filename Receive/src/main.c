#include "../include/BIT_MATH.h"
#include "../include/STD_Types.h"
#include "../include/RCC/MRCC_Interface.h"
#include "../include/GPIO/MGPIO_Interface.h"
#include "../include/STK/MSTK_interface.h"
#include "../include/SPI/MSPI_interface.h"
#include "../include/TFT/TFT_image.h"
#include "../include/TFT/HTFT_interface.h"
#include "../include/NVIC/MNVIC_Interface.h"
#include "../include/EXTI/MEXTI_Interface.h"
#include "../include/UART/MUSART_Interface.h"
#include "../include/LEDMATRIX/HLEDMATRIX_Interface.h"

// Define constants
#define CHAR_DELAY (20000/2500)
#define ARRAY_SIZE 46

// Global variable to store received data from USART
u8 Global_u8RX;

// USART interrupt handler
void handler_USART(void);

void main(void)
{

    // RCC initialization
    MRCC_voidInit();

    // Enable GPIOA, GPIOB and GPIOC
    MRCC_voidEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOA);
    MRCC_voidEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOB);
    MRCC_voidEnablePeripheral(RCC_AHB1, RCC_AHB1_GPIOC);

    // Enable SPI and UART peripherals
    MRCC_voidEnablePeripheral(RCC_APB2, RCC_APB2_SPI1);
    MRCC_voidEnablePeripheral(RCC_APB2, RCC_APB2_USART1);

    // Pin Configuration of SPI
    MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT); // Reset
    MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT); // A0
    MGPIO_voidSetAltFunction(GPIO_PORTA, GPIO_PIN5, GPIOx_AF5); // SCK
    MGPIO_voidSetAltFunction(GPIO_PORTA, GPIO_PIN7, GPIOx_AF5); // MOSI

    // Configure Pins 9 & 10 TX and RX of UART
    MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN9, GPIO_ALT_FUN);
    MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN10, GPIO_ALT_FUN);
    // Setup the pins of the alternate functions
    MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN9, 0b0111);
    MGPIO_voidSetAlternativeFunction(GPIO_PORTA, GPIO_PIN10, 0b0111);

    // Enable USART interrupt
    MNVIC_voidEnablePeripheralInterrupt(37);
    MSUART_voidSetCallBack(handler_USART);

    // Systick initialization
    MSTK_voidInit();

    // SPI initialization
    MSPI_voidInit();

    // TFT initialization
    HTFT_voidInit();

    // USART initialization
    MUSART_voidInit();
    MUSART_EnableUSART(MUSART_USART1);

    // Configure LED pins
    MGPIO_voidSetPinMode(GPIO_PORTC, GPIO_PIN13, GPIO_OUTPUT); // LED0
    MGPIO_voidSetPinMode(GPIO_PORTC, GPIO_PIN14, GPIO_OUTPUT); // LED1
    MGPIO_voidSetPinMode(GPIO_PORTC, GPIO_PIN15, GPIO_OUTPUT); // LED1

    HLEDMATRIX_voidInit();

    while (1);

}

// USART interrupt handler function
    void handler_USART(void)
    {
        // Receive initial command from USART
        MUSART_voidReceive(MUSART_USART1, &Global_u8RX);
        if(Global_u8RX == '1'){
            // Send picture via TFT
        	HTFT_voidSendPicture(AMRDIAB);

        	//LEDs
        	for (int i = 0; i < 4; i++) {
        	    MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN13,GPIO_PIN_HIGH);
        	    MSTK_voidDelayus(100000);
        	    MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN14,GPIO_PIN_HIGH);
        	    MSTK_voidDelayus(100000);
        	    MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN15,GPIO_PIN_HIGH);
        	    MSTK_voidDelayus(100000);
        	    MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN13,GPIO_PIN_LOW);
        	    MSTK_voidDelayus(100000);
        	    MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN14,GPIO_PIN_LOW);
        	    MSTK_voidDelayus(100000);
        	    MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN15,GPIO_PIN_LOW);
        	    MSTK_voidDelayus(100000);
        	}
        }

        if(Global_u8RX == '2'){
            // Send picture via TFT
        	HTFT_voidSendPicture(Monir);

        	//LEDs
        	for (int i = 0; i < 8; i++){
				MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN13,GPIO_PIN_HIGH);
				MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN14,GPIO_PIN_LOW);
				MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN15,GPIO_PIN_HIGH);
				MSTK_voidDelayus(100000);
				MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN13,GPIO_PIN_LOW);
				MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN14,GPIO_PIN_HIGH);
				MGPIO_voidSetPinValue(GPIO_PORTC,GPIO_PIN15,GPIO_PIN_LOW);
				MSTK_voidDelayus(100000);
        	}
        }
    }


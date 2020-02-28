/**********************************************************
 * [AUTHOR] : Ahmed mohamed
 *
 * [Drivers] : ADC , LCD
 *
 * [DATE] : 25/2/2020
 *
 ***********************************************************/

/*********************************************************************************
 * 									Drivers										 *
 *********************************************************************************/
#include"lcd.h"
#include"adc.h"
#include"thermal_sensor.h"
#include "uart.h"

#define MAX_MESSEGE 20

void BLUETOOTH_init(void)
{
	/**************************************************
	 * [name] : UART_ConfigType
	 * [Type] : Structure
	 * [Function] : UART Module Dynamic configuration
	 * [Members] :
	 * 			Parity_enable enable or disable
	 * 			Parity_type odd disable or even
	 * 			stop_bit 1 or 2
	 * 			character_size 5,6,7,8bits char
	 * 			speed x or U2x
	 * 			type  Sync or Async
	 * 	[DEFAULT] : Baudrate -> 9600 bps
	 ***************************************************/

	UART_ConfigType UART_configStruct = {	UART_PARITY_BIT_DISABLE ,
			UART_PARITY_DISABLE ,
			UART_1_STOP_BIT ,
			UART_8_BIT ,
			UART_2X ,
			UART_ASYNCHRONOUS_OPERATION ,};

	UART_init(&UART_configStruct);
}

void BLUETOOTH_recieve(uint8* str)
{
	UART_receiveString(str);
}
void BLUETOOTH_transmit(uint8* str)
{
	UART_sendString(str);
}
int main(void)
{
	/*initializaiton code*/
	uint8 str[MAX_MESSEGE];
	/*
	 * initializing bluetooth module
	 */
	BLUETOOTH_init();
	/*
	 * creating configuration structure for adc driver
	 */
	ADC_struct ADC_config = {_2_56v , POLLING , F_CPU_8 };
	/*
	 * initiating adc driver
	 */
	ADC_init(&ADC_config);
	/*
	 * initiating lcd driver
	 */
	LCD_init();
	/*
	 * to convert the result current_reading to temperature reading
	 */
	ADC_setCallBack(THERMAL_conversion);
	//CLEAR_BIT(DDRA , 2);
	/*
	 *  setting I-bit for interrupt enable in case you need it
	 */

	GLOBAL_INTERRUPT_ENABLE();

	LCD_displayString((uint8*)"temperature = ");
	/*super loop*/
	while(TRUE)
	{
		/*Application code*/
#if FALSE
		/*
		 * converting ADC2 channel in the ADC module and storing the
		 * sensor reading in "Temp" variable
		 */
		ADC_readChannel(&ADC_config , ADC0);
		/*
		 * displaying that sensor reading
		 */
		LCD_goToColRow(1 , 1);
		LCD_displayInt(Temp);
		LCD_displayString((uint8*)".");
		LCD_displayInt(((uint32)(Temp*10))%10);
#endif

		BLUETOOTH_recieve(str);
		LCD_clearScreen();
		LCD_displayString(str);
	}
}

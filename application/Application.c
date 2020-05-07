/**********************************************************
 * [AUTHOR] : Ahmed mohamed
 *
 * [Drivers] : ADC , LCD , UART
 *
 * [DATE] : 25/2/2020
 *
 ***********************************************************/

/*********************************************************************************
 * 									Drivers										 *
 *********************************************************************************/
#include"lcd.h"
#include"thermal_sensor.h"
#include "uart.h"
#include <stdlib.h>
#define MAX_MESSEGE 50
uint8 output[MAX_MESSEGE];
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

void BLUETOOTH_receiveMessege(uint8* str)
{

	/* messege must be terminated by # to be sent */
	UART_receiveString(str);

}
void BLUETOOTH_sendMessege(uint8* str)
{

	/* messege must be terminated by # to be sent */
	UART_sendString(str);

}
void BLUETOOTH_sendByte(uint8 character)
{

	/* sending ordinary character */
	UART_sendByte(character);

}
uint8 BLUETOOTH_receiveByte(void)
{

	/* receiving ordinary character */
	return UART_receiveByte();

}

void sensorRead(const ADC_struct * config_ptr , ADC_channel a_channel)
{
	/*
	 * converting ADC2 channel in the ADC module and storing the
	 * sensor reading in "Temp" variable
	 */
	ADC_readChannel(config_ptr  ,a_channel);
	/*
	 * displaying that sensor reading
	 */
	LCD_goToColRow(1 , 1);
	LCD_displayInt(Temp);
	LCD_displayString((uint8*)".");
	LCD_displayInt(((uint32)(Temp*10))%10);

}
int main(void)
{
	/*
	LCD_init();
	LCD_displayString((uint8*)"Hello!");
	_delay_ms(1000);
	 */
	/*initializaiton code*/

	uint8 option;
	/*
	 * initializing bluetooth module
	 */
	LCD_init();

	BLUETOOTH_init();
	/*
	 * initiating lcd driver
	 */

	/****************************ADC INIT**********************/
	/*
	 * creating configuration structure for adc driver
	 */
	ADC_struct ADC_config = { _2_56v, POLLING , F_CPU_8 };
	/*
	 * initiating adc driver
	 */
	ADC_init(&ADC_config);
	/*
	 * to convert the result current_reading to temperature reading
	 */
	ADC_setCallBack(THERMAL_conversion);
	/*
	 *  setting I-bit for interrupt enable in case you need it
	 */
	GLOBAL_INTERRUPT_ENABLE();
	/************************************************************/
	LCD_displayString((uint8*)"temperature = ");

	//	sensorRead(&ADC_config , ADC0);
	/*super loop*/
	while(TRUE)
	{
		/*Application code*/
		/*
		 * taking input character from the terminal connected with bluetooth
		 */
		option = UART_receiveByte();
		if(option == '1')
		{
			sensorRead(&ADC_config , ADC0);
		}
		if(option == '2')
		{
			sensorRead(&ADC_config , ADC1);

		}
		if(option == '3')
		{
			sensorRead(&ADC_config , ADC2);

		}

		if(option == '4')
		{
			sensorRead(&ADC_config , ADC3);

		}
	}


}

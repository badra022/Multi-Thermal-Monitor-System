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

int main(void)
{
	/*initializaiton code*/
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
		/*
		 * converting ADC2 channel in the ADC module and storing the
		 * sensor reading in "Temp" variable
		 */
		ADC_readChannel(&ADC_config , ADC2);
		/*
		 * displaying that sensor reading
		 */
		LCD_goToColRow(1 , 1);
		LCD_displayInt(Temp);
		/*
		 * clearing the screen
		 */
	}
}

#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"

int main()
{
	HAL_Init();
	Stm32_Clock_Init(336, 8, 2, 7);
	delay_init(168);
	led_init();
	while(1){
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_SET);
		delay_ms(500);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET);
		delay_ms(500);
		HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_RESET);
	
	}
	
}

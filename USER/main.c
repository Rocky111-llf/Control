#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"

int main()
{
	led_init();
	delay_init(168);
	
	while(1){
		GPIO_ResetBits(GPIOF,GPIO_Pin_9);
		delay_ms(500);
		GPIO_SetBits(GPIOF,GPIO_Pin_9);
		GPIO_ResetBits(GPIOF,GPIO_Pin_10);
		delay_ms(500);
		GPIO_SetBits(GPIOF,GPIO_Pin_10);
	}

}



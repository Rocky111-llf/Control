#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "usart.h"

int main()
{
	HAL_Init();
	Stm32_Clock_Init(336, 8, 2, 7);
	delay_init(168);
	led_init();
	uart_init(115200);
	while(1){
		if (USART_RX_STA & 0x8000)
		{
			int i;
			for (i = 0; i < USART_REC_LEN; i++)
			{
				if(USART_RX_BUF[i] == 0x01){
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_RESET);
					delay_ms(500);
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
					delay_ms(500);
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_SET);
				}
			}
			USART_RX_STA = 0;
		}
		
		
	}
	
}

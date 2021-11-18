#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "uart.h"

int main()
{
	HAL_Init();
	Stm32_Clock_Init(336, 8, 2, 7);
	delay_init(168);
	led_init();
	exti_init();
	uart_init(115200);
	while(1){
		delay_ms(1000);
	}
	// while(1){
	// 	if (uart_rx_state & 0x8000)
	// 	{
	// 		int i;
	// 		for (i = 1; i < (uart_rx_state & 0x3FFF); i++)
	// 		{
	// 			if(i%2 != 0 && uart_rx_buff[i] == 0x01){
	// 				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_RESET);
	// 				delay_ms(500);
	// 				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_SET);
	// 				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
	// 				delay_ms(500);
	// 				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10,GPIO_PIN_SET);
	// 			}else if(i%2 == 0 && uart_rx_buff[i] == 0x02){
	// 				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_RESET);
	// 				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET);
	// 				delay_ms(1000);
	// 				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_SET);
	// 				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10,GPIO_PIN_SET);
	// 			}

	// 		}
	// 		uart_rx_state = 0;
	// 	}
		
		
	// }
	
}

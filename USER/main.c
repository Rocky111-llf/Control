#include "stm32f4xx.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "exti.h"
#include "task2_scheduler.h"

int main()
{
	HAL_Init();
	Stm32_Clock_Init(336, 8, 2, 7);
	delay_init(168);
	led_init();
	exti_init();
	uart_init(115200);
	scheduler_setup();
	while(1){
		scheduler_run();
	}
	
	
}

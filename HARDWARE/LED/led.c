#include "led.h"
#include "delay.h"

void led_init(void){
	GPIO_InitTypeDef GPIO_Initure;
  __HAL_RCC_GPIOF_CLK_ENABLE();          
	
  GPIO_Initure.Pin=GPIO_PIN_9|GPIO_PIN_10; 
  GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
  GPIO_Initure.Pull=GPIO_PULLUP;          
  GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
  HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9|GPIO_PIN_10,GPIO_PIN_SET);
}

void led_switch(void){//实现LED灯交替闪烁
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_RESET);
  delay_ms(10);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10,GPIO_PIN_RESET);
  delay_ms(10);
  HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10,GPIO_PIN_SET);
}

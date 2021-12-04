#include "exti.h"
#include "delay.h"
#include "led.h"

void exti_init(void){
    GPIO_InitTypeDef gpio_init;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    gpio_init.Pin = GPIO_PIN_0;
    gpio_init.Mode = GPIO_MODE_IT_RISING;
    gpio_init.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA, &gpio_init);

    gpio_init.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
    gpio_init.Mode = GPIO_MODE_IT_FALLING;
    gpio_init.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &gpio_init);

    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);

    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    HAL_NVIC_SetPriority(EXTI4_IRQn,2,3);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

void EXTI0_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
void EXTI2_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}
void EXTI3_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}
void EXTI4_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN){
    delay_ms(10);
    switch (GPIO_PIN) {
        case GPIO_PIN_0:
            if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == 1){
                HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_RESET);
            }
            break;
        case GPIO_PIN_2:
            if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2) == 0){
                HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_SET);
            }
            break;
        case GPIO_PIN_3:
            if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3) == 0){
                HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET);
            }
            break;
        case GPIO_PIN_4:
            if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4) == 0){
                HAL_GPIO_WritePin(GPIOF,GPIO_PIN_9,GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOF,GPIO_PIN_10,GPIO_PIN_SET);
            }
            break;
    }
}




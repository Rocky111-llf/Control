#include "uart.h"

uint8_t rx_buff[RX_BUFF_SIZE];
uint8_t uart_rx_buff[DATA_MAX_LEN];
UART_HandleTypeDef uart_handle;
uint16_t uart_rx_state = 0;

void uart_init(uint32_t bound){
    uart_handle.Instance = USART1;
    uart_handle.Init.BaudRate = 115200;
    uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    uart_handle.Init.StopBits = UART_STOPBITS_1;
    uart_handle.Init.Parity = UART_PARITY_NONE;
    uart_handle.Init.Mode = UART_MODE_TX_RX;
    uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    HAL_UART_Init(&uart_handle);

    HAL_UART_Receive_IT(&uart_handle,rx_buff,RX_BUFF_SIZE);

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart){
    GPIO_InitTypeDef gpio_initStruct;
    if(huart->Instance == USART1){
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();

        gpio_initStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        gpio_initStruct.Mode = GPIO_MODE_AF_PP;
        gpio_initStruct.Pull = GPIO_PULLUP;
        gpio_initStruct.Speed = GPIO_SPEED_FAST;
        gpio_initStruct.Alternate = GPIO_AF7_USART1;

        HAL_GPIO_Init(GPIOA, &gpio_initStruct);
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);
        HAL_NVIC_EnableIRQ(USART1_IRQn);

    }

}

void USART1_IRQHandler(void){
    uint32_t timeout = 0;

    HAL_UART_IRQHandler(&uart_handle);
    while (HAL_UART_GetState(&uart_handle) != HAL_UART_STATE_READY)//等待就绪
	{
	    timeout++;////超时处理
        if(timeout>HAL_MAX_DELAY) break;		
	
	}
    timeout = 0;
    while(HAL_UART_Receive_IT(&uart_handle, (uint8_t *)rx_buff, RX_BUFF_SIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
	    timeout++; //超时处理
	    if(timeout>HAL_MAX_DELAY) break;	
	}


}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance==USART1)//如果是串口1
	{
		if((uart_rx_state & 0x8000) == 0)//接收未完成
		{
			if(uart_rx_state & 0x4000)//接收到了0x5B
			{
				if(rx_buff[0] == 0x5D){
					uart_rx_state |= 0x8000;
				}else{
					uart_rx_buff[uart_rx_state & 0x3FFF] = rx_buff[0];
					uart_rx_state++;
					if((uart_rx_state & 0x3FFF)> DATA_MAX_LEN - 1)uart_rx_state = 0;
				} 
			}else{
				if (rx_buff[0] == 0x5B)
				{
					uart_rx_state |= 0x4000;
				}
			}
		}

	}


}


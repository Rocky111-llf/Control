#ifndef __USART1__
#define __USART1__

#include "stm32f4xx.h"

#define RX_BUFF_SIZE 1
#define DATA_MAX_LEN 200

extern UART_HandleTypeDef uart_handle;
extern uint8_t uart_rx_buff[DATA_MAX_LEN];
extern uint16_t uart_rx_state;

void uart_init(uint32_t bound);

#endif

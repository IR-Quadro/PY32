#ifndef _UART_H_
#define _UART_H_

#include "py32f0xx.h"
#include "gpio.h"

#include <stdbool.h>
#include <stdint.h>

void USART1_Init(void);
void UART1_SendChar(uint8_t data);
void UART1_SendString(const char *ptr);
void USART1_Flush(void);

void USART1_IRQHandler(void);

// CallBack Function:
void UART1_RxCpltCallback(volatile char *data);

#endif

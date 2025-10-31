#include "py32f0xx.h"
#include "system_py32f0xx.h"

#include "uart.h"
#include "TIM16.h"

#include <stdio.h>
#include <stdbool.h>

static volatile uint32_t msTicks = 0;

static char UART1_TX_BUFFER[30];

void GPIO_SetPinAsOutput(GPIO_TypeDef *GPIOx,  uint8_t PinNumber);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t PinNumber, uint8_t state);
	
void SysTick_Handler(void);
void delay_ms(uint32_t ms);

void TIM16_IRQHandler(void);


int main(void)
{
	SystemInit();
	
	SysTick_Config(SystemCoreClock / 1000);
	
	
	GPIO_SetPinAsOutput(GPIOA, 13);
	
	USART1_Init();
	TIM16_Init();
	
	sprintf(UART1_TX_BUFFER, "Core Clock: %ul \r\n", SystemCoreClock);
	UART1_SendString(UART1_TX_BUFFER);
	
	UART1_SendString("TIM16 TimeBase\r\n");
	

	while(1)
	{			
		GPIO_WritePin(GPIOA, 13, 1);
		delay_ms(50);		
		GPIO_WritePin(GPIOA, 13, 0);	
		delay_ms(500);		
	}	
}


void SysTick_Handler(void)
{
	msTicks++;
}


void delay_ms(uint32_t ms) 
{
	uint32_t start = msTicks;
	while((msTicks - start) < ms);
}



void UART1_RxCpltCallback(volatile char *data)
{
    UART1_SendString("You sent: ");
    UART1_SendString((const char*)data);
    UART1_SendString("\r\n");
		USART1_Flush();
}


void TIM16_OVFCallback(void)
{
	UART1_SendString("TIM16 OVF ^_^ \r\n");
}

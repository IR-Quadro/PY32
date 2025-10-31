#include "uart.h"

#include <string.h>

#define UART1_RX_BUFFER_SIZE 30


volatile static char UART1_Rx_Buffer[UART1_RX_BUFFER_SIZE];
volatile static uint8_t UART1_Rx_Buffer_Index = 0;

void USART1_Init(void)
{
	// Enable GPIOA Clock
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	
	// Enable UART Clock
	RCC->APBENR2 |= RCC_APBENR2_USART1EN;

	
	//========================> Enable PA2/PA3 for TX/RX: <========================//
	
	// Set PA2/PA3 to Alternate Function
	GPIOA->MODER &= ~(0x3U << (2U * 2U));
	GPIOA->MODER &= ~(0x3U << (3U * 2U));
	
	GPIOA->MODER |= (GPIO_MODE_AF << (2U * 2U));
	GPIOA->MODER |= (GPIO_MODE_AF << (3U * 2U));
	
	// AF1 for USART1
	GPIOA->AFR[0] &= ~(0xFU << (2U * 4U));
	GPIOA->AFR[0] &= ~(0xFU << (3U * 4U));
	
	GPIOA->AFR[0] |= (0x01U << (2U * 4U));
	GPIOA->AFR[0] |= (0x01U << (3U * 4U));
	
	
	// Push-Pull, High Speed, Pull-up
	GPIOA->OTYPER &= ~((0x1U << 2U) | (0x1U << 3U));
	
	GPIOA->OSPEEDR &= ~((0x3U << (2U * 2U)) | (0x3U << (3U * 2U)));
	GPIOA->OSPEEDR |=  ((GPIO_OSPEEDR_HIGHSPEED << (2U * 2U)) | (GPIO_OSPEEDR_HIGHSPEED << (3U * 2U)));
	
	GPIOA->PUPDR &= ~((0x3U << (2U * 2U)) | (0x3 << (3U * 2U)));
	GPIOA->PUPDR |=  ((GPIO_PUPDR_PULLUP << (2U * 2U)) | (GPIO_PUPDR_PULLUP << (3U * 2U)));
	
	
	//========================> UART Setting <========================//
	
	// Baudrate = 9600 (BRR = Fclk / Baud)
	USART1->BRR = 833;
	
	// 8N1 (8Bit Data , Parity None , 1Bit Stop)
	USART1->CR1 &= ~(USART_CR1_M | USART_CR1_PCE);
	
	// Enable Recive & Transmit
	USART1->CR1 |= (USART_CR1_RE | USART_CR1_TE);
	
	//========================> Enable RX Interrupt <========================//
	
	// Enable UART1 RX Inrerrupt
	USART1->CR1 |= (USART_CR1_RXNEIE);
	
	// Enable NVIC for UART1
	NVIC_EnableIRQ(USART1_IRQn);
	
	
	// Enable UART	
	USART1->CR1 |= (USART_CR1_UE);	
}



void UART1_SendChar(uint8_t data)
{
	while(!(USART1->SR & (1U << 7U)));
	USART1->DR = data;
}


void UART1_SendString(const char *ptr)
{
	while(*ptr != '\0')
	{
		UART1_SendChar((uint8_t)*ptr++);
	}
}


void USART1_Flush(void)
{
	memset(UART1_Rx_Buffer, 0, UART1_RX_BUFFER_SIZE);
	UART1_Rx_Buffer_Index = 0;
}


void USART1_IRQHandler(void)
{
	if (USART1->SR & (1U << 5U))
	{
		uint8_t data = (uint8_t)(USART1->DR & 0xFF);
				
		if (data == '\r')
		{
			UART1_Rx_Buffer[UART1_Rx_Buffer_Index] = '\0';
			UART1_Rx_Buffer_Index = 0;
			
			// CallBack Function
			UART1_RxCpltCallback(UART1_Rx_Buffer);
		}
		else if (data == '\n') // ignore '\n'
		{
		}
		else
		{
			if (UART1_Rx_Buffer_Index < sizeof(UART1_Rx_Buffer) - 1)
		  {
				UART1_Rx_Buffer[UART1_Rx_Buffer_Index++] = data;
		  }
			else
			{
				UART1_Rx_Buffer_Index = 0;
			}
		}
		
	}
}

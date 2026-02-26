/**
 * @file    main.c
 * @author  Abolfazl ResalatiFar
 * @github  https://github.com/IR-Quadro
 * @brief   UART Printf implementation using Polling mode for PY32F002A.
 * @version 1.0
 * @date    2026
 */




#include "py32f002ax5.h"
#include "system_py32f0xx.h"

#include "stdio.h"



/* Global variable */
volatile uint32_t msTick = 0;


/* Function prototypes */
void UART1_Init(uint32_t baudrate);
void UART1_SendChar(char ch);
void UART1_SendString(char *str);
void delay_ms(uint32_t ms);



/**
 * @brief Redirects standard printf output to UART1.
 */
int fputc(int ch, FILE *f)
{
  (void)f;
  UART1_SendChar((char)ch);
  return ch;
}




/**
 * @brief Main application entry point.
 */
int main(void)
{
	SysTick_Config(SystemCoreClock / 1000);
	
	/* Initialize UART1 at 115200 bps */
	UART1_Init(115200);
	
	/* Welcome message */
  UART1_SendString("UART Printf Initialized...\r\n");
	
	while(1)
	{
		/* Print formatted message and current tick count */
    printf("System Uptime: %u ms\r\n", msTick);
        
    /* Delay for 1 second */
    delay_ms(1000);
	}	
}




/**
 * @brief  Initializes USART1 with the given baudrate.
 * @param  baudrate: Target baudrate (e.g. 115200)
 */
void UART1_Init(uint32_t baudrate)
{
	/* 1. Enable peripheral clocks */
	RCC->IOPENR  |= RCC_IOPENR_GPIOAEN;			/* Enable GPIOA clock */
	RCC->APBENR2 |= RCC_APBENR2_USART1EN;   /* Enable USART1 clock */
	
	
	/* 2. Configure PA2 as UART1_TX (Alternate Function 1) */
	GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODE2_1;		/* Set to Alternate Function mode */
	
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_Msk;
	GPIOA->AFR[0] |=  GPIO_AFRL_AFSEL2_0;		/* AF1 for Pin 2 */
		
	
  /* 3. Configure Baud Rate */
  USART1->BRR = (SystemCoreClock / baudrate);
	
	
	/* 4. Enable Transmitter and UART peripheral */
	USART1->CR1 |= (USART_CR1_TE
								 |USART_CR1_UE);								 
}



/**
 * @brief Sends a single character through UART1.
 * @param ch: Character to be sent
 */
void UART1_SendChar(char ch)
{
	/* Wait until Transmit Data Register is empty */
	while(!(USART1->SR & USART_SR_TXE));
	USART1->DR = ch;
}



/**
 * @brief Sends a null-terminated string through UART1.
 * @param str: Pointer to the string
 */
void UART1_SendString(char *str)
{
	while(*str)
	{
		UART1_SendChar(*str++);
	}
}



/**
 * @brief SysTick interrupt handler (called every 1ms).
 */
void SysTick_Handler(void)
{
	msTick++;
}



/**
 * @brief Blocking delay in milliseconds.
 * @param ms: Delay duration
 */
void delay_ms(uint32_t ms)
{
	uint32_t start = msTick;
	
	/* Wait until the required number of milliseconds has passed */
	while((msTick - start) < ms);
}

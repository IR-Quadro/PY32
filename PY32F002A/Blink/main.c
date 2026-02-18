#include "py32f0xx.h"
#include "system_py32f0xx.h"


/* Global variable */
volatile uint32_t msTick = 0;


/* Function prototypes */
void delay_ms(uint32_t ms);



int main (void)
{
	
 /* Configure SysTick timer to generate interrupt every 1 ms
  * SystemCoreClock / 1000 => 1 kHz SysTick interrupt
  */
	SysTick_Config(SystemCoreClock / 1000);
	
	
	/* ----- GPIO Configuration for PA2 ----- */
	
	/* 1. Enable Peripheral Clock for GPIOA Port */
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
		
  /* 2. Set PA2 Mode to General Purpose Output (01) */
	GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;	
	GPIOA->MODER |=  GPIO_MODER_MODE2_0;		
		
	/* 3. Set PA2 Output Type to Push-Pull (0) */
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT2_Msk;
	
	/* 4. Set PA2 Output Speed to Low Speed (01) */
	GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED2_Msk;
	GPIOA->OSPEEDR |=  GPIO_OSPEEDR_OSPEED2_0;
	
	
	
	/* ----- GPIO Configuration for PB0 ----- */
	
	/* 1. Enable Peripheral Clock for GPIOB Port */
	RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	
	/* 2. Set PB0 Mode to Input mode (00) */
	GPIOB->MODER &= ~GPIO_MODER_MODE0_Msk;
	
	/* 3. Enable Pull-Up for PB0 */
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD0_Msk;
	GPIOB->PUPDR |=  GPIO_PUPDR_PUPD0_0;
	
	
	while(1)
	{
		
	 /* Main loop
    * Application code can be placed here
    */
		
		if((GPIOB->IDR & GPIO_IDR_ID0) == 0)
		{
			GPIOA->BSRR = GPIO_BSRR_BS2;		
			delay_ms(50);
			GPIOA->BSRR = GPIO_BSRR_BR2;		
			delay_ms(50);
		}
			
	}
}



/* SysTick interrupt handler
 * This function is called every 1 ms
 */
void SysTick_Handler(void)
{
	msTick++;
}



/* Blocking delay function in milliseconds
 * Uses SysTick-based millisecond counter
 */
void delay_ms(uint32_t ms)
{
	uint32_t start = msTick;
	
	/* Wait until the required number of milliseconds has passed */
	while((msTick - start) < ms);
}
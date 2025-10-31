#include "TIM16.h"


void TIM16_Init(void)
{
	RCC->APBENR2 |= RCC_APBENR2_TIM16EN;
	
	TIM16->PSC = 7999;
	TIM16->ARR = 1000;
	
	// Update Genaration
	TIM16->EGR |= TIM_EGR_UG;
	
	// Update Flag Clear
	TIM16->SR  &= ~TIM_SR_UIF;
	
	TIM16->CNT = 0;
	
	// Update Interrupt Enable 
	TIM16->DIER |= TIM_DIER_UIE;
	
	NVIC_EnableIRQ(TIM16_IRQn);
	
	// Enable Counter
	TIM16->CR1 |= TIM_CR1_CEN;
}


void TIM16_IRQHandler(void)
{
	if (TIM16->SR & TIM_SR_UIF) // overflow check
	{  
		TIM16->SR &= ~TIM_SR_UIF;  // Reset Flag   

		// CallBack Function
		TIM16_OVFCallback();
	}
}

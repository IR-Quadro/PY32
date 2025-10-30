#include "gpio.h"

void GPIO_SetPinAsOutput(GPIO_TypeDef *GPIOx,  uint8_t PinNumber)
{
	if (GPIOx == GPIOA) RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	else if (GPIOx == GPIOB) RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	else if (GPIOx == GPIOF) RCC->IOPENR |= RCC_IOPENR_GPIOFEN;
	
	GPIOx->MODER &= ~(0x3UL << (PinNumber * 2));
	GPIOx->MODER |=  (0x1UL << (PinNumber * 2));
	
	GPIOx->OTYPER &= ~(0x1UL << PinNumber);
	
	GPIOx->OSPEEDR &= ~(0x3UL << (PinNumber * 2));
	GPIOx->OSPEEDR |=  (0x1UL << (PinNumber * 2));
	
	GPIOx->PUPDR &= ~(3UL << (PinNumber * 2));
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t PinNumber, uint8_t state)
{
	if (state == 1)
	{
		GPIOx->BSRR = (1UL << PinNumber);
	}
	else
	{
		GPIOx->BSRR = (1UL << (PinNumber + 16));
	}
}
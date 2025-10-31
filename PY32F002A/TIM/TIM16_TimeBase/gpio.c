#include "gpio.h"

void GPIO_SetPinAsOutput(GPIO_TypeDef *GPIOx,  uint8_t PinNumber)
{
	if (GPIOx == GPIOA) RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	else if (GPIOx == GPIOB) RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	else if (GPIOx == GPIOF) RCC->IOPENR |= RCC_IOPENR_GPIOFEN;
	
	// set as Output
	GPIOx->MODER &= ~(3UL << (PinNumber * 2));
	GPIOx->MODER |=  (GPIO_MODE_OUTPUT << (PinNumber * 2));
	
	// set as PushPull
	GPIOx->OTYPER &= ~(1UL << PinNumber);
	
	// set as LowSpeed
	GPIOx->OSPEEDR &= ~(3UL << (PinNumber * 2));
	GPIOx->OSPEEDR |=  (GPIO_OSPEEDR_LOWSPEED << (PinNumber * 2));
	
	// no PULL
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

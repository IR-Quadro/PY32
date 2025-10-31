#ifndef _GPIO_H_
#define _GPIO_H_

#include "py32f0xx.h"
#include <stdint.h>

#define GPIO_MODE_INPUT      				(0U)
#define GPIO_MODE_OUTPUT    				(1U)
#define GPIO_MODE_AF         				(2U)
#define GPIO_MODE_ANALOG     				(3U)

#define GPIO_OTYPER_PUSHPULL  			(0U)
#define GPIO_OTYPER_OPENDRAIN 			(1U)

#define GPIO_OSPEEDR_VERYLOWSPEED 	(0U)
#define GPIO_OSPEEDR_LOWSPEED 			(1U)
#define GPIO_OSPEEDR_HIGHSPEED 			(2U)
#define GPIO_OSPEEDR_VERYHIGHSPEED  (3U)

#define GPIO_PUPDR_NOPULL    				(0U)
#define GPIO_PUPDR_PULLUP    				(1U)
#define GPIO_PUPDR_PULLDOWN  				(2U)


void GPIO_SetPinAsOutput(GPIO_TypeDef *GPIOx,  uint8_t PinNumber);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t PinNumber, uint8_t state);

#endif

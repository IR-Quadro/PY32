#ifndef _GPIO_H_
#define _GPIO_H_

#include "py32f0xx.h"
#include <stdint.h>

void GPIO_SetPinAsOutput(GPIO_TypeDef *GPIOx,  uint8_t PinNumber);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t PinNumber, uint8_t state);

#endif

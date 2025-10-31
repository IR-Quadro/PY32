#ifndef _TIM16_H_
#define _TIM16_H_

#include "py32f0xx.h"

void TIM16_Init(void);

void TIM16_IRQHandler(void);

// CallBack Function
void TIM16_OVFCallback(void);

#endif

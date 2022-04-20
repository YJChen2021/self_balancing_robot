#ifndef _DELAY_H
#define _DELAY_H
#include "stm32f3xx.h"
#include "stdint.h"
#include "stdio.h"

void SystemTick_Init(void);
void Delay_Us(uint32_t t);
void TimeDecrement(void);
void SysTick_Handler(void);

#endif
#ifndef _PWM_H
#define _PWM_H

#include "stm32f3xx.h"
#include <stdio.h>
#include <stdint.h>

void PWM_TIM3_Init(uint16_t, uint16_t);
void PWM_TIM3_Control(uint8_t, uint8_t);
void PWM_Example(void);
#endif
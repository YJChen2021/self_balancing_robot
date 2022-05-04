/**
*****************************************************************************
**
**  File        : usart.c
**
**  Abstract    : stm32f303re Serial Monitor Initialization and Serial Monitor Example
**
**  Environment : System Workbench for MCU / VSCode Platformio
**
**  Distribution: The file is distributed as is, without any warranty of any kind.
**
*****************************************************************************
*/
#include <usart.h>

void Serial_Monitor_Init(){
	/*The order does matter, follow the order*/
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;							//Adavanced High performance Enable Register - GPIO Port A Enable
	GPIOA->MODER |= (0b10 << 4) | (0b10 << 6);					//Mode Register - PA2/PA3 Alternate Function
	GPIOA->AFR[0] |= (7 << 12) | (7 << 8);						//Alternate Function Register - PA2/PA3 Setting
	RCC->APB1ENR = RCC_APB1ENR_USART2EN;						//Advanced Peripheral Enable Register - USART2 Enable
	USART2->BRR = (uint32_t)(72000000 / 9600);					//BaudRate Register - Sys / 9600 
	USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;	//Control Register - TX/RX/Enbale
}
/*
void Serial_Monitor_Example(){
    while(1){
		printf("test\n");
	}
}
*/
#include <delay.h>
#include <stm32f3xx.h>
#include <usart.h>
#include <FXOS8700.h>
#include <FXAS21002C.h>
#include <pwm.h>
#include <stdbool.h>

#define LED_On {GPIOA->ODR |= (1 << 5);}
#define LED_Off {GPIOA->ODR &= ~(1 << 5);}

//#define USART_Example
//#define PWM_Example
//#define IIC_Debug
//#define IIC_Example
void Robot_Init(){
	/***************************************/
	RCC->CR |= 1 << 0;//1: HSI oscillator ON
	FLASH->ACR |= FLASH_ACR_PRFTBE;// Enable Prefetch Buffer 
    // Flash 2 wait state 
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;	
	
	RCC->CFGR |= 0b10 << 0;//System Clock Switch - PLL selected as System Clock 
	RCC->CFGR |= 0b10 << 2;//System Clock Switch - PLL selected as System Clock 
	RCC->CFGR |= 0b0111 << 18;//PLL multiplication factor x9
	RCC->CFGR |= 0b01 << 15;//PLL entry clock source - HSI used as PREDIV1 entry
	RCC->CR |= 1 << 24;
	/***************************************/
	Serial_Monitor_Init();
    SystemTick_Init();
	FXOS8700_Init();
	FXAS21002C_Init();
	//PWM_TIM3_Init(719, 99);
	//RCC->AHBENR |= RCC_AHBENR_GPIOAEN;//LED enable
	//GPIOA->MODER |= 0b01 << (5 * 2);//LED Mode Setting
	//RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
}


int main(void){
	Robot_Init();
	while(1){
		//PWM_TIM3_Control(4, 100);
		//PWM_TIM3_Control(2, 100);
		printf("\n--- start ---\n");
		printf("%f\n", (get_Gyro_X() / 3.14) * 180);
		Delay_Us(5000000);
	}
}
//if SystemClock = 72M
/*
int main(void){
	Robot_Init();

	#ifdef USART_Example
		uint32_t count = 0;
	#endif
	#ifdef IIC_Debug
		uint32_t count = 0;
	#endif
	

	while(1){
		#ifdef USART_Example
			printf("%ld\n", count);
			Delay_Us(1000000);
			count++;
		#endif
		#ifdef PWM_Example
		PWM_TIM3_Control(4, 100);//PC8
		PWM_TIM3_Control(2, 100);
		#endif
		#ifdef IIC_Debug
			printf("scan %ld\n", count);
			Delay_Us(1000000);
			count++;
			IIC_Scan();
		#endif
		#ifdef IIC_Example
			printf("%lf\n", (double)(get_Gyro_Z() / 3.14) * 180);
			//printf("%f\n", (float)get_Accelerometer_Y());
			
			Delay_Us(500000);
		#endif 
	}
}*/
#include <delay.h>
volatile uint32_t TimingDelay;

void SystemTick_Init(void){
	/*SysTick_Config(N) in core_cm4.h, which means "after how many N times of tick will the interrupt occur".
	1 Tick is 1/(SystemCoreClock)[s]. 1ms = 1/1000s = 1 Tick(1/SystemCoreClock s) * (SystemCoreClock/1000).
	SysTick_Config(SystemCoreClock/1000) means that the interrupt occurs every (1/8M s) * (8M/1000)[s] = 1ms.*/
	//SysTick_Config returns 0 = no errors
	//SysTick_Config returns 1 = error
	/*
	using systick_config () function to achieve counting function in the following code SysTick_CTRL_TICKINT_Msk Interrupts are enabled. 
	If your system clock frequencies below 36MHz, best not to let Systick 1us interrupted once, otherwise, 
	most of the system in the implementation of the interrupt routine.
	*/
	if (SysTick_Config((uint32_t)(72000000 / 1000000))){
		while (1){
			;//error
		}
	}
}

void Delay_Us( uint32_t t){
	TimingDelay = t;
	SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;//SysTick Register enable
	while(TimingDelay != 0){
		;
	}
}
void TimeDecrement(void){
	if (TimingDelay != 0){
		TimingDelay--;//Decrement
	}
}

//SysTick-interrupt
void SysTick_Handler(void){
	/*Every time(1ms) when the interrupt occurs, "TimeDelay" in TimeDecrement decreases.*/
	TimeDecrement();
}
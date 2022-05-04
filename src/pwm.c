/*
1.Datsheet Page 48 2. Datasheet Page.56
Port and Pin - Alternate Function - Channel
PC6          - AF2                - TIM3_CH1
PC7          - AF2                - TIM3_CH2
PC8          - AF2                - TIM3_CH3
PC9          - AF2                - TIM3_CH4
**One Timer - one frequency; each Channel - diffenent duty cycle.
*/
#include<pwm.h>
uint16_t arr_global = 0;
void PWM_TIM3_Init(uint16_t psc, uint16_t arr){
    /*Setting for Channels 1-4*/
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;      //Adavanced High-performace Bus Enable Register - Port C Enable
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     //Advanced Peripheral Bus Enable Register - Timer 3 Enable
    GPIOC->MODER |= 0b10 << 12;             //Mode Register - Port C Pin 6: Alternate Function Mode
    GPIOC->MODER |= 0b10 << 14;             //Mode Register - Port C Pin 7: Alternate Function Mode
    GPIOC->MODER |= 0b10 << 16;             //Mode Register - Port C Pin 8: Alternate Function Mode
    GPIOC->MODER |= 0b10 << 18;             //Mode Register - Port C Pin 9: Alternate Function Mode
    GPIOC->AFR[0] |= 0b0010 << 24;          //Alternate Function Register Low - Port C Pin 6: Alternate Function 2
    GPIOC->AFR[0] |= 0b0010 << 28;          //Alternate Function Register Low - Port C Pin 7: Alternate Function 2
    GPIOC->AFR[1] |= 0b0010 << 0;           //Alternate Function Register High - Port C Pin 8: Alternate Function 2
    GPIOC->AFR[1] |= 0b0010 << 4;           //Alternate Function Register High - Port C Pin 9: Alternate Function 2
    /*Setting for Timer 3*/
    TIM3->PSC = psc;                        //Prescaler
    TIM3->ARR = arr;                        //Auto Reload Register
    TIM3->CR1 = TIM_CR1_CEN;                //Control Register 1 - Timer 3 Enable
    arr_global = arr + 1;
}

void PWM_TIM3_Control(uint8_t Channel, uint8_t DutyCycle){        
    DutyCycle = (DutyCycle >= 100) ? (100) : (DutyCycle);
    switch (Channel){
    case 1:
        TIM3->CCMR1 = 0x00;                 //Compare/Capture Mode Register - Reset
        TIM3->CCMR1 = 0 << 16 | 0b110 << 4; //Compare/Capture Mode Register - Ch1 Output Mode, PWM Mode1
        TIM3->CCER = TIM_CCER_CC1E;         //Compare/Capture Enable Register - Ch1 Enable
        TIM3->CCR1 = 100 - DutyCycle;//Compute duty cycle
        break;
    case 2:
        TIM3->CCMR1 = 0x00;                 //Compare/Capture Mode Register - Reset
        TIM3->CCMR1 = 0 << 24 | 0b110 << 12;//Compare/Capture Mode Register  - Ch2 Output Mode, PWM Mode1
        TIM3->CCER = TIM_CCER_CC2E;         //Compare/Capture Enable Register - Ch2 Enable
        TIM3->CCR2 = 100 - DutyCycle;//Compute duty cycle
        break;
    case 3:
        TIM3->CCMR2 = 0x00;                 //Compare/Capture Mode Register - Reset
        TIM3->CCMR2 = 0 << 16 | 0b110 << 4; //Compare/Capture Mode Register  - Ch3 Output Mode, PWM Mode1
        TIM3->CCER = TIM_CCER_CC3E;         //Compare/Capture Enable Register - Ch3 Enable
        TIM3->CCR3 = 100 - DutyCycle;//Compute duty cycle
        break;
    case 4:
        TIM3->CCMR2 = 0x00;                 //Compare/Capture Mode Register - Reset    
        TIM3->CCMR2 = 0 << 24 | 0b110 << 12;//Compare/Capture Mode Register - Ch4 Output Mode, PWM Mode1
        TIM3->CCER = TIM_CCER_CC4E;         //Compare/Capture Enable Register - Ch4 Enable
        TIM3->CCR4 = 100 - DutyCycle;//Compute duty cycle
        break;
    default:
        break;
    }
}
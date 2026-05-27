/*
 * EE 329 A4 Timers and Interrupts
 *******************************************************************************
 * @file           : timer.c
 * @brief          : configures timer and interrupt handler
 * project         : EE 329 S'26 A3
 * authors         : Facundo Soto-Wang
 * version         : 0.1
 * date            : 260415
 * compiler        : STM32CubeIDE v.1.19.0 Build: 14980_20230301_1550 (UTC)
 * target          : NUCLEO-L4A6ZG
 * clocks          : 4 MHz MSI to AHB2
 * @attention      : (c) 2026 STMicroelectronics.  All rights reserved.
 *******************************************************************************
 * PIN ASSIGNMENTS
 * MCO output:          PA8
 * Square wave output:  PA0
 *******************************************************************************
 *******************************************************************************
 * Header format adapted from [Code Appendix by Kevin Vo] pg 5
 */
#include "timer.h"

void TIME_PIN_CONFIG(void){
    TIMER_PORT -> MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1);    // clear mode bits PC0
	TIMER_PORT -> MODER   |=  (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0);// set PC0 as GP output
	TIMER_PORT -> OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1);      // push-pull output
	TIMER_PORT -> PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1);    // no pull-up/pull-down
	TIMER_PORT -> OSPEEDR |=  (3 << GPIO_OSPEEDR_OSPEED0_Pos 
                              |3 << GPIO_OSPEEDR_OSPEED1_Pos);          // very high speed
	TIMER_PORT -> BRR     |=  (TIMER_PIN | ISR_MEAS_PIN);               // preset output low
}   

//function provided by EE329 lab manual 
void setup_TIM2( int iDutyCycle ) {
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;           // enable clock for TIM2
    TIM2->DIER |= (TIM_DIER_CC1IE | TIM_DIER_UIE);  // enable event gen, rcv CCR1
    TIM2->ARR = PERIOD;                             // ARR = T = counts @4MHz
    TIM2->CCR1 = iDutyCycle;                        // ticks for duty cycle
    TIM2->SR &= ~(TIM_SR_CC1IF | TIM_SR_UIF);       // clr IRQ flag in status reg
    NVIC->ISER[0] |= (1 << (TIM2_IRQn & 0x1F));     // set NVIC interrupt: 0x1F
    __enable_irq();                                 // global IRQ enable
    TIM2->CR1 |= TIM_CR1_CEN;                       // start TIM2 CR1
}

//partially modified code from EE329 lab manual 
void TIM2_IRQHandler(void) {              //Interrupt handler for TIM2
    TIMER_PORT->BSRR |= (ISR_MEAS_PIN);   //set pin high on entering ISR
    if (TIM2->SR & TIM_SR_CC1IF) {        // triggered by CCR1 event 
        TIM2->SR &= ~(TIM_SR_CC1IF);      // manage the flag
        TIMER_PORT -> ODR ^= (TIMER_PIN); // <-- toggle output
        TIM2->CCR1 = DUTYCYCLE;           //update counter
    }
    if (TIM2->SR & TIM_SR_UIF) {         // triggered by ARR event
        TIM2->SR &= ~(TIM_SR_UIF);       // manage the flag
    }
    TIMER_PORT->BRR |= (ISR_MEAS_PIN);   //set pin low on ISR exit
}

//function provided by EE329 lab manual 
void setup_MCO_CLK(void) {
   // enable MCO, MCOSEL = 0b0001 to select SYSCLK = MSI (4 MHz source)
   RCC->CFGR = ((RCC->CFGR & ~(RCC_CFGR_MCOSEL)) | (RCC_CFGR_MCOSEL_0));
   // configure MCO output on PA8
   RCC->AHB2ENR   |=  (RCC_AHB2ENR_GPIOAEN);
   GPIOA->MODER   &= ~(GPIO_MODER_MODE8);    	// clear MODER bits to set ...
   GPIOA->MODER   |=  (GPIO_MODER_MODE8_1);	    // MODE = alternate function
   GPIOA->OTYPER  &= ~(GPIO_OTYPER_OT8);     	// push-pull output
   GPIOA->PUPDR   &= ~(GPIO_PUPDR_PUPD8);    	// pullup & pulldown OFF
   GPIOA->OSPEEDR |=  (GPIO_OSPEEDR_OSPEED8);   // high speed
   GPIOA->AFR[1]  &= ~(GPIO_AFRH_AFSEL8);    	// select MCO (AF0) on PA8 (AFRH)
}


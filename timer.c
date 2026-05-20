/*
 * EE
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

//function provided by EE329 lab manual 
void setup_TIM2( int PERIOD ) {
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;           // enable clock for TIM2
    TIM2->DIER |= (TIM_DIER_CC1IE | TIM_DIER_UIE);  // enable event gen, rcv CCR1
    TIM2->ARR = PERIOD;                             // ARR = T = counts @4MHz
    NVIC->ISER[0] |= (1 << (TIM2_IRQn & 0x1F));     // set NVIC interrupt: 0x1F
    __enable_irq();                                 // global IRQ enable
    TIM2->CR1 |= TIM_CR1_CEN;                       // start TIM2 CR1
}


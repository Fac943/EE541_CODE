/*
 *******************************************************************************
 * EE 329 A4 TIMERS & INTERRUPTS
 *******************************************************************************
 * @file           :timer.h
 * @brief          : header file for timer.c
 * project         : EE 329 S'26 A3
 * authors         : Facundo Soto-Wang
 * version         : 0.1
 * date            : 04/24/2026
 * compiler        : STM32CubeIDE v.1.19.0 Build: 14980_20230301_1550 (UTC)
 * target          : NUCLEO-L4A6ZG
 * clocks          : 4 MHz MSI to AHB2
 * @attention      : (c) 2026 STMicroelectronics.  All rights reserved.
 *******************************************************************************
 * PIN ASSIGNMENTS
 *
 *******************************************************************************
 * Header format adapted from [Code Appendix by Kevin Vo] pg 5
 */
#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "stm32l4xx_hal.h"
#include "delay.h"

//define function parameters
#define BUTTON_PRESS ( ((~GPIOC->IDR) >> 13) & 0x1 ) //bool to check button press
#define BUTTON_PORT GPIOC

/*timer.c function declarations*/
void setup_TIM2( int iDutyCycle );
void WAIT_FOR_BUTTON_PRESS(void);
void CONFIG_RNG(void);
void BUTTON_CONFIG(void);

#endif /* INC_TIMER_H_ */
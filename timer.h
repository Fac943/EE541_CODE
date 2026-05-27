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

//define function parameters
#define PERIOD 0xFFFFFFFF  // run TIM2 continuously 
#define DUTYCYCLE 400      //for 50% duty cycle @5kHz

#define TIMER_PORT GPIOE
#define TIMER_PIN    0x1   //PE0
#define ISR_MEAS_PIN 0x2   //PE1

/*timer.c function declarations*/
void setup_TIM2( int iDutyCycle );
void TIME_PIN_CONFIG(void);
void TIM2_IRQHandler(void);
void setup_MCO_CLK(void);
#endif /* INC_TIMER_H_ */
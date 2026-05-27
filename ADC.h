/*
 *******************************************************************************
 * EE 329 A8 NUCLEO ADC & Current Source
 *******************************************************************************
 * @file           : ADC.h
 * @brief          : Header file for ADC.c
 * authors         : Facundo Soto-Wang & Samuel Weston.
 * version         : 0.1
 * date            : 260526
 * compiler        : STM32CubeIDE v.1.19.0 Build: 14980_20230301_1550 (UTC)
 * target          : NUCLEO-L4A6ZG
 * clocks          : 4 MHz MSI to AHB2
 * @attention      : (c) 2026 STMicroelectronics.  All rights reserved.
 *******************************************************************************
 * Header format adapted from [Code Appendix by Kevin Vo] pg 5
 */

#include "stm32l4xx_hal.h"
#include "delay.h"

#ifndef INC_ADC_H_
#define INC_ADC_H_

#define VREF        3300    	// Reference voltage (mV)
#define ADC_MAX     4095    	// 12-bit max (2^12 - 1)
#define M           1000    	// slope of uncalibrated DAC (mV)
#define B           0   	   // y intercept of uncalibrated DAC (mV)

void ADC_init(void);
uint16_t Conv_ADC(void);
uint16_t Get_Min(uint16_t ADC_Samples[]);
uint16_t Get_Avg(uint16_t ADC_Samples[]);
uint16_t Get_Max(uint16_t ADC_Samples[]);
void ADC1_2_IRQHandler(void);

extern volatile uint16_t ADC_sample;
extern volatile uint8_t ADC_DRDY;


#endif /* INC_ADC_H_ */

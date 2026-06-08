/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c - A4 Part D Reaction Timer
 * project         : EE 329 S'26 A4
 * authors         : Facundo Soto-Wang
 * version         : 0.1
 * date            : 2026-04-30
 * compiler        : STM32CubeIDE v.1.19.0
 * target          : NUCLEO-L4A6ZG
 * clocks          : 4 MHz MSI to AHB2
 ******************************************************************************
*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "delay.h"
#include "MOTOR_CNTRL.h"
#include "UART.h"
#include "ADC.h"
#include "NUCLEO.h"
#include "Measure.h"

void Error_Handler(void);
void SystemClock_Config(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

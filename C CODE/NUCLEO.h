/*
 *******************************************************************************
 * EE541
 *******************************************************************************
 * @file           : NUCLEO.h
 * @brief          : header file for NUCLEO.c
 * project         : EE541
 * authors         : Facundo Soto-Wang
 * version         : 0.1
 * date            : 230413
 * compiler        : STM32CubeIDE v.1.19.0 Build: 14980_20230301_1550 (UTC)
 * target          : NUCLEO-L4A6ZG
 * clocks          : 4 MHz MSI to AHB2
 * @attention      : (c) 2026 STMicroelectronics.  All rights reserved.
 *
 *******************************************************************************
 */

/*------------------ Define to prevent recursive inclusion -------------------*/

#ifndef INC_NUCLEO_H_
#define INC_NUCLEO_H_

#include "stm32l4xx_hal.h"

/*----------------------------- Port Definitions -----------------------------*/
#define PBSW_PORT	GPIOC

/*------------------------------ Pin Definitions -----------------------------*/
#define PBSW_PIN 	GPIO_PIN_13

/*------------------------------ Function Shells -----------------------------*/

void PBSW_GPIO_Init( void );
int PBSW_IsPressed( void );
uint8_t PBSW_Debounce( uint32_t samples, uint32_t delay_ms );
uint8_t PBSW_WaitForPress(void);

#endif /* INC_NUCLEO_H_ */

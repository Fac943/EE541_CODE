/*
 *******************************************************************************
 * EE 541 Antenna Measurement System
 *******************************************************************************
 * @file           : lcd.h
 * @brief          : header file for MOTOR_CNTRL.h
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
 *      signal      – ODR bit mask – pin
 * MOTOR1           – 0x0F         – PC0-PC3  (4-phases)
 * MOTOR2           – 0x0F         – PA0-PA3  (4-phases)

 *******************************************************************************
 * Header format adapted from [Code Appendix by Kevin Vo] pg 5
 */

#ifndef INC_MOTOR_CNTRL_H_
#define INC_MOTOR_CNTRL_H_

#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "delay.h"

/* port assignments */
#define M1_PORT GPIOC              // Motor 1 port
#define M2_PORT GPIOF              // Motor 2 port

/* Motor control pin masks (ODR/BSRR bit values) */
#define COILS 0xF          // Pins 0-3 (one for each motor coil)

/* lcd.c function declarations */
void Motor_Config( void );
void Spin_90_Motor( int port );
void Step(int port);
void Step_Reverse(int port);
void Spin_90_Motor_Reverse(int port);

#endif /* INC_LCD_H_ */

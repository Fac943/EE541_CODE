/*
 *******************************************************************************
 * EE 541 Antenna Measurement System
 *******************************************************************************
 * @file           : lcd.h
 * @brief          : header file for lcd.c; contains function prototypes for
 * LCD and LED configuration, initialization, and display functions; defines
 * for LCD control pin masks, data bit mask, and port assignments for
 * NHD-0216HZ-FSW-FBW-33V3C 2x16 character LCD in 4-bit parallel mode
 * project         : EE 329 S'26 A3
 * authors         : Alex Tauber
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

/* port assignments */
#define M1_PORT GPIOC              // Motor 1 port
#define M2_PORT GPIOA              // Motor 2 port

/* Motor control pin masks (ODR/BSRR bit values) */
#define COILS         0xF          // Pins 0-3 (one for each motor coil)

/* Motor control sequence array */
#define Motor_Drive [0b1000, 0b1100, 0b0100, 0x0110, 0b0010, 0b0011, 0b0001, 0b1001]
/* lcd.c function declarations */
void Motor_Config( void );                                    // configure PC8 as LED output
void Spin_360_Motor( void );   
void Spin_90_Motor( void )                                   // initialize LCD in 4-bit mode


#endif /* INC_LCD_H_ */

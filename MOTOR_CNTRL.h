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
#define Motor_Drive [0x7, 0x3, 0xB, 0x9, 0xD, 0xC, 0xE, 0x6]
/* lcd.c function declarations */
void Motor_Config( void );                                    // configure PC8 as LED output
void LCD_init( void );                                      // initialize LCD in 4-bit mode
void LCD_pulse_ENA( void );                                 // generate EN falling edge pulse
void LCD_4b_command( uint8_t command );                     // send high nibble only (wake-up)
void LCD_command( uint8_t command );                        // send full byte in 4-bit mode
void LCD_write_char( uint8_t letter );                      // write single ASCII character
void LCD_write_string( char string[] );                     // write null-terminated string
void LCD_set_cursor( uint8_t row, uint8_t column );         // set DDRAM address by row/column
void LCD_write_intro_message( void );                       // display EE329 A3 TIMER intro
void Prompt_user_4_numbers( void );                         // display digit entry prompt
void Update_entered_numbers( uint8_t nums[4], uint8_t currentCnt ); // update LCD with each digit press
void Wait_for_4_User_Digits( uint8_t lcd_In[4] );           // block until 4 digits entered
void Update_time( uint8_t lcd_In[4] );                      // update LCD countdown display

#endif /* INC_LCD_H_ */

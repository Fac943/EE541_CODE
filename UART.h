/**
 ******************************************************************************
 * @file           : UART.h
 * @brief          : Header for main.c - A7 - UART
 * project         : EE 329 S'26 A7
 * authors         : Facundo Soto-Wang
 * version         : 0.1
 * date            : 2026-04-30
 * compiler        : STM32CubeIDE v.1.19.0
 * target          : NUCLEO-L4A6ZG
 * clocks          : 4 MHz MSI to AHB2
 ******************************************************************************
 */
#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "delay.h"

#define BAUD_DIV (0x22B8)
#define UART_PORT GPIOG

void UART1_INIT(void);
void LPUART_Send(uint32_t ADC_data);
#endif /* INC_UART_H_ */



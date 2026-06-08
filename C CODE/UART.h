/**
 ******************************************************************************
 * @file           : UART.h
 * @brief          : Header for UART.c
 * project         : EE541
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
#include "delay.h"

#define BAUD_DIV (0x22B8)
#define UART_PORT GPIOG



void UART1_INIT(void);
void LPUART_Print(const char *message);
void UART_Print_Char(char c);
void LPUART_Send_ADC_Bytes(uint16_t ADC_Count);
void LPUART_Send_Header(void);
#endif /* INC_UART_H_ */


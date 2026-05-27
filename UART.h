/**
 ******************************************************************************
 * @file           : UART.h
 * @brief          : Header for main.c - A8 - ADC
 * project         : EE 329 S'26 A8
 * authors         : Facundo Soto-Wang & Samuel Weston
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
#define CLEAR "\033[2J"
#define RESET "\033[2J\033[H"
#define HOME "\033[H"
#define CLEAR_ATT "\033[0m"
#define SAVE "\033[7"
#define RET "\033[8"
#define INVIS "\033[?25l"

#define RES 200 //UPDATE THIS WHEN YOU CHOOSE RESISTOR

enum command {
	up, down, forward, back
};

void UART1_INIT(void);
void LPUART_Print(const char *message);
void LPUART_MOVE_CURSOR(int command, char *n);
void UART_Print_Char(char c);
void LPUART_PRINT_ADC(void);
void LPUART_PrintVolts(uint16_t ADC_mV);
void LPUART_UPDATE_VOLTS(uint16_t min, uint16_t avg, uint16_t max);
#endif /* INC_UART_H_ */


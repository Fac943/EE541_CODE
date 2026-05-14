/*
 *******************************************************************************
 * EE 329 A7 UART
 *******************************************************************************
 * @file           : UART.c
 * @brief          : Src file for UART code
 * project         : EE 329 S'26 A7
 * authors         : Facundo Soto-Wang
 * version         : 0.2
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

#include "UART.h"

void UART1_INIT(void){
	PWR->CR2 |= (PWR_CR2_IOSV);              // power avail on PG[15:2] (LPUART1)
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOGEN);   // enable GPIOG clock
	RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN; // enable LPUART clock bridge
	/* USER: configure GPIOG registers MODER/PUPDR/OTYPER/OSPEEDR then
	   select AF mode and specify which function with AFR[0] and AFR[1] */
	UART_PORT -> MODER   &= ~(GPIO_MODER_MODE7 | GPIO_MODER_MODE8);
	UART_PORT -> MODER   |=  (GPIO_MODER_MODE7_1 | GPIO_MODER_MODE8_1);

	UART_PORT -> OTYPER  &= ~(GPIO_OTYPER_OT7 | GPIO_OTYPER_OT8);

	UART_PORT -> PUPDR   &= ~(GPIO_PUPDR_PUPD7 | GPIO_PUPDR_PUPD8);
	UART_PORT -> PUPDR   |= (GPIO_PUPDR_PUPD7_0| GPIO_PUPDR_PUPD8_0);

	UART_PORT -> OSPEEDR |= ((3 << GPIO_OSPEEDR_OSPEED7_Pos) |
									(3 << GPIO_OSPEEDR_OSPEED8_Pos));
	UART_PORT ->AFR[0] &= ~(0x000F << GPIO_AFRL_AFSEL7_Pos);
	UART_PORT ->AFR[0] |=  (0x0008 << GPIO_AFRL_AFSEL7_Pos);
	UART_PORT ->AFR[1] &= ~(0x000F << GPIO_AFRH_AFSEL8_Pos);
	UART_PORT ->AFR[1] |=  (0x0008 << GPIO_AFRH_AFSEL8_Pos);

	LPUART1->CR1 &= ~(USART_CR1_M1 | USART_CR1_M0); // 8-bit data
	LPUART1->CR1 |= USART_CR1_UE;                   // enable LPUART1
	LPUART1->CR1 |= (USART_CR1_TE | USART_CR1_RE);  // enable xmit & recv
	LPUART1->CR1 ~= USART_CR1_RXNEIE;        // enable LPUART1 recv interrupt
	LPUART1->ISR &= ~(USART_ISR_RXNE);       // clear Recv-Not-Empty flag
	LPUART1-> BRR = (BAUD_DIV); /* USER: set baud rate register (LPUART1->BRR) */
	NVIC->ISER[2] = (0 << (LPUART1_IRQn & 0x1F));   // enable LPUART1 ISR
}


void LPUART_Send(uint32_t ADC_data) {
      while(!(LPUART1->ISR & USART_ISR_TXE))// wait for empty xmit buffer
         ;
      LPUART1->TDR = ADC_data;       // send this character
}



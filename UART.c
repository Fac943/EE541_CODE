/*
 *******************************************************************************
 * EE 329 A8 ADC
 *******************************************************************************
 * @file           : UART.c
 * @brief          : Src file for UART code
 * project         : EE 329 S'26 A8
 * authors         : Facundo Soto-Wang & Samuel Weston
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

uint8_t USER_FLAG = 0; //user flag to transition between screens
uint8_t it_count = 0;
uint8_t volatile Cursor_x = 0;
uint8_t volatile Cursor_y = 0;
uint8_t volatile red_timer = 0;


/*-----------------------------------------------------------------------------
 * function : UART1_INIT();
 * INs      : none
 * OUTs     : none
 * action   : inits UART1 for 115200 bps
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
void UART1_INIT(void) {
	PWR->CR2 |= (PWR_CR2_IOSV);              // power avail on PG[15:2] (LPUART1)
	RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOGEN);   // enable GPIOG clock
	RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN; // enable LPUART clock bridge
	/* USER: configure GPIOG registers MODER/PUPDR/OTYPER/OSPEEDR then
	 select AF mode and specify which function with AFR[0] and AFR[1] */
	UART_PORT->MODER &= ~(GPIO_MODER_MODE7 | GPIO_MODER_MODE8);
	UART_PORT->MODER |= (GPIO_MODER_MODE7_1 | GPIO_MODER_MODE8_1);

	UART_PORT->OTYPER &= ~(GPIO_OTYPER_OT7 | GPIO_OTYPER_OT8);

	UART_PORT->PUPDR &= ~(GPIO_PUPDR_PUPD7 | GPIO_PUPDR_PUPD8);
	UART_PORT->PUPDR |= (GPIO_PUPDR_PUPD7_0 | GPIO_PUPDR_PUPD8_0);

	UART_PORT->OSPEEDR |= ((3 << GPIO_OSPEEDR_OSPEED7_Pos)
			| (3 << GPIO_OSPEEDR_OSPEED8_Pos));
	UART_PORT->AFR[0] &= ~(0x000F << GPIO_AFRL_AFSEL7_Pos);
	UART_PORT->AFR[0] |= (0x0008 << GPIO_AFRL_AFSEL7_Pos);
	UART_PORT->AFR[1] &= ~(0x000F << GPIO_AFRH_AFSEL8_Pos);
	UART_PORT->AFR[1] |= (0x0008 << GPIO_AFRH_AFSEL8_Pos);

	LPUART1->CR1 &= ~(USART_CR1_M1 | USART_CR1_M0); // 8-bit data
	LPUART1->CR1 |= USART_CR1_UE;                   // enable LPUART1
	LPUART1->CR1 |= (USART_CR1_TE);                 // enable xmit & recv
	LPUART1->BRR = (BAUD_DIV); /* USER: set baud rate register (LPUART1->BRR) */
}

/*-----------------------------------------------------------------------------
 * function : LPUART_Print();
 * INs      : string enclosed in ""
 * OUTs     : none
 * action   : prints string at cursor position in terminal 
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
void LPUART_Print(const char *message) {
	uint16_t iStrIdx = 0;
	while (message[iStrIdx] != 0) {
		while (!(LPUART1->ISR & USART_ISR_TXE))
			// wait for empty xmit buffer
			;
		LPUART1->TDR = message[iStrIdx];       // send this character
		iStrIdx++;                             // advance index to next char
	}
}

/*-----------------------------------------------------------------------------
 * function : UART1_Print_Char();
 * INs      : single character enclosed in ''
 * OUTs     : none
 * action   : prints single character to terminal 
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
void UART_Print_Char(char c) {
	while (!(LPUART1->ISR & USART_ISR_TXE))
		;
	LPUART1->TDR = c;
}

/*-----------------------------------------------------------------------------
 * function : LPUART_MOVE_CURSOR();
 * INs      : single character enclosed in ''
 * OUTs     : none
 * action   : moves cursor desired distance "forward", "back", "down" or "up" 
 * 			  n times then prints desired test at cursor position
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by LPUART_PRINT_ADC, LPUART_UPDATE_VOLTS
 *----------------------------------------------------------------------------*/
void LPUART_MOVE_CURSOR(int command, char *n) {
	UART_Print_Char('\x1b');
	UART_Print_Char('[');
	LPUART_Print(n);
	switch (command) {
	case up:
		LPUART_Print("A");
		break;

	case down:
		LPUART_Print("B");
		break;

	case forward:
		LPUART_Print("C");
		break;

	case back:
		LPUART_Print("D");
		break;
	}

}

/*-----------------------------------------------------------------------------
 * function : LPUART_PrintVolts();
 * INs      : 16b ADC voltage
 * OUTs     : none
 * action   : prints voltage in form of X.XXX at cursor position
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by LPUART_UPDATE_VOLTS
 *----------------------------------------------------------------------------*/
void LPUART_PrintVolts(uint16_t ADC_mV) {
	uint16_t Volts = ADC_mV / 1000;
	uint16_t milVolts = ADC_mV % 1000;
	UART_Print_Char(Volts + '0'); 						//print ones place (V)
	UART_Print_Char('.');         						//print decimal point
	UART_Print_Char((milVolts / 100) + '0'); //print hundreds place (mV)
	UART_Print_Char(((milVolts / 10) % 10) + '0');  //print tens place (mV)
	UART_Print_Char((milVolts % 10) + '0');			//print ones place (mV)
}

/*-----------------------------------------------------------------------------
 * function : LPUART_PrintHEX();
 * INs      : 16b ADC data
 * OUTs     : none
 * action   : prints data in hex at cursor position in terminal 
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by LPUART_UPDATE_VOLTS
 *----------------------------------------------------------------------------*/
void LPUART_PrintHEX(uint16_t ADC_mV){

}

/*-----------------------------------------------------------------------------
 * function : LPUART_PRINT_ADC();
 * INs      : none
 * OUTs     : none
 * action   : prints initial splash for displaying ADC data
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
void LPUART_PRINT_ADC(void) {
	LPUART_Print(RESET);
	LPUART_Print(HOME);
	LPUART_Print(CLEAR_ATT);
	LPUART_Print(INVIS);

	LPUART_MOVE_CURSOR(down, "8");
	LPUART_MOVE_CURSOR(forward, "24");
	LPUART_Print("|----|----|----|----|----|----|");

	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "9");
	LPUART_MOVE_CURSOR(forward, "24");
	LPUART_Print("0   0.5  1.0  1.5  2.0  2.5  3.0");

	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "11");
	LPUART_MOVE_CURSOR(forward, "31");
	LPUART_Print("ADC counts volts");

	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "12");
	LPUART_MOVE_CURSOR(forward, "31");
	LPUART_Print("MIN  XXXX  X.XXX V");

	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "13");
	LPUART_MOVE_CURSOR(forward, "31");
	LPUART_Print("MAX  XXXX  X.XXX V");

	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "14");
	LPUART_MOVE_CURSOR(forward, "31");
	LPUART_Print("AVG  XXXX  X.XXX V");

	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "15");
	LPUART_MOVE_CURSOR(forward, "29");
	LPUART_Print("coil current = X.XXX A");
}

/*-----------------------------------------------------------------------------
 * function : LPUART_UPDATE_VOLTS();
 * INs      : 16b ADC min, avg, max voltages
 * OUTs     : none
 * action   : updates ADC values in splash screen table and bar graph
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
void LPUART_UPDATE_VOLTS(uint16_t min, uint16_t avg, uint16_t max) {
	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "7");
	LPUART_MOVE_CURSOR(forward, "24");

	//update bar based on average voltage value
	if (avg > 3000) {		   //maxed out voltage
		LPUART_Print("###############################");
	} else if (avg < 100) {   //voltage = 0
		LPUART_Print("#");
		LPUART_Print("                             ");
	} else {                  //for voltages between 0-3V
		uint8_t Bar_Length = (avg / 100);   //calculate length of bar
		uint8_t Empty = (31 - Bar_Length);  //spaces needed to clear unused bar
		LPUART_Print("#");
		while (Bar_Length > 0) {
			LPUART_Print("#");
			Bar_Length--;
		}
		while (Empty > 0) {
			LPUART_Print(" ");
			Empty--;
		}
	}
	//display voltages
	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "12");
	LPUART_MOVE_CURSOR(forward, "42");
	LPUART_PrintVolts(min);

	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "13");
	LPUART_MOVE_CURSOR(forward, "42");
	LPUART_PrintVolts(avg);

	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "14");
	LPUART_MOVE_CURSOR(forward, "42");
	LPUART_PrintVolts(max);

	uint16_t Current = (avg / RES);
	LPUART_Print(HOME);
	LPUART_MOVE_CURSOR(down, "15");
	LPUART_MOVE_CURSOR(forward, "44");
	LPUART_PrintVolts(Current);
}

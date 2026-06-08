/******************************************************************************
 * @file           : MOTOR_CNTRL.c
 * @brief          : functions needed to spin motor
 * Author			     : Facundo Soto-Wang
 * Date            : 04052026
 * Target          : STM32F446RE
 * @attention      : (c) 2026 STMicroelectronics.
 ******************************************************************************
 * motor plan :
 * configure
 *******************************************************************************
 * MOTOR WIRING (28BYJ-48)
 *      peripheral – Nucleo I/O
 *******************************************************************************
 * PIN DEFINITIONS (see MOTOR_CNTRL.h)
 *******************************************************************************
 */

#include "MOTOR_CNTRL.h"

/*-----------------------------------------------------------------------------
 * function : MOTOR_Config( )
 * INs      : none
 * OUTs     : none
 * action   : configures PC0-3 & PA0-3 as general purpose push-pull output, no pull,
 *            high speed; presets motor controls low
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 4/22/2026
 * usage    : called in main.c before main loop
 *----------------------------------------------------------------------------*/
void Motor_Config(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOFEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	//clear mode register pits for pins 0-3 in Port C and A
	M1_PORT->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2
			| GPIO_MODER_MODE3);
	M2_PORT->MODER &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2
			| GPIO_MODER_MODE3);
	//set pins 0-3 in port C and A to output mode
	M1_PORT->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0
			| GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);
	M2_PORT->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0
			| GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);
	// set pins 0-3 in port C and A to push-pull outputs
	M1_PORT->OTYPER &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 |
	GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);
	M2_PORT->OTYPER &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 |
	GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3);
	// no pull-up/pull-down
	M1_PORT->PUPDR &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 |
	GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);
	M2_PORT->PUPDR &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 |
	GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);
	// very high speed outputs
	M1_PORT->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED0_Pos
			| 3 << GPIO_OSPEEDR_OSPEED1_Pos | 3 << GPIO_OSPEEDR_OSPEED2_Pos
			| 3 << GPIO_OSPEEDR_OSPEED3_Pos);
	M2_PORT->OSPEEDR |= (3 << GPIO_OSPEEDR_OSPEED0_Pos
			| 3 << GPIO_OSPEEDR_OSPEED1_Pos | 3 << GPIO_OSPEEDR_OSPEED2_Pos
			| 3 << GPIO_OSPEEDR_OSPEED3_Pos);
	// preset both motors off
	M1_PORT->BRR |= (0xF);
	M2_PORT->BRR |= (0xF);
}

void Step(int port) {
	const uint8_t Motor_Drive[] = { 0b1000, 0b1100, 0b0100, 0b0110, 0b0010,
			0b0011, 0b0001, 0b1001 };

	for (int i = 0; i < 8; i++) {
		delay_us(250);

		switch (port) {
		case 1:
			M1_PORT->BRR = 0xF;
			M1_PORT->BSRR = Motor_Drive[i];
			break;
		case 2:
			M2_PORT->BRR = 0xF;
			M2_PORT->BSRR = Motor_Drive[i];
			break;
		}
	}
	M1_PORT->BRR = 0xF;
	M2_PORT->BRR = 0xF;
}

void Spin_90_Motor(int port) {
	uint16_t step_cnt = 128; //number of steps for 90 degree turn
	while (step_cnt > 0) {
		Step(port);
		step_cnt--;
	}
}

void Step_Reverse(int port) {
	const uint8_t Motor_Drive[] = { 0b1000, 0b1100, 0b0100, 0b0110, 0b0010,
			0b0011, 0b0001, 0b1001 };
	for (int i = 7; i >= 0; i--) {
		delay_us(200);
		switch (port) {
		case 1:
			M1_PORT->BRR = 0xF;
			M1_PORT->BSRR = Motor_Drive[i];
			break;
		case 2:
			M2_PORT->BRR = 0xF;
			M2_PORT->BSRR = Motor_Drive[i];
			break;
		}
	}
	M1_PORT->BRR = 0xF;
	M2_PORT->BRR = 0xF;
}

void Spin_90_Motor_Reverse(int port) {
	uint16_t step_cnt = 128;
	while (step_cnt > 0) {
		Step_Reverse(port);
		step_cnt--;
	}
}

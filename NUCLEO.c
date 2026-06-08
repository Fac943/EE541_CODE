/*
 *******************************************************************************
 * EE541
 *******************************************************************************
 * @file           : NUCLEO.c
 * @brief          : Inits on board LED (LD2), contains function to toggle LED
 * project         : EE 541
 * authors         : Facundo Soto-Wang
 * version         : 0.1
 * date            : 230413
 * compiler        : STM32CubeIDE v.1.19.0 Build: 14980_20230301_1550 (UTC)
 * target          : NUCLEO-L4A6ZG
 * clocks          : 4 MHz MSI to AHB2
 * @attention      : (c) 2026 STMicroelectronics.  All rights reserved.
 *******************************************************************************
 * Header format adapted from [Code Appendix by Kevin Vo] pg 5*/

#include "NUCLEO.h"

/*-----------------------------------------------------------------------------
 * function : PBSW_GPIO_Init();
 * INs      : none
 * OUTs     : none
 * action   : configures on-board pushbutton switch as input
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260517
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
void PBSW_GPIO_Init(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	GPIOC->MODER &= ~(GPIO_MODER_MODE13);
	GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13);
}

/*-----------------------------------------------------------------------------
 * function : PBSW_IsPressed();
 * INs      : none
 * OUTs     : none
 * action   : returns 1 if B1 is pressed and 0 otherwise
 * authors  : Facundo Soto-Wang 
 * version  : 0.1
 * date     : 260528
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
int PBSW_IsPressed(void) {
	return (PBSW_PORT->IDR & PBSW_PIN);
}

/*-----------------------------------------------------------------------------
 * function : PBSW_Debounce();
 * INs      : none
 * OUTs     : none
 * action   : returns 1 if B1 is debounced and pressed and 0 otherwise
 * authors  : Facundo Soto-Wang 
 * version  : 0.1
 * date     : 260528
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/

uint8_t PBSW_Debounce( uint32_t samples, uint32_t delay ) {
	uint32_t count = 0;
	for( uint8_t i = 0; i<samples; i++ ) {
		if ( PBSW_PORT->IDR & PBSW_PIN ) {
			count++;
		}
		// small delay between samples
		for ( uint32_t loopIdx = 0; loopIdx < delay; loopIdx++ ) {
			; // nop
		}
	}

	// If the number of samples measuring high > 50% return 1, else 0
	return ( count > (samples / 2U) ) ? 1U : 0U;
}

/*-----------------------------------------------------------------------------
 * function : PBSW_WaitForPress();
 * INs      : none
 * OUTs     : 1 if valid button press detected
 * action   : checks for button press, debounces it, waits for release
 * authors  : Facundo Soto-Wang & Samuel Weston
 * version  : 0.1
 * date     : 260602
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
uint8_t PBSW_WaitForPress(void) {
    if(PBSW_IsPressed()) {
        if(PBSW_Debounce(20U, 1000U)) {
            // wait for release
            while(PBSW_IsPressed()) {
                ;
            }
            return 1U;
        }
    }
    return 0U;
}

  /******************************************************************************
  * @file           : MOTOR_CNTRL.c
  * @brief          : functions needed to spin motor  
  * Author			    : Facundo Soto-Wang
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
 * action   : configures PC8 as general purpose push-pull output, no pull,
 *            high speed; presets pin low (LED off)
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 4/22/2026
 * usage    : called in main.c before main loop
 *----------------------------------------------------------------------------*/
void LED_Config(void){

	M1_PORT  -> MODER   &= ~(GPIO_MODER_MODE8);         // clear mode bits PC8
	M1_PORT  -> MODER   |=  (GPIO_MODER_MODE8_0);       // set PC8 as GP output
	M1_PORT -> OTYPER  &= ~(GPIO_OTYPER_OT8);          // push-pull output
	M1_PORT -> PUPDR   &= ~(GPIO_PUPDR_PUPD8);         // no pull-up/pull-down
	M1_PORT -> OSPEEDR |=  (3 << GPIO_OSPEEDR_OSPEED8_Pos); // very high speed
	M1_PORT -> BRR     |=  (GPIO_PIN_8);               // preset LED off (LO)

}
	
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
 * action   : configures PC0-3 & PA0-3 as general purpose push-pull output, no pull,
 *            high speed; presets motor controls low
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 4/22/2026
 * usage    : called in main.c before main loop
 *----------------------------------------------------------------------------*/
void Motor_Config(void){
  //clear mode register pits for pins 0-3 in Port C and A
	M1_PORT  -> MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 
                          | GPIO_MODER_MODE2 | GPIO_MODER_MODE3); 
	M2_PORT  -> MODER   &= ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 
                          | GPIO_MODER_MODE2 | GPIO_MODER_MODE3); 
  //set pins 0-3 in port C and A to output mode
  M1_PORT  -> MODER   |=  (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0
                          | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);     
  M2_PORT  -> MODER   |=  (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0
                          | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0);  
  // set pins 0-3 in port C and A to push-pull outputs
	M1_PORT  -> OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 |
                           GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3 );          
  M2_PORT  -> OTYPER  &= ~(GPIO_OTYPER_OT0 | GPIO_OTYPER_OT1 |
                           GPIO_OTYPER_OT2 | GPIO_OTYPER_OT3 );  
  // no pull-up/pull-down
	M1_PORT  -> PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | 
                           GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3);         
  M2_PORT  -> PUPDR   &= ~(GPIO_PUPDR_PUPD0 | GPIO_PUPDR_PUPD1 | 
                           GPIO_PUPDR_PUPD2 | GPIO_PUPDR_PUPD3); 
  // very high speed outputs           
	M1_PORT -> OSPEEDR |=  (3 << GPIO_OSPEEDR_OSPEED0_Pos | 
                          3 << GPIO_OSPEEDR_OSPEED1_Pos
                          3 << GPIO_OSPEEDR_OSPEED2_Pos
                          3 << GPIO_OSPEEDR_OSPEED3_Pos); 
  M2_PORT -> OSPEEDR |=  (3 << GPIO_OSPEEDR_OSPEED0_Pos | 
                          3 << GPIO_OSPEEDR_OSPEED1_Pos
                          3 << GPIO_OSPEEDR_OSPEED2_Pos
                          3 << GPIO_OSPEEDR_OSPEED3_Pos);
  // preset both motors off
	M1_PORT -> BRR     |=  (0xF);  
  M2_PORT -> BRR     |=  (0xF);
}

void Spin_360_Motor(void){

}

void Spin_90_Motor(void){

}
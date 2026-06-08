/*
 *******************************************************************************
 * EE541 Antenna Measurement System
 *******************************************************************************
 * @file           : ADC.c
 * @brief          : Inits ADC1 in port A, functions to read data from PA0
 * project         : EE 329 S'26 A8
 * authors         : Facundo Soto-Wang
 * version         : 0.1
 * date            : 260523
 * compiler        : STM32CubeIDE v.1.19.0 Build: 14980_20230301_1550 (UTC)
 * target          : NUCLEO-L4A6ZG
 * clocks          : 4 MHz MSI to AHB2
 * @attention      : (c) 2026 STMicroelectronics.  All rights reserved.
 * ADC WIRING
 * PA0  put connetor pin -> relay NO to resistor node
 *******************************************************************************
 * Header format adapted from [Code Appendix by Kevin Vo] pg 5
 */

#include "ADC.h"

volatile uint16_t ADC_sample = 0;
volatile uint8_t ADC_DRDY = 0;
/*-----------------------------------------------------------------------------
 * function : ADC_init();
 * INs      : none
 * OUTs     : none
 * action   : initializes ADC1 CH5 with Vref = 3.3V
 * authors  : EE329 Lab Manual - A8 sample code - Modified by Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
void ADC_init(void){
   RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;         // turn on clock for ADC
// power up & calibrate ADC
   ADC123_COMMON->CCR |= (1 << ADC_CCR_CKMODE_Pos); // clock source = HCLK/1
   ADC1->CR &= ~(ADC_CR_DEEPPWD);             // disable deep-power-down
   ADC1->CR |= (ADC_CR_ADVREGEN);             // enable V regulator - see RM 18.4.6
   delay_us(20);                              // wait 20us for ADC to power up
   ADC1->DIFSEL &= ~(ADC_DIFSEL_DIFSEL_5);    // PA0=ADC1_IN5, single-ended
   ADC1->CR &= ~(ADC_CR_ADEN | ADC_CR_ADCALDIF); // disable ADC, single-end calib
   ADC1->CR |= ADC_CR_ADCAL;                  // start calibration
   while (ADC1->CR & ADC_CR_ADCAL) {;}        // wait for calib to finish
   // enable ADC
   ADC1->ISR |= (ADC_ISR_ADRDY);              // set to clr ADC Ready flag
   ADC1->CR |= ADC_CR_ADEN;                   // enable ADC
   while(!(ADC1->ISR & ADC_ISR_ADRDY)) {;}    // wait for ADC Ready flag
   ADC1->ISR |= (ADC_ISR_ADRDY);              // set to clr ADC Ready flag
   // configure ADC sampling & sequencing
   ADC1->SQR1  |= (5 << ADC_SQR1_SQ1_Pos);    // sequence = 1 conv., ch 5
   ADC1->SMPR1 |= (1 << ADC_SMPR1_SMP5_Pos);  // ch 5 sample time = 6.5 clocks
   ADC1->CFGR  &= ~( ADC_CFGR_CONT  |         // single conversion mode
                  ADC_CFGR_EXTEN |         // h/w trig disabled for s/w trig
                  ADC_CFGR_RES   );        // 12-bit resolution

   // configure & enable ADC interrupt
   ADC1->IER |= ADC_IER_EOCIE;                // enable end-of-conv interrupt
   ADC1->ISR |= ADC_ISR_EOC;                  // set to clear EOC flag
   NVIC->ISER[0] = (1<<(ADC1_2_IRQn & 0x1F)); // enable ADC interrupt service
   __enable_irq();                            // enable global interrupts

   //GPIO config
   RCC->AHB2ENR  |= (RCC_AHB2ENR_GPIOAEN);    // AHB2 clock to GPIOA
   GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL0); 			// clear alt function
   GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL0_Pos); 	// SEL AF 7 for CH5 of ADC1
   GPIOA->MODER  |= (GPIO_MODER_MODE0);       // analog mode

   ADC1->CR |= ADC_CR_ADSTART;                // start 1st conversion
}

/*-----------------------------------------------------------------------------
 * function : Conv_ADC();
 * INs      : none
 * OUTs     : 16 bit ADC voltage reading (mV)
 * action   : reads ADC data register,
 *            converts to voltage with calibrated slope and offset
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by ADC1_2_IRQHandler
 *----------------------------------------------------------------------------*/
uint16_t Conv_ADC(void){
   uint16_t ADC_Data = ADC1->DR;
   return ADC_Data;
}

/*-----------------------------------------------------------------------------
 * function : Get_Min();
 * INs      : none
 * OUTs     : 16b Min voltage of ADC sample array [20]
 * action   : Finds min voltage in 20 element wide array
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
uint16_t Get_Min(uint16_t ADC_Samples[], uint8_t size){
   uint16_t Min_volts = ADC_Samples[0];
   for(uint8_t i = 1; i < size; i++){
      if(ADC_Samples[i] < Min_volts){
         Min_volts = ADC_Samples[i];
      }
   }
   return Min_volts;
}

/*-----------------------------------------------------------------------------
 * function : Get_Avg();
 * INs      : none
 * OUTs     : 16b avg voltage of ADC sample array [20]
 * action   : calculates avg voltage in 20 element wide array
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
uint16_t ADC_filter(uint16_t ADC_Samples[], uint8_t size){
   //uint32_t Sum_volts = 0;
   //uint16_t Avg_volts = 0;
   //for(uint8_t i = 0; i < size; i++){
   	//Sum_volts += ADC_Samples[i];
   //}

   uint16_t max_volts = Get_Max(ADC_Samples, size);
   //uint16_t min_volts = Get_Min(ADC_Samples, size);

   //throw out outliers and average
   //Avg_volts = ((uint32_t)(Sum_volts-(min_volts+ max_volts)) / (size-2));
   return (uint16_t)max_volts;
}

/*-----------------------------------------------------------------------------
 * function : Get_Max();
 * INs      : none
 * OUTs     : 16b Max voltage of ADC sample array [20]
 * action   : Finds max voltage in 20 element wide array
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
uint16_t Get_Max(uint16_t ADC_Samples[], uint8_t size){
   uint16_t Max_volts = ADC_Samples[0];
   for(uint8_t i = 1; i < size; i++){
      if(ADC_Samples[i] > Max_volts){
         Max_volts = ADC_Samples[i];
      }
   }
   return Max_volts;
}

/*-----------------------------------------------------------------------------
 * function : ADC1_2_IRQHandler();
 * INs      : none
 * OUTs     : none
 * action   : When data is ready, EOC flag is raised
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260523
 * usage    : called by ADC1_2_IRQHandler
 *----------------------------------------------------------------------------*/
void ADC1_2_IRQHandler(void){
	if(ADC1->ISR & ADC_ISR_EOC){
		ADC_sample = Conv_ADC();   //get sample
		ADC_DRDY = 1;              //set data ready flag
	   ADC1->ISR = ADC_ISR_EOC;   //clear EOC flag
	}
}

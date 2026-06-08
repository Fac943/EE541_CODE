/*
 *******************************************************************************
 * EE541
 *******************************************************************************
 * @file           : measure.c
 * @brief          : has logic for measuring antenna
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

#include "Measure.h"
/*-----------------------------------------------------------------------------
 * function : MeasureAndTransmitSweep();
 * INs      : none
 * OUTs     : none
 * action   : measures antenna signal then steps motor for a whole 360
 * authors  : Facundo Soto-Wang
 * version  : 0.1
 * date     : 260517
 * usage    : called by main.c
 *----------------------------------------------------------------------------*/
void MeasureAndTransmitSweep(void)
{
    uint16_t Samples[20];
    uint8_t Sample_cnt = 0;
    uint16_t Step_cnt = 2695;

    while(Step_cnt > 0)
    {
        if(Sample_cnt < 20)
        {
            while(!ADC_DRDY);

            Samples[Sample_cnt] = ADC_sample;
            Sample_cnt++;
            ADC_DRDY = 0;
            ADC1->CR |= ADC_CR_ADSTART;
        }
        else
        {
            Sample_cnt = 0;
            uint16_t ADC_count = ADC_filter(Samples,20);
            LPUART_Send_ADC_Bytes(ADC_count);
            Step(1);
            Step_cnt--;
        }
    }
}



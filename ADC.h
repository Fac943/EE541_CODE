/*
 * ADC.h
 *
 *  Created on: May 19, 2026
 *      Author: facun
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

void ADC_init(void);
void Sample_Angle(void);

extern volatile uint16_t ADC_Samples [20];
extern volatile uint16_t ADC_SampleCount;

#endif /* INC_ADC_H_ */

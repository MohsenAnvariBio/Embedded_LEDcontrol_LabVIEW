/*
 * main_app.h
 *
 *  Created on: Jul 31, 2024
 *      Author: Mohsen PC
 */

#ifndef INC_MAIN_APP_H_
#define INC_MAIN_APP_H_

#include "stm32f4xx_hal.h"

#define SYS_CLOCK_FREQ_50_MHZ 50
#define SYS_CLOCK_FREQ_84_MHZ 84
#define SYS_CLOCK_FREQ_120_MHZ 120

#define TRUE 1
#define FALSE 0

void HAL_MspInit(void);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);

#endif /* INC_MAIN_APP_H_ */

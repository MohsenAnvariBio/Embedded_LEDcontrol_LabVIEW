/*
 * it.c
 *
 *  Created on: Aug 7, 2024
 *      Author: Mohsen PC
 */
#include "main_app.h"
extern TIM_HandleTypeDef htimer2;
extern TIM_HandleTypeDef htimer6;
extern UART_HandleTypeDef huart2;

#include "main_app.h"
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer2);
}
void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart2);
}
















































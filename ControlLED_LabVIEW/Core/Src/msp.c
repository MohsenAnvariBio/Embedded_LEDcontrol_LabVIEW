/*
 * msp.c
 *
 *  Created on: Aug 7, 2024
 *      Author: Mohsen PC
 */

#include "main_app.h"

void HAL_MspInit(void)
{
	//Here will do low level processor specific inits.

	//1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions of the arm cortex
	SCB->SHCSR |= (0x07<<16);//usage fault, memory fault and bus fault system exceptions

	//3. configure the priority for the system exceptions

	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0); // memory location is not valid
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;

	//1. enable the clock for the USART2 peripheral as well as for GPIO port A peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//2. do the pin muxing configurations
	gpio_uart.Pin = GPIO_PIN_2; // USART2 Tx
	gpio_uart.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3; // USART2 Rx
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	//3. enable the IRQ and set up the priority, NVIC settings.
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}



void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef gpio_tim2oc;

	//PA0 - CH1
	//PA1 - CH2
	//PB10 - CH3
	//PB2 - CH4

	//1. enable the clock for the TIM2 peripheral as well as for GPIO port A and B peripheral
	  __HAL_RCC_TIM2_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
//	  __HAL_RCC_GPIOB_CLK_ENABLE();

	//2. Configure a gpio to behave as timer2 channel 1, 2, 3 and 4
	gpio_tim2oc.Pin = GPIO_PIN_0;// | GPIO_PIN_1;
	gpio_tim2oc.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_tim2oc.Pull = GPIO_NOPULL;
	gpio_tim2oc.Mode = GPIO_MODE_AF_PP;
	gpio_tim2oc.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &gpio_tim2oc);

//	gpio_tim2oc.Pin = GPIO_PIN_10 | GPIO_PIN_2;
//	gpio_tim2oc.Speed = GPIO_SPEED_FREQ_LOW;
//	gpio_tim2oc.Pull = GPIO_NOPULL;
//	gpio_tim2oc.Mode = GPIO_MODE_AF_PP;
//	gpio_tim2oc.Alternate = GPIO_AF1_TIM2;
//	HAL_GPIO_Init(GPIOB, &gpio_tim2oc);

	//3. enable the IRQ and set up the priority, NVIC settings.
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
}















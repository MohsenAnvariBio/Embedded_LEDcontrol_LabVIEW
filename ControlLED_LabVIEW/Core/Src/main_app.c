/*
 * main_app.c
 *
 *  Created on: Aug 7, 2024
 *      Author: Mohsen PC
 */

#include "stm32f4xx_hal.h"
#include "main_app.h"
#include <string.h>
#include <stdio.h>


void SystemClock_Config_HSE(uint32_t clock_freq);
void SystemClockConfig(void);
void Error_handler(void);
void TIMER2_Init(void);
void GPIO_Init(void);
void UART2_Init(void);

TIM_HandleTypeDef htimer2;
UART_HandleTypeDef huart2;
TIM_OC_InitTypeDef timer2PWM_Config;

volatile uint8_t new_data_available = 0;


uint8_t pData = 1;

char msg[100];

int main(void)
{
	HAL_Init();

	SystemClock_Config_HSE(SYS_CLOCK_FREQ_50_MHZ);

	UART2_Init();
	GPIO_Init();

	TIMER2_Init();

	if( HAL_TIM_PWM_Start_IT(&htimer2,TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}

	while(1)
	{

        HAL_UART_Receive_IT(&huart2, &pData, 1);  // Re-enable the UART receive interrupt
        HAL_Delay(100);

//		char data_receive[100];
//		for (int i = 0; i <4; i++)
//		{
//			HAL_UART_Receive(&huart2, &pData, 1, HAL_MAX_DELAY);
//			data_receive[i] = pData;
//		}
//		HAL_UART_Receive(&huart2, &pData, 1, HAL_MAX_DELAY);
//		__HAL_TIM_SET_COMPARE(&htimer2, TIM_CHANNEL_1, pData);


	}

	return 0;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        new_data_available = 1;
//        HAL_UART_Receive_IT(&huart2, &pData, 1);  // Re-enable the UART receive interrupt
    }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (new_data_available)
    {
        new_data_available = 0;
        __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, (htimer2.Init.Period * pData) / 100);
    }
}




//	if (pData != pdata_buffer)
//	{
//		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, (pData));
//		pdata_buffer = pData;
//
//	}else
//	{
//		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, (pdata_buffer));
//	}



//	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
//	{
//
//		uint8_t step = 5;
//		if(count%step == 0)
//		{
//			__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, duty_cycle*(count/step));
//		}
//		if(count == 99*step)
//		{
//			count = 1;
//		}
//		count++;
//	}






void GPIO_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;

	//2. do the pin configurations
	ledgpio.Pin = GPIO_PIN_8; // LED pin on the my board
	ledgpio.Pull = GPIO_PULLUP;
	ledgpio.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA, &ledgpio);
}

void TIMER2_Init(void)
{


	htimer2.Instance = TIM2;
	htimer2.Init.Prescaler = 4;
	htimer2.Init.Period = 10000 -1;
	if ( HAL_TIM_PWM_Init(&htimer2) != HAL_OK)
	{
		Error_handler();
	}

	memset(&timer2PWM_Config,0,sizeof(timer2PWM_Config));

	timer2PWM_Config.OCNPolarity = TIM_OCPOLARITY_HIGH;
	timer2PWM_Config.OCMode = TIM_OCMODE_PWM1;

	timer2PWM_Config.Pulse = (htimer2.Init.Period * pData) / 100; // CH1: 25%
	if ( HAL_TIM_PWM_ConfigChannel(&htimer2, &timer2PWM_Config, TIM_CHANNEL_1) != HAL_OK){Error_handler();}

}

void SystemClock_Config_HSE(uint32_t clock_freq)
{
	RCC_OscInitTypeDef Osc_Init;
	RCC_ClkInitTypeDef Clock_Init;

	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_HSI ;
	Osc_Init.HSEState = RCC_HSE_ON;
	Osc_Init.LSEState = RCC_LSE_ON;
	Osc_Init.HSIState = RCC_HSI_ON;
	Osc_Init.PLL.PLLState = RCC_PLL_ON;

	Osc_Init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	switch(clock_freq) {
	case SYS_CLOCK_FREQ_50_MHZ:
	Osc_Init.PLL.PLLM = 8;
	Osc_Init.PLL.PLLN = 50;
	Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
	Osc_Init.PLL.PLLQ = 2;
	Osc_Init.PLL.PLLR = 2;
	Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
						   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;
	Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
	break;

  case SYS_CLOCK_FREQ_84_MHZ:
	Osc_Init.PLL.PLLM = 8;
	Osc_Init.PLL.PLLN = 84;
	Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
	Osc_Init.PLL.PLLQ = 2;
	Osc_Init.PLL.PLLR = 2;
	Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
						   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;
	Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
	break;

  case SYS_CLOCK_FREQ_120_MHZ:
	Osc_Init.PLL.PLLM = 8;
	Osc_Init.PLL.PLLN = 120;
	Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
	Osc_Init.PLL.PLLQ = 2;
	Osc_Init.PLL.PLLR = 2;
	Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
						   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	Clock_Init.APB1CLKDivider = RCC_HCLK_DIV4;
	Clock_Init.APB2CLKDivider = RCC_HCLK_DIV2;
	break;

  default:
	return ;
	}

	if (HAL_RCC_OscConfig(&Osc_Init) != HAL_OK)
	{
	  Error_handler();
	}

	if (HAL_RCC_ClockConfig(&Clock_Init, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_handler();
	}

	/*Configure the systick timer interrupt frequency (for every 1 ms) */
	uint32_t hclk_freq = HAL_RCC_GetHCLKFreq();
	HAL_SYSTICK_Config(hclk_freq/1000);

	/**Configure the Systick
	*/
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void Error_handler(void)
{
	while(1);
}

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		// There is a problem
		Error_handler();
	}
}


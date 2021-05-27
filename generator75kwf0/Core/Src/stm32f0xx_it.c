/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f0xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
_Bool adc=0,working=0;
uint16_t av=0;
uint16_t vbat_int,vadc_int,vac_sample_int;
extern uint16_t adc_val[3];
extern volatile uint32_t freq,fr;
volatile uint32_t thick=0,working_time=0;
extern float samples[80];
extern float vbat,vadc,vac_sample;
extern uint32_t sample_cnt;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void)
{
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */

	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */
	while (1)
	{
	}
	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void)
{
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1)
	{
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void)
{
	/* USER CODE BEGIN SVC_IRQn 0 */

	/* USER CODE END SVC_IRQn 0 */
	/* USER CODE BEGIN SVC_IRQn 1 */

	/* USER CODE END SVC_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void)
{
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void)
{
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */

	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f0xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles DMA1 channel 1 interrupt.
 */
void DMA1_Channel1_IRQHandler(void)
{
	/* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

	if(LL_DMA_IsActiveFlag_TC1(DMA1) == 1)
	{
		//if(!adc)
		//{
		//adc=1;
		vac_sample_int=adc_val[2];
		vadc_int=adc_val[1];
		vbat_int=adc_val[0];
		//new_val=1;
		vac_sample=vac_sample_int*(float)(3.3/4096);
//		if(vac_sample<2.5){
//			pulse=1;
//		}else{
//			if(vac_sample>2.9 && pulse){
//				fr++;
//				pulse=0;
//			}
//		}
		samples[sample_cnt++]=vac_sample;
		if(sample_cnt==80){
			sample_cnt=0;
			//min_sample=cal_min(samples);
			//if(min_sample)
		}



		vadc=vadc_int*(float)(3.3/4096);
		adc=0;
		//}
		/* Clear flag DMA transfer complete */
		LL_DMA_ClearFlag_TC1(DMA1);
	}
	/* USER CODE END DMA1_Channel1_IRQn 0 */

	/* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

	/* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
 * @brief This function handles TIM3 global interrupt.
 */
void TIM3_IRQHandler(void)
{
	/* USER CODE BEGIN TIM3_IRQn 0 */
	if(LL_TIM_IsActiveFlag_UPDATE(TIM3) == 1)
	{
		/* Clear the update interrupt flag*/
		LL_TIM_ClearFlag_UPDATE(TIM3);
		thick++;
		if(thick%500==0){
			freq=fr;
			fr=0;
		}
		if(working){
			working_time++;
		}else{
			working_time=0;
		}
		//LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
	}
	/* USER CODE END TIM3_IRQn 0 */
	/* USER CODE BEGIN TIM3_IRQn 1 */

	/* USER CODE END TIM3_IRQn 1 */
}

/**
 * @brief This function handles USART1 global interrupt.
 */
void USART1_IRQHandler(void)
{
	/* USER CODE BEGIN USART1_IRQn 0 */

	/* USER CODE END USART1_IRQn 0 */
	/* USER CODE BEGIN USART1_IRQn 1 */

	/* USER CODE END USART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_ll_adc.h"
#include "stm32f0xx_ll_dma.h"
#include "stm32f0xx_ll_crs.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_tim.h"
#include "stm32f0xx_ll_usart.h"
#include "stm32f0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define er_Pin LL_GPIO_PIN_13
#define er_GPIO_Port GPIOC
#define pwr_Pin LL_GPIO_PIN_14
#define pwr_GPIO_Port GPIOC
#define bat_l_Pin LL_GPIO_PIN_15
#define bat_l_GPIO_Port GPIOC
#define fr_Pin LL_GPIO_PIN_1
#define fr_GPIO_Port GPIOA
#define ac_sample_Pin LL_GPIO_PIN_2
#define ac_sample_GPIO_Port GPIOA
#define bat_adc_Pin LL_GPIO_PIN_4
#define bat_adc_GPIO_Port GPIOA
#define water_Pin LL_GPIO_PIN_7
#define water_GPIO_Port GPIOA
#define oil_Pin LL_GPIO_PIN_0
#define oil_GPIO_Port GPIOB
#define ol_Pin LL_GPIO_PIN_1
#define ol_GPIO_Port GPIOB
#define oil_l_Pin LL_GPIO_PIN_2
#define oil_l_GPIO_Port GPIOB
#define water_l_Pin LL_GPIO_PIN_10
#define water_l_GPIO_Port GPIOB
#define ol_l_Pin LL_GPIO_PIN_11
#define ol_l_GPIO_Port GPIOB
#define emr_l_Pin LL_GPIO_PIN_12
#define emr_l_GPIO_Port GPIOB
#define feul_l_Pin LL_GPIO_PIN_13
#define feul_l_GPIO_Port GPIOB
#define gen_Pin LL_GPIO_PIN_14
#define gen_GPIO_Port GPIOB
#define feul_Pin LL_GPIO_PIN_15
#define feul_GPIO_Port GPIOB
#define emr_Pin LL_GPIO_PIN_8
#define emr_GPIO_Port GPIOA
#define mute_Pin LL_GPIO_PIN_15
#define mute_GPIO_Port GPIOA
#define btn_start_Pin LL_GPIO_PIN_3
#define btn_start_GPIO_Port GPIOB
#define start_Pin LL_GPIO_PIN_4
#define start_GPIO_Port GPIOB
#define gov_Pin LL_GPIO_PIN_5
#define gov_GPIO_Port GPIOB
#define sir_Pin LL_GPIO_PIN_6
#define sir_GPIO_Port GPIOB
#define freq_l_Pin LL_GPIO_PIN_7
#define freq_l_GPIO_Port GPIOB
#define vac_l_Pin LL_GPIO_PIN_8
#define vac_l_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

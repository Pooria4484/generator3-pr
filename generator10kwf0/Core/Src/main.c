/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define report 0
#if report==1
#include "string.h"
#include "stdio.h"
#endif
#include "macro.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

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
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t adc_val[3]={0,0,0};
char tx[30]="";
void print(char* str);
extern _Bool adc,working;
float vbat,vadc,vac_sample;
extern uint16_t vbat_int,vadc_int,vac_sample_int;
extern volatile uint32_t thick;
volatile uint32_t old_thick=0,mscnt=0,start_cnt=0;
void leds_test();
void adc_init();
_Bool check_err();
_Bool mute=0,new_val=0;
float samples[80];
uint8_t sample_cnt=0;
uint16_t fr=0,pulse=0,freq=0;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	/* System interrupt init*/

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC_Init();
	MX_USART1_UART_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	//print("start\r\n");

	//leds_test();
	adc_init();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		if(check_err()){
			if(working){
				if(!mute)
				{
					siren_on;
					if(isMutePressed){
						mute=1;
					}
				}
				else
				{
					siren_off;
				}
			}else{
				if(isStartPressed){
					if(!mute)
					{
						siren_on;
						if(isMutePressed){
							mute=1;
						}
					}
					else
					{
						siren_off;
					}
				}
			}
			if(mscnt%250==0)
			{
				pwr_off;
				er_toggle;
			}


		}else{
			er_off;
			siren_off;
			mute=0;
			if(working){
				if(mscnt%250==0)
				{
					pwr_toggle;
				}
			}else{
				pwr_on;
				if(isStartPressed){
					if(start_cnt<20000){
						start_on;
					}else{
						start_off;
					}
					start_cnt++;
				}else{
					start_off;
					start_cnt=0;
				}
			}
		}


		while(thick==old_thick);
		old_thick=thick;
		mscnt++;

#if report==1
		if(adc && mscnt>1000)
		{
			//LL_GPIO_TogglePin(feul_l_GPIO_Port, feul_l_Pin);
			mscnt=0;
			vac_sample*=(float)(3.3/4096);
			vbat*=(float)(3.3/4096);
			vbat*=5.54;
			vbat+=0.6;
			vadc*=(float)(3.3/4096);
			sprintf(tx,"\r\nvbat:%d.%d%d\r\n",(int)(vbat),(int)(vbat*10)%10,(int)(vbat*100)%10);
			print(tx);
			sprintf(tx,"vac_sample:%d.%d%d\r\n",(int)(vac_sample),(int)(vac_sample*10)%10,(int)(vac_sample*100)%10);
			print(tx);
			sprintf(tx,"vadc:%d.%d%d\r\n",(int)(vadc),(int)(vadc*10)%10,(int)(vadc*100)%10);
			print(tx);
			adc=0;
		}
#endif
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
	while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
	{
	}
	LL_RCC_HSI_Enable();

	/* Wait till HSI is ready */
	while(LL_RCC_HSI_IsReady() != 1)
	{

	}
	LL_RCC_HSI_SetCalibTrimming(16);
	LL_RCC_HSI14_Enable();

	/* Wait till HSI14 is ready */
	while(LL_RCC_HSI14_IsReady() != 1)
	{

	}
	LL_RCC_HSI14_SetCalibTrimming(16);
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

	/* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
	{

	}
	LL_Init1msTick(8000000);
	LL_SetSystemCoreClock(8000000);
	LL_RCC_HSI14_EnableADCControl();
	LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
}

/* USER CODE BEGIN 4 */
#if report==1
void print(char* str){
	for(int j=0;j<strlen(str);j++)
	{
		LL_USART_TransmitData8(USART1, (uint8_t)str[j]);
		while(!LL_USART_IsActiveFlag_TXE(USART1));
	}
}
#endif


float cal_min(float*val){
	float min=val[0];
	for(int i=0;i<80;i++){
		if(min>val[i])min=val[i];
	}
	return min;
}

_Bool check_err(){
	_Bool flag=0;
	float min_sample=0;
	if(adc){
		new_val=1;
		vac_sample=vac_sample_int*(float)(3.3/4096);
		if(vac_sample<2.5){
			pulse=1;
		}else{
			if(vac_sample>2.9 && pulse){
				fr++;
				pulse=0;
			}
		}
		samples[sample_cnt++]=vac_sample;
		if(sample_cnt==80){
			sample_cnt=0;
			min_sample=cal_min(samples);
			//if(min_sample)
		}



		vadc=vadc_int*(float)(3.3/4096);
		adc=0;

	}
	if(working){
		if(oil_err){
			oil_on;
			flag=1;
		}else{
			oil_off;
		}
		if(new_val){
			new_val=0;
			vbat=vbat_int*(float)(3.3/4096);
//			vbat*=5.54;
//			vbat+=0.6;
		}
		if(vbat<vdyn_min || dyn_err){
			bat_on;
			flag=1;
		}else{
			bat_off;
		}

		if(min_sample<vac_min || min_sample>vac_max){
			vac_on;
			flag=1;
		}else{
			vac_off;
		}

		if(freq<195||freq>205){
			fr_on;
			flag=1;
		}else{
			fr_off;
		}
	}else{
		if(new_val){
			new_val=0;
			vbat=vbat_int*(float)(3.3/4096);
//			vbat*=5.54;
//			vbat+=0.6;
		}
		if(vbat<vbat_min){
			bat_on;
			flag=1;
		}else{
			bat_off;
		}

	}

	if(water_err){
		water_on;
		flag=1;
	}else{
		water_off;
	}

	if(feul_err){
		feul_on;
		flag=1;
	}else{
		feul_off;
	}

	if(emr_err){
		emr_on;
		flag=1;
	}else{
		emr_off;
	}


	if(ol_err){
		ol_on;
		flag=1;
	}else{
		ol_off;
	}
	return flag;
}
void adc_init() {
	LL_TIM_EnableCounter(TIM3);
	LL_TIM_EnableIT_UPDATE(TIM3);
	LL_ADC_StartCalibration(ADC1);
	while (LL_ADC_IsCalibrationOnGoing(ADC1));

	LL_ADC_Enable(ADC1);
	LL_ADC_REG_StartConversion(ADC1);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 3);
	LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1,
			LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA));
	LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1,(uint32_t)adc_val);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);
}

void leds_test() {
	for (int i = 0; i < 5; i++) {
		vac_off;
		oil_on;
		ms_delay(250);
		oil_off;
		water_on;
		ms_delay(250);
		feul_on;
		water_off;
		ms_delay(250);
		feul_off;
		emr_on;
		ms_delay(250);
		bat_on;
		emr_off;
		ms_delay(250);
		bat_off;
		ol_on;
		ms_delay(250);
		ol_off;
		pwr_on;
		ms_delay(250);
		pwr_off;
		er_on;
		ms_delay(250);
		fr_on;
		er_off;
		ms_delay(250);
		vac_on;
		fr_off;
		ms_delay(250);
	}
	vac_off;
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

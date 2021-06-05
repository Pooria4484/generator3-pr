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
#define turn_off gov_off;is_off=1;
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
extern volatile uint32_t thick,working_time;
volatile uint32_t old_thick=0,mscnt=0,start_cnt=0,mute_cnt=0;
void leds_test();
void adc_init();
_Bool check_err();
_Bool mute=0,new_val=0,oil_err_flag=0,
		feul_err_flag=0,emr_err_flag=0,
		dyn_err_flag=0,water_err_flag=0,
		freq_err_flag=0,vac_err_high_flag=0,vac_err_low_flag=0,
		ol_err_flag=0,bat_err_flag=0,is_off=0;
float samples[200];
float min_sample=0;
uint32_t sample_cnt=0,err_cnt=0;
volatile uint32_t fr=0,pulse=0,freq=0,fr_err_cnt=0,off_delay_cnt=0,vac_err_cnt=0;
_Bool flag=0,first_check=0,starting=0;
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
	//working=1;
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
	er_on;
	ms_delay(3000);
	er_off;
	leds_test();
	adc_init();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		if(is_off){
			off_delay_cnt++;
			if(off_delay_cnt>20000){
				gov_off;
				//is_off=0;
				working=0;
				off_delay_cnt=0;
			}
		}
		if(check_err()){
			if(mscnt%250==0)
			{
				pwr_off;
				er_toggle;
				if(vac_err_low_flag){
					vac_toggle;
				}
			}
			pwr_off;
			if(working){
				if(!mute)
				{
					siren_on;
					if(isMutePressed){
						mute_cnt++;
						if (mute_cnt>3000){
							//turn off
							if(!is_off)
								turn_off;
						}
						else if(mute_cnt>300){
							mute=1;
						}
					}else{
						mute_cnt=0;
					}
				}
				else
				{
					siren_off;
				}

				if(dyn_err_flag){
					if(oil_err_flag||water_err_flag||ol_err_flag||emr_err_flag||freq_err_flag||vac_err_high_flag||vac_err_low_flag){
						//turn off
						if(!is_off)
							turn_off;
					}else{

					}
				}else{
					//turn off
					if(oil_err_flag||water_err_flag||ol_err_flag||emr_err_flag||freq_err_flag||vac_err_high_flag||vac_err_low_flag){
						if(!is_off)
							turn_off;
					}else{
						flag=0;
					}
				}
			}else{
				if(isStartPressed){
					if(!mute)
					{
						siren_on;
					}
				}


				if(!mute)
				{
					if(isMutePressed){
						mute_cnt++;
						if(mute_cnt>300){
							mute=1;
						}
					}else{
						mute_cnt=0;
					}
				}
				else
				{
					siren_off;
					mute=0;
				}
			}

		}else{
			if(first_check){
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
				}

				if((isStartPressed)&&!(vbat>vdyn_min && freq>150)){//if(vbat>vdyn_min || freq>150)
					if(start_cnt<20000){
						start_on;
						gov_on;
						starting=1;
					}else{
						start_off;
						starting=0;
					}
					start_cnt++;
				}else{
					start_off;
					start_cnt=0;
					starting=0;
				}

				if(isMutePressed){
					mute_cnt++;
					if(mute_cnt>3000){
						//turn off
						turn_off;
					}
				}else{
					mute_cnt=0;
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
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_4);
	LL_RCC_PLL_Enable();

	/* Wait till PLL is ready */
	while(LL_RCC_PLL_IsReady() != 1)
	{

	}
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	/* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{

	}
	LL_Init1msTick(16000000);
	LL_SetSystemCoreClock(16000000);
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
	for(int i=0;i<200;i++){
		if(min>val[i])min=val[i];
	}
	return min;
}

_Bool check_err(){
	if(!is_off){
		if(adc){
			new_val=1;
			vac_sample=vac_sample_int*(float)(3.3/4096);
			if(vac_sample<2.0){
				pulse=1;
			}else{
				if(vac_sample>2.7 && pulse){
					fr++;
					pulse=0;
				}
			}
			samples[sample_cnt++]=vac_sample;
			if(sample_cnt==sizeof(samples)/4){
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
				oil_err_flag=1;
				//err_cnt++;
				flag=1;
			}
			//		else{
			//			oil_err_flag=0;
			//			oil_off;
			//		}
			if(new_val){
				new_val=0;
				vbat=vbat_int*(float)(3.3/4096);
				//			vbat*=5.54;
				//			vbat+=0.6;
			}
			if((vbat<vdyn_min && working_time>20000) || dyn_err){
				bat_on;
				dyn_err_flag=1;

				flag=1;
			}else{
				dyn_err_flag=0;
				bat_off;
			}

			if((min_sample<vac_min)&& working_time>20000){
				//vac_on;
				//flag=1;
				//err_cnt++;
				vac_err_high_flag=1;
			}

			if((min_sample>vac_max)&& working_time>20000){
				//flag=1;
				//err_cnt++;
				vac_err_low_flag=1;
			}

			if(!(vac_err_high_flag||vac_err_low_flag)){
				//vac_off;
				vac_err_cnt=0;
			}else{
				vac_err_cnt++;
			}
			if((freq<192||freq>208)&&(working_time>20000)){//
				//fr_on;
				fr_err_cnt++;
				//flag=1;
				//err_cnt++;
				//freq_err_flag=1;
			}else{
				fr_err_cnt=0;
				//fr_off;
				//freq_err_flag=0;
			}
		}else{
			//not working


			if(new_val){
				new_val=0;
				vbat=vbat_int*(float)(3.3/4096);
				//			vbat*=5.54;
				//			vbat+=0.6;
			}


			if(vbat<vbat_min&&!starting){
				bat_on;
				flag=1;
				//err_cnt++;
				bat_err_flag=1;
			}else{
				bat_off;
				bat_err_flag=0;
			}

			if(vbat>vdyn_min || freq>150){
				working=1;
			}

		}

		if(water_err){
			water_on;
			water_err_flag=1;
			flag=1;
			//err_cnt++;
		}

		if(feul_err){
			feul_on;
			flag=1;
			//err_cnt++;
			feul_err_flag=1;
		}

		if(emr_err){
			emr_on;
			flag=1;
			//err_cnt++;
			emr_err_flag=1;
		}


		if(ol_err){
			ol_err_flag=1;
			ol_on;
			flag=1;
			//err_cnt++;
		}

		if(vac_err_cnt>100){
			flag=1;
			err_cnt++;
			//freq_err_flag=1;
			if(vac_err_high_flag){
				vac_on;
			}
		}else{
			vac_err_high_flag=0;
			vac_err_low_flag=0;
			vac_off;
		}

		if(fr_err_cnt>3000){
			flag=1;
			err_cnt++;
			fr_on;
			freq_err_flag=1;
		}

		if(!flag){
			err_cnt=0;
		}else{
			err_cnt++;
			if(err_cnt<200){
				flag=0;
			}
		}
		if(mscnt>1000){
			first_check=1;
		}
		if(!flag){
			oil_off;
			water_off;
			emr_off;
			ol_off;
			feul_off;
			bat_off;
			fr_off;
			vac_off;
		}
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

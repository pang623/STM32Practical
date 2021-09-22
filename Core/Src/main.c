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
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Gpio.h"
#include "Rcc.h"
#include "Timer.h"
#include "Nvic.h"
#include "Adc.h"
#include "Retarget.h"
#include "Usart.h"
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
volatile int adcValue = 0;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void setPWMFrequency(TimReg *timer, int freq);
void setPWMDutyCycle(TimReg *timer, int chnNum, int duty);
void adjustCCR(TimReg *timer, int chnNum, int CCR_VAL);
void readADC();
void experiment1();
void experiment2();
void experiment3();
void experiment4();
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  //experiment1();
  /*	Experiment 2	*/
/*
  rccUnresetAndEnableDevice(RCC_GPIOB);
  rccUnresetAndEnableDevice(RCC_TIMER4);
  //SW (PB6)
  gpioConfigurePin(gpioB, PIN6, GPIO_INPUT);
  //CH3
  gpioConfigurePin(gpioB, PIN8, GPIO_ALT_FUNC | AF_2 | GPIO_PUSH_PULL | GPIO_HIGH_SPEED);
  timerConfigure(timer4, TIM_EN);
  timerConfigureEventGeneration(timer4, TIM_UG);
*/
  /*	Experiment 3	*/
  //experiment3();
  MX_GPIO_Init();
  experiment4();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	readADC();
	//experiment2();
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 50;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
#define ARR_VALUE	65000
#define	VREFPLUS	3.3

void setPWMFrequency(TimReg *timer, int freq) {
	uint32_t APB_TIMER_CLK = HAL_RCC_GetHCLKFreq();
	timerSetPrescaler(timer, APB_TIMER_CLK / (ARR_VALUE * freq));
	timerSetARR(timer, ARR_VALUE);
}

void setPWMDutyCycle(TimReg *timer, int chnNum, int duty) {
	timerSetCapComReg(timer, chnNum, (duty/100.0)*ARR_VALUE);
}

void adjustCCR(TimReg *timer, int chnNum, int CCR_VAL) {
	if((uint32_t)(timer->CCR[chnNum-1] + CCR_VAL) > (uint32_t)(timer->ARR))
		timer->CCR[chnNum-1] = CCR_VAL - (timer->ARR - timer->CCR[chnNum-1]);
	else
		timer->CCR[chnNum-1] += CCR_VAL;
}

void experiment1() {
	rccUnresetAndEnableDevice(RCC_GPIOB);
	rccUnresetAndEnableDevice(RCC_TIMER4);
	//CH1 (button)
	gpioConfigurePin(gpioB, PIN6, GPIO_ALT_FUNC | AF_2);
	//CH3 (LED)
	gpioConfigurePin(gpioB, PIN8, GPIO_ALT_FUNC | AF_2 | GPIO_PUSH_PULL | GPIO_HIGH_SPEED);
	timerConfigureEventGeneration(timer4, TIM_UG);
	timerConfigureCaptureCompare(timer4, 1, TIM_CC1_IP_CAPTURE_EN | TIM_CC1S_INPUT_IC1_TI1);
	timerConfigureCaptureCompare(timer4, 3, TIM_CC3S_OUTPUT | TIM_OC3M_PWM_MODE1 | TIM_CC3_OP_EN | TIM_CC3P_OC_HIGH | TIM_OC3_PRELOAD_EN);
	setPWMFrequency(timer4, 1);			//1Hz PWM signal
	setPWMDutyCycle(timer4, 3, 20);		//80% duty cycle
	timerConfigure(timer4, TIM_EN | TIM_AUTO_RELOAD_PRELOAD_EN | TIM_SLAVE_GATED | TIM_TS_TI1FP1);
}

void experiment2() {
	volatile int button_state = gpioReadPin(gpioB, PIN6);
	if(button_state)
		timerConfigureCaptureCompare(timer4, 3, TIM_CC3S_OUTPUT | TIM_OC3M_FORCE_ACT | TIM_CC3_OP_EN | TIM_CC3P_OC_HIGH);
	else
		timerConfigureCaptureCompare(timer4, 3, TIM_CC3S_OUTPUT | TIM_OC3M_FORCE_INACT | TIM_CC3_OP_EN | TIM_CC3P_OC_HIGH);
}

void experiment3() {
	rccUnresetAndEnableDevice(RCC_GPIOB);
	rccUnresetAndEnableDevice(RCC_TIMER4);
	//CH3
	gpioConfigurePin(gpioB, PIN8, GPIO_ALT_FUNC | AF_2 | GPIO_PUSH_PULL | GPIO_HIGH_SPEED);
	timerConfigureCaptureCompare(timer4, 3, TIM_CC3S_OUTPUT | TIM_OC3M_TOGGLE | TIM_CC3_OP_EN | TIM_CC3P_OC_HIGH);
	//Initialise to 1Hz 50% duty cycle
	setPWMFrequency(timer4, 1);
	setPWMDutyCycle(timer4, 3, 50);
	nvicEnableIrq(TIM4_IRQ);
	timerConfigure(timer4, TIM_EN | TIM_CC3I_EN);
	timerConfigureEventGeneration(timer4, TIM_UG);
}

void experiment4() {
	int channels[1] = {0};
	rccUnresetAndEnableDevice(RCC_USART2);
	rccUnresetAndEnableDevice(RCC_GPIOA);
	rccUnresetAndEnableDevice(RCC_TIMER4);
	rccUnresetAndEnableDevice(RCC_ADC1);

	//Configure GPIOA AF for USART2 (Virtual COM port) and Analog In
	//PA2 as USART2 Tx, PA0 as ANALOG IN CHANNEL 0
	gpioConfigurePin(gpioA, PIN2, GPIO_ALT_FUNC | GPIO_HIGH_SPEED | AF_7 | GPIO_PUSH_PULL);
	gpioConfigurePin(gpioA, PIN0, GPIO_ANALOG_IN);

	//Setup usart
	usartSetBaudRate(usart2, 115200);
	usartConfigure(usart2, USART_TX_EN | USART_9_DATA_BIT | USART_STOPB_2 | USART_ODD_PARITY | USART_EN);

	//Setup timer
	timerConfigureCaptureCompare(timer4, 4, TIM_CC4S_OUTPUT | TIM_OC4M_PWM_MODE1 | TIM_CC4_OP_EN | TIM_CC4P_OC_LOW | TIM_OC4_PRELOAD_EN);
	//2kHz signal generation
	timerSetPrescaler(timer4, 2);
	timerSetARR(timer4, 12500);
	timerSetCapComReg(timer4, 4, 12500);

	//Configure ADC
	adcSetSampleTime(adc1, 0, SAMPLE_3_CYCLES);				//channel 0, sampling time of 3 cycles (fastest)
	adcCommonConfigure(ADC_PSC_2);							//ADC clock is half of PCLK2
	adcConfigureRegularChannel(adc1, ADC_TIM4_CH4_TRG | ADC_TRG_RISING_EDGE);		//event triggered by TIM4_CH4_OC signal
	adcSetChannelSequence(adc1, channels, 1);				//Scan one channel, channel 0
	nvicEnableIrq(ADC1_IRQ);								//Enable ADC interrupt
	configureADC(adc1, ADC_SINGLE_MODE | ADC_RIGHT_ALIGN | ADC_RESOLUTION_12 | ADC_EOC_INT_EN | ADC_EN);

	//Start
	timerConfigure(timer4, TIM_EN | TIM_AUTO_RELOAD_PRELOAD_EN);
	timerConfigureEventGeneration(timer4, TIM_UG);
}

void readADC() {
	static int lastAdcValue = 0;
	if(adcValue != lastAdcValue) {
		lastAdcValue = adcValue;
		double voltage = (adcValue / 4096.0000) * VREFPLUS;
		printf("ADC Value: %d, voltage: %.4lfV\r\n", adcValue, voltage);
	}
}

void ADC_IRQHandler(void) {
	static int count = 0;
	static int tempAdc = 0;
	if(adc1->SR & ADC_END_OF_CONVERSION) {
		count++;
		tempAdc += adc1->DR;
		if(count == 400) {
			adcValue = tempAdc / 400;
			tempAdc = count = 0;
		}
		adc1->SR &= ~ADC_END_OF_CONVERSION;
	}
}

void TIM4_IRQHandler(void) {
	static int i = 1;
	if(timer4->SR & TIM_CC3IF) {
		timer4->SR &= ~TIM_CC3IF;
		i++;
		if(i <= 8)
			adjustCCR(timer4, 3, 32500);
		else if(i <= 24)
			adjustCCR(timer4, 3, 16250);
		else if(i <= 56)
			adjustCCR(timer4, 3, 8125);
		else {
			i = 1;
			adjustCCR(timer4, 3, 32500);
		}
	}
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

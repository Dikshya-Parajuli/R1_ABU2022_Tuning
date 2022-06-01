/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>

#include "robooperation.h"
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

RobotState robot_state;
JoystickState joystick_state;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
//int getAnglePitch( int ppr, float gr);
//float getPulsesNeeded(int degree, int ppr, float gr);
//void setAnglePitch(int degree, int ppr, float gr);
//void setAngleYaw(int degree, int ppr, float gr);
//int getAngleYaw(int ppr, float gr);
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
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
//  MX_USB_HOST_Init();
  /* USER CODE BEGIN 2 */

  // Start PWM signals for speed control(Rollers)
  // HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  // HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);

  // // Start Encoder Mode For Pitch Motor
  // HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);
  // // Start Encoder Mode For Yaw Motor

  // HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);

  // // Start PWM signal for Pitch Motor
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  // int speedPercentage = 17;

  // int pwmSignal = speedPercentage * 65535 / 100;
  // int currentSignal = 0;
  // int prevRoll = HAL_GetTick();

  // int pprPitch = 1000;
  // float gearRatioPitch = 3.5;

  // int pprYaw = 1000;
  // float gearRatioYaw = 250/24;

  // htim2.Instance->CNT = 0;
  // htim3.Instance->CNT = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  roboPlay(&robot_state, &joystick_state);
  while (1)
  {
   
    /* USER CODE END WHILE */
//    MX_USB_HOST_Process(); 3

    /* USER CODE BEGIN 3 */

    // Roller COntrol
    

    // Control of Pitch Motor
//    HAL_GPIO_WritePin(PITCH_DIR_GPIO_Port, PITCH_DIR_Pin, GPIO_PIN_SET);
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 40000);

//    int angle = getAnglePitch(pprPitch, gearRatioPitch);
//    printf("Instance = %d, Angle = %d\n", (int)htim2.Instance->CNT ,angle);
    // setAnglePitch(20, pprPitch, gearRatioPitch);
    // setAngleYaw(50,pprYaw, gearRatioYaw);
    // printf("PitchAngle: %d && Yaw Angle: %d\n",getAnglePitch(pprPitch, gearRatioPitch),getAngleYaw(pprYaw, gearRatioYaw));




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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
// int getAnglePitch(int ppr, float gr) {
// 	return (360*2* htim2.Instance->CNT) / (ppr * gr);
// }

// int getAngleYaw(int ppr, float gr) {
// 	return (360*2* htim3.Instance->CNT) / (ppr * gr);
// }

// float getPulsesNeeded(int degrees, int ppr, float gr) {
// 	return ppr * degrees * gr / (360*2);
// }

// void setAnglePitch(int degree, int ppr, float gr) {
// 	int pulses = getPulsesNeeded(degree, ppr, gr);
// 	printf("Pulse needed pitch = %d\n", pulses);
// 	int pulsesFound = htim2.Instance->CNT;
// 	printf("Pulse found pitch = %d\n", pulsesFound);
// 	if (pulsesFound >= pulses * 1.1) {
// 		HAL_GPIO_WritePin(PITCH_DIR_GPIO_Port, PITCH_DIR_Pin, GPIO_PIN_RESET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 40000);
// 	} else if (pulsesFound >= pulses * 1.05) {
// 		HAL_GPIO_WritePin(PITCH_DIR_GPIO_Port, PITCH_DIR_Pin, GPIO_PIN_RESET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 20000);
// 	} else if (pulsesFound >= pulses * 1.01) {
// 		HAL_GPIO_WritePin(PITCH_DIR_GPIO_Port, PITCH_DIR_Pin, GPIO_PIN_RESET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 10000);
// 	} else if (pulsesFound <= pulses * 0.9) {
// 		HAL_GPIO_WritePin(PITCH_DIR_GPIO_Port, PITCH_DIR_Pin, GPIO_PIN_SET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 40000);
// 	} else if (pulsesFound <= pulses * 0.95) {
// 		HAL_GPIO_WritePin(PITCH_DIR_GPIO_Port, PITCH_DIR_Pin, GPIO_PIN_SET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 20000);
// 	} else if (pulsesFound <= pulses * 0.99) {
// 		HAL_GPIO_WritePin(PITCH_DIR_GPIO_Port, PITCH_DIR_Pin, GPIO_PIN_SET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 10000);
// 	} else {
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
// 	}
// }

// void setAngleYaw(int degree, int ppr, float gr) {
// 	int pulses = getPulsesNeeded(degree, ppr, gr);
// 	printf("Pulse needed yaw= %d\n", pulses);
// 	int pulsesFound = htim3.Instance->CNT;
// 	printf("Pulse found yaw= %d\n", pulsesFound);
// 	if (pulsesFound >= pulses * 1.1) {
// 		HAL_GPIO_WritePin(YAW_DIR_GPIO_Port, YAW_DIR_Pin, GPIO_PIN_RESET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 40000);
// 	} else if (pulsesFound >= pulses * 1.05) {
// 		HAL_GPIO_WritePin(YAW_DIR_GPIO_Port, YAW_DIR_Pin, GPIO_PIN_RESET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 20000);
// 	} else if (pulsesFound >= pulses * 1.01) {
// 		HAL_GPIO_WritePin(YAW_DIR_GPIO_Port, YAW_DIR_Pin, GPIO_PIN_RESET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 10000);
// 	} else if (pulsesFound <= pulses * 0.9) {
// 		HAL_GPIO_WritePin(YAW_DIR_GPIO_Port, YAW_DIR_Pin, GPIO_PIN_SET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 40000);
// 	} else if (pulsesFound <= pulses * 0.95) {
// 		HAL_GPIO_WritePin(YAW_DIR_GPIO_Port, YAW_DIR_Pin, GPIO_PIN_SET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 20000);
// 	} else if (pulsesFound <= pulses * 0.99) {
// 		HAL_GPIO_WritePin(YAW_DIR_GPIO_Port, YAW_DIR_Pin, GPIO_PIN_SET);
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 10000);
// 	} else {
// 		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
// 	}
// }
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


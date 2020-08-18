/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HBridgeController.hpp"
#include "SoftPWMController.hpp"
#include "HardPWMController.hpp"
#include "ioExpanderController.hpp"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define NUM_OF_SOFT_PWM 39
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

HBridgeController outputs[64] = {
    HBridgeController(ioExp1, new SoftPWMController(PWM1_GPIO_Port, PWM1_Pin)),
    HBridgeController(ioExp1, new SoftPWMController(PWM2_GPIO_Port, PWM2_Pin)),
    HBridgeController(ioExp1, new SoftPWMController(PWM3_GPIO_Port, PWM3_Pin)),
    HBridgeController(ioExp1, new HardPWMController(&htim9, TIM_CHANNEL_1)),
    HBridgeController(ioExp1, new HardPWMController(&htim9, TIM_CHANNEL_2)),
    HBridgeController(ioExp1, new SoftPWMController(PWM6_GPIO_Port, PWM6_Pin)),
    HBridgeController(ioExp1, new SoftPWMController(PWM7_GPIO_Port, PWM7_Pin)),
    HBridgeController(ioExp1, new SoftPWMController(PWM8_GPIO_Port, PWM8_Pin)),
    HBridgeController(ioExp2, new SoftPWMController(PWM9_GPIO_Port, PWM9_Pin)),
    HBridgeController(ioExp2, new SoftPWMController(PWM10_GPIO_Port, PWM10_Pin)),
    HBridgeController(ioExp2, new SoftPWMController(PWM11_GPIO_Port, PWM11_Pin)),
    HBridgeController(ioExp2, new SoftPWMController(PWM12_GPIO_Port, PWM12_Pin)),
    HBridgeController(ioExp2, new HardPWMController(&htim5, TIM_CHANNEL_1)),
    HBridgeController(ioExp2, new HardPWMController(&htim5, TIM_CHANNEL_2)),
    HBridgeController(ioExp2, new HardPWMController(&htim5, TIM_CHANNEL_3)),
    HBridgeController(ioExp2, new HardPWMController(&htim5, TIM_CHANNEL_4)),
    HBridgeController(ioExp3, new HardPWMController(&htim2, TIM_CHANNEL_1)),
    HBridgeController(ioExp3, new SoftPWMController(PWM18_GPIO_Port, PWM18_Pin)),
    HBridgeController(ioExp3, new SoftPWMController(PWM19_GPIO_Port, PWM19_Pin)),
    HBridgeController(ioExp3, new HardPWMController(&htim3, TIM_CHANNEL_3)),
    HBridgeController(ioExp3, new HardPWMController(&htim3, TIM_CHANNEL_4)),
    HBridgeController(ioExp3, new SoftPWMController(PWM22_GPIO_Port, PWM22_Pin)),
    HBridgeController(ioExp3, new SoftPWMController(PWM23_GPIO_Port, PWM23_Pin)),
    HBridgeController(ioExp3, new SoftPWMController(PWM24_GPIO_Port, PWM24_Pin)),
    HBridgeController(ioExp4, new HardPWMController(&htim1, TIM_CHANNEL_1)),
    HBridgeController(ioExp4, new SoftPWMController(PWM26_GPIO_Port, PWM26_Pin)),
    HBridgeController(ioExp4, new HardPWMController(&htim1, TIM_CHANNEL_2)),
    HBridgeController(ioExp4, new SoftPWMController(PWM28_GPIO_Port, PWM28_Pin)),
    HBridgeController(ioExp4, new HardPWMController(&htim1, TIM_CHANNEL_3)),
    HBridgeController(ioExp4, new HardPWMController(&htim1, TIM_CHANNEL_4)),
    HBridgeController(ioExp4, new SoftPWMController(PWM31_GPIO_Port, PWM31_Pin)),
    HBridgeController(ioExp4, new SoftPWMController(PWM32_GPIO_Port, PWM32_Pin)),
    HBridgeController(ioExp5, new SoftPWMController(PWM33_GPIO_Port, PWM33_Pin)),
    HBridgeController(ioExp5, new HardPWMController(&htim12, TIM_CHANNEL_1)),
    HBridgeController(ioExp5, new HardPWMController(&htim12, TIM_CHANNEL_2)),
    HBridgeController(ioExp5, new SoftPWMController(PWM36_GPIO_Port, PWM36_Pin)),
    HBridgeController(ioExp5, new SoftPWMController(PWM37_GPIO_Port, PWM37_Pin)),
    HBridgeController(ioExp5, new SoftPWMController(PWM38_GPIO_Port, PWM38_Pin)),
    HBridgeController(ioExp5, new SoftPWMController(PWM39_GPIO_Port, PWM39_Pin)),
    HBridgeController(ioExp5, new HardPWMController(&htim4, TIM_CHANNEL_3)),
    HBridgeController(ioExp6, new HardPWMController(&htim4, TIM_CHANNEL_4)),
    HBridgeController(ioExp6, new HardPWMController(&htim8, TIM_CHANNEL_1)),
    HBridgeController(ioExp6, new HardPWMController(&htim8, TIM_CHANNEL_2)),
    HBridgeController(ioExp6, new HardPWMController(&htim8, TIM_CHANNEL_3)),
    HBridgeController(ioExp6, new SoftPWMController(PWM45_GPIO_Port, PWM45_Pin)),
    HBridgeController(ioExp6, new SoftPWMController(PWM46_GPIO_Port, PWM46_Pin)),
    HBridgeController(ioExp6, new SoftPWMController(PWM47_GPIO_Port, PWM47_Pin)),
    HBridgeController(ioExp6, new SoftPWMController(PWM48_GPIO_Port, PWM48_Pin)),
    HBridgeController(ioExp7, new SoftPWMController(PWM49_GPIO_Port, PWM49_Pin)),
    HBridgeController(ioExp7, new SoftPWMController(PWM50_GPIO_Port, PWM50_Pin)),
    HBridgeController(ioExp7, new SoftPWMController(PWM51_GPIO_Port, PWM51_Pin)),
    HBridgeController(ioExp7, new SoftPWMController(PWM52_GPIO_Port, PWM52_Pin)),
    HBridgeController(ioExp7, new SoftPWMController(PWM53_GPIO_Port, PWM53_Pin)),
    HBridgeController(ioExp7, new SoftPWMController(PWM54_GPIO_Port, PWM54_Pin)),
    HBridgeController(ioExp7, new SoftPWMController(PWM55_GPIO_Port, PWM55_Pin)),
    HBridgeController(ioExp8, new SoftPWMController(PWM56_GPIO_Port, PWM56_Pin)),
    HBridgeController(ioExp8, new SoftPWMController(PWM57_GPIO_Port, PWM57_Pin)),
    HBridgeController(ioExp8, new SoftPWMController(PWM58_GPIO_Port, PWM58_Pin)),
    HBridgeController(ioExp8, new HardPWMController(&htim2, TIM_CHANNEL_2)),
    HBridgeController(ioExp8, new HardPWMController(&htim3, TIM_CHANNEL_1)),
    HBridgeController(ioExp8, new HardPWMController(&htim3, TIM_CHANNEL_2)),
    HBridgeController(ioExp8, new HardPWMController(&htim10, TIM_CHANNEL_1)),
    HBridgeController(ioExp8, new HardPWMController(&htim11, TIM_CHANNEL_1)),
    HBridgeController(ioExp8, new SoftPWMController(PWM64_GPIO_Port, PWM64_Pin))
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
extern "C"
{
    void SystemClock_Config(void);
}
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
	  SoftPWMController::setResolution(15);
    /* USER CODE END 1 */

    /* Enable I-Cache---------------------------------------------------------*/
    SCB_EnableICache();

    /* Enable D-Cache---------------------------------------------------------*/
    SCB_EnableDCache();

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
    MX_DMA_Init();
    MX_ADC1_Init();
    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_I2C3_Init();
    MX_I2C4_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_TIM6_Init();
    MX_TIM7_Init();
    MX_TIM8_Init();
    MX_TIM9_Init();
    MX_TIM10_Init();
    MX_TIM11_Init();
    MX_TIM12_Init();
    MX_TIM13_Init();
    MX_TIM14_Init();
    MX_USB_DEVICE_Init();
    MX_UART8_Init();
    /* USER CODE BEGIN 2 */
    HAL_TIM_Base_Start_IT(&htim6);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
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
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
  */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 432;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Activate the Over-Drive mode
  */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
  */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_I2C2 | RCC_PERIPHCLK_I2C3 | RCC_PERIPHCLK_I2C4 | RCC_PERIPHCLK_CLK48;
    PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
    PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
    PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
    PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    SoftPWMController::updateOutputs();
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

    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

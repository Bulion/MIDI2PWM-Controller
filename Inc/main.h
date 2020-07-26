/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_ll_system.h"
#include "stm32f7xx_ll_gpio.h"
#include "stm32f7xx_ll_exti.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_cortex.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx_ll_utils.h"
#include "stm32f7xx_ll_pwr.h"
#include "stm32f7xx_ll_dma.h"

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
#define PWM1_Pin LL_GPIO_PIN_2
#define PWM1_GPIO_Port GPIOE
#define PWM2_Pin LL_GPIO_PIN_3
#define PWM2_GPIO_Port GPIOE
#define PWM3_Pin LL_GPIO_PIN_4
#define PWM3_GPIO_Port GPIOE
#define PWM6_Pin LL_GPIO_PIN_13
#define PWM6_GPIO_Port GPIOC
#define PWM7_Pin LL_GPIO_PIN_14
#define PWM7_GPIO_Port GPIOC
#define PWM8_Pin LL_GPIO_PIN_15
#define PWM8_GPIO_Port GPIOC
#define PWM9_Pin LL_GPIO_PIN_0
#define PWM9_GPIO_Port GPIOC
#define PWM10_Pin LL_GPIO_PIN_1
#define PWM10_GPIO_Port GPIOC
#define PWM11_Pin LL_GPIO_PIN_2
#define PWM11_GPIO_Port GPIOC
#define PWM12_Pin LL_GPIO_PIN_3
#define PWM12_GPIO_Port GPIOC
#define PWM19_Pin LL_GPIO_PIN_4
#define PWM19_GPIO_Port GPIOC
#define PWM20_Pin LL_GPIO_PIN_5
#define PWM20_GPIO_Port GPIOC
#define PWM23_Pin LL_GPIO_PIN_2
#define PWM23_GPIO_Port GPIOB
#define PWM24_Pin LL_GPIO_PIN_7
#define PWM24_GPIO_Port GPIOE
#define PWM25_Pin LL_GPIO_PIN_8
#define PWM25_GPIO_Port GPIOE
#define PWM27_Pin LL_GPIO_PIN_10
#define PWM27_GPIO_Port GPIOE
#define PWM29_Pin LL_GPIO_PIN_12
#define PWM29_GPIO_Port GPIOE
#define PWM30_Pin LL_GPIO_PIN_15
#define PWM30_GPIO_Port GPIOE
#define PWM31_Pin LL_GPIO_PIN_12
#define PWM31_GPIO_Port GPIOB
#define PWM32_Pin LL_GPIO_PIN_13
#define PWM32_GPIO_Port GPIOB
#define PWM35_Pin LL_GPIO_PIN_8
#define PWM35_GPIO_Port GPIOD
#define PWM36_Pin LL_GPIO_PIN_9
#define PWM36_GPIO_Port GPIOD
#define PWM37_Pin LL_GPIO_PIN_10
#define PWM37_GPIO_Port GPIOD
#define PWM38_Pin LL_GPIO_PIN_11
#define PWM38_GPIO_Port GPIOD
#define PWM44_Pin LL_GPIO_PIN_9
#define PWM44_GPIO_Port GPIOA
#define PWM45_Pin LL_GPIO_PIN_10
#define PWM45_GPIO_Port GPIOA
#define PWM46_Pin LL_GPIO_PIN_15
#define PWM46_GPIO_Port GPIOA
#define PWM47_Pin LL_GPIO_PIN_10
#define PWM47_GPIO_Port GPIOC
#define PWM48_Pin LL_GPIO_PIN_11
#define PWM48_GPIO_Port GPIOC
#define PWM49_Pin LL_GPIO_PIN_12
#define PWM49_GPIO_Port GPIOC
#define PWM50_Pin LL_GPIO_PIN_0
#define PWM50_GPIO_Port GPIOD
#define PWM51_Pin LL_GPIO_PIN_1
#define PWM51_GPIO_Port GPIOD
#define PWM52_Pin LL_GPIO_PIN_2
#define PWM52_GPIO_Port GPIOD
#define PWM53_Pin LL_GPIO_PIN_3
#define PWM53_GPIO_Port GPIOD
#define PWM54_Pin LL_GPIO_PIN_4
#define PWM54_GPIO_Port GPIOD
#define PWM55_Pin LL_GPIO_PIN_5
#define PWM55_GPIO_Port GPIOD
#define PWM56_Pin LL_GPIO_PIN_6
#define PWM56_GPIO_Port GPIOD
#define PWM57_Pin LL_GPIO_PIN_7
#define PWM57_GPIO_Port GPIOD
#define PWM64_Pin LL_GPIO_PIN_1
#define PWM64_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

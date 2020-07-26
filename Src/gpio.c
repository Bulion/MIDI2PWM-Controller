/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOE);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);

  /**/
  LL_GPIO_ResetOutputPin(PWM1_GPIO_Port, PWM1_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM2_GPIO_Port, PWM2_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM3_GPIO_Port, PWM3_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM6_GPIO_Port, PWM6_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM7_GPIO_Port, PWM7_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM8_GPIO_Port, PWM8_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM9_GPIO_Port, PWM9_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM10_GPIO_Port, PWM10_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM11_GPIO_Port, PWM11_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM12_GPIO_Port, PWM12_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM19_GPIO_Port, PWM19_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM20_GPIO_Port, PWM20_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM23_GPIO_Port, PWM23_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM24_GPIO_Port, PWM24_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM25_GPIO_Port, PWM25_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM27_GPIO_Port, PWM27_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM29_GPIO_Port, PWM29_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM30_GPIO_Port, PWM30_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM31_GPIO_Port, PWM31_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM32_GPIO_Port, PWM32_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM35_GPIO_Port, PWM35_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM36_GPIO_Port, PWM36_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM37_GPIO_Port, PWM37_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM38_GPIO_Port, PWM38_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM44_GPIO_Port, PWM44_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM45_GPIO_Port, PWM45_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM46_GPIO_Port, PWM46_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM47_GPIO_Port, PWM47_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM48_GPIO_Port, PWM48_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM49_GPIO_Port, PWM49_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM50_GPIO_Port, PWM50_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM51_GPIO_Port, PWM51_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM52_GPIO_Port, PWM52_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM53_GPIO_Port, PWM53_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM54_GPIO_Port, PWM54_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM55_GPIO_Port, PWM55_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM56_GPIO_Port, PWM56_Pin);

  /**/
  LL_GPIO_ResetOutputPin(PWM57_GPIO_Port, PWM57_Pin);

  /**/
  GPIO_InitStruct.Pin = PWM1_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM1_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM2_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM2_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM3_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM3_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM6_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM6_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM7_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM7_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM8_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM8_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM9_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM9_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM10_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM10_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM11_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM11_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM12_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM12_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM19_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM19_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM20_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM20_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM23_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM23_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM24_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM24_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM25_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM25_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM27_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM27_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM29_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM29_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM30_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM30_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM31_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM31_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM32_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM32_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM35_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM35_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM36_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM36_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM37_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM37_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM38_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM38_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM44_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM44_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM45_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM45_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM46_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM46_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM47_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM47_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM48_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM48_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM49_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM49_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM50_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM50_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM51_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM51_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM52_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM52_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM53_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM53_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM54_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM54_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM55_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM55_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM56_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM56_GPIO_Port, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = PWM57_Pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(PWM57_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

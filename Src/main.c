/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "gfxsimulator.h"
#include "i2c.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "usbd_midi_if.h"
#include "fifo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef enum {
	bidirectionalPWM,
	oneDirectionPWM,
} outputType;

typedef struct {
	TIM_HandleTypeDef *htim;
	uint16_t 		  timChannel;
	I2C_HandleTypeDef *hi2c;
	uint8_t			  deviceAddress;
	GPIO_TypeDef	  *gpio;
	uint16_t		  pin;
	uint16_t		  dirMask;
	uint8_t			  pwmFill;
	outputType		  outType;
	uint8_t			  outputEnabled;
	uint8_t			  isOutputSetByNoteOn;
} outputParams;

typedef struct {
	float lastData;
	float LPF_Beta;
} lpfData;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PCAL6416A_ADDR_GND_W	0x40
#define PCAL6416A_ADDR_VCC_W	0x42
#define PCAL6416A_ADDR_GND_R	0x41
#define PCAL6416A_ADDR_VCC_R	0x43
#define PCAL6416A_OUTPUT_REG	0x02

#define CURRENT_DIRECTION_1		0xAA
#define CURRENT_DIRECTION_2		0x55

#define MIDI_STATUS_CC			0x0B
#define MIDI_STATUS_NOTE_ON		0x09
#define MIDI_STATUS_NOTE_OFF	0x08

#define MAX_SOFT_PWM_VAL		12

#define MIDI_HISTERESIS 10

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define ARRAY_SIZE(array)	sizeof(array)/sizeof(array[0])
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint8_t i2cOutputsConfig[8][2];
outputParams outputs[64];

midiFifo fifo;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void setupOutputHardPWM(outputParams      *out,
        		 	 	TIM_HandleTypeDef *htim,
						uint16_t	       timChannel,
						I2C_HandleTypeDef *hi2c,
						uint8_t           deviceAddress,
						uint16_t          dirMask,
						outputType        outType)
{
	out->htim = htim;
	out->timChannel = timChannel;
	out->hi2c = hi2c;
	out->deviceAddress = deviceAddress;
	out->gpio = NULL;
	out->pin = 0;
	out->dirMask = dirMask;
	out->outType = outType;
	out->outputEnabled = 0;
	out->isOutputSetByNoteOn = 0;
}

void setupOutputSoftPWM(outputParams      *out,
						I2C_HandleTypeDef *hi2c,
						uint8_t           deviceAddress,
						GPIO_TypeDef	  *gpio,
						uint16_t		  pin,
						uint16_t          dirMask,
						outputType        outType)
{
	out->htim = NULL;
	out->timChannel = 0;
	out->hi2c = hi2c;
	out->deviceAddress = deviceAddress;
	out->gpio = gpio;
	out->pin = pin;
	out->dirMask = dirMask;
	out->outType = outType;
	out->outputEnabled = 0;
	out->isOutputSetByNoteOn = 0;
}

void initializeOutputs()
{
	setupOutputSoftPWM(&outputs[0],  &hi2c1, PCAL6416A_ADDR_GND_W, PWM1_GPIO_Port, PWM1_Pin, 0x0003, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[1],  &hi2c1, PCAL6416A_ADDR_GND_W, PWM2_GPIO_Port, PWM2_Pin, 0x000C, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[2],  &hi2c1, PCAL6416A_ADDR_GND_W, PWM3_GPIO_Port, PWM3_Pin, 0x0030, oneDirectionPWM);
	setupOutputHardPWM(&outputs[3],  &htim9, TIM_CHANNEL_1, &hi2c1, PCAL6416A_ADDR_GND_W, 0x00C0, oneDirectionPWM);
	setupOutputHardPWM(&outputs[4],  &htim9, TIM_CHANNEL_2, &hi2c1, PCAL6416A_ADDR_GND_W, 0x0300, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[5],  &hi2c1, PCAL6416A_ADDR_GND_W, PWM6_GPIO_Port, PWM6_Pin, 0x0C00, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[6],  &hi2c1, PCAL6416A_ADDR_GND_W, PWM7_GPIO_Port, PWM7_Pin, 0x3000, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[7],  &hi2c1, PCAL6416A_ADDR_GND_W, PWM8_GPIO_Port, PWM8_Pin, 0xC000, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[8],  &hi2c1, PCAL6416A_ADDR_VCC_W, PWM9_GPIO_Port, PWM9_Pin, 0x0003, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[9],  &hi2c1, PCAL6416A_ADDR_VCC_W, PWM10_GPIO_Port, PWM10_Pin, 0x000C, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[10], &hi2c1, PCAL6416A_ADDR_VCC_W, PWM11_GPIO_Port, PWM11_Pin, 0x0030, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[11], &hi2c1, PCAL6416A_ADDR_VCC_W, PWM12_GPIO_Port, PWM12_Pin, 0x00C0, oneDirectionPWM);
	setupOutputHardPWM(&outputs[12], &htim5, TIM_CHANNEL_1, &hi2c1, PCAL6416A_ADDR_VCC_W, 0x0300, oneDirectionPWM);
	setupOutputHardPWM(&outputs[13], &htim5, TIM_CHANNEL_2, &hi2c1, PCAL6416A_ADDR_VCC_W, 0x0C00, oneDirectionPWM);
	setupOutputHardPWM(&outputs[14], &htim5, TIM_CHANNEL_3, &hi2c1, PCAL6416A_ADDR_VCC_W, 0x3000, oneDirectionPWM);
	setupOutputHardPWM(&outputs[15], &htim5, TIM_CHANNEL_4, &hi2c1, PCAL6416A_ADDR_VCC_W, 0xC000, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[16], &hi2c2, PCAL6416A_ADDR_GND_W, PWM17_GPIO_Port, PWM17_Pin, 0x0003, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[17], &hi2c2, PCAL6416A_ADDR_GND_W, PWM18_GPIO_Port, PWM18_Pin, 0x000C, oneDirectionPWM);
	setupOutputHardPWM(&outputs[18], &htim3, TIM_CHANNEL_3, &hi2c2, PCAL6416A_ADDR_GND_W, 0x0030, oneDirectionPWM);
	setupOutputHardPWM(&outputs[19], &htim3, TIM_CHANNEL_4, &hi2c2, PCAL6416A_ADDR_GND_W, 0x00C0, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[20], &hi2c2, PCAL6416A_ADDR_GND_W, PWM21_GPIO_Port, PWM21_Pin, 0x0300, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[21], &hi2c2, PCAL6416A_ADDR_GND_W, PWM22_GPIO_Port, PWM22_Pin, 0x0C00, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[22], &hi2c2, PCAL6416A_ADDR_GND_W, PWM23_GPIO_Port, PWM23_Pin, 0x3000, oneDirectionPWM);
	setupOutputHardPWM(&outputs[23], &htim1, TIM_CHANNEL_1, &hi2c2, PCAL6416A_ADDR_GND_W, 0xC000, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[24], &hi2c2, PCAL6416A_ADDR_VCC_W, PWM25_GPIO_Port, PWM25_Pin, 0x0003, oneDirectionPWM);
	setupOutputHardPWM(&outputs[25], &htim1, TIM_CHANNEL_2, &hi2c2, PCAL6416A_ADDR_VCC_W, 0x000C, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[26], &hi2c2, PCAL6416A_ADDR_VCC_W, PWM27_GPIO_Port, PWM27_Pin, 0x0030, oneDirectionPWM);
	setupOutputHardPWM(&outputs[27], &htim1, TIM_CHANNEL_3, &hi2c2, PCAL6416A_ADDR_VCC_W, 0x00C0, oneDirectionPWM);
	setupOutputHardPWM(&outputs[28], &htim1, TIM_CHANNEL_4, &hi2c2, PCAL6416A_ADDR_VCC_W, 0x0300, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[29], &hi2c2, PCAL6416A_ADDR_VCC_W, PWM30_GPIO_Port, PWM30_Pin, 0x0C00, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[30], &hi2c2, PCAL6416A_ADDR_VCC_W, PWM31_GPIO_Port, PWM31_Pin, 0x3000, oneDirectionPWM);
	setupOutputSoftPWM(&outputs[31], &hi2c2, PCAL6416A_ADDR_VCC_W, PWM32_GPIO_Port, PWM32_Pin, 0xC000, oneDirectionPWM);
	setupOutputHardPWM(&outputs[32], &htim12, TIM_CHANNEL_1, &hi2c3, PCAL6416A_ADDR_GND_W, 0x0003, bidirectionalPWM);
	setupOutputHardPWM(&outputs[33], &htim12, TIM_CHANNEL_2, &hi2c3, PCAL6416A_ADDR_GND_W, 0x000C, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[34], &hi2c3, PCAL6416A_ADDR_GND_W, PWM35_GPIO_Port, PWM35_Pin, 0x0030, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[35], &hi2c3, PCAL6416A_ADDR_GND_W, PWM36_GPIO_Port, PWM36_Pin, 0x00C0, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[36], &hi2c3, PCAL6416A_ADDR_GND_W, PWM37_GPIO_Port, PWM37_Pin, 0x0300, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[37], &hi2c3, PCAL6416A_ADDR_GND_W, PWM38_GPIO_Port, PWM38_Pin, 0x0C00, bidirectionalPWM);
	setupOutputHardPWM(&outputs[38], &htim4, TIM_CHANNEL_3, &hi2c3, PCAL6416A_ADDR_GND_W, 0x3000, bidirectionalPWM);
	setupOutputHardPWM(&outputs[39], &htim4, TIM_CHANNEL_4, &hi2c3, PCAL6416A_ADDR_GND_W, 0xC000, bidirectionalPWM);
	setupOutputHardPWM(&outputs[40], &htim8, TIM_CHANNEL_1, &hi2c3, PCAL6416A_ADDR_VCC_W, 0x0003, bidirectionalPWM);
	setupOutputHardPWM(&outputs[41], &htim8, TIM_CHANNEL_2, &hi2c3, PCAL6416A_ADDR_VCC_W, 0x000C, bidirectionalPWM);
	setupOutputHardPWM(&outputs[42], &htim8, TIM_CHANNEL_3, &hi2c3, PCAL6416A_ADDR_VCC_W, 0x0030, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[43], &hi2c3, PCAL6416A_ADDR_VCC_W, PWM44_GPIO_Port, PWM44_Pin, 0x00C0, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[44], &hi2c3, PCAL6416A_ADDR_VCC_W, PWM45_GPIO_Port, PWM45_Pin, 0x0300, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[45], &hi2c3, PCAL6416A_ADDR_VCC_W, PWM46_GPIO_Port, PWM46_Pin, 0x0C00, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[46], &hi2c3, PCAL6416A_ADDR_VCC_W, PWM47_GPIO_Port, PWM47_Pin, 0x3000, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[47], &hi2c3, PCAL6416A_ADDR_VCC_W, PWM48_GPIO_Port, PWM48_Pin, 0xC000, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[48], &hi2c4, PCAL6416A_ADDR_GND_W, PWM49_GPIO_Port, PWM49_Pin, 0x0003, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[49], &hi2c4, PCAL6416A_ADDR_GND_W, PWM50_GPIO_Port, PWM50_Pin, 0x000C, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[50], &hi2c4, PCAL6416A_ADDR_GND_W, PWM51_GPIO_Port, PWM51_Pin, 0x0030, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[51], &hi2c4, PCAL6416A_ADDR_GND_W, PWM52_GPIO_Port, PWM52_Pin, 0x00C0, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[52], &hi2c4, PCAL6416A_ADDR_GND_W, PWM53_GPIO_Port, PWM53_Pin, 0x0300, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[53], &hi2c4, PCAL6416A_ADDR_GND_W, PWM54_GPIO_Port, PWM54_Pin, 0x0C00, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[54], &hi2c4, PCAL6416A_ADDR_GND_W, PWM55_GPIO_Port, PWM55_Pin, 0x3000, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[55], &hi2c4, PCAL6416A_ADDR_GND_W, PWM56_GPIO_Port, PWM56_Pin, 0xC000, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[56], &hi2c4, PCAL6416A_ADDR_VCC_W, PWM57_GPIO_Port, PWM57_Pin, 0x0003, bidirectionalPWM);
	setupOutputHardPWM(&outputs[57], &htim2, TIM_CHANNEL_2, &hi2c4, PCAL6416A_ADDR_VCC_W, 0x000C, bidirectionalPWM);
	setupOutputHardPWM(&outputs[58], &htim3, TIM_CHANNEL_1, &hi2c4, PCAL6416A_ADDR_VCC_W, 0x0030, bidirectionalPWM);
	setupOutputHardPWM(&outputs[59], &htim3, TIM_CHANNEL_2, &hi2c4, PCAL6416A_ADDR_VCC_W, 0x00C0, bidirectionalPWM);
	setupOutputHardPWM(&outputs[60], &htim10, TIM_CHANNEL_1, &hi2c4, PCAL6416A_ADDR_VCC_W, 0x0300, bidirectionalPWM);
	setupOutputHardPWM(&outputs[61], &htim11, TIM_CHANNEL_1, &hi2c4, PCAL6416A_ADDR_VCC_W, 0x0C00, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[62], &hi2c4, PCAL6416A_ADDR_VCC_W, PWM63_GPIO_Port, PWM63_Pin, 0x3000, bidirectionalPWM);
	setupOutputSoftPWM(&outputs[63], &hi2c4, PCAL6416A_ADDR_VCC_W, PWM64_GPIO_Port, PWM64_Pin, 0xC000, bidirectionalPWM);
}

void setHardPWM(TIM_HandleTypeDef *htim, uint16_t timChannel, uint8_t pwmValue)
{
	switch(timChannel)
	{
	case TIM_CHANNEL_1:
		htim->Instance->CCR1 = pwmValue;
		break;
	case TIM_CHANNEL_2:
		htim->Instance->CCR2 = pwmValue;
		break;
	case TIM_CHANNEL_3:
		htim->Instance->CCR3 = pwmValue;
		break;
	case TIM_CHANNEL_4:
		htim->Instance->CCR4 = pwmValue;
		break;
	case TIM_CHANNEL_5:
		htim->Instance->CCR5 = pwmValue;
		break;
	case TIM_CHANNEL_6:
		htim->Instance->CCR6 = pwmValue;
		break;
	}
}

void setBidirectionalPWM(outputParams *out, uint8_t pwmValue, uint8_t channel)
{
	uint8_t txBuff[3] = { PCAL6416A_OUTPUT_REG, 0, 0 };
	if(pwmValue >= 64)
	{
		txBuff[1] = ((uint8_t)out->dirMask & CURRENT_DIRECTION_1) | (i2cOutputsConfig[channel/8][0] & ~(uint8_t)out->dirMask);
		txBuff[2] = ((uint8_t)(out->dirMask >> 8) & CURRENT_DIRECTION_1) | (i2cOutputsConfig[channel/8][1] & ~(uint8_t)(out->dirMask >> 8));
		i2cOutputsConfig[channel/8][0] = txBuff[1];
		i2cOutputsConfig[channel/8][1] = txBuff[2];
		pwmValue -= 64;
	}
	else
	{
		txBuff[1] = ((uint8_t)out->dirMask & CURRENT_DIRECTION_2) | (i2cOutputsConfig[channel/8][0] & ~(uint8_t)out->dirMask);
		txBuff[2] = ((uint8_t)(out->dirMask >> 8) & CURRENT_DIRECTION_2) | (i2cOutputsConfig[channel/8][1] & ~(uint8_t)(out->dirMask >> 8));
		i2cOutputsConfig[channel/8][0] = txBuff[1];
		i2cOutputsConfig[channel/8][1] = txBuff[2];
		pwmValue = 64 - pwmValue;
	}
	HAL_I2C_Master_Transmit(out->hi2c,out->deviceAddress,txBuff,ARRAY_SIZE(txBuff),100);
	if(out->htim != NULL)
	{
		setHardPWM(out->htim, out->timChannel, pwmValue*2);
	}
	else
	{
		out->pwmFill = MAX_SOFT_PWM_VAL * pwmValue/63 ;
	}
}

void setOneDirectionPWM(outputParams *out, uint8_t pwmValue, uint8_t channel)
{
	uint8_t txBuff[3] = { PCAL6416A_OUTPUT_REG, ((uint8_t)out->dirMask & CURRENT_DIRECTION_1) | (i2cOutputsConfig[channel/8][0] & ~(uint8_t)out->dirMask),
												((uint8_t)(out->dirMask >> 8) & CURRENT_DIRECTION_1) | (i2cOutputsConfig[channel/8][1] & ~(uint8_t)(out->dirMask >> 8)) };
	i2cOutputsConfig[channel/8][0] = ((uint8_t)out->dirMask & CURRENT_DIRECTION_1) | (i2cOutputsConfig[channel/8][0] & ~(uint8_t)out->dirMask);
	i2cOutputsConfig[channel/8][1] = ((uint8_t)(out->dirMask >> 8) & CURRENT_DIRECTION_1) | (i2cOutputsConfig[channel/8][1] & ~(uint8_t)(out->dirMask >> 8));
	HAL_I2C_Master_Transmit(out->hi2c,out->deviceAddress,txBuff,ARRAY_SIZE(txBuff),100);
	if(out->htim != NULL)
	{
		setHardPWM(out->htim, out->timChannel, pwmValue);
	}
	else
	{
		out->pwmFill = MAX_SOFT_PWM_VAL * pwmValue/127;
	}
}

void setOutputOn(outputParams *out, uint8_t pwmValue, uint8_t channel)
{
	if(out->htim != NULL)
	{
		HAL_TIM_PWM_Start(out->htim,out->timChannel);
		out->outputEnabled = 1;
		out->isOutputSetByNoteOn = 1;
	}
	else
	{
		out->outputEnabled = 1;
		out->isOutputSetByNoteOn = 1;
	}
}

void setOutputOff(outputParams *out)
{
	if(out->htim != NULL)
	{
		HAL_TIM_PWM_Stop(out->htim,out->timChannel);
		out->outputEnabled = 0;
		out->isOutputSetByNoteOn = 0;
	}
	else
	{
		out->outputEnabled = 0;
		out->isOutputSetByNoteOn = 0;
	}
}

void setOutputPWMValue(uint8_t channel, uint8_t pwm)
{
	if(channel < 65)
	{
		outputParams *out = &outputs[channel-1];

		switch(out->outType)
		{
		case bidirectionalPWM:
			setBidirectionalPWM(out, pwm, channel-1);
			break;
		case oneDirectionPWM:
			setOneDirectionPWM(out, pwm, channel-1);
			break;
		}
	}
}

void setOutputNoteValue(uint8_t channel, uint8_t noteVel)
{
	if(channel < 65)
	{
		outputParams *out = &outputs[channel-1];

		if(noteVel)
		{
			setOutputOn(out, 0, channel-1);
		}
		else
		{
			setOutputOff(out);
		}
	}
}

void panicOff()
{
	for(int i = 0; i < 64; ++i)
	{
		if(outputs[i].htim != NULL)
		{
			setHardPWM(outputs[i].htim,outputs[i].timChannel,0);
		}
		else
		{
			outputs[i].pwmFill = 0;
		}
	}
}

void allOff()
{
	for(int i = 0; i < 64; ++i)
	{
		if(outputs[i].isOutputSetByNoteOn)
		{
			if(outputs[i].htim != NULL)
			{
				HAL_TIM_PWM_Stop(outputs[i].htim,outputs[i].timChannel);
				outputs[i].outputEnabled = 0;
			}
			else
			{
			outputs[i].outputEnabled = 0;
			}
		}
	}
}

void allOn()
{
	for(int i = 0; i < 64; ++i)
	{
		if(outputs[i].isOutputSetByNoteOn)
		{
			if(outputs[i].htim != NULL)
			{
				HAL_TIM_PWM_Start(outputs[i].htim,outputs[i].timChannel);
				outputs[i].outputEnabled = 1;
			}
			else
			{
				outputs[i].outputEnabled = 1;
			}
		}
	}
}

void startAllTimers()
{
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
//	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
	HAL_TIM_Base_Start_IT(&htim6);
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
//	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
//	HAL_TIM_PWM_Start(&htim10,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim11,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);
}

uint8_t lpfFilter(uint8_t inputValue, lpfData *filterData)
{
	 filterData->lastData = filterData->lastData - (filterData->LPF_Beta * (filterData->lastData - inputValue));
	 if(filterData->lastData > 255)
	 {
		 filterData->lastData = 255;
	 }
	 return filterData->lastData;
}

uint8_t rxBuff;
volatile uint8_t midiOutLastData[4];
volatile uint8_t midiOutData[4];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t momentarySwithWasPressed = 0;
	uint8_t pressedDownFlag = 0;
	uint8_t pressedCount = 0;
	uint8_t adcConvNum = 0;
	uint8_t lastAdcConvNum = 123;
	uint8_t pcal6416aConfig[3] = { 0x06, 0x00, 0x00 };
	initFifo(&fifo);
	midiData_t rxMidiMessage = { 0, 0, 0, 0 };
	uint8_t txMidiMessage[4][4] = {{ MIDI_STATUS_CC, MIDI_STATUS_CC << 4, 1, 0 },
								   { MIDI_STATUS_CC, MIDI_STATUS_CC << 4, 2, 0 },
								   { MIDI_STATUS_CC, MIDI_STATUS_CC << 4, 3, 0 },
								   { MIDI_STATUS_CC, MIDI_STATUS_CC << 4, 4, 0 }};

	lpfData lpfAdc0 = {0, 0.1};
	lpfData lpfAdc1 = {0, 0.1};
	lpfData lpfAdc2 = {0, 0.1};

	uint32_t lastSystickVal = 0;

	rxBuff = 0;
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
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  MX_I2C4_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM9_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM12_Init();
  MX_TIM6_Init();
  MX_USB_DEVICE_Init();
  MX_GFXSIMULATOR_Init();
  MX_ADC1_Init();
  MX_UART8_Init();
  /* USER CODE BEGIN 2 */
  HAL_I2C_Master_Transmit(&hi2c1, PCAL6416A_ADDR_GND_W ,pcal6416aConfig, ARRAY_SIZE(pcal6416aConfig), 100);
  HAL_I2C_Master_Transmit(&hi2c1, PCAL6416A_ADDR_VCC_W ,pcal6416aConfig, ARRAY_SIZE(pcal6416aConfig), 100);
  HAL_I2C_Master_Transmit(&hi2c2, PCAL6416A_ADDR_GND_W ,pcal6416aConfig, ARRAY_SIZE(pcal6416aConfig), 100);
  HAL_I2C_Master_Transmit(&hi2c2, PCAL6416A_ADDR_VCC_W ,pcal6416aConfig, ARRAY_SIZE(pcal6416aConfig), 100);
  HAL_I2C_Master_Transmit(&hi2c3, PCAL6416A_ADDR_GND_W ,pcal6416aConfig, ARRAY_SIZE(pcal6416aConfig), 100);
  HAL_I2C_Master_Transmit(&hi2c3, PCAL6416A_ADDR_VCC_W ,pcal6416aConfig, ARRAY_SIZE(pcal6416aConfig), 100);
  HAL_I2C_Master_Transmit(&hi2c4, PCAL6416A_ADDR_GND_W ,pcal6416aConfig, ARRAY_SIZE(pcal6416aConfig), 100);
  HAL_I2C_Master_Transmit(&hi2c4, PCAL6416A_ADDR_VCC_W ,pcal6416aConfig, ARRAY_SIZE(pcal6416aConfig), 100);

  initializeOutputs();
  startAllTimers();
  HAL_UART_Receive_IT(&huart8,&rxBuff,1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  rxMidiMessage = pop(&fifo);
	  if(rxMidiMessage.status != 0)
	  {
		  switch(rxMidiMessage.status)
		  {
		  case MIDI_STATUS_CC:
			  setOutputPWMValue(rxMidiMessage.data1, rxMidiMessage.data2);
			  break;
		  case MIDI_STATUS_NOTE_OFF:
			  setOutputNoteValue(rxMidiMessage.data1, 0);
			  break;
		  case MIDI_STATUS_NOTE_ON:
			  setOutputNoteValue(rxMidiMessage.data1, rxMidiMessage.data2);
			  break;
		  }
	  }
	  if(adcConvNum == 0 && adcConvNum != lastAdcConvNum)
	  {
		  lastAdcConvNum = adcConvNum;
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1,100);
		  midiOutData[0]= 127 * lpfFilter(HAL_ADC_GetValue(&hadc1), &lpfAdc0)/62;
		  if(midiOutData[0] < 64)
		  {
			  panicOff();
		  }
		  if((midiOutData[0] > midiOutLastData[0]) || (midiOutData[0] < midiOutLastData[0]))
		  {
		      txMidiMessage[0][3] = midiOutData[0];
		      midiOutLastData[0] = midiOutData[0];
		      MIDI_Transmit_FS(txMidiMessage[0],4);
		  }
	  }
	  if(adcConvNum == 1 && adcConvNum != lastAdcConvNum)
	  {
		  lastAdcConvNum = adcConvNum;
		  midiOutData[1] = (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_13) ? 127 : 0);
		  if((midiOutData[1] > midiOutLastData[1]) || (midiOutData[1] < midiOutLastData[1]))
		  {
			  txMidiMessage[1][3] = midiOutData[1];
			  midiOutLastData[1] = midiOutData[1];
			  MIDI_Transmit_FS(txMidiMessage[1],4);
		  }
	  }
	  if(adcConvNum == 2 && adcConvNum != lastAdcConvNum)
	  {
		  lastAdcConvNum = adcConvNum;
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1,100);
		  midiOutData[2]= 127 * lpfFilter(HAL_ADC_GetValue(&hadc1), &lpfAdc1)/62;
		  if(midiOutData[2] < 63)
		  {
			  if(pressedDownFlag != 1)
			  {
				  if(pressedCount == 0)
				  {
					  pressedCount = 1;
					  allOff();
				  }
				  else
				  {
					  pressedCount = 0;
					  allOn();
				  }
				  pressedDownFlag = 1;
			  }
		  }
		  else
		  {
			  pressedDownFlag = 0;
		  }
		  if((midiOutData[2] > midiOutLastData[2]) || (midiOutData[2] < midiOutLastData[2]))
		  {
			  txMidiMessage[2][3] = midiOutData[2];
			  midiOutLastData[2] = midiOutData[2];
			  MIDI_Transmit_FS(txMidiMessage[2],4);
		  }
	  }
	  if(adcConvNum == 3 && adcConvNum != lastAdcConvNum)
	  {
		  lastAdcConvNum = adcConvNum;
		  HAL_ADC_Start(&hadc1);
		  HAL_ADC_PollForConversion(&hadc1,100);
		  midiOutData[3]= 127 * lpfFilter(HAL_ADC_GetValue(&hadc1), &lpfAdc2)/62;
		  if(midiOutData[3] < 63)
		  {
			  pressedCount = 0;
			  allOff();
			  momentarySwithWasPressed = 1;
		  }
		  else
		  {
			  if(momentarySwithWasPressed == 1)
			  {
				  allOn();
				  momentarySwithWasPressed = 0;
			  }
		  }
		  if((midiOutData[3] > midiOutLastData[3]) || (midiOutData[3] < midiOutLastData[3]))
		  {
			  txMidiMessage[3][3] = midiOutData[3];
			  midiOutLastData[3] = midiOutData[3];
			  MIDI_Transmit_FS(txMidiMessage[3],4);
		  }
	  }
	  if(lastSystickVal != HAL_GetTick())
	  {
		  adcConvNum++;
		  if(adcConvNum > 3)
		  {
			  adcConvNum = 0;
		  }
		  lastSystickVal = HAL_GetTick();
	  }
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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART8|RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_I2C2
                              |RCC_PERIPHCLK_I2C3|RCC_PERIPHCLK_I2C4
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart8ClockSelection = RCC_UART8CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static int i;
    static uint8_t count = 0;

	for(i = 0; i < 64; ++i)
	{
		if(outputs[i].gpio != NULL)
		{
			if(outputs[i].pwmFill > count && outputs[i].outputEnabled)
			{
				outputs[i].gpio->BSRR = outputs[i].pin;
			}
			else
			{
				outputs[i].gpio->BSRR = (uint32_t)outputs[i].pin << 16;
			}
		}
	}

	++count;
	if(count > MAX_SOFT_PWM_VAL)
	{
		count = 0;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static midiData_t midiFrame;
	static uint8_t frameFlag = 0;
	if(frameFlag == 3)
	{
		midiFrame.data2 = rxBuff;
		push(&fifo,&midiFrame);
		frameFlag = 0;
	}
	if(frameFlag == 2)
	{
		midiFrame.data1 = rxBuff;
		frameFlag = 3;
	}
	if(frameFlag == 1)
	{
		if(midiFrame.channel == (rxBuff << 4))
		{
			frameFlag = 2;
		}
		else
		{
			midiFrame.status = 0;
			midiFrame.channel = 0;
		}
	}
	if(rxBuff == MIDI_STATUS_CC || rxBuff == MIDI_STATUS_NOTE_ON || rxBuff == MIDI_STATUS_NOTE_OFF)
	{
		midiFrame.status = rxBuff;
		midiFrame.channel = rxBuff<<4;
		frameFlag = 1;
	}
	else if(rxBuff >> 4 == MIDI_STATUS_CC || rxBuff >> 4 == MIDI_STATUS_NOTE_ON || rxBuff >> 4 == MIDI_STATUS_NOTE_OFF)
	{
		midiFrame.status = rxBuff >> 4;
		midiFrame.channel = rxBuff;
		frameFlag = 2;
	}
	HAL_UART_Receive_IT(huart,&rxBuff,1);
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

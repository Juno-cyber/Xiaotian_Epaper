/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

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
#define DS1302_CE_Pin GPIO_PIN_13
#define DS1302_CE_GPIO_Port GPIOC
#define IO_LED_Pin GPIO_PIN_1
#define IO_LED_GPIO_Port GPIOA
#define EP_SDI_Pin GPIO_PIN_4
#define EP_SDI_GPIO_Port GPIOA
#define EP_SCK_Pin GPIO_PIN_5
#define EP_SCK_GPIO_Port GPIOA
#define EP_CS_Pin GPIO_PIN_6
#define EP_CS_GPIO_Port GPIOA
#define EP_DC_Pin GPIO_PIN_7
#define EP_DC_GPIO_Port GPIOA
#define EP_RST_Pin GPIO_PIN_0
#define EP_RST_GPIO_Port GPIOB
#define EP_BUSY_Pin GPIO_PIN_1
#define EP_BUSY_GPIO_Port GPIOB
#define DS1302_SCL_Pin GPIO_PIN_8
#define DS1302_SCL_GPIO_Port GPIOB
#define DS1302_DATA_Pin GPIO_PIN_9
#define DS1302_DATA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

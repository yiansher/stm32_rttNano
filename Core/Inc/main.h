/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
//#include "rtthread.h"
#include <stdio.h>
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
void SystemClock_Config(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RESET_Pin GPIO_PIN_4
#define RESET_GPIO_Port GPIOA
#define CS_Pin GPIO_PIN_4
#define CS_GPIO_Port GPIOC
#define DC_Pin GPIO_PIN_5
#define DC_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_8
#define LED_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define USER_MAIN_DEBUG 1
#ifdef USER_MAIN_DEBUG
#define	APP_ERROR(fmt, ...) do {rt_kprintf("[ERROR][%s,%d]: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);} while(0)
#define	APP_TRACE(fmt, ...) do {rt_kprintf("[TRACE][%s,%d]: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);} while(0)
#define	APP_DEBUG(fmt, ...) do {rt_kprintf("[DEBUG][%s,%d]: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);} while(0)
#else
#define	APP_ERROR(fmt, ...)
#define	APP_TRACE(fmt, ...)
#define	APP_DEBUG(fmt, ...)
#endif
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

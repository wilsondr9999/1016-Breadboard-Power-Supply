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
#include "stm32c0xx_hal.h"

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
#define LED_Error_Pin GPIO_PIN_0
#define LED_Error_GPIO_Port GPIOA
#define LED_Output_Pin GPIO_PIN_1
#define LED_Output_GPIO_Port GPIOA
#define LED_5VT_Pin GPIO_PIN_2
#define LED_5VT_GPIO_Port GPIOA
#define LED_5VB_Pin GPIO_PIN_3
#define LED_5VB_GPIO_Port GPIOA
#define LED_3V3T_Pin GPIO_PIN_4
#define LED_3V3T_GPIO_Port GPIOA
#define LED_3V3B_Pin GPIO_PIN_5
#define LED_3V3B_GPIO_Port GPIOA
#define Btn_Config_Pin GPIO_PIN_6
#define Btn_Config_GPIO_Port GPIOA
#define Btn_OutputEn_Pin GPIO_PIN_7
#define Btn_OutputEn_GPIO_Port GPIOA
#define Select_VRailB_Pin GPIO_PIN_8
#define Select_VRailB_GPIO_Port GPIOA
#define Select_VRailT_Pin GPIO_PIN_11
#define Select_VRailT_GPIO_Port GPIOA
#define Output_Enable_Pin GPIO_PIN_12
#define Output_Enable_GPIO_Port GPIOA
#define PGood_RailB_Pin GPIO_PIN_6
#define PGood_RailB_GPIO_Port GPIOB
#define PGood_RailT_Pin GPIO_PIN_7
#define PGood_RailT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

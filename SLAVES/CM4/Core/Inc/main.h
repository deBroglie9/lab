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
#include "stm32h7xx_hal.h"

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
#define SPI3_NSS_Pin GPIO_PIN_10
#define SPI3_NSS_GPIO_Port GPIOE
#define SPI3_IRQ_Pin GPIO_PIN_4
#define SPI3_IRQ_GPIO_Port GPIOD
#define SYNC_L0_Pin GPIO_PIN_5
#define SYNC_L0_GPIO_Port GPIOD
#define SYNC_L1_Pin GPIO_PIN_6
#define SYNC_L1_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */
#define SPI3_IRQ_EXTI_IRQn EXTI4_IRQn
#define SYNC_L0_EXTI_IRQn EXTI9_5_IRQn
#define SYNC_L1_EXTI_IRQn EXTI9_5_IRQn

#define DESELECT_SPI HAL_GPIO_WritePin(SPI3_NSS_GPIO_Port,SPI3_NSS_Pin,GPIO_PIN_SET)
#define SELECT_SPI HAL_GPIO_WritePin(SPI3_NSS_GPIO_Port,SPI3_NSS_Pin,GPIO_PIN_RESET)


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

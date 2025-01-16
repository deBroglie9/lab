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
#include "openamp.h"
static struct rpmsg_endpoint rp_endpoint;
extern uint32_t message;
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
#define SSI2_CLK_Pin GPIO_PIN_3
#define SSI2_CLK_GPIO_Port GPIOE
#define SSI2_RX_Pin GPIO_PIN_4
#define SSI2_RX_GPIO_Port GPIOE
#define SSI3_CLK_Pin GPIO_PIN_8
#define SSI3_CLK_GPIO_Port GPIOE
#define SSI3_RX_Pin GPIO_PIN_9
#define SSI3_RX_GPIO_Port GPIOE
#define SSI4_CLK_Pin GPIO_PIN_11
#define SSI4_CLK_GPIO_Port GPIOE
#define SSI4_RX_Pin GPIO_PIN_12
#define SSI4_RX_GPIO_Port GPIOE
#define SSI5_CLK_Pin GPIO_PIN_13
#define SSI5_CLK_GPIO_Port GPIOE
#define SSI5_RX_Pin GPIO_PIN_14
#define SSI5_RX_GPIO_Port GPIOE
#define SSI6_CLK_Pin GPIO_PIN_6
#define SSI6_CLK_GPIO_Port GPIOG
#define SSI6_RX_Pin GPIO_PIN_7
#define SSI6_RX_GPIO_Port GPIOG
#define SSI7_CLK_Pin GPIO_PIN_8
#define SSI7_CLK_GPIO_Port GPIOG
#define SSI7_RX_Pin GPIO_PIN_9
#define SSI7_RX_GPIO_Port GPIOG
#define SSI8_CLK_Pin GPIO_PIN_10
#define SSI8_CLK_GPIO_Port GPIOG
#define SSI8_RX_Pin GPIO_PIN_11
#define SSI8_RX_GPIO_Port GPIOG
#define SSI1_CLK_Pin GPIO_PIN_0
#define SSI1_CLK_GPIO_Port GPIOE
#define SSI1_RX_Pin GPIO_PIN_1
#define SSI1_RX_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

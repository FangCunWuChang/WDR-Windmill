/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define EXTI_A_Pin GPIO_PIN_4
#define EXTI_A_GPIO_Port GPIOE
#define EXTI_A_EXTI_IRQn EXTI4_IRQn
#define DATA_E0_Pin GPIO_PIN_0
#define DATA_E0_GPIO_Port GPIOA
#define DATA_reserve_Pin GPIO_PIN_1
#define DATA_reserve_GPIO_Port GPIOA
#define DATA_A1_Pin GPIO_PIN_2
#define DATA_A1_GPIO_Port GPIOA
#define DATA_B1_Pin GPIO_PIN_3
#define DATA_B1_GPIO_Port GPIOA
#define DATA_C1_Pin GPIO_PIN_6
#define DATA_C1_GPIO_Port GPIOA
#define DATA_D1_Pin GPIO_PIN_7
#define DATA_D1_GPIO_Port GPIOA
#define DATA_E1_Pin GPIO_PIN_0
#define DATA_E1_GPIO_Port GPIOB
#define DATA_res1_Pin GPIO_PIN_1
#define DATA_res1_GPIO_Port GPIOB
#define EXTI_reserve_Pin GPIO_PIN_8
#define EXTI_reserve_GPIO_Port GPIOE
#define EXTI_reserve_EXTI_IRQn EXTI9_5_IRQn
#define DATA_A0_Pin GPIO_PIN_9
#define DATA_A0_GPIO_Port GPIOE
#define EXTI_E_Pin GPIO_PIN_10
#define EXTI_E_GPIO_Port GPIOE
#define EXTI_E_EXTI_IRQn EXTI15_10_IRQn
#define DATA_B0_Pin GPIO_PIN_11
#define DATA_B0_GPIO_Port GPIOE
#define DATA_C0_Pin GPIO_PIN_13
#define DATA_C0_GPIO_Port GPIOE
#define DATA_D0_Pin GPIO_PIN_14
#define DATA_D0_GPIO_Port GPIOE
#define EXTI_D_Pin GPIO_PIN_15
#define EXTI_D_GPIO_Port GPIOD
#define EXTI_D_EXTI_IRQn EXTI15_10_IRQn
#define EXTI_C_Pin GPIO_PIN_7
#define EXTI_C_GPIO_Port GPIOC
#define EXTI_C_EXTI_IRQn EXTI9_5_IRQn
#define EXTI_B_Pin GPIO_PIN_1
#define EXTI_B_GPIO_Port GPIOE
#define EXTI_B_EXTI_IRQn EXTI1_IRQn
/* USER CODE BEGIN Private defines */
extern  uint32_t color;
#define	ORANGE  0x7f2000
#define  CYAN   0x006043
#define _color_chose(mode)       \
{                                \
	if(mode == 1)                \
	{							\
		color = ORANGE;			\
	}							\
	else						\
	{							\
		color = CYAN;			\
	}							\
}								
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

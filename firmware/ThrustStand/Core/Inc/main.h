/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Charles Surianto
 * All rights reserved.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

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

    void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

    /* Exported functions prototypes ---------------------------------------------*/
    void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define V_SENSE_Pin GPIO_PIN_4
#define V_SENSE_GPIO_Port GPIOA
#define I_SENSE_Pin GPIO_PIN_5
#define I_SENSE_GPIO_Port GPIOA
#define ESC_SIG_Pin GPIO_PIN_7
#define ESC_SIG_GPIO_Port GPIOA
#define AMP1_Pin GPIO_PIN_0
#define AMP1_GPIO_Port GPIOB
#define AMP2_Pin GPIO_PIN_1
#define AMP2_GPIO_Port GPIOB
#define AMP3_Pin GPIO_PIN_12
#define AMP3_GPIO_Port GPIOB
#define AMP4_Pin GPIO_PIN_13
#define AMP4_GPIO_Port GPIOB
#define AMP5_Pin GPIO_PIN_14
#define AMP5_GPIO_Port GPIOB
#define AMP6_Pin GPIO_PIN_15
#define AMP6_GPIO_Port GPIOB
#define AMP_CLK_Pin GPIO_PIN_6
#define AMP_CLK_GPIO_Port GPIOC
#define UARTA_TX_Pin GPIO_PIN_10
#define UARTA_TX_GPIO_Port GPIOC
#define UARTA_RX_Pin GPIO_PIN_11
#define UARTA_RX_GPIO_Port GPIOC
#define UARTB_TX_Pin GPIO_PIN_3
#define UARTB_TX_GPIO_Port GPIOB
#define UARTB_RX_Pin GPIO_PIN_4
#define UARTB_RX_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define NUM_OF_CELLS 6
    /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

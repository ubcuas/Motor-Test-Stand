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
extern "C" {
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
#define CELL1_Pin GPIO_PIN_0
#define CELL1_GPIO_Port GPIOB
#define CELL2_Pin GPIO_PIN_1
#define CELL2_GPIO_Port GPIOB
#define CELL3_Pin GPIO_PIN_2
#define CELL3_GPIO_Port GPIOB
#define CELLAMP_CLK_Pin GPIO_PIN_10
#define CELLAMP_CLK_GPIO_Port GPIOB
#define CELL4_Pin GPIO_PIN_11
#define CELL4_GPIO_Port GPIOB
#define CELL5_Pin GPIO_PIN_12
#define CELL5_GPIO_Port GPIOB
#define CELL6_Pin GPIO_PIN_13
#define CELL6_GPIO_Port GPIOB
#define UARTA_TX_Pin GPIO_PIN_10
#define UARTA_TX_GPIO_Port GPIOC
#define UARTA_RX_Pin GPIO_PIN_11
#define UARTA_RX_GPIO_Port GPIOC

/* USER CODE BEGIN Private defines */
#define NUM_OF_CELLS 6
#define HUARTA huart3
#define UART_RX_BUFFER_SIZE 20
#define UART_TX_BUFFER_SIZE 200
#define CELLAMP_CLK_HTIM htim2
#define CELLAMP_CLK_CHANNEL TIM_CHANNEL_3
#define ESCSIG_HTIM htim17
#define ESCSIG_CHANNEL TIM_CHANNEL_1
#define UART_TIMEOUT_HTIM htim16
#define PERIODIC_INT_HTIM htim15
#define EEPROM_DEVICE_ADDR 0x50
#define EEPROM_PAGE_SIZE 16
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

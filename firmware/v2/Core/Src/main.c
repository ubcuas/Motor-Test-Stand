/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 Charles Surianto
 * All rights reserved.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdint.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc2;
DMA_HandleTypeDef hdma_adc2;

I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim6;
TIM_HandleTypeDef htim17;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
GPIO_TypeDef *HX717DataPorts[NUM_OF_CELLS] = {
    CELL1_GPIO_Port,
    CELL2_GPIO_Port,
    CELL3_GPIO_Port,
    CELL4_GPIO_Port,
    CELL5_GPIO_Port,
    CELL6_GPIO_Port};
uint16_t HX717DataPins[NUM_OF_CELLS] = {
    CELL1_Pin,
    CELL2_Pin,
    CELL3_Pin,
    CELL4_Pin,
    CELL5_Pin,
    CELL6_Pin};
int32_t RawCellReadings[NUM_OF_CELLS];
int8_t PulseCounter = -1;

uint16_t RawADCReadings[2];
float Voltage;
float Current;
float VoltPerADC;
float VoltOffset;
float AmpPerADC;
float AmpOffset;

float ForcePerADC[NUM_OF_CELLS];
float ForceOffset[NUM_OF_CELLS];

uint8_t UARTARxCounter = 0;
uint8_t UARTARxByte;
uint8_t UARTARxBuffer[UART_RX_BUFFER_SIZE];
uint8_t UARTATxBuffer[UART_TX_BUFFER_SIZE];

uint16_t ESCPulse = 1000;
uint16_t PrevESCPulse;

uint8_t EEPROMWriteBuffer[EEPROM_PAGE_SIZE]; // 16 bytes page size
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC2_Init(void);
static void MX_TIM17_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */
void HX717_Init(void);
void ReadEEPROM(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

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
    MX_DMA_Init();
    MX_USART3_UART_Init();
    MX_ADC2_Init();
    MX_TIM17_Init();
    MX_I2C2_Init();
    MX_TIM2_Init();
    MX_TIM6_Init();
    /* USER CODE BEGIN 2 */
    HX717_Init();
    ReadEEPROM();

    HAL_TIM_PWM_Start(&ESCSIG_HTIM, ESCSIG_CHANNEL);
    HAL_TIM_Base_Start_IT(&PERIODIC_INT_HTIM);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
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

    /** Configure the main internal regulator output voltage
     */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
    RCC_OscInitStruct.PLL.PLLN = 24;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief ADC2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC2_Init(void)
{

    /* USER CODE BEGIN ADC2_Init 0 */

    /* USER CODE END ADC2_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC2_Init 1 */

    /* USER CODE END ADC2_Init 1 */

    /** Common config
     */
    hadc2.Instance = ADC2;
    hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc2.Init.Resolution = ADC_RESOLUTION_12B;
    hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc2.Init.GainCompensation = 0;
    hadc2.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc2.Init.LowPowerAutoWait = DISABLE;
    hadc2.Init.ContinuousConvMode = ENABLE;
    hadc2.Init.NbrOfConversion = 2;
    hadc2.Init.DiscontinuousConvMode = DISABLE;
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc2.Init.DMAContinuousRequests = DISABLE;
    hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;
    hadc2.Init.OversamplingMode = ENABLE;
    hadc2.Init.Oversampling.Ratio = ADC_OVERSAMPLING_RATIO_256;
    hadc2.Init.Oversampling.RightBitShift = ADC_RIGHTBITSHIFT_8;
    hadc2.Init.Oversampling.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;
    hadc2.Init.Oversampling.OversamplingStopReset = ADC_REGOVERSAMPLING_CONTINUED_MODE;
    if (HAL_ADC_Init(&hadc2) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_17;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Regular Channel
     */
    sConfig.Channel = ADC_CHANNEL_13;
    sConfig.Rank = ADC_REGULAR_RANK_2;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC2_Init 2 */

    /* USER CODE END ADC2_Init 2 */
}

/**
 * @brief I2C2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C2_Init(void)
{

    /* USER CODE BEGIN I2C2_Init 0 */

    /* USER CODE END I2C2_Init 0 */

    /* USER CODE BEGIN I2C2_Init 1 */

    /* USER CODE END I2C2_Init 1 */
    hi2c2.Instance = I2C2;
    hi2c2.Init.Timing = 0x00E063FF;
    hi2c2.Init.OwnAddress1 = 0;
    hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c2.Init.OwnAddress2 = 0;
    hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
    hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c2) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Analogue filter
     */
    if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        Error_Handler();
    }

    /** Configure Digital filter
     */
    if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C2_Init 2 */

    /* USER CODE END I2C2_Init 2 */
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 150 - 1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_DOWN;
    htim2.Init.Period = 15;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 10;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */

    /* USER CODE END TIM2_Init 2 */
    HAL_TIM_MspPostInit(&htim2);
}

/**
 * @brief TIM6 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM6_Init(void)
{

    /* USER CODE BEGIN TIM6_Init 0 */

    /* USER CODE END TIM6_Init 0 */

    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM6_Init 1 */

    /* USER CODE END TIM6_Init 1 */
    htim6.Instance = TIM6;
    htim6.Init.Prescaler = 1500 - 1;
    htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim6.Init.Period = 5000;
    htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM6_Init 2 */

    /* USER CODE END TIM6_Init 2 */
}

/**
 * @brief TIM17 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM17_Init(void)
{

    /* USER CODE BEGIN TIM17_Init 0 */

    /* USER CODE END TIM17_Init 0 */

    TIM_OC_InitTypeDef sConfigOC = {0};
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

    /* USER CODE BEGIN TIM17_Init 1 */

    /* USER CODE END TIM17_Init 1 */
    htim17.Instance = TIM17;
    htim17.Init.Prescaler = 150 - 1;
    htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim17.Init.Period = 19999;
    htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim17.Init.RepetitionCounter = 0;
    htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim17) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 1000;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    if (HAL_TIM_PWM_ConfigChannel(&htim17, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.BreakFilter = 0;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    if (HAL_TIMEx_ConfigBreakDeadTime(&htim17, &sBreakDeadTimeConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM17_Init 2 */

    /* USER CODE END TIM17_Init 2 */
    HAL_TIM_MspPostInit(&htim17);
}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void)
{

    /* USER CODE BEGIN USART3_Init 0 */

    /* USER CODE END USART3_Init 0 */

    /* USER CODE BEGIN USART3_Init 1 */

    /* USER CODE END USART3_Init 1 */
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 250000;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART3_Init 2 */
    HAL_UART_Receive_IT(&HUARTA, &UARTARxByte, 1);
    /* USER CODE END USART3_Init 2 */
}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void)
{

    /* DMA controller clock enable */
    __HAL_RCC_DMAMUX1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /*Configure GPIO pins : CELL1_Pin CELL2_Pin CELL3_Pin CELL4_Pin
                             CELL5_Pin CELL6_Pin */
    GPIO_InitStruct.Pin = CELL1_Pin | CELL2_Pin | CELL3_Pin | CELL4_Pin | CELL5_Pin | CELL6_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HX717_Init(void)
{
    __HAL_TIM_SET_COMPARE(&CELLAMP_CLK_HTIM, CELLAMP_CLK_CHANNEL, 20); // 100% duty cycle
    HAL_TIM_PWM_Start(&CELLAMP_CLK_HTIM, CELLAMP_CLK_CHANNEL);
    HAL_Delay(1); // wait
    __HAL_TIM_SET_COUNTER(&CELLAMP_CLK_HTIM, 0xffff);
    HAL_TIM_PWM_Stop(&CELLAMP_CLK_HTIM, CELLAMP_CLK_CHANNEL);
    __HAL_TIM_SET_COMPARE(&CELLAMP_CLK_HTIM, CELLAMP_CLK_CHANNEL, 10);
    PulseCounter = 0;
}

void ReadEEPROM(void)
{
    /*
    EEPROM layout:
    +-------+-------------+-------------+-------------+-------------+
    |       | 00 01 02 03 | 04 05 06 07 | 08 09 0a 0b | 0c 0d 0e 0f |
    +-------+-------------+-------------+-------------+-------------+
    | 0x00: | V mult      | V offset    | A mult      | A offset    |
    | 0x10: | F1 mult     | F1 offset   | F2 mult     | F2 offset   |
    | 0x20: | F3 mult     | F3 offset   | F4 mult     | F4 offset   |
    | 0x30: | F5 mult     | F5 offset   | F6 mult     | F6 offset   |
    +-------+-------------+-------------+-------------+-------------+
    */

    uint8_t readBuffer[EEPROM_PAGE_SIZE * 4];
    HAL_I2C_Mem_Read(&hi2c2, EEPROM_DEVICE_ADDR << 1, 0x00, 1, readBuffer, EEPROM_PAGE_SIZE * 4, 1000);

    memcpy((uint8_t *)(&VoltPerADC), &readBuffer[4 * 0], 4);
    memcpy((uint8_t *)(&VoltOffset), &readBuffer[4 * 1], 4);
    memcpy((uint8_t *)(&AmpPerADC), &readBuffer[4 * 2], 4);
    memcpy((uint8_t *)(&AmpOffset), &readBuffer[4 * 3], 4);
    memcpy((uint8_t *)(&ForcePerADC[0]), &readBuffer[4 * 4], 4);
    memcpy((uint8_t *)(&ForceOffset[0]), &readBuffer[4 * 5], 4);
    memcpy((uint8_t *)(&ForcePerADC[1]), &readBuffer[4 * 6], 4);
    memcpy((uint8_t *)(&ForceOffset[1]), &readBuffer[4 * 7], 4);
    memcpy((uint8_t *)(&ForcePerADC[2]), &readBuffer[4 * 8], 4);
    memcpy((uint8_t *)(&ForceOffset[2]), &readBuffer[4 * 9], 4);
    memcpy((uint8_t *)(&ForcePerADC[3]), &readBuffer[4 * 10], 4);
    memcpy((uint8_t *)(&ForceOffset[3]), &readBuffer[4 * 11], 4);
    memcpy((uint8_t *)(&ForcePerADC[4]), &readBuffer[4 * 12], 4);
    memcpy((uint8_t *)(&ForceOffset[4]), &readBuffer[4 * 13], 4);
    memcpy((uint8_t *)(&ForcePerADC[5]), &readBuffer[4 * 14], 4);
    memcpy((uint8_t *)(&ForceOffset[5]), &readBuffer[4 * 15], 4);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    // periodic interrupt
    if (htim == &PERIODIC_INT_HTIM)
    {
        // start next cycle read
        if (HAL_GPIO_ReadPin(GPIOB, CELL1_Pin | CELL2_Pin | CELL3_Pin | CELL4_Pin | CELL5_Pin | CELL6_Pin) == 0 && PulseCounter == 0)
        {
            // read channel A with 128 gain (HX717 datasheet)
            HAL_TIM_PWM_Start_IT(&CELLAMP_CLK_HTIM, CELLAMP_CLK_CHANNEL);
        }

        // start adc reading
        HAL_ADC_Start_DMA(&hadc2, (uint32_t *)RawADCReadings, 2);

        // extend RawCellReadings sign bits
        for (int i = 0; i < NUM_OF_CELLS; i++)
        {
            if ((RawCellReadings[i] & (1 << 23)) != 0)
            {
                RawCellReadings[i] |= 0xff000000;
            }
            else
            {
                RawCellReadings[i] &= 0x00ffffff;
            }
        }

        // cook the string
        int bufferSize = sprintf((char *)UARTATxBuffer, "%u %.3f %.3f", ESCPulse, Voltage, Current);
        for (int i = 0; i < NUM_OF_CELLS; i++)
        {
            bufferSize += sprintf((char *)UARTATxBuffer + bufferSize, " %.3f", (float)RawCellReadings[i] * ForcePerADC[i] - ForceOffset[i]);
        }
        bufferSize += sprintf((char *)UARTATxBuffer + bufferSize, "\n");

        // write to serial
        HAL_UART_Transmit_IT(&HUARTA, UARTATxBuffer, bufferSize);
    }
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    // cell amp clock falling edge
    if (htim == &CELLAMP_CLK_HTIM)
    {
        PulseCounter++;

        // read all the bits
        if (PulseCounter <= 24)
        {
            for (int i = 0; i < NUM_OF_CELLS; i++)
            {
                RawCellReadings[i] <<= 1;
                if (HAL_GPIO_ReadPin(HX717DataPorts[i], HX717DataPins[i]))
                {
                    RawCellReadings[i] |= 1;
                }
            }
        }
        else if (PulseCounter >= 25)
        {
            __HAL_TIM_SET_COUNTER(&CELLAMP_CLK_HTIM, 0xffff);            // set pin low
            HAL_TIM_PWM_Stop_IT(&CELLAMP_CLK_HTIM, CELLAMP_CLK_CHANNEL); // stop clock pulses
            PulseCounter = 0;                                            // reset counter
        }
    }
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc2)
    {
        // convert raw to volts and amps
        Voltage = (float)RawADCReadings[0] * VoltPerADC - VoltOffset;
        Current = (float)RawADCReadings[1] * AmpPerADC - AmpOffset;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &HUARTA)
    {
        if (HAL_UART_Receive_IT(&HUARTA, &UARTARxByte, 1) == HAL_OK)
        {
            if (UARTARxByte == '\n' || UARTARxByte == '\r' || UARTARxCounter >= UART_RX_BUFFER_SIZE)
            {
                UARTARxBuffer[UARTARxCounter] = 0; // put string terminator
                UARTARxCounter = 0;                // reset counter

                if (UARTARxBuffer[0] == 'P')
                {
                    // save and set esc pulse
                    int receivedPulse = (UARTARxBuffer[1] - '0') * 1000  //
                                        + (UARTARxBuffer[2] - '0') * 100 //
                                        + (UARTARxBuffer[3] - '0') * 10  //
                                        + (UARTARxBuffer[4] - '0');      //

                    if (receivedPulse >= 1000 && receivedPulse <= 2000)
                    {
                        if (receivedPulse == PrevESCPulse)
                        {
                            ESCPulse = receivedPulse;
                            __HAL_TIM_SET_COMPARE(&ESCSIG_HTIM, ESCSIG_CHANNEL, ESCPulse);
                        }
                        PrevESCPulse = receivedPulse;
                    }
                }
                else if (UARTARxBuffer[0] == 'f' || UARTARxBuffer[0] == 'F')
                {
                    uint8_t cellNum = UARTARxBuffer[1] - '1';
                    if (cellNum >= 0 && cellNum <= 5)
                    {
                        float temp;
                        sscanf((char *)(&UARTARxBuffer[2]), "%f", &temp);

                        switch (UARTARxBuffer[0])
                        {
                        case 'f':
                            ForcePerADC[cellNum] *= temp;
                            ForceOffset[cellNum] *= temp;
                            break;
                        case 'F':
                            ForceOffset[cellNum] += temp;
                            break;
                        default:
                            break;
                        }

                        // write to eeprom
                        memcpy(&EEPROMWriteBuffer[0], (uint8_t *)(&ForcePerADC[cellNum]), 4);
                        memcpy(&EEPROMWriteBuffer[4], (uint8_t *)(&ForceOffset[cellNum]), 4);
                        HAL_I2C_Mem_Write(&hi2c2, EEPROM_DEVICE_ADDR << 1, (uint8_t)(0x10 + cellNum * 8), 1, EEPROMWriteBuffer, 8, 200);
                    }
                }
                else
                {
                    float temp;
                    sscanf((char *)(&UARTARxBuffer[1]), "%f", &temp);

                    switch (UARTARxBuffer[0])
                    {
                    case 'v':
                        VoltPerADC *= temp;
                        VoltOffset *= temp;
                        break;
                    case 'V':
                        VoltOffset += temp;
                        break;
                    case 'a':
                        AmpPerADC *= temp;
                        AmpOffset *= temp;
                        break;
                    case 'A':
                        AmpOffset += temp;
                        break;
                    default:
                        break;
                    }

                    // write to eeprom
                    memcpy(&EEPROMWriteBuffer[0], (uint8_t *)(&VoltPerADC), 4);
                    memcpy(&EEPROMWriteBuffer[4], (uint8_t *)(&VoltOffset), 4);
                    memcpy(&EEPROMWriteBuffer[8], (uint8_t *)(&AmpPerADC), 4);
                    memcpy(&EEPROMWriteBuffer[12], (uint8_t *)(&AmpOffset), 4);
                    HAL_I2C_Mem_Write(&hi2c2, EEPROM_DEVICE_ADDR << 1, 0x00, 1, EEPROMWriteBuffer, EEPROM_PAGE_SIZE, 200);
                }
            }
            else
            {
                // fill the buffer
                UARTARxBuffer[UARTARxCounter++] = UARTARxByte;
            }
        }
        else
        {
            HAL_UART_AbortReceive(&HUARTA);
            HAL_UART_Receive_IT(&HUARTA, &UARTARxByte, 1);
        }
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    // if (huart == &HUARTA)
    // {
    // }
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    // if (hi2c == &hi2c2)
    // {
    // }
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    // if (hi2c == &hi2c2)
    // {
    // }
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
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
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
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

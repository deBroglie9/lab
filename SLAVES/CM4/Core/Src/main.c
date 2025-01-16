/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "openamp.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ecat_def.h"
#include "ecatappl.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

#define RPMSG_SERVICE_NAME              "openamp_test"
#define LENGTH_DATA               32
static volatile int message_received;
char *received_data_str;
static unsigned int received_data[8];
static struct rpmsg_endpoint rp_endpoint;
//static char data[100];
static int length_data;
unsigned int data_pointer[8];
float data_angle;
float angle_all[8];
GPIO_PinState State_SCK;
GPIO_PinState State_MISO[2][8];
GPIO_PinState State_MOSI[2][8];
int counter=0;
int counter2=0;
double c1;
double c2;
double c3;
double c4;
double c5;
double c6;
double c7;

static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data, size_t len, uint32_t src, void *priv)
{
//	received_data = *((unsigned int *) data);
	received_data_str = (char *) data;
//	length_data=sizeof(received_data_str);
	memcpy(received_data,received_data_str,LENGTH_DATA);
	message_received=1;
	return 0;
}

unsigned int receive_message(void)
{
	while (message_received == 0)
	{
		OPENAMP_check_for_message();
	}
	message_received = 0;

	return 0;
}
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim2;

/* Definitions for rxTask */
osThreadId_t rxTaskHandle;
const osThreadAttr_t rxTask_attributes = {
  .name = "rxTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for txTask */
osThreadId_t txTaskHandle;
const osThreadAttr_t txTask_attributes = {
  .name = "txTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for TestTask */
osThreadId_t TestTaskHandle;
const osThreadAttr_t TestTask_attributes = {
  .name = "TestTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for txSem */
osSemaphoreId_t txSemHandle;
const osSemaphoreAttr_t txSem_attributes = {
  .name = "txSem"
};
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_SPI3_Init(void);
void rxTaskFun(void *argument);
void txTaskFun(void *argument);
void TestTaskFun(void *argument);

/* USER CODE BEGIN PFP */
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

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /*HW semaphore Clock enable*/
  __HAL_RCC_HSEM_CLK_ENABLE();
  /* Activate HSEM notification for Cortex-M4*/
  HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
  /*
  Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
  perform system initialization (system clock config, external memory configuration.. )
  */
  HAL_PWREx_ClearPendingEvent();
  HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
  /* Clear HSEM flag */
  __HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
// State_MISO[0][0]=GPIO_PIN_SET;
// State_MISO[0][3]=GPIO_PIN_SET;
// State_MISO[0][6]=GPIO_PIN_SET;
// State_MISO[0][7]=GPIO_PIN_SET;
  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */
  HW_Init();
	 int32_t status = 0;

	  /* Initialize the mailbox use notify the other core on new message */
	  MAILBOX_Init();

	  /* Initialize OpenAmp and libmetal libraries */
	  if (MX_OPENAMP_Init(RPMSG_REMOTE, NULL)!= HAL_OK)
	    Error_Handler();

	  /* Create an endpoint for rmpsg communication */
	  status = OPENAMP_create_endpoint(&rp_endpoint, RPMSG_SERVICE_NAME, RPMSG_ADDR_ANY, rpmsg_recv_callback, NULL);
	  if (status < 0)
	  {
	    Error_Handler();
	  }




 //OPENAMP_DeInit();

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of txSem */
  txSemHandle = osSemaphoreNew(1, 0, &txSem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of rxTask */
  rxTaskHandle = osThreadNew(rxTaskFun, NULL, &rxTask_attributes);

  /* creation of txTask */
  txTaskHandle = osThreadNew(txTaskFun, NULL, &txTask_attributes);

  /* creation of TestTask */
  TestTaskHandle = osThreadNew(TestTaskFun, NULL, &TestTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

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
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 0x0;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi3.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi3.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi3.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi3.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi3.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi3.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi3.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi3.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi3.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

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

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1000;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 199;
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
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI3_NSS_GPIO_Port, SPI3_NSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SPI3_NSS_Pin */
  GPIO_InitStruct.Pin = SPI3_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SPI3_NSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI3_IRQ_Pin SYNC_L0_Pin SYNC_L1_Pin */
  GPIO_InitStruct.Pin = SPI3_IRQ_Pin|SYNC_L0_Pin|SYNC_L1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

}
uint8_t WR_CMD (uint8_t tx)
{
	uint8_t rx = 0;
	int r;

	r = HAL_SPI_TransmitReceive(&hspi3, &tx, &rx, 1, 0xffffffff);

	if (r != HAL_OK)
		Error_Handler();
	return rx;

}
void EXTI3_Configuration(){
	GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOA_CLK_ENABLE();

	 GPIO_InitStruct.Pin = SPI3_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SPI3_IRQ_GPIO_Port, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}


/* USER CODE END 4 */

/* USER CODE BEGIN Header_rxTaskFun */
/**
  * @brief  Function implementing the rxTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_rxTaskFun */
void rxTaskFun(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
  	  receive_message();
//  	  data_pointer=received_data;
  	  memcpy(angle_all, received_data, sizeof(received_data));
//  	  sprintf(data,"%u\n\r",received_data);
  	  osDelay(1);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_txTaskFun */
/**
* @brief Function implementing the txTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_txTaskFun */
void txTaskFun(void *argument)
{
  /* USER CODE BEGIN txTaskFun */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END txTaskFun */
}

/* USER CODE BEGIN Header_TestTaskFun */
/**
* @brief Function implementing the TestTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TestTaskFun */
void TestTaskFun(void *argument)
{
  /* USER CODE BEGIN TestTaskFun */
  /* Infinite loop */
	   MainInit();

	    bRunApplication = TRUE;
	    do
	    {
	        MainLoop();

	    } while (bRunApplication == TRUE);

	    HW_Release();



//	for(;;){



//	for(counter2=0;counter2<2;counter2++){
//	  for(counter=0;counter<8;counter++)
//	  {
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, State_MISO[counter2][counter]);
//		osDelay(100);
//		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
//		State_MOSI[counter2][counter]=HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);
//		osDelay(100);
//	  }
//	}
//	osDelay(1);
//	}
  /* USER CODE END TestTaskFun */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  else if(htim->Instance==TIM2){

  	}
  /* USER CODE END Callback 1 */
}

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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

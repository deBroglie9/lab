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
#define RPMSG_CHAN_NAME "openamp_test"

uint32_t message=1234;
static volatile int message_received;
static volatile int service_created;
volatile unsigned int received_data;
static struct rpmsg_endpoint rp_endpoint;
uint32_t binary_code=0;
uint32_t binaryangle=0;
static float angle_fd[8];
static float angle[8];
char ang[32];
static int status_sta;

static int rpmsg_recv_callback(struct rpmsg_endpoint *ept,void *data,size_t len,uint32_t src,void *priv);
unsigned int receive_message(void);
void service_destory_cb(struct rpmsg_endpoint *ept);
void new_service_cb(struct rpmsg_device *rdev,const char *name,uint32_t dest);
uint32_t GraytoNatural(uint32_t gary);
void dev_encoder_read(int ssi,float *pangle);
static void hal_ssi_delay_us(uint16_t us);
uint32_t hal_ssi_readbit(int ssi,uint8_t nbit);
void hai_ssi_clk_clr(int ssi);
void hai_ssi_clk_set(int ssi);
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define HAL_SSI_PIN_CLK     GPIO_PIN_0
#define HAL_SSI_GPIO_CLK    GPIOE
#define HAL_SSI_PIN_DATA    GPIO_PIN_1
#define HAL_SSI_GPIO_DATA   GPIOE

#define HAL_SSI_CLK_SET     HAL_GPIO_WritePin(HAL_SSI_GPIO_CLK,HAL_SSI_PIN_CLK,GPIO_PIN_SET)
#define HAL_SSI_CLK_CLR     HAL_GPIO_WritePin(HAL_SSI_GPIO_CLK,HAL_SSI_PIN_CLK,GPIO_PIN_RESET)
#define HAL_SSI_DATA_IN     HAL_GPIO_ReadPin(HAL_SSI_GPIO_DATA ,HAL_SSI_PIN_DATA)

#define HAL_SSI2_PIN_CLK     GPIO_PIN_3
#define HAL_SSI2_GPIO_CLK    GPIOE
#define HAL_SSI2_PIN_DATA    GPIO_PIN_4
#define HAL_SSI2_GPIO_DATA   GPIOE

#define HAL_SSI2_CLK_SET     HAL_GPIO_WritePin(HAL_SSI2_GPIO_CLK,HAL_SSI2_PIN_CLK,GPIO_PIN_SET)
#define HAL_SSI2_CLK_CLR     HAL_GPIO_WritePin(HAL_SSI2_GPIO_CLK,HAL_SSI2_PIN_CLK,GPIO_PIN_RESET)
#define HAL_SSI2_DATA_IN     HAL_GPIO_ReadPin(HAL_SSI2_GPIO_DATA ,HAL_SSI2_PIN_DATA)

#define HAL_SSI3_PIN_CLK     GPIO_PIN_8
#define HAL_SSI3_GPIO_CLK    GPIOE
#define HAL_SSI3_PIN_DATA    GPIO_PIN_9
#define HAL_SSI3_GPIO_DATA   GPIOE

#define HAL_SSI3_CLK_SET     HAL_GPIO_WritePin(HAL_SSI3_GPIO_CLK,HAL_SSI3_PIN_CLK,GPIO_PIN_SET)
#define HAL_SSI3_CLK_CLR     HAL_GPIO_WritePin(HAL_SSI3_GPIO_CLK,HAL_SSI3_PIN_CLK,GPIO_PIN_RESET)
#define HAL_SSI3_DATA_IN     HAL_GPIO_ReadPin(HAL_SSI3_GPIO_DATA ,HAL_SSI3_PIN_DATA)

#define HAL_SSI4_PIN_CLK     GPIO_PIN_11
#define HAL_SSI4_GPIO_CLK    GPIOE
#define HAL_SSI4_PIN_DATA    GPIO_PIN_12
#define HAL_SSI4_GPIO_DATA   GPIOE

#define HAL_SSI4_CLK_SET     HAL_GPIO_WritePin(HAL_SSI4_GPIO_CLK,HAL_SSI4_PIN_CLK,GPIO_PIN_SET)
#define HAL_SSI4_CLK_CLR     HAL_GPIO_WritePin(HAL_SSI4_GPIO_CLK,HAL_SSI4_PIN_CLK,GPIO_PIN_RESET)
#define HAL_SSI4_DATA_IN     HAL_GPIO_ReadPin(HAL_SSI4_GPIO_DATA ,HAL_SSI4_PIN_DATA)

#define HAL_SSI5_PIN_CLK     GPIO_PIN_13
#define HAL_SSI5_GPIO_CLK    GPIOE
#define HAL_SSI5_PIN_DATA    GPIO_PIN_14
#define HAL_SSI5_GPIO_DATA   GPIOE

#define HAL_SSI5_CLK_SET     HAL_GPIO_WritePin(HAL_SSI5_GPIO_CLK,HAL_SSI5_PIN_CLK,GPIO_PIN_SET)
#define HAL_SSI5_CLK_CLR     HAL_GPIO_WritePin(HAL_SSI5_GPIO_CLK,HAL_SSI5_PIN_CLK,GPIO_PIN_RESET)
#define HAL_SSI5_DATA_IN     HAL_GPIO_ReadPin(HAL_SSI5_GPIO_DATA ,HAL_SSI5_PIN_DATA)

#define HAL_SSI6_PIN_CLK     GPIO_PIN_6
#define HAL_SSI6_GPIO_CLK    GPIOG
#define HAL_SSI6_PIN_DATA    GPIO_PIN_7
#define HAL_SSI6_GPIO_DATA   GPIOG

#define HAL_SSI6_CLK_SET     HAL_GPIO_WritePin(HAL_SSI6_GPIO_CLK,HAL_SSI6_PIN_CLK,GPIO_PIN_SET)
#define HAL_SSI6_CLK_CLR     HAL_GPIO_WritePin(HAL_SSI6_GPIO_CLK,HAL_SSI6_PIN_CLK,GPIO_PIN_RESET)
#define HAL_SSI6_DATA_IN     HAL_GPIO_ReadPin(HAL_SSI6_GPIO_DATA ,HAL_SSI6_PIN_DATA)

#define HAL_SSI7_PIN_CLK     GPIO_PIN_8
#define HAL_SSI7_GPIO_CLK    GPIOG
#define HAL_SSI7_PIN_DATA    GPIO_PIN_9
#define HAL_SSI7_GPIO_DATA   GPIOG

#define HAL_SSI7_CLK_SET     HAL_GPIO_WritePin(HAL_SSI7_GPIO_CLK,HAL_SSI7_PIN_CLK,GPIO_PIN_SET)
#define HAL_SSI7_CLK_CLR     HAL_GPIO_WritePin(HAL_SSI7_GPIO_CLK,HAL_SSI7_PIN_CLK,GPIO_PIN_RESET)
#define HAL_SSI7_DATA_IN     HAL_GPIO_ReadPin(HAL_SSI7_GPIO_DATA ,HAL_SSI7_PIN_DATA)

#define HAL_SSI8_PIN_CLK     GPIO_PIN_10
#define HAL_SSI8_GPIO_CLK    GPIOG
#define HAL_SSI8_PIN_DATA    GPIO_PIN_11
#define HAL_SSI8_GPIO_DATA   GPIOG

#define HAL_SSI8_CLK_SET     HAL_GPIO_WritePin(HAL_SSI8_GPIO_CLK,HAL_SSI8_PIN_CLK,GPIO_PIN_SET)
#define HAL_SSI8_CLK_CLR     HAL_GPIO_WritePin(HAL_SSI8_GPIO_CLK,HAL_SSI8_PIN_CLK,GPIO_PIN_RESET)
#define HAL_SSI8_DATA_IN     HAL_GPIO_ReadPin(HAL_SSI8_GPIO_DATA ,HAL_SSI8_PIN_DATA)


#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

osThreadId rxTaskHandle;
osThreadId txTaskHandle;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
void rxTaskFun(void const * argument);
void txTaskFun(void const * argument);

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
/* USER CODE BEGIN Boot_Mode_Sequence_0 */
  int32_t timeout;
/* USER CODE END Boot_Mode_Sequence_0 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* Enable the CPU Cache */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

/* USER CODE BEGIN Boot_Mode_Sequence_1 */
  /* Wait until CPU2 boots and enters in stop mode or timeout*/
  timeout = 0xFFFF;
  while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) != RESET) && (timeout-- > 0));
  if ( timeout < 0 )
  {
  Error_Handler();
  }
/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
/* USER CODE BEGIN Boot_Mode_Sequence_2 */
/* When system initialization is finished, Cortex-M7 will release Cortex-M4 by means of
HSEM notification */
/*HW semaphore Clock enable*/
__HAL_RCC_HSEM_CLK_ENABLE();
/*Take HSEM */
HAL_HSEM_FastTake(HSEM_ID_0);
/*Release HSEM in order to notify the CPU2(CM4)*/
HAL_HSEM_Release(HSEM_ID_0,0);
/* wait until CPU2 wakes up from stop mode */
timeout = 0xFFFF;
while((__HAL_RCC_GET_FLAG(RCC_FLAG_D2CKRDY) == RESET) && (timeout-- > 0));
if ( timeout < 0 )
{
Error_Handler();
}
/* USER CODE END Boot_Mode_Sequence_2 */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
int32_t status = 0;

	/* Initialize the mailbox use notify the other core on new message */
	MAILBOX_Init();

	/* Initialize the rpmsg endpoint to set default addresses to RPMSG_ADDR_ANY */
	rpmsg_init_ept(&rp_endpoint, RPMSG_CHAN_NAME, RPMSG_ADDR_ANY, RPMSG_ADDR_ANY, NULL, NULL);

	/* Initialize OpenAmp and libmetal libraries */
	if (MX_OPENAMP_Init(RPMSG_MASTER, new_service_cb)!= HAL_OK)
	{
		Error_Handler();
	}

	/*
	* The rpmsg service is initiate by the remote processor, on M7 new_service_cb
	* callback is received on service creation. Wait for the callback
	*/
	OPENAMP_Wait_EndPointready(&rp_endpoint);
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

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
  /* definition and creation of rxTask */
  osThreadDef(rxTask, rxTaskFun, osPriorityNormal, 0, 128);
  rxTaskHandle = osThreadCreate(osThread(rxTask), NULL);

  /* definition and creation of txTask */
  osThreadDef(txTask, txTaskFun, osPriorityNormal, 0, 128);
  txTaskHandle = osThreadCreate(osThread(txTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

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
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, SSI2_CLK_Pin|SSI3_CLK_Pin|SSI4_CLK_Pin|SSI5_CLK_Pin
                          |SSI1_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, SSI6_CLK_Pin|SSI7_CLK_Pin|SSI8_CLK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SSI2_CLK_Pin SSI3_CLK_Pin SSI4_CLK_Pin SSI5_CLK_Pin
                           SSI1_CLK_Pin */
  GPIO_InitStruct.Pin = SSI2_CLK_Pin|SSI3_CLK_Pin|SSI4_CLK_Pin|SSI5_CLK_Pin
                          |SSI1_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SSI2_RX_Pin SSI3_RX_Pin SSI4_RX_Pin SSI5_RX_Pin
                           SSI1_RX_Pin */
  GPIO_InitStruct.Pin = SSI2_RX_Pin|SSI3_RX_Pin|SSI4_RX_Pin|SSI5_RX_Pin
                          |SSI1_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : SSI6_CLK_Pin SSI7_CLK_Pin SSI8_CLK_Pin */
  GPIO_InitStruct.Pin = SSI6_CLK_Pin|SSI7_CLK_Pin|SSI8_CLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : SSI6_RX_Pin SSI7_RX_Pin SSI8_RX_Pin */
  GPIO_InitStruct.Pin = SSI6_RX_Pin|SSI7_RX_Pin|SSI8_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data, size_t len, uint32_t src, void *priv)
{
  received_data = *((unsigned int *) data);
  message_received=1;

  return 0;
}

void service_destroy_cb(struct rpmsg_endpoint *ept)
{
  /* this function is called while remote endpoint as been destroyed, the
   * service is no more available
   */
  service_created = 0;
}

void new_service_cb(struct rpmsg_device *rdev, const char *name, uint32_t dest)
{
  /* create a endpoint for rmpsg communication */
  OPENAMP_create_endpoint(&rp_endpoint, name, dest, rpmsg_recv_callback, service_destroy_cb);
  service_created = 1;
}

uint32_t GraytoNatural(uint32_t gary)
{
    uint32_t natural = gary;
    while (gary != 0)
    {
        gary = gary >> 1;
        natural ^= gary;
    }
    return natural;
}


void dev_encoder_read(int ssi,float *pangle)
{
    binary_code = GraytoNatural(hal_ssi_readbit(ssi,21));
    *pangle = ((float)(binary_code))/ 2097152 * 360;
//   *pangle = ceil(100 * *pangle)/100;
    if((ssi==6)||(ssi==7)){
    	*pangle=*pangle*(-1);
    	*pangle=*pangle+360;
    }
//    *pangle = (float)((binary_code)- 4194304)/ 4194304 * 360;
//	*pangle=*pangle+180;//rj2
//	if(*pangle>180) *pangle=*pangle-360;
	//*pangle=*pangle*(-1);
}
void hai_ssi_clk_clr(int ssi){
    switch(ssi){
	case 0:  HAL_SSI_CLK_CLR;    break;
	case 1:  HAL_SSI2_CLK_CLR;   break;
	case 2:  HAL_SSI3_CLK_CLR;   break;
	case 3:  HAL_SSI4_CLK_CLR;   break;
	case 4:  HAL_SSI5_CLK_CLR;   break;
	case 5:  HAL_SSI6_CLK_CLR;   break;
	case 6:  HAL_SSI7_CLK_CLR;   break;
	case 7:  HAL_SSI8_CLK_CLR;   break;
	default: break;
    }
}
void hai_ssi_clk_set(int ssi){
    switch(ssi){
	case 0:  HAL_SSI_CLK_SET;    break;
	case 1:  HAL_SSI2_CLK_SET;   break;
	case 2:  HAL_SSI3_CLK_SET;   break;
	case 3:  HAL_SSI4_CLK_SET;   break;
	case 4:  HAL_SSI5_CLK_SET;   break;
	case 5:  HAL_SSI6_CLK_SET;   break;
	case 6:  HAL_SSI7_CLK_SET;   break;
	case 7:  HAL_SSI8_CLK_SET;   break;
	default: break;
    }
}
GPIO_PinState hai_ssi_data_in(int ssi){
	GPIO_PinState pin_state=0;
	switch(ssi){
	case 0:  pin_state=HAL_SSI_DATA_IN;    break;
	case 1:  pin_state=HAL_SSI2_DATA_IN;   break;
	case 2:  pin_state=HAL_SSI3_DATA_IN;   break;
	case 3:  pin_state=HAL_SSI4_DATA_IN;   break;
	case 4:  pin_state=HAL_SSI5_DATA_IN;   break;
	case 5:  pin_state=HAL_SSI6_DATA_IN;   break;
	case 6:  pin_state=HAL_SSI7_DATA_IN;   break;
	case 7:  pin_state=HAL_SSI8_DATA_IN;   break;
	default: pin_state= 0;  break;

	return pin_state;
    }
}


static void hal_ssi_delay_us(uint16_t us)
{
	int c = 62*us;
    while (c--);
}

uint32_t hal_ssi_readbit(int ssi,uint8_t nbit)
{
	uint32_t temp = 0; uint8_t i;
    __disable_irq();
    hai_ssi_clk_clr(ssi);
    hal_ssi_delay_us(5);
    for (i = nbit; i > 0; i--)
    {
    	hai_ssi_clk_set(ssi);
    	hal_ssi_delay_us(1);
    	hai_ssi_clk_clr(ssi);
    	temp <<= 1;
        if ((hai_ssi_data_in(ssi)) != 0)
        {
            temp |= 0x01;
        }
        hal_ssi_delay_us(1);

    }
    hai_ssi_clk_set(ssi);
    __enable_irq();
    return temp;
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_rxTaskFun */
/**
  * @brief  Function implementing the rxTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_rxTaskFun */
void rxTaskFun(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {		for(int i = 0;i<8;i++)
  	  {
			dev_encoder_read(i,&angle[i]);
			angle_fd[i]=angle[i];
			osDelay(1);
  	  }

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
void txTaskFun(void const * argument)
{
  /* USER CODE BEGIN txTaskFun */
	int status;
  /* Infinite loop */
  for(;;)
  {


	  memcpy(ang, &angle_fd, sizeof(ang));
//		message=(uint32_t)angle_fd;
		status = OPENAMP_send(&rp_endpoint, &ang, sizeof(ang));
		status_sta=status;
//	  message++;
	  osDelay(10);
	  		if (status < 0)
	  		{
	  			Error_Handler();
	  		}

  }
  /* USER CODE END txTaskFun */
}

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x38000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

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

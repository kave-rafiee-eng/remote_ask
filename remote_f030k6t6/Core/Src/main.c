
#include "main.h"

TIM_HandleTypeDef htim14;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM14_Init(void);

#define 	Min_Pulse_Len	200 	/* In us */
#define 	Max_Pulse_Len	15000	/* In us*/
	
#define IS_Valid_Pulse_Len(T1,T2)		((T1 > Min_Pulse_Len) && (T2 < Max_Pulse_Len))
#define IS_Sync_Start_Pulse(T1,T2)		(T2 > (T1*29))
#define Bit_IS_Zero(T1,T2)				(T2 > (T1*2))

uint8_t		Remode_Data[24];
uint8_t		Revice_Flag = 0;

	int i=0;
	uint16_t timer = 0;
	

void Start_Timer(void)
{
	HAL_TIM_Base_Stop(&htim14);
	TIM14->CNT=0;
	HAL_TIM_Base_Start(&htim14);
}


void Stop_Timer(void)
{
	HAL_TIM_Base_Stop(&htim14);
}


uint16_t Read_timer(void)
{
   return TIM14->CNT;
}

uint16_t Stop_Read_timer(void)
{
		HAL_TIM_Base_Stop(&htim14);
     return TIM14->CNT*2;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_3) 
    {
				static uint16_t	Time_Falling=0;
				static uint16_t	Time_Rising=0;
				static uint16_t	Start_Sync = 0;
				static uint8_t	Bit_Index = 0;

				if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3) == 1 ) // Rising Edge
				{

						Time_Falling =Stop_Read_timer();

						if(IS_Valid_Pulse_Len(Time_Rising,Time_Falling)) //If Valid Pulse Len
						{
							if(IS_Sync_Start_Pulse(Time_Rising,Time_Falling))	// Start
							{
								Start_Sync = 1;
							}
							else
							{
								if(Start_Sync==1)	// Start Sended
								{
									if(Bit_Index < 24)
									{
										Remode_Data[Bit_Index] = !Bit_IS_Zero(Time_Rising,Time_Falling);
										Bit_Index++;
									}
									else
									{	// All Bit Recive
										Bit_Index = 0;
										Start_Sync = 0;
										Revice_Flag = 1;
									}
								}	// End of Start Sync Send
							}
						}
						else	// Not Valid Pulse Len
						{
							Start_Sync = 0;
							Bit_Index = 0;
						}
						Start_Timer();
				}
				else	//Falling Edge
				{
					//MCUCR=0x03; // Make As Rising Edge
					Time_Rising = Stop_Read_timer() ;
					Start_Timer();
				}
    }
}

uint8_t	IS_Recive_Valid_Remote(void)
{
	return (Revice_Flag==1);
}

void Get_Remote_Code(uint8_t *Code)
{
	Code[0] = Code[1]= Code[2] = 0;

	for(uint8_t i=0;i<24;i++)
	{
		Code[i/8] |= Remode_Data[i]<<(7-(i%8));
	}

	Revice_Flag = 0;
}

uint8_t Code[4];

int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_TIM14_Init();


	/*HAL_TIM_Base_Stop(&htim14);
	TIM14->CNT=0;
	HAL_TIM_Base_Start(&htim14);
	HAL_Delay(100);
	HAL_TIM_Base_Stop(&htim14);
	timer = TIM14->CNT;*/
	
	
	/*Start_Timer();
	HAL_Delay(10);
	timer = Stop_Read_timer();*/
	
  while (1)
  {

		if(IS_Recive_Valid_Remote()){
		
			Get_Remote_Code(Code);
			/*for(uint8_t i=0;i<24;i++)
						printf("%i",Remode_Data[i]);
			printf("---%X-%X-%X\r",Code[0],Code[1],Code[2]);*/
			i++;
		}
		HAL_Delay(10);
		
  }

}



void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }
  LL_SetSystemCoreClock(8000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 16;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 65535;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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

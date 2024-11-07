#include "main.h"
#include "ask.h"


extern TIM_HandleTypeDef htim14;

uint8_t		Remode_Data[24];
uint8_t		Revice_Flag = 0;


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
    if(GPIO_Pin == GPIO_PIN_1) 
    {
				static uint16_t	Time_Falling=0;
				static uint16_t	Time_Rising=0;
				static uint16_t	Start_Sync = 0;
				static uint8_t	Bit_Index = 0;

				if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1) == 1 ) // Rising Edge
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
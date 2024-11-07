
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_gpio.h"


#include "../LIB/FLASH/Internal_Flash.H"
#include "../LIB/ASK/ask.H"
#include "../LIB/SOFT_WARE_TIMER/CPU_TIMER.H"
#include "../LIB/remote.h"

#define led(x) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,x);
#define opto(x) HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,x);
#define buzzer(x) HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,x);
#define BTN 1 - HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4)


#define NUM_REMOTE 10

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

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/**
  ******************************************************************************
  * @file           : middlecallback.cpp
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-5-28
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <usart.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "middlecallback.h"
#include "dr16.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UARTEx_RxEventCallback(const UART_HandleTypeDef *huart, const uint16_t Size)
{
  if(huart == &huart5){

    userUart5RxHandler(huart,Size);

  }
}
/* USER CODE END 0 */

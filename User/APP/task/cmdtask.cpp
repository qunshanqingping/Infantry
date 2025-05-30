/**
  ******************************************************************************
  * @file           : cmdtask.cpp
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-5-28
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <cmsis_os.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmdtask.h"
#include "dr16.h"
#include "ws2812.h"
#include "BMI088driver.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
WS2812  ws2812;
float gyro[3], accel[3], temp;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void startCmdTask(void const * argument)
{
  /* USER CODE BEGIN LedTask */
  ws2812.init();
  dr16Init();
  BMI088_init();
  /* Infinite loop */
  // ReSharper disable CppDFAEndlessLoop
  for(;;)
  {
    BMI088_read(gyro, accel, &temp);
    osDelay(10);
  }
  /* USER CODE END LedTask */
}
/* USER CODE END 0 */

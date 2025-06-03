/**
  ******************************************************************************
  * @file           : test.c
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-6-3
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <cmsis_os.h>
/* Private includes -----------------------------------------------------------*/
#include "test.h"
#include "bsp_log.h"

/* Private variables ---------------------------------------------------------*/


/* Private functions prototypes ----------------------------------------------*/
void startCmdTask(void const * argument)
{
    /* USER CODE BEGIN startCmdTask */
    BspLogInit();
    /* Infinite loop */
    for(;;)
    {
        LOGINFO("Hello World!");
        osDelay(100);
    }
    /* USER CODE END startCmdTask */
}
/* Exported functions prototypes ---------------------------------------------*/
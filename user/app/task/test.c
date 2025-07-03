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
#include "module_ws2812.h"
/* Private variables ---------------------------------------------------------*/


/* Private functions prototypes ----------------------------------------------*/
void startCmdTask(void const * argument)
{
    /* USER CODE BEGIN startCmdTask */

    /* Infinite loop */
    for(;;)
    {
        WS2812_Clear();
        LOGDEBUG("Hello World!");
        osDelay(100);
    }
    /* USER CODE END startCmdTask */
}
/* Exported functions prototypes ---------------------------------------------*/
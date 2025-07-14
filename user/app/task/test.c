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
#include "bsp_log.h"
#include "test.h"

#include "spi.h"
/* Private variables ---------------------------------------------------------*/


/* Private functions prototypes ----------------------------------------------*/
void startCmdTask(void const * argument)
{
    /* USER CODE BEGIN startCmdTask */
    /* Infinite loop */
    for(;;)
    {
        LOGDEBUG("Hello World!");

        osDelay(100);
    }
    /* USER CODE END startCmdTask */
}
/* Exported functions prototypes ---------------------------------------------*/
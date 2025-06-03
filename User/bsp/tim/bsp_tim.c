/**
  ******************************************************************************
  * @file           : bsp_tim.c
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-6-3
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <cmsis_os.h>
#include <stdint.h>
/* Private includes -----------------------------------------------------------*/
#include "bsp_tim.h"

/* Private variables ---------------------------------------------------------*/


/* Private functions prototypes ----------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
/**
 *
 * @return 当前系统时间戳ms
 */
uint32_t getCurrentTime(void)
{
    TickType_t ticks = xTaskGetTickCount();
    uint32_t milliSeconds = ticks * portTICK_PERIOD_MS;
    return milliSeconds;
}
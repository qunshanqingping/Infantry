
/**
  ******************************************************************************
  * @file           : bsp_log.c
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

/* Private variables ---------------------------------------------------------*/


/* Private functions prototypes ----------------------------------------------*/
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

/* Exported functions prototypes ---------------------------------------------*/
/**
 * @brief 日志系统初始化，这里为了统一bsp层，重新封装
 */
void BspLogInit()
{
    SEGGER_RTT_Init();
}
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
#include "ws2812.h"
#include "spi.h"
#include "bsp_dwt.h"
/* Private variables ---------------------------------------------------------*/
Ws2812Config ws2812_config = {
    .spi_config = {
        .hspi_handle = &hspi6,
        .master_slave_mode = MASTER_MODE,
        .rx_tx_mode = TX_MODE,
        .work_mode = BLOCK_MODE,
        .cs_port = NULL,
        .cs_pin = 0,
        .callback = NULL,
        .handle = NULL
    },
    .color = GREEN
};
Ws2812Instance *ws2812_instance = NULL;
float gyro[3], accel[3], temp;
/* Private functions prototypes ----------------------------------------------*/
void startCmdTask(void const * argument)
{
    /* USER CODE BEGIN startCmdTask */
    ws2812_instance=mod_ws2812_register(&ws2812_config);
    mod_ws2812_publish(ws2812_instance, GREEN);
    /* Infinite loop */
    for(;;)
    {
        dwt_get_time_line_s();
        LOGDEBUG("Hello World!");

        osDelay(100);
    }
    /* USER CODE END startCmdTask */
}
/* Exported functions prototypes ---------------------------------------------*/
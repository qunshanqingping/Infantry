/******************************************************************************

                  版权所有 (C), 2025-2025, Adonis Jin

 ******************************************************************************
  文 件 名   : module_ws2812.h
  版 本 号   : 初稿
  作    者   :Adonis Jin
  生成日期   : 25-7-2
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 25-7-2
    作    者   : Adonis Jin
    修改内容   : 创建文件

******************************************************************************/

#ifndef WS2812_H
#define WS2812_H
#include <stdint.h>
#include "bsp_spi.h"
#include "bsp_gpio.h"
typedef enum
{
    GREEN = 0,
    BLUE = 1,
    YELLOW = 2,
    RED = 3,
} WS2812_color_e;

typedef struct
{
    WS2812_color_e color;
    SPIInstance *spi_tx;
    GPIOInstance *gpio_tx;
} WS2812Instance;

typedef struct
{
    WS2812_color_e color_config;
    SPI_Init_Config_s *spi_config_tx;
    GPIO_Init_Config_s *gpio_config_tx;
} WS2812_Init_Config_s;
WS2812Instance *WS2812Register(WS2812_Init_Config_s *config);
void WS2812_Publish(WS2812Instance *ws2812_instance,uint8_t update_color);
#endif //WS2812_H

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

#ifndef MODULE_WS2812_H
#define MODULE_WS2812_H
#include <stdint.h>
#include "bsp_spi.h"
#define WS2812_SPI_UNIT     hspi6
typedef enum
{
    GREEN = 1,
    BLUE = 2,
    YELLOW = 3,
    RED = 4,
} color_e;

typedef struct ws2812_ins_temp
{
    color_e color;
    SPIInstance *spi_ins;
} WS2812Instance;

void WS2812_Init(void);
void WS2812_SetColor(uint8_t r, uint8_t g, uint8_t b);
void WS2812_Error(void);
void WS2812_Clear(void);
#endif //MODULE_WS2812_H

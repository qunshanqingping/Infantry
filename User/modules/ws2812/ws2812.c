/******************************************************************************

                  版权所有 (C), 2025-2025，Adonis Jin

 ******************************************************************************
  文 件 名   : module_ws2812.c
  版 本 号   : 初稿
  作    者   : Adonis Jin
  生成日期   : 25-7-2
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
  1.日    期   : 25-7-2
    作    者   : Adonis Jin
    修改 内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
#include "ws2812.h"
#include <memory.h>
#include <stdint.h>
#include "spi.h"

#include <stdlib.h>

#include "basic_math.h"
#include "sys_log.h"
/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define WS2812_LowLevel    0xC0     // 0码
#define WS2812_HighLevel   0xF0     // 1码
static uint8_t ColorTxBuf[4][24] = {
    {/*GREEN*/
        0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60, //  G: 0x11
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, //  R: 0x00
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60  //  B: 0x00
        },

     {/*BLUE*/
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // G: 0x00
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // R: 0x00
        0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60  // B: 0x11
        },
    {/*YELLOW*/
         0x60, 0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, // G: 0x11
         0x60, 0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, // R: 0x11
         0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60  // B: 0x00
        },
    {/*RED*/
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // G: 0x00
        0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60, // R: 0x11
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60  // B: 0x00
        },
};
static uint8_t res1 = 0;
static uint8_t res2[100]={0};

Ws2812Instance * ModWs2812Register(Ws2812Config *config)
{
    Ws2812Instance *ws2812_instance = (Ws2812Instance *)user_malloc(sizeof(Ws2812Instance));
    memset(ws2812_instance,0,sizeof(Ws2812Instance));
    if (ws2812_instance == NULL)
    {
        user_free(ws2812_instance);
        LOGERROR("WS2812 instance memory allocation failed! Please check your memory.");
        while (1); // 内存分配失败,请检查内存是否足够
    }
    ws2812_instance->color = config->color;
    ws2812_instance->spi_instance = BspSpiRegister(&config->spi_config);


    return ws2812_instance;
}
// static WS2812Instance ws2812_instance =
// {
//     .color = GREEN, // 设置默认颜色为绿色
//     .spi_handle = &hspi6,
// };
//
// /*----------------------------------------------*
//  * 外部函数原型说明                             *
//  *----------------------------------------------*/
//
// void WS2812_Publish(uint8_t update_color)
// {
//     ws2812_instance.color = update_color;
//     HAL_SPI_Transmit(ws2812_instance.spi_handle, &res1,0,1000);
//     while (ws2812_instance.spi_handle->State != HAL_SPI_STATE_READY){}
//     HAL_SPI_Transmit(ws2812_instance.spi_handle, ColorTxBuf[ws2812_instance.color],24,1000);
//     HAL_SPI_Transmit(ws2812_instance.spi_handle, &res2[0],100,1000);
// }
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
#include "bsp_spi.h"

#include <stdlib.h>
/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/
#define WS2812_LowLevel    0xC0     // 0码
#define WS2812_HighLevel   0xF0     // 1码
/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/
static uint8_t GreenTxBuf[24]={
    0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60, //  G: 0x00
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, //  R: 0x11
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60  //  B: 0x00
};

static uint8_t BlueTxBuf[24] = {
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // G: 0x00
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // R: 0x00
    0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60  // B: 0x11
};
static uint8_t YellowTxBuf[24] = {
    0x7F, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7F, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00
};

static uint8_t RedTxBuf[24] = {
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // G: 0x00
    0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60, // R: 0x11
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60  // B: 0x00
};

static uint8_t ColorTxBuf[4][24] = {
    {
        0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60, //  G: 0x00
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, //  R: 0x11
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60  //  B: 0x00
        },

     {
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // G: 0x00
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // R: 0x00
        0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60  // B: 0x11
        },
    {
        0x7F, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x7F, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00
        },

    {
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // G: 0x00
        0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60, // R: 0x11
        0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60  // B: 0x00
        },
};
static uint8_t res1 = 0;
static uint8_t res2[100]={0};

WS2812Instance *WS2812Register(WS2812_Init_Config_s *config)
{
    // 申请内存
    WS2812Instance *ws2812_instance = (WS2812Instance *)malloc(sizeof(WS2812Instance));
    config->gpio_config_tx->id =
        config->spi_config_tx->id = ws2812_instance;
    ws2812_instance->color = config->color_config;
    SPIRegister(config->spi_config_tx);
    GPIORegister(config->gpio_config_tx);
    return ws2812_instance;
}

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

void WS2812_Publish(WS2812Instance *ws2812_instance,uint8_t update_color)
{
    ws2812_instance->color = update_color;
    SPITransmit(ws2812_instance->spi_tx, &res1,0);
    while (ws2812_instance->spi_tx->spi_handle->State != HAL_SPI_STATE_READY){}
    SPITransmit(ws2812_instance->spi_tx, ColorTxBuf[ws2812_instance->color],24);
    SPITransmit(ws2812_instance->spi_tx, &res2[0],100);
}
// void WS2812_Error()
// {
//     SPITransmit();
//     HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
//     while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
//     HAL_SPI_Transmit(&WS2812_SPI_UNIT, RedTxBuf, 24, 0xFFFF);
//     for (int i = 0; i < 100; i++)
//     {
//         HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
//     }
// }
// void WS2812_Clear()
// {
//     HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
//     while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
//     for (int i = 0; i < 100; i++)
//     {
//         HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
//     }
// }
//
// void WS2812_SetColor(uint8_t r, uint8_t g, uint8_t b)
// {
//     uint8_t TxBuf[24];
//     color_decode( r,  g,  b, TxBuf);
//     HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
//     while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
//     HAL_SPI_Transmit(&WS2812_SPI_UNIT, TxBuf, 24, 0xFFFF);
//     for (int i = 0; i < 100; i++)
//     {
//         HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
//     }
// }
//
//
//

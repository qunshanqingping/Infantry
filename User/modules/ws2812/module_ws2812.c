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
#include "module_ws2812.h"
#include <stdint.h>
#include "bsp_spi.h"
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
static uint8_t RedTxBuf[24] = {
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // G: 0x00
    0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60, // R: 0x11
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60  // B: 0x00
};
static uint8_t BlueTxBuf[24] = {
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // G: 0x00
    0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, // R: 0x00
    0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60  // B: 0x11
};

static uint8_t res = 0;

static SPI_Init_Config_s WS2812_SPI_Config;
static SPIInstance* WS2812_SPI_Ins;
/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

static void color_decode( uint8_t r,  uint8_t g,  uint8_t b, uint8_t *TxBuf)
{

    for (int i = 0; i < 8; i++) {
        const uint8_t mask = 0x80 >> i; // 从高位到低位依次检测

        TxBuf[7 - i]  = ((g & mask) ? WS2812_HighLevel : WS2812_LowLevel) >> 1;
        TxBuf[15 - i] = ((r & mask) ? WS2812_HighLevel : WS2812_LowLevel) >> 1;
        TxBuf[23 - i] = ((b & mask) ? WS2812_HighLevel : WS2812_LowLevel) >> 1;
    }
}


/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

void WS2812_Init()
{
   WS2812_SPI_Ins=SPIRegister(&WS2812_SPI_Config);
    // HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
    // while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
    // HAL_SPI_Transmit(&WS2812_SPI_UNIT, GreenTxBuf, 24, 0xFFFF);
    // for (int i = 0; i < 100; i++)
    // {
    //     HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
    // }
}
void WS2812_Error()
{
    SPITransmit(&[0]);
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
    while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, RedTxBuf, 24, 0xFFFF);
    for (int i = 0; i < 100; i++)
    {
        HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
    }
}
void WS2812_Clear()
{
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
    while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
    for (int i = 0; i < 100; i++)
    {
        HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
    }
}

void WS2812_SetColor(uint8_t r, uint8_t g, uint8_t b)
{
    uint8_t TxBuf[24];
    color_decode( r,  g,  b, TxBuf);
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
    while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, TxBuf, 24, 0xFFFF);
    for (int i = 0; i < 100; i++)
    {
        HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
    }
}




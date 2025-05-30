/**
  ******************************************************************************
  * @file           : ws2812.cpp
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-5-28
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ws2812.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
static uint8_t GreenTxBuf[24]={
  0x60, 0x60, 0x78, 0x60, 0x60, 0x60, 0x78, 0x60, //  G: 0x11
  0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, //  R: 0x00
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
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void WS2812::init()
{
  HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
  while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
  HAL_SPI_Transmit(&WS2812_SPI_UNIT, GreenTxBuf, 24, 0xFFFF);
  for (int i = 0; i < 100; i++)
  {
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
  }
}
void WS2812::error()
{
  HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
  while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
  HAL_SPI_Transmit(&WS2812_SPI_UNIT, RedTxBuf, 24, 0xFFFF);
  for (int i = 0; i < 100; i++)
  {
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
  }
}


void WS2812::setColor(uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t TxBuf[24];
  for (int i = 0; i < 8; i++)
  {
    TxBuf[7-i]  = (((g>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
    TxBuf[15-i] = (((r>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
    TxBuf[23-i] = (((b>>i)&0x01) ? WS2812_HighLevel : WS2812_LowLevel)>>1;
  }
  HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 0, 0xFFFF);
  while (WS2812_SPI_UNIT.State != HAL_SPI_STATE_READY){}
  HAL_SPI_Transmit(&WS2812_SPI_UNIT, TxBuf, 24, 0xFFFF);
  for (int i = 0; i < 100; i++)
  {
    HAL_SPI_Transmit(&WS2812_SPI_UNIT, &res, 1, 0xFFFF);
  }
}
/* USER CODE END 0 */

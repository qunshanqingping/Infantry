/**
  ******************************************************************************
  * @file           : dr16.cpp
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-5-28
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_usart.h"
#include <usart.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "dr16.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
DmaDoubleRX dr16;
RC dbusRC;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
constexpr uint32_t bufLength = 18;
constexpr uint32_t dataLength = 36;
constexpr uint16_t rcChValueOffSet = 1024;
/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
uint8_t dbusMultiRxBuf[2][bufLength];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static void dbusToRC(const uint8_t* dbusBuf, RC* rc)
{
    rc->ch[0] = static_cast<uint16_t>((dbusBuf[0] | (dbusBuf[1] << 8)) & 0x07FFU);
    rc->ch[1] = static_cast<uint16_t>(((dbusBuf[1] >> 3) | (dbusBuf[2] << 5)) & 0x07FFU);
    rc->ch[2] = static_cast<uint16_t>(((dbusBuf[2] >> 6) | (dbusBuf[3] << 2) | (dbusBuf[4] << 10)) & 0x07FFU);
    rc->ch[3] = static_cast<uint16_t>(((dbusBuf[4] >> 1) | (dbusBuf[5] << 7)) & 0x07FFU);
    rc->ch[4] = static_cast<uint16_t>(dbusBuf[16] | (dbusBuf[17] << 8)); // Wheel

    rc->s[0] = static_cast<uint8_t>((dbusBuf[5] >> 4) & 0x03U); // 左开关
    rc->s[1] = static_cast<uint8_t>(((dbusBuf[5] >> 4) & 0x0CU) >> 2); // 右开关

    for (short& i : rc->ch)
    {
        i -= rcChValueOffSet;
    }
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void dr16Init()
{
    DmaDoubleRX::initUartRxDmaDoubleBuffer(&huart5, reinterpret_cast<uint32_t*>(dbusMultiRxBuf[0]),
                                           reinterpret_cast<uint32_t*>(dbusMultiRxBuf[1]), dataLength);
}

void userUart5RxHandler(const UART_HandleTypeDef* huart, const uint16_t Size)
{
    if ((static_cast<DMA_Stream_TypeDef*>(huart->hdmarx->Instance)->CR & DMA_SxCR_CT) == RESET)
    {
        __HAL_DMA_DISABLE(huart->hdmarx);

        static_cast<DMA_Stream_TypeDef*>(huart->hdmarx->Instance)->CR |= DMA_SxCR_CT;

        __HAL_DMA_SET_COUNTER(huart->hdmarx, dataLength);

        if (Size == bufLength)
        {
            /*CallBack BEGIN*/
            dbusToRC(dbusMultiRxBuf[0], &dbusRC);
            /*CallBack END*/
        }
    }
    else
    {
        __HAL_DMA_DISABLE(huart->hdmarx);

        static_cast<DMA_Stream_TypeDef*>(huart->hdmarx->Instance)->CR &= ~(DMA_SxCR_CT);

        __HAL_DMA_SET_COUNTER(huart->hdmarx, dataLength);

        if (Size == bufLength)
        {
            /*CallBack BEGIN*/
            dbusToRC(dbusMultiRxBuf[1], &dbusRC);
            /*CallBack END*/
        }
    }
    __HAL_DMA_ENABLE(huart->hdmarx);
}

/* USER CODE END 0 */

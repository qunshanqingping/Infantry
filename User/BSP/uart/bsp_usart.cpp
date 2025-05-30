/**
  ******************************************************************************
  * @file           : bsp_usart.cpp
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-5-28
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <usart.h>
#include <cstdint>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_usart.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void DmaDoubleRX::initUartRxDmaDoubleBuffer(UART_HandleTypeDef *uartHandle, const uint32_t *dstAddress, const uint32_t *secondMemAddress, const uint32_t dataLength)
{
  uartHandle->ReceptionType = HAL_UART_RECEPTION_TOIDLE;

  uartHandle->RxEventType = HAL_UART_RXEVENT_IDLE;

  uartHandle->RxXferSize    = dataLength;

  SET_BIT(uartHandle->Instance->CR3,USART_CR3_DMAR);

  __HAL_UART_ENABLE_IT(uartHandle, UART_IT_IDLE);

  do{
    __HAL_DMA_DISABLE(uartHandle->hdmarx);
  }while(static_cast<DMA_Stream_TypeDef*>(uartHandle->hdmarx->Instance)->CR & DMA_SxCR_EN);

  static_cast<DMA_Stream_TypeDef*>(uartHandle->hdmarx->Instance)->PAR = reinterpret_cast<uint32_t>(&uartHandle->Instance->RDR);

  static_cast<DMA_Stream_TypeDef*>(uartHandle->hdmarx->Instance)->M0AR = reinterpret_cast<uint32_t>(dstAddress);

  static_cast<DMA_Stream_TypeDef*>(uartHandle->hdmarx->Instance)->M1AR =reinterpret_cast<uint32_t>(secondMemAddress);

  static_cast<DMA_Stream_TypeDef*>(uartHandle->hdmarx->Instance)->NDTR = dataLength;

  SET_BIT(static_cast<DMA_Stream_TypeDef*>(uartHandle->hdmarx->Instance)->CR, DMA_SxCR_DBM);

  __HAL_DMA_ENABLE(uartHandle->hdmarx);
}
// /* USER CODE END 0 */

/**
  ******************************************************************************
  * @file           : bsp_usart.h
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-5-28
  ******************************************************************************
  */

#ifndef BSP_USART_H
#define BSP_USART_H

#ifndef  __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <usart.h>
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

/* USER CODE BEGIN Class */
class DmaDoubleRX
{
public:
  static void initUartRxDmaDoubleBuffer(UART_HandleTypeDef *uartHandle, const uint32_t *dstAddress, const uint32_t *secondMemAddress, const uint32_t dataLength);
};
/* USER CODE END Class */
#ifndef  __cplusplus
}
#endif // __cplusplus

#endif //BSP_USART_H
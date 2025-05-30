/**
  ******************************************************************************
  * @file           : dr16.h
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-5-28
  ******************************************************************************
  */

#ifndef DR16_H
#define DR16_H

#ifndef  __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <cstdint>
#include <usart.h>
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
    void dr16Init();
    void userUart5RxHandler(const UART_HandleTypeDef *huart,  uint16_t Size);
/* USER CODE END Prototypes */

/* USER CODE BEGIN Class */
class RC
{
public:
    int16_t ch[5];
    uint8_t s[2];
};
/* USER CODE END Class */
#ifndef  __cplusplus
}
#endif // __cplusplus

#endif //DR16_H
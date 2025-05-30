/**
  ******************************************************************************
  * @file           : ws2812.h
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-5-28
  ******************************************************************************
  */

#ifndef WS2812_H
#define WS2812_H

#ifndef  __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <spi.h>
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define WS2812_SPI_UNIT    hspi6
#define WS2812_LowLevel    0xC0     // 低电平
#define WS2812_HighLevel   0xF0     // 高电平
#define GREEN 0x110000              // 绿色
#define RED   0x001100              //  红色
#define BLUE  0x000011              //  蓝色
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

/* USER CODE BEGIN Class */
  class WS2812
  {
    public:
    void init();
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void error();
  };
/* USER CODE END Class */
#ifndef  __cplusplus
}


#endif // __cplusplus

#endif //WS2812_H

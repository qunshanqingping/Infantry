/**
  ******************************************************************************
  * @file           : bsp_spi.h
  * @author         : Adonis_Jin
  * @brief          : None
  * @version        : 1.0
  * @date           : 25-6-2
  ******************************************************************************
  */

#ifndef BSP_SPI_H
#define BSP_SPI_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <spi.h>
/* Private includes -----------------------------------------------------------*/


/* Private types -------------------------------------------------------------*/
/* spi传输模式枚举 */
typedef enum
{
  SpiBlockMode = 0, // 默认使用阻塞模式
  SpiItMode,
  SpiDmaMode,
} SpiTxRxModeE;

/* SPI实例结构体定义 */
typedef struct SpiInsTemp
{
  SPI_HandleTypeDef *SpiHandle;                              // SPI外设handle
  GPIO_TypeDef *GPIOx;           // 片选信号对应的GPIO,如GPIOA,GPIOB等等
  uint16_t CsPin;               // 片选信号对应的引脚号,GPIO_PIN_1,GPIO_PIN_2等等

  SpiTxRxModeE SpiWorkMode; // 传输工作模式
  uint8_t RxSize;               // 本次接收的数据长度
  uint8_t *RxBuf;            // 本次接收的数据缓冲区
  uint8_t CsState;              // 片选信号状态,用于中断模式下的片选控制
  uint8_t * CsPinState;        // 片选信号状态,用于中断模式下的片选控制
  void (*callback)(struct SpiInsTemp *); // 接收回调函数
  void *Id;                                // 模块指针
} SpiInstance;
/* Private defines -----------------------------------------------------------*/
/* 根据开发板引出的spi引脚以及CubeMX中的初始化配置设定 */
#define SpiDeviceCnt 3       // 达妙开发板引出三路spi,分别连接BMI088/WS2812/作为扩展IO在16pin排母引出
#define MxSpiBusSlaveCnt 4 // 单个spi总线上挂载的从机数目

/* Private macro -------------------------------------------------------------*/


/* Private functions prototypes ----------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/


#endif /* BSP_SPI_H */
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


/* Private defines -----------------------------------------------------------*/
/* 根据开发板引出的spi引脚以及CubeMX中的初始化配置设定 */
#define SpiDeviceCnt 3       // 达妙开发板引出三路spi,分别连接BMI088/WS2812/作为扩展IO在16pin排母引出
#define MxSpiBusSlaveCnt 4 // 单个spi总线上挂载的从机数目

/* Private types -------------------------------------------------------------*/
/* spi传输模式枚举 */
typedef enum
{
  SpiBlockMode = 0, // 默认使用阻塞模式
  SpiItMode,//中断模式
  SpiDmaMode,//DMA模式
} SPI_TxRx_MODE_e;

/* SPI实例结构体定义 */
typedef struct SPI_Ins_Temp
{
  SPI_HandleTypeDef *SpiHandle;                              // SPI外设handle
  GPIO_TypeDef *GPIOx;           // 片选信号对应的GPIO,如GPIOA,GPIOB等等
  uint16_t CsPin;               // 片选信号对应的引脚号,GPIO_PIN_1,GPIO_PIN_2等等

  SPI_TxRx_MODE_e SpiWorkMode; // 传输工作模式
  uint8_t RxSize;               // 本次接收的数据长度
  uint8_t *RxBuf;            // 本次接收的数据缓冲区
  uint8_t CsState;              // 片选信号状态,用于中断模式下的片选控制
  uint8_t * CsPinState;        // 片选信号引脚状态,用于中断模式下的片选控制
  void (*callback)(struct SPI_Ins_Temp *); // 接收回调函数
  void *Id;                                // 模块指针
} SPIInstance;

/* 接收回调函数定义,包含SPI的module按照此格式构建回调函数 */
typedef void (*spi_rx_callback)(SPIInstance *);

/* SPI初始化配置,其实基本和SPIInstance一模一样,为了代码风格统一因此再次定义 */
typedef struct
{
    SPI_HandleTypeDef *spi_handle; // SPI外设handle
    GPIO_TypeDef *GPIOx;           // 片选信号对应的GPIO,如GPIOA,GPIOB等等
    uint16_t cs_pin;               // 片选信号对应的引脚号,GPIO_PIN_1,GPIO_PIN_2等等

    SPI_TxRx_MODE_e spi_work_mode; // 传输工作模式

    spi_rx_callback callback; // 接收回调函数
    void *id;                 // 模块指针
} SPI_Init_Config_s;

/* Private macro -------------------------------------------------------------*/


/* Private functions prototypes ----------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/


#endif /* BSP_SPI_H */
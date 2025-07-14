/**
******************************************************************************
 * @file           : bsp_spi.h
 * @author         : Adonis_Jin
 * @brief          : None
 * @version        : 1.0
 * @date           : 25-7-9
 ******************************************************************************
 */
#ifndef BSP_SPI_H
#define BSP_SPI_H

#include "spi.h"

#define BSP_SPI_DEVICE_CNT 5 // BSP SPI设备数量,和SPI_DEVICE_CNT宏保持一致
#define MX_SPI_BUS_SLAVE_CNT 4 // 单个spi总线上挂载的从机数目
/*spi主从工作模式*/
typedef enum
{
    MASTER_MODE,
    SLAVE_MODE,
}SpiMasterSlaveMode;

/*spi接收发送模式*/
typedef enum
{
    RX_TX_MODE,
    RX_MODE,
    TX_MODE,
}SpiRxTxMode;

/*spi工作模式*/
typedef enum
{
    BLOCK_MODE,
    IT_MODE,
    DMA_MODE,
}SpiWorkMode;


typedef struct spi_ins_temp
{
    SPI_HandleTypeDef *hspi_handle;                 // SPI句柄,用于操作SPI外设

    SpiMasterSlaveMode master_slave_mode;    // 主从模式
    SpiRxTxMode rx_tx_mode;                  // 接收发送模式
    SpiWorkMode work_mode;                   // 工作模式

    GPIO_TypeDef *cs_port;                   // 片选端口
    uint16_t cs_pin;                         // 片选引脚
    uint8_t *spi_state;                   // 片选状态指针,用于中断模式下的片选控制
    uint8_t CS_State;                        // 片选状态,用于中断模式下的片选控制

    uint8_t *rx_buffer;                      // 接收缓冲区,用于DMA或IT模式下接收数据
    uint8_t rx_size;                         // 接收数据长度,用于DMA或IT模式下
    uint8_t *tx_buffer;                      // 发送缓冲区,用于DMA或IT模式下发送数据
    uint8_t tx_size;                         // 发送数据长度,用于DMA或IT模式下

    void (*callback)(struct spi_ins_temp *); // 接收回调函数
    void *handle;                            // 模块指针,用于在回调函数中识别不同模块
}SpiInstance;

/* 接收回调函数定义,包含SPI的module按照此格式构建回调函数 */
typedef void (*spi_rx_callback)(SpiInstance *);

typedef struct
{
    SPI_HandleTypeDef *hspi_handle;                 // SPI句柄,用于操作SPI外设

    SpiMasterSlaveMode master_slave_mode;    // 主从模式
    SpiRxTxMode rx_tx_mode;                  // 接收发送模式
    SpiWorkMode work_mode;                   // 工作模式

    GPIO_TypeDef *cs_port;                   // 片选端口
    uint16_t cs_pin;                         // 片选引脚

    void (*callback)(struct spi_ins_temp *); // 接收回调函数
    void *handle;                            // 模块指针,用于在回调函数中识别不同模块
}SpiConfig;

/**
 * @brief 注册一个spi instance
 *
 * @param conf 传入spi配置
 * @return SpiInstance* 返回一个spi实例指针,之后通过该指针操作spi外设
 */
SpiInstance *BspSpiRegister(SpiConfig *conf);
#endif

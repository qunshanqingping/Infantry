#include "bsp_spi.h"
#include "basic_math.h"
#include "sys_log.h"
/* 所有的spi instance保存于此,用于callback时判断中断来源*/
static SpiInstance *spi_instance[BSP_SPI_DEVICE_CNT] = {NULL};
static uint8_t idx = 0;                         // 配合中断以及初始化
uint8_t SPIDeviceOnGoing[BSP_SPI_DEVICE_CNT] = {1}; // 用于判断当前spi是否正在传输,防止多个模块同时使用一个spi总线 (0: 正在传输, 1: 未传输)

SpiInstance * BspSpiRegister(SpiConfig *conf)
{
    if (idx >= MX_SPI_BUS_SLAVE_CNT) // 超过最大实例数
    {
        LOGERROR("SPI instance count exceeds limit! Please check your configuration.");
        while (1);
    }
    SpiInstance *instance = (SpiInstance *)user_malloc(sizeof(SpiInstance));
    memset(instance, 0, sizeof(SpiInstance));
    if (instance == NULL)
    {
        user_free(instance);
        LOGERROR("SPI instance memory allocation failed! Please check your memory.");
        while (1); // 内存分配失败,请检查内存是否足够
    }

    instance->hspi_handle = conf->hspi_handle;

    instance->master_slave_mode = conf->master_slave_mode;
    instance->rx_tx_mode = conf->rx_tx_mode;
    instance->work_mode = conf->work_mode;

    instance->cs_port = conf->cs_port;
    instance->cs_pin = conf->cs_pin;

    instance->callback = conf->callback;
    instance->handle = conf->handle;

    if (instance->cs_port!= NULL)
    {
        if (instance->hspi_handle->Instance == SPI1)
        {
            instance->spi_state = &SPIDeviceOnGoing[0];
        }
        else if (instance->hspi_handle->Instance == SPI2)
        {
            instance->spi_state = &SPIDeviceOnGoing[1];
        }
        else if (instance->hspi_handle->Instance == SPI3)
        {
            instance->spi_state = &SPIDeviceOnGoing[2];
        }
        else if (instance->hspi_handle->Instance == SPI6)
        {
            instance->spi_state = &SPIDeviceOnGoing[3];
        }
        else
        {
            while (1);
        }
    }
    spi_instance[idx] = instance;
    idx++;
    return instance;
}

void BspSpiTransmit(SpiInstance *spi_ins, uint8_t *ptr_data, uint8_t len)
{
    // 拉低片选,开始传输(选中从机)
    if (spi_ins->cs_port != NULL && spi_ins->cs_pin != 0)
    {
        HAL_GPIO_WritePin(spi_ins->cs_port, spi_ins->cs_pin, GPIO_PIN_RESET);
    }
    switch (spi_ins->work_mode)
    {
    case BLOCK_MODE:
        HAL_SPI_Transmit(spi_ins->hspi_handle, ptr_data, len, 1000); // 默认1000ms超时
        // 阻塞模式不会调用回调函数,传输完成后直接拉高片选结束
        HAL_GPIO_WritePin(spi_ins->cs_port, spi_ins->cs_pin, GPIO_PIN_SET);
        break;
    case IT_MODE:
        HAL_SPI_Transmit_IT(spi_ins->hspi_handle, ptr_data, len);
        break;
    case DMA_MODE:
        HAL_SPI_Transmit_DMA(spi_ins->hspi_handle, ptr_data, len);
        break;
    default:
        while (1)
        {
        }
        // error mode! 请查看是否正确设置模式，或出现指针越界导致模式被异常修改的情况
    }
}
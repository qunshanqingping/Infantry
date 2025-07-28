#include "bsp_spi.h"
#include "basic_math.h"
#include "stdbool.h"
/* 所有的spi instance保存于此,用于callback时判断中断来源*/
static SpiInstance *spi_instance[BSP_SPI_DEVICE_CNT] = {NULL};
static uint8_t idx = 0;                         // 配合中断以及初始化
uint8_t SPIDeviceOnGoing[BSP_SPI_DEVICE_CNT] = {1}; // 用于判断当前spi是否正在传输,防止多个模块同时使用一个spi总线 (0: 正在传输, 1: 未传输)

SpiInstance * spi_register(SpiConfig *conf)
{
    if (idx >= MX_SPI_BUS_SLAVE_CNT) // 超过最大实例数
    {
        while (1);
    }
    SpiInstance *instance = (SpiInstance *)user_malloc(sizeof(SpiInstance));
    memset(instance, 0, sizeof(SpiInstance));
    if (instance == NULL)
    {
        user_free(instance);
        while (1); // 内存分配失败,请检查内存是否足够
    }

    instance->hspi_handle = conf->hspi_handle;

    instance->master_slave_mode = conf->master_slave_mode;
    instance->rx_tx_mode = conf->rx_tx_mode;
    instance->work_mode = conf->work_mode;
    instance->cs_mode = conf->cs_mode;

    instance->cs_port = conf->cs_port;
    instance->cs_pin = conf->cs_pin;

    instance->module_spi_callback = conf->callback;
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

void spi_tx_reset(SpiInstance *spi_ins, uint8_t *tx_buffer, uint8_t tx_len)
{
    if (spi_ins == NULL || spi_ins->hspi_handle == NULL)
    {
        while (1);
    }
    spi_ins->tx_len = tx_len;
    spi_ins->tx_buffer = tx_buffer;
    spi_ins->tx_len = tx_len;
}

void spi_rx_reset(SpiInstance *spi_ins, uint8_t *rx_buffer, uint8_t rx_len)
{
    if (spi_ins == NULL || spi_ins->hspi_handle == NULL)
    {
        while (1);
    }
    spi_ins->rx_buffer = rx_buffer;
    spi_ins->rx_len = rx_len;
}
void spi_cs_high(SpiInstance *spi_ins)
{
    HAL_GPIO_WritePin(spi_ins->cs_port, spi_ins->cs_pin, GPIO_PIN_SET);
    spi_ins->CS_State = HAL_GPIO_ReadPin(spi_ins->cs_port, spi_ins->cs_pin);
}
void spi_cs_low(SpiInstance *spi_ins)
{
    HAL_GPIO_WritePin(spi_ins->cs_port, spi_ins->cs_pin, GPIO_PIN_RESET);
    spi_ins->CS_State = HAL_GPIO_ReadPin(spi_ins->cs_port, spi_ins->cs_pin);
}

void spi_transmit(SpiInstance *spi_ins)
{
    switch (spi_ins->work_mode)
    {
    case BLOCK_MODE:
        HAL_SPI_Transmit(spi_ins->hspi_handle,spi_ins->tx_buffer, spi_ins->tx_len, 1000); // 默认1000ms超时
        break;
    case IT_MODE:
        HAL_SPI_Transmit_IT(spi_ins->hspi_handle, spi_ins->tx_buffer, spi_ins->tx_len);
        break;
    case DMA_MODE:
        HAL_SPI_Transmit_DMA(spi_ins->hspi_handle, spi_ins->tx_buffer, spi_ins->tx_len);
        break;
    default:
        while (1)
        {
        }
        // error mode! 请查看是否正确设置模式，或出现指针越界导致模式被异常修改的情况
    }
}

void spi_trans_recv(SpiInstance* spi_ins, uint8_t *tx_buffer, uint8_t *rx_buffer, uint8_t len)
{
    spi_ins->tx_buffer = tx_buffer;
    spi_ins->rx_buffer = rx_buffer;
    spi_ins->tx_len = spi_ins->tx_len = len;
    switch (spi_ins->work_mode)
    {
        case DMA_MODE:
            HAL_SPI_TransmitReceive_DMA(spi_ins->hspi_handle, tx_buffer, rx_buffer, len);
            break;
        case IT_MODE:
            HAL_SPI_TransmitReceive_IT(spi_ins->hspi_handle, tx_buffer, rx_buffer, len);
            break;
        case BLOCK_MODE:
            HAL_SPI_TransmitReceive(spi_ins->hspi_handle, tx_buffer, rx_buffer, len, 1000);
            break;
        default:
            while (1){}
    }
}

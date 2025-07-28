/*
 * bmi088 IMU传感器驱动模块
 *
 * Created by honor on 25-7-27.
 */

#include "bmi088.h"
#include "bmi088reg.h"
#include "bsp_spi.h"
#include "stdint.h"
/* 私有函数声明 */

/**
 * @brief 通过SPI总线执行单字节数据的全双工传输
 * @param spi_ins: SPI实例指针
 * @param tx_data: 要发送的字节数据
 * @retval 从设备接收到的字节数据
 */
static uint8_t BMI088_read_write_byte(SpiInstance *spi_ins, uint8_t tx_data);

/**
 * @brief 向bmi088传感器的指定寄存器写入单字节数据
 * @param spi_ins: SPI实例指针
 * @param reg: 目标寄存器地址
 * @param data: 待写入的寄存器数据
 * @retval None
 */
static void BMI088_write_single_reg(SpiInstance *spi_ins, uint8_t reg, uint8_t data);

/**
 * @brief 从bmi088传感器的指定寄存器读取单字节数据
 * @param spi_ins: SPI实例指针
 * @param reg: 目标寄存器地址
 * @param return_data: 指向存储读取结果的变量地址
 * @retval None
 */
static void BMI088_read_single_reg(SpiInstance *spi_ins, uint8_t reg, uint8_t *return_data);

/**
 * @brief 向bmi088传感器连续写入多个寄存器数据
 * @param spi_ins: SPI实例指针
 * @param reg: 起始寄存器地址
 * @param buf: 指向待写入数据的缓冲区指针
 * @param len: 待写入的数据长度(字节数)
 * @retval None
 */
static void BMI088_write_muli_reg(SpiInstance *spi_ins, uint8_t reg, uint8_t* buf, uint8_t len);

/**
 * @brief 从bmi088传感器连续读取多个寄存器数据
 * @param spi_ins: SPI实例指针
 * @param reg: 起始寄存器地址
 * @param buf: 指向存储读取结果的缓冲区指针
 * @param len: 需要读取的数据长度(字节数)
 * @retval None
 */
static void BMI088_read_muli_reg(SpiInstance *spi_ins, uint8_t reg, uint8_t *buf, uint8_t len);

/**
 * @brief 通过SPI总线执行单字节数据的全双工传输
 * @param spi_ins: SPI实例指针
 * @param tx_data: 要发送的字节数据
 * @retval 从设备接收到的字节数据
 */
static uint8_t BMI088_read_write_byte(SpiInstance *spi_ins, uint8_t tx_data)
{
    uint8_t rx_data;
    spi_trans_recv(spi_ins, &tx_data, &rx_data, 1);
    return rx_data;
}

/**
 * @brief 向bmi088传感器的指定寄存器写入单字节数据
 * @param spi_ins: SPI实例指针
 * @param reg: 目标寄存器地址
 * @param data: 待写入的寄存器数据
 * @retval None
 */
static void BMI088_write_single_reg(SpiInstance *spi_ins, uint8_t reg, uint8_t data)
{
    BMI088_read_write_byte(spi_ins, reg);
    BMI088_read_write_byte(spi_ins, data);
}

/**
 * @brief 从bmi088传感器的指定寄存器读取单字节数据
 * @param spi_ins: SPI实例指针
 * @param reg: 目标寄存器地址
 * @param return_data: 指向存储读取结果的变量地址
 * @retval None
 */
static void BMI088_read_single_reg(SpiInstance *spi_ins, uint8_t reg, uint8_t *return_data)
{
    BMI088_read_write_byte(spi_ins, reg | 0x80);  /* 设置读操作标志位(最高位置1) */
    *return_data = BMI088_read_write_byte(spi_ins, 0x55);  /* 发送哑数据并接收寄存器值 */
}

/**
 * @brief 向bmi088传感器连续写入多个寄存器数据
 * @param spi_ins: SPI实例指针
 * @param reg: 起始寄存器地址
 * @param buf: 指向待写入数据的缓冲区指针
 * @param len: 待写入的数据长度(字节数)
 * @retval None
 */
static void BMI088_write_muli_reg(SpiInstance *spi_ins, uint8_t reg, uint8_t* buf, uint8_t len)
{
    BMI088_read_write_byte(spi_ins, reg);  /* 发送起始寄存器地址 */
    while(len != 0) {
        BMI088_read_write_byte(spi_ins, *buf);  /* 逐字节发送缓冲区数据 */
        buf++;
        len--;
    }
}

/**
 * @brief 从bmi088传感器连续读取多个寄存器数据
 * @param spi_ins: SPI实例指针
 * @param reg: 起始寄存器地址
 * @param buf: 指向存储读取结果的缓冲区指针
 * @param len: 需要读取的数据长度(字节数)
 * @retval None
 */
static void BMI088_read_muli_reg(SpiInstance *spi_ins, uint8_t reg, uint8_t *buf, uint8_t len)
{
    BMI088_read_write_byte(spi_ins, reg | 0x80);  /* 设置读操作标志位(最高位置1) */

    while(len != 0) {
        *buf = BMI088_read_write_byte(spi_ins, 0x55);  /* 发送哑数据并接收寄存器值 */
        buf++;
        len--;
    }
}

/**
* @brief:      	BMI088_accel_write_single_reg(reg, data)
* @param:       reg - 寄存器地址
*               data - 写入的数据
* @retval:     	void
* @details:    	通过bmi088加速度计的SPI总线写入单个寄存器的宏定义
*/
static void BMI088_accel_write_single_reg(SpiInstance *bmi088_acc, uint8_t reg, uint8_t data)
{
    spi_cs_low(bmi088_acc);
    BMI088_write_single_reg(bmi088_acc, reg, data);
    spi_cs_high(bmi088_acc);
}

static uint8_t BMI088_accel_read_single_reg(SpiInstance *bmi088_acc, uint8_t reg, uint8_t data)
{
    spi_cs_low(bmi088_acc);
    BMI088_read_write_byte(bmi088_acc,(reg) | 0x80);
    BMI088_read_write_byte(bmi088_acc,0x55);
    data = BMI088_read_write_byte(bmi088_acc,0x55);
    spi_cs_high(bmi088_acc);
    return data;
}

static void BMI088_accel_read_muli_reg(SpiInstance *bmi088_acc, uint8_t reg,uint8_t data,uint8_t len)
{

    BMI088_read_write_byte(bmi088_acc,reg | 0x80);
    BMI088_read_muli_reg(bmi088_acc,reg, &data, len);
    spi_cs_high(bmi088_acc);
}

static void BMI088_gyro_write_single_reg(SpiInstance*bmi088_gyro, uint8_t reg,uint8_t data)
{
    spi_cs_low(bmi088_gyro);
    BMI088_write_single_reg(bmi088_gyro,reg, data);
    spi_cs_high(bmi088_gyro);
}

static void BMI088_gyro_read_single_reg(SpiInstance*bmi088_gyro, uint8_t reg, uint8_t *data)
{
    spi_cs_low(bmi088_gyro);
    BMI088_read_single_reg(bmi088_gyro,reg, data);
    spi_cs_high(bmi088_gyro);
}

/*
 * @brief 通过bmi088陀螺仪的SPI总线连续读取多个寄存器
 * @param reg: 起始寄存器地址
 * @param data: 存储读取数据的缓冲区
 * @param len: 要读取的字节数
 * @retval None
 */
static void BMI088_gyro_read_muli_reg(SpiInstance*bmi088_gyro, uint8_t reg, uint8_t *data, uint8_t len)
{
    spi_cs_low(bmi088_gyro);
    BMI088_read_muli_reg(bmi088_gyro,reg, data, len);
    spi_cs_high(bmi088_gyro);
}

static uint8_t write_BMI088_accel_reg_data_error[BMI088_WRITE_ACCEL_REG_NUM][3] =
    {
    {BMI088_ACC_PWR_CTRL, BMI088_ACC_ENABLE_ACC_ON, BMI088_ACC_PWR_CTRL_ERROR},
    {BMI088_ACC_PWR_CONF, BMI088_ACC_PWR_ACTIVE_MODE, BMI088_ACC_PWR_CONF_ERROR},
    {BMI088_ACC_CONF,  BMI088_ACC_NORMAL| BMI088_ACC_800_HZ | BMI088_ACC_CONF_MUST_Set, BMI088_ACC_CONF_ERROR},
    {BMI088_ACC_RANGE, BMI088_ACC_RANGE_3G, BMI088_ACC_RANGE_ERROR},
    {BMI088_INT1_IO_CTRL, BMI088_ACC_INT1_IO_ENABLE | BMI088_ACC_INT1_GPIO_PP | BMI088_ACC_INT1_GPIO_LOW, BMI088_INT1_IO_CTRL_ERROR},
    {BMI088_INT_MAP_DATA, BMI088_ACC_INT1_DRDY_INTERRUPT, BMI088_INT_MAP_DATA_ERROR}

    };

static uint8_t write_BMI088_gyro_reg_data_error[BMI088_WRITE_GYRO_REG_NUM][3] =
    {
    {BMI088_GYRO_RANGE, BMI088_GYRO_2000, BMI088_GYRO_RANGE_ERROR},
    {BMI088_GYRO_BANDWIDTH, BMI088_GYRO_1000_116_HZ | BMI088_GYRO_BANDWIDTH_MUST_Set, BMI088_GYRO_BANDWIDTH_ERROR},
    {BMI088_GYRO_LPM1, BMI088_GYRO_NORMAL_MODE, BMI088_GYRO_LPM1_ERROR},
    {BMI088_GYRO_CTRL, BMI088_DRDY_ON, BMI088_GYRO_CTRL_ERROR},
    {BMI088_GYRO_INT3_INT4_IO_CONF, BMI088_GYRO_INT3_GPIO_PP | BMI088_GYRO_INT3_GPIO_LOW, BMI088_GYRO_INT3_INT4_IO_CONF_ERROR},
    {BMI088_GYRO_INT3_INT4_IO_MAP, BMI088_GYRO_DRDY_IO_INT3, BMI088_GYRO_INT3_INT4_IO_MAP_ERROR}
    };

static void BMI088_GPIO_init(){}
static void BMI088_com_init(){}

uint8_t bmi088_accel_init(SpiInstance *bmi088_acc)
{
    uint8_t res = 0;
    uint8_t write_reg_num = 0;

    //check commiunication
    BMI088_accel_read_single_reg(bmi088_acc,BMI088_ACC_CHIP_ID, res);
    dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_accel_read_single_reg(bmi088_acc,BMI088_ACC_CHIP_ID, res);
    dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    //accel software reset
    BMI088_accel_write_single_reg(bmi088_acc,BMI088_ACC_SOFTRESET, BMI088_ACC_SOFTRESET_VALUE);
    dwt_delay_ms(BMI088_LONG_DELAY_TIME);

    //check commiunication is normal after reset
    BMI088_accel_read_single_reg(bmi088_acc,BMI088_ACC_CHIP_ID, res);
    dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_accel_read_single_reg(bmi088_acc,BMI088_ACC_CHIP_ID, res);
    dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    // check the "who am I"
    if (res != BMI088_ACC_CHIP_ID_VALUE)
    {
        return BMI088_NO_SENSOR;
    }

    //set accel sonsor config and check
    for (write_reg_num = 0; write_reg_num < BMI088_WRITE_ACCEL_REG_NUM; write_reg_num++)
    {

        BMI088_accel_write_single_reg(bmi088_acc,write_BMI088_accel_reg_data_error[write_reg_num][0], write_BMI088_accel_reg_data_error[write_reg_num][1]);
        dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        BMI088_accel_read_single_reg(bmi088_acc,write_BMI088_accel_reg_data_error[write_reg_num][0], res);
        dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        if (res != write_BMI088_accel_reg_data_error[write_reg_num][1])
        {
            return write_BMI088_accel_reg_data_error[write_reg_num][2];
        }
    }
    return BMI088_NO_ERROR;
}

uint8_t bmi088_gyro_init(SpiInstance *bmi088_gyro)
{
    uint8_t write_reg_num = 0;
    uint8_t res = 0;

    //check commiunication
    BMI088_gyro_read_single_reg(bmi088_gyro,BMI088_GYRO_CHIP_ID, &res);
    dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_gyro_read_single_reg(bmi088_gyro,BMI088_GYRO_CHIP_ID, &res);
    dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    //reset the gyro sensor
    BMI088_gyro_write_single_reg(bmi088_gyro,BMI088_GYRO_SOFTRESET, BMI088_GYRO_SOFTRESET_VALUE);
    dwt_delay_ms(BMI088_LONG_DELAY_TIME);
    //check commiunication is normal after reset
    BMI088_gyro_read_single_reg(bmi088_gyro,BMI088_GYRO_CHIP_ID, &res);
    dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);
    BMI088_gyro_read_single_reg(bmi088_gyro,BMI088_GYRO_CHIP_ID, &res);
    dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

    // check the "who am I"
    if (res != BMI088_GYRO_CHIP_ID_VALUE)
    {
        return BMI088_NO_SENSOR;
    }

    //set gyro sonsor config and check
    for (write_reg_num = 0; write_reg_num < BMI088_WRITE_GYRO_REG_NUM; write_reg_num++)
    {

        BMI088_gyro_write_single_reg(bmi088_gyro,write_BMI088_gyro_reg_data_error[write_reg_num][0], write_BMI088_gyro_reg_data_error[write_reg_num][1]);
        dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        BMI088_gyro_read_single_reg(bmi088_gyro,write_BMI088_gyro_reg_data_error[write_reg_num][0], &res);
        dwt_delay_us(BMI088_COM_WAIT_SENSOR_TIME);

        if (res != write_BMI088_gyro_reg_data_error[write_reg_num][1])
        {
            return write_BMI088_gyro_reg_data_error[write_reg_num][2];
        }
    }

    return BMI088_NO_ERROR;
}

uint8_t BMI088_init(BMI088Instance *bmi088)
{
    uint8_t error = BMI088_NO_ERROR;
    // GPIO and SPI  Init .
    BMI088_GPIO_init();
    BMI088_com_init();

    error |= bmi088_accel_init(bmi088->accel);
    error |= bmi088_gyro_init(bmi088->accel);

    return error;
}

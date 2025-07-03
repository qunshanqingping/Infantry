/**
 ******************************************************************************
 * @file           : bsp_gpio.h
 * @author         : Adonis_Jin
 * @brief          : None
 * @version        : 1.0
 * @date           : 25-6-4
 ******************************************************************************
 */

#ifndef BSP_GPIO_H
#define BSP_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include <gpio.h>
#include <stdint.h>
/* Private includes -----------------------------------------------------------*/


/* Private defines -----------------------------------------------------------*/
/*定义可用的 GPIO 设备数量*/
#define GPIO_MX_DEVICE_NUM 10

/* Private types -------------------------------------------------------------*/
/**
 * @brief EXTI中断触发模式枚举类型，用于配置GPIO外部中断的触发方式
 *
 */
typedef enum
{
    GPIO_EXTI_MODE_RISING, // 上升沿触发
    GPIO_EXTI_MODE_FALLING, // 下降沿触发
    GPIO_EXTI_MODE_RISING_FALLING, // 上升沿和下降沿均触发
    GPIO_EXTI_MODE_NONE, // 无触发（常用于关闭中断或初始化默认值）
} GPIO_EXTI_MODE_e;

/**
 * @brief GPIO实例结构体定义
 *
 */
typedef struct GPIO_Ins_Temp
{
    GPIO_TypeDef *GPIOx; // GPIOA,GPIOB,GPIOC...
    GPIO_PinState pin_state; // 引脚状态,Set,Reset;not frequently used
    GPIO_EXTI_MODE_e exti_mode; // 外部中断模式 not frequently used
    uint16_t GPIO_Pin; // 引脚号,
    void (*gpio_model_callback)(struct GPIO_Ins_Temp *); // exti中断回调函数
    void *id; // 区分不同的GPIO实例

} GPIOInstance;


/**
 * @brief GPIO初始化配置结构体定义
 *
 */
typedef struct
{
    GPIO_TypeDef *GPIOx; // GPIOA,GPIOB,GPIOC...
    GPIO_PinState pin_state; // 引脚状态,Set,Reset not frequently used
    GPIO_EXTI_MODE_e exti_mode; // 外部中断模式 not frequently used
    uint16_t GPIO_Pin; // 引脚号,@note 这里的引脚号是GPIO_PIN_0,GPIO_PIN_1...
    // 这些引脚是stm32f4xx_hal_gpio.h中定义的宏!!! 一定要注意

    void (*gpio_model_callback)(GPIOInstance *); // exti中断回调函数
    void *id; // 区分不同的GPIO实例

} GPIO_Init_Config_s;

/* Private macro -------------------------------------------------------------*/


/* Private functions prototypes ----------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
/**
 * @brief 注册GPIO实例
 *
 * @param GPIO_config
 * @return GPIOInstance*
 */
GPIOInstance *GPIORegister(const GPIO_Init_Config_s *GPIO_config);

/**
 * @brief GPIO API,切换GPIO电平
 *
 * @param _instance
 */
void GPIOToggle(const GPIOInstance *_instance);

/**
 * @brief 设置GPIO电平
 *
 * @param _instance
 */
void GPIOSet(const GPIOInstance *_instance);

/**
 * @brief 复位GPIO电平
 *
 * @param _instance
 */
void GPIOReset(const GPIOInstance *_instance);

/**
 * @brief 读取GPIO电平
 *
 * @param _instance
 * @return GPIO_PinState
 */
GPIO_PinState GPIORead(const GPIOInstance *_instance);

#endif /* BSP_GPIO_H */

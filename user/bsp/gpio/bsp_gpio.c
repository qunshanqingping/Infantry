/**
 ******************************************************************************
 * @file           : bsp_gpio.c
 * @author         : Adonis_Jin
 * @brief          : None
 * @version        : 1.0
 * @date           : 25-6-4
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <memory.h>
#include <stdlib.h>
/* Private includes -----------------------------------------------------------*/
#include "bsp_gpio.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t idx;
static GPIOInstance *gpio_instance[GPIO_MX_DEVICE_NUM] = {NULL};

/* Private functions prototypes ----------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief EXTI中断回调函数,根据GPIO_Pin找到对应的GPIOInstance,并调用模块回调函数(如果有)
 * @param GPIO_Pin 发生中断的GPIO_Pin
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // 如有必要,可以根据PinState和HAL_GPIO_ReadPin来判断是上升沿还是下降沿/rise&fall等
    for (size_t i = 0; i < idx; i++)
    {
        GPIOInstance *gpio = gpio_instance[i];
        if (gpio->GPIO_Pin == GPIO_Pin && gpio->gpio_model_callback != NULL)
        {
            gpio->gpio_model_callback(gpio);
            return;
        }
    }
}

GPIOInstance *GPIORegister(const GPIO_Init_Config_s *GPIO_config)
{
    GPIOInstance *ins = (GPIOInstance *)malloc(sizeof(GPIOInstance));
    memset(ins, 0, sizeof(GPIOInstance));

    ins->GPIOx = GPIO_config->GPIOx;
    ins->GPIO_Pin = GPIO_config->GPIO_Pin;
    ins->pin_state = GPIO_config->pin_state;
    ins->exti_mode = GPIO_config->exti_mode;
    ins->id = GPIO_config->id;
    ins->gpio_model_callback = GPIO_config->gpio_model_callback;
    gpio_instance[idx++] = ins;
    return ins;
}

/**
 * @brief GPIO操作函数
 * @note
 * @param _instance
 */

void GPIOToggle(const GPIOInstance *_instance) { HAL_GPIO_TogglePin(_instance->GPIOx, _instance->GPIO_Pin); }

void GPIOSet(const GPIOInstance *_instance) { HAL_GPIO_WritePin(_instance->GPIOx, _instance->GPIO_Pin, GPIO_PIN_SET); }

void GPIOReset(const GPIOInstance *_instance) { HAL_GPIO_WritePin(_instance->GPIOx, _instance->GPIO_Pin, GPIO_PIN_RESET); }

GPIO_PinState GPIORead(const GPIOInstance *_instance) { return HAL_GPIO_ReadPin(_instance->GPIOx, _instance->GPIO_Pin); }

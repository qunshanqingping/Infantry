/**
 ******************************************************************************
 * @file           : bsp_log.h
 * @author         : Adonis_Jin
 * @brief          : None
 * @version        : 1.0
 * @date           : 25-6-3
 ******************************************************************************
 */

#ifndef BSP_LOG_H
#define BSP_LOG_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
/* Private includes -----------------------------------------------------------*/
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "bsp_tim.h"
/* Private types -------------------------------------------------------------*/


/* Private defines -----------------------------------------------------------*/
#define BUFFER_INDEX 0

/* Private macro -------------------------------------------------------------*/

#define SYS_MS getCurrentTime()

/**
 * @brief 日志功能原型,供下面的LOGINFO,LOGWARNING,LOGERROR等使用
 *
 */
#define LOG_PROTO(type, color, format, ...)                                                                       \
    SEGGER_RTT_printf(BUFFER_INDEX,                                                                               \
                      "%s"                                                                                        \
                      "[%02d:%03d:%03d]"                                                                          \
                      "%s" format "\r\n%s",                                                                       \
                      color, SYS_MS / 1000 / 60, SYS_MS / 1000 % 60, SYS_MS % 1000, \
                      type, ##__VA_ARGS__, RTT_CTRL_RESET)

/**
 * @brief 清屏
 */
#define LOG_CLEAR() SEGGER_RTT_WriteString(0, "  " RTT_CTRL_CLEAR)

/**
 *@brief 无颜色日志输出
 * @param format 输出内容
 */
#define LOG(format, ...) LOG_PROTO("", "", format, ##__VA_ARGS__)

// information level
#define LOGINFO(format, ...) LOG_PROTO("I:", RTT_CTRL_TEXT_BRIGHT_GREEN, format, ##__VA_ARGS__)
// warning level
#define LOGWARNING(format, ...) LOG_PROTO("W:", RTT_CTRL_TEXT_BRIGHT_YELLOW, format, ##__VA_ARGS__)
// error level
#define LOGERROR(format, ...) LOG_PROTO("E:", RTT_CTRL_TEXT_BRIGHT_RED, format, ##__VA_ARGS__)

/* Private functions prototypes ----------------------------------------------*/


/* Exported variables ---------------------------------------------------------*/


/* Exported functions prototypes ---------------------------------------------*/
/**
 * @brief 日志系统初始化，这里为了统一bsp层，重新封装
 */
void BspLogInit();
#endif /* BSP_LOG_H */

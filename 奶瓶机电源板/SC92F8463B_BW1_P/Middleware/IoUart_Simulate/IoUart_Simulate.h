/**
 *******************************************************************************
 * 
 * @file    IoUart_Simulate.h
 * @author  lgx
 * @version 1.0
 * @date    2024.12.7
 * @brief   模拟串口通信模块
 * 
 *******************************************************************************
 *
 * @attention
 * 
 */

#ifndef _SIMULATE_UART_H_
#define _SIMULATE_UART_H_


#include "GpioDrv.h"
#include "TimerDrv.h"
#include "product_config.h"

#if CONFIG_UARTSIMULATE
#if CONFIG_NIGHTLIGHT
#if NEWTYPE1
#define NIGHTLIGHT_MAX_LENGTH  10
#define IoUart_Location P23

extern ByteFlag IoUart_Flags;
#define IoUartFlag              IoUart_Flags.f_byte
#define IoUart_RxStart          IoUart_Flags.f_bits.no0
#define IoUart_RxByteStart      IoUart_Flags.f_bits.no1
#define IoUart_RxHasReceived    IoUart_Flags.f_bits.no2
#define IoUart_TxStart          IoUart_Flags.f_bits.no3
#define IoUart_TxByteStart      IoUart_Flags.f_bits.no4
#define IoUart_TxValue          IoUart_Flags.f_bits.no5
#define IoUart_TxOutput         IoUart_Flags.f_bits.no6
#define IoUart_TxHasSand        IoUart_Flags.f_bits.no7


/**
 * @brief 模拟串口通信模块初始化
 * 
 * @param 无
 * @return 无
 */
void Init_IoUartSimulate(void);

/**
 * @brief 接收校验和
 * 
 * @param 无
 * @return bit ret
 */
bit IoUart_HasReceived(void);

/**
 * @brief 发送使能
 * 
 * @param 无
 * @return 无
 */
void IoUart_SandEnable( unsigned char* txbuf, unsigned short txnum );

/**
 * @brief 接收使能
 * 
 * @param 无
 * @return 无
 */
void IoUart_ReceivedEnable( unsigned char* rxbuf, unsigned short rxnum );

#endif
#endif
#endif
#endif
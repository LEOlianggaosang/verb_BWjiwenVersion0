/**
 *******************************************************************************
 * Copyright (c) 20250424
 * 
 * @file    product_config.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */

#ifndef _PRODUCT_CONFIG_H_
#define _PRODUCT_CONFIG_H_

#include "user_define.h"
#define VERSION_NUMBER	002
#define NEWTYPE1    1
#define CONFIG_NIGHTLIGHT    1
#define CONFIG_UARTSIMULATE    1
#define CONFIG_FCT_UART        1//烧录口串口通信进入
#define IO_BAUDRATE     200
#define IOBAUD_VALUE    (1000000/IO_BAUDRATE)
#define CONFIG_INT_CHECK    1//增加流量计脉冲上升沿检测(INT23)，增加风机反馈方波上升沿检测(INT22)
//*********************************
//mcu selection
//#define  SC92F8463B_ENABLED
//20250424 系统时钟为24M分频12M，T0分频12定时1ms中断，检测霍尔为1ms中断定时检测输入
//20250424 初始化UART0(Timer2)，UART1，PWM0，AIN9
//20250603 更改蜂鸣类型
//20250603 更改通信规则，由主逻辑模块定时主动发送，主动完成握手

/*
//NEWTYPE1
1.芯片引脚差异GpioDrv
2.功能端口差异Serail、Pwm、Adc
3.AdDrv.h/SerialDrv.c/SerialDrv.h/TicketHandling.c
4.temperatures差距不大
5.F_MovePumpEn/F_OutFanEn
*/

/*
//20251020
//CONFIG_NIGHTLIGHT//CONFIG_UARTSIMULATE
1.  定时器T0作为1ms时间基准，T2作为UART0波特率发生器，T1作为模拟通信定时器//IOBAUD_VALUE
*/

/*
//20251025
//CONFIG_FCT_UART
1.  夜灯通信从UART0改为模拟通信，UART0作为FCT使用
//20251115
1、更改//Test_WaitFctActionCount//Test_FctingActionCount0//Test_FctingActionCount1//计数定义
2、FCT模式验证通信显示需要同时修改显示板通信，夜灯发送，夜灯定时中断
*/
/*
//20251203
//#define CONFIG_INT_CHECK    1
//#if (CONFIG_INT_CHECK&&NEWTYPE1)
1.增加外部中断初始化，FM与FB都需要从GPIO初始化为上拉输入//ExternalIntDrv
2.增加流量计脉冲上升沿检测(INT23)，增加风机反馈方波上升沿检测(INT22)//TicketHandling.c
3.增加通信反馈方波数数据位//FeedBackCnt
4.两个输入在同一个中断中，需要增加双沿判断
5.增加开门马上关洗涤泵的限制
ps1:显示板流量单位
ps2:显示板读取反馈显示，显示板风机故障检测机制
*/
//20260430//臭氧驱动//限制臭氧配置//限制进水阀共用
#endif

/**
 *******************************************************************************
 * Copyright (c) 20250606
 * 
 * @file    ReadSwitch.h
 * @author  lianggaosang@qq.com
 * @brief   开关状态控制
 *
 *******************************************************************************
 */
#ifndef _READSWITCH_H_
#define _READSWITCH_H_

#include "product_config.h"

#define		C_LOW_CNT			4
#define		C_HIGH_CNT		16
#define		C_TOTAL_CNT		20
extern ByteFlag Switch_Flags;
#define  SwitchFlag						Switch_Flags.f_byte
#define  Signal_IaqsSwitch		Switch_Flags.f_bits.no0
#define  Signal_IssSwitch			Switch_Flags.f_bits.no1
#define  Signal_IsbSwitch			Switch_Flags.f_bits.no2
#define  Signal_PreSwitch			Switch_Flags.f_bits.no3
#define  Signal_DoorSwitch		Switch_Flags.f_bits.no4
#define  Signal_ErrIaqs				Switch_Flags.f_bits.no5

/**
 * @brief 信号捕获
 * 
 * @param 无
 * @return 无
 */
void Read_Switch(void);
void Init_Switch(void);

#endif
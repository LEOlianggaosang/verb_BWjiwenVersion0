/**
 *******************************************************************************
 * Copyright (c) 202500606
 *
 * @file    LoadDrive.h
 * @author  lianggaosang@qq.com
 * @brief   继电器控制
 *
 *******************************************************************************
 */
#ifndef _LOADDRIVE_H_
#define _LOADDRIVE_H_

#include "product_config.h"

/**
 * @name 输出使能标志位
 */
///@{
//输出使能
extern WordFlag Load_Enables;//debug
#define  LoadEnable         Load_Enables.f_word
#define  Load_R             Load_Enables.f_bits.no0
#define  Load_Ps			Load_Enables.f_bits.no1
#define  Load_Ptc			Load_Enables.f_bits.no2
#define  Load_Ml			Load_Enables.f_bits.no8
#define  Load_Ip			Load_Enables.f_bits.no9
#define  Load_Mp			Load_Enables.f_bits.no10
#define  Load_Ev1			Load_Enables.f_bits.no11
#define  Load_Fan			Load_Enables.f_bits.no12
#define  Load_Fan2    Load_Enables.f_bits.no13
#define  Load_Led			Load_Enables.f_bits.no14

extern UCHAR_XDATA	FlowMPreSecErrCnt;
/**
 * @brief 继电器驱动
 * 
 * @param 无
 * @return 无
 */
void Load_Driver(void);
void Init_Load(void);

#endif
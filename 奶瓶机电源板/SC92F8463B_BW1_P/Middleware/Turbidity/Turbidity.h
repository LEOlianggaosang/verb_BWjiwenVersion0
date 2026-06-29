/**
 *******************************************************************************
 * Copyright (c) 2022
 *  
 * @file    Turbidity.c
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief   浊度控制
 * 
 *******************************************************************************
 */

#ifndef _TURBIDITY_H_
#define _TURBIDITY_H_

#include "AdDrv.h"
#include "user_define.h"
#include "product_config.h"

#if CONFIG_AUTO_WASH
extern USHORT_XDATA zhuodudianya;
void zhuodu_Read(void);
extern UCHAR_XDATA zhuodu_AdValue;

void Init_Turbidity(void);

#endif

#endif

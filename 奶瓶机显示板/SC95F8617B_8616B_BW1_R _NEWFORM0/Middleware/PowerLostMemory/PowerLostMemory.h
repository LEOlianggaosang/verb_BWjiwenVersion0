/**
 *******************************************************************************
  * Copyright (c) 2025.5.17
 * 
 * @file    PowerLostMemory.h
 * @author  lianggaosang@qq.com
 * @brief   掉电记忆控制
 *
 *******************************************************************************
 */
#ifndef _POWER_LOST_MEMORY_H_
#define _POWER_LOST_MEMORY_H_
#include "EepromDrv.h"
#include "product_config.h"

#define	    EEPROM_MAX_LENTH	32

extern UCHAR_XDATA Work_EEPROM_Datas[EEPROM_MAX_LENTH];

void Work_PowerDownDeal(bit memaryEnable);
void Recovery_Power_Lost_Memory(bit memaryEnable);
void Init_PowerLostMemory(void);
#endif
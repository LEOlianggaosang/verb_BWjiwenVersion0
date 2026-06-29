/**
 *******************************************************************************
 * Copyright (c) 2025.4.7
 * 
 * @file    IapAddrDevice.h
 * @author  lianggaosang@qq.com
 * @brief   循环使用EEPROM空间模块//20250403 SOC
 *
 *******************************************************************************
 */
#ifndef IAPADDRDEVICE_H
#define IAPADDRDEVICE_H
/*
 *------------------------------------------------------------------------------
 * include
 *------------------------------------------------------------------------------
 */
#include "EepromDrv.h"
#include "product_config.h"

#define IAP_SECTOR_NUM       12//可用扇区个数
#define IAP_SECTOR_SIZE      512//扇区大小
#define IAP_REMEBER_LOCETION 2//拓展地址
#define IAP_START_ADDRESS  0x0000


extern UCHAR_XDATA IapSectorCnt;

void IapAddrDevice_Init(void);

void Iap_Address_Device_Write(unsigned char *WByte, unsigned char NumByte);

void Iap_Address_Device_Read(unsigned char *WByte, unsigned char NumByte);

#endif
/**
 *******************************************************************************
 * Copyright (c) 2024.9.12
 *  
 * @file    EepromDrv.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _EEPROM_DRV_H_
#define _EEPROM_DRV_H_

#include "Hardware_Config.h"

extern void eepromSaveData(unsigned char *WByte, unsigned char NumByte);
extern void eepromRestoreData(unsigned char *dataPtr, unsigned char NumByte);

#endif //_EEPROM_DRV_H_

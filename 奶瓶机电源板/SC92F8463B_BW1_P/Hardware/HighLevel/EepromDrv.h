/**
 *******************************************************************************
 * Copyright (c) 20240614
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
#ifdef EEPROM_ENABLED
extern unsigned char eepromSaveData(unsigned char *WByte, unsigned char NumByte);
extern void eepromRestoreData(unsigned char *dataPtr, unsigned char NumByte);
#endif
#endif //_EEPROM_DRV_H_

/**
 *******************************************************************************
 * Copyright (c) 20240613
 *  
 * @file    EepromDrv.c
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "EepromDrv.h"
#ifdef EEPROM_ENABLED

unsigned char eepromSaveData(unsigned char *WByte, unsigned char NumByte)
{
#ifdef SC92F8463B_ENABLED
   return IAP_eepromSaveData(WByte, NumByte);
#endif
}

void eepromRestoreData(unsigned char *dataPtr, unsigned char NumByte)
{
#ifdef SC92F8463B_ENABLED
   IAP_eepromRestoreData(dataPtr, NumByte);
#endif
}
#endif

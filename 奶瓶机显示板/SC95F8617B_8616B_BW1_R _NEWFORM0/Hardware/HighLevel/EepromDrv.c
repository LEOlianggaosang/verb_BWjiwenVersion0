/**
 *******************************************************************************
 * Copyright (c) 2024.9.12
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
#include "product_config.h"
#if CONFIG_IAPADDR_DEVICE
#include "IapAddrDevice\IapAddrDevice.h"
#endif

void eepromSaveData(unsigned char *WByte, unsigned char NumByte)
{
#ifdef	SC95F8617_ENABLED	
   IAP_eepromSaveData(WByte, NumByte);
#endif
#ifdef SC95F8616B_ENABLED
   #if CONFIG_IAPADDR_DEVICE
      Iap_Address_Device_Write(WByte, NumByte);
   #else
      IAP_eepromSaveData(WByte, NumByte);
   #endif
#endif
}

void eepromRestoreData(unsigned char *dataPtr, unsigned char NumByte)
{
#ifdef	SC95F8617_ENABLED	
   IAP_eepromRestoreData(dataPtr, NumByte);
#endif
#ifdef SC95F8616B_ENABLED
   #if CONFIG_IAPADDR_DEVICE
      Iap_Address_Device_Read(dataPtr, NumByte);
   #else
      IAP_eepromRestoreData(dataPtr, NumByte);
   #endif
#endif
}

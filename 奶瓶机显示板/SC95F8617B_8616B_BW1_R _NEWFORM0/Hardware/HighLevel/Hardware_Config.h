/**
 *******************************************************************************
 * Copyright (c) 2025.4.26
 *  
 * @file    Hardware_Config.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _HARDWARE_CONFIG_H_
#define _HARDWARE_CONFIG_H_

/*
**-----------------------------------------------------------------------------
**
**-----------------------------------------------------------------------------
*/
//mcu selection
//#define     SC95F8616B_ENABLED
#include "product_config.h"
/*
**-----------------------------------------------------------------------------
**
**-----------------------------------------------------------------------------
*/
//devices selection
#define     TIMER_ENABLED
// #define     GPIO_ENABLED
#define     WATCHDOG_ENABLED
// #define     EXTERNAL_INT_ENABLED
// #define     AD_ENABLED
#define     SERIAL_ENABLED
#define     CONFIG_EEPROM_ENABLED
// #define     PCL_BUZZ_ENABLED
#define     LEDRAM_ENABLED

/*
**-----------------------------------------------------------------------------
**
**-----------------------------------------------------------------------------
*/
//include enabled mcu and device header file
#ifdef SC95F8616B_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\SC95F861xB_C.H"

#ifdef TIMER_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\Timer.h"
#endif //TIMER_ENABLED

#ifdef GPIO_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\Gpio.h"
#endif //GPIO_ENABLED

#ifdef WATCHDOG_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\Watchdog.h"
#endif //WATCHDOG_ENABLED

#ifdef EXTERNAL_INT_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\ExternalInterrupt.h"
#endif //EXTERNAL_INT_ENABLED

#ifdef SERIAL_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\Serial.h"
#endif //SERIAL_ENABLED

#ifdef CONFIG_EEPROM_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\IAP.h"
#endif //CONFIG_EEPROM_ENABLED

#ifdef AD_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\Ad.h"
#endif //AD_ENABLED

#ifdef PCL_BUZZ_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\PWM.h"
#endif //PCL_BUZZ_ENABLED

#ifdef LEDRAM_ENABLED
#include "..\LowLevel\SinOne\SC95F7617\devs\LedRam.h"
#endif //LEDRAM_ENABLED

#endif //SC95F8616B_ENABLED

#endif //_HARDWARE_CONFIG_H_

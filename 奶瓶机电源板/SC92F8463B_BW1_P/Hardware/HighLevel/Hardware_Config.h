/**
 *******************************************************************************
 * Copyright (c) 20250423
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

/*
**-----------------------------------------------------------------------------
**
**-----------------------------------------------------------------------------
*/
//devices selection
#define     TIMER_ENABLED
#define     GPIO_ENABLED
#define     WATCHDOG_ENABLED
#define     EXTERNAL_INT_ENABLED	
#define     AD_ENABLED
#define     PCL_BUZZ_ENABLED
#define     SERIAL_ENABLED
//#define     EEPROM_ENABLED


/*
**-----------------------------------------------------------------------------
**
**-----------------------------------------------------------------------------
*/

#ifdef SC92F8463B_ENABLED
#include "..\H\SC92F846xB_C.H"

#ifdef TIMER_ENABLED
#include "..\Hardware\LowLevel\SinOne\SC92F8463\devs\Timer.h"
//extern void Timer1msSub(void);//20240619
#endif //TIMER_ENABLED

#ifdef GPIO_ENABLED
#include "..\Hardware\LowLevel\SinOne\SC92F8463\devs\Gpio.h"
#endif //GPIO_ENABLED

#ifdef WATCHDOG_ENABLED
#include "..\Hardware\LowLevel\SinOne\SC92F8463\devs\Watchdog.h"
#endif //WATCHDOG_ENABLED

#ifdef EXTERNAL_INT_ENABLED
#include "..\Hardware\LowLevel\SinOne\SC92F8463\devs\ExternalInterrupt.h"
#endif //EXTERNAL_INT_ENABLED

#ifdef SERIAL_ENABLED
#include "..\Hardware\LowLevel\SinOne\SC92F8463\devs\Serial.h"
#endif //SERIAL_ENABLED

#ifdef EEPROM_ENABLED
#include "..\Hardware\LowLevel\SinOne\SC92F8463\devs\IAP.h"
#endif //EEPROM_ENABLED

#ifdef AD_ENABLED
#include "..\Hardware\LowLevel\SinOne\SC92F8463\devs\Ad.h"
#endif //AD_ENABLED

#ifdef PCL_BUZZ_ENABLED
#include "..\Hardware\LowLevel\SinOne\SC92F8463\devs\PWM.h"
#endif //PCL_BUZZ_ENABLED

#define CONFIG_FMCHECKTINER_ENABLED	1
#define CONFIG_ZEEROCROSS_ENABLED	0
#define CONFIG_WATERLEVEL_ENABLED	0
#define CONFIG_WATEROVERCHECK_ENABLED	0

#endif //SC92F8463B_ENABLED

#endif //_HARDWARE_CONFIG_H_

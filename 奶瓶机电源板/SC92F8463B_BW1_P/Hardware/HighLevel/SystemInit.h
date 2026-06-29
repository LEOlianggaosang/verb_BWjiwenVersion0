/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    SystemInit.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _SYSTEMINIT_H_
#define _SYSTEMINIT_H_

#include "GpioDrv.h"
#include "AdDrv.h"
#include "PclBuzDrv.h"
#include "TimerDrv.h"
#include "SystemDrv.h"
#include "SerialDrv.h"
//#include "EepromDrv.h"
#include "WatchdogDrv.h"
#include "ExternalIntDrv.h"

extern void SystemInit(void);

#endif //_SYSTEM_INIT_H_

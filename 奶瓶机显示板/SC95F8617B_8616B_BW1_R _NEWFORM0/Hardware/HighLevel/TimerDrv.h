/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    TimerDrv.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */
 
#ifndef _TIMER_DRV_H_
#define _TIMER_DRV_H_

#include "Hardware_Config.h"

typedef enum
{
   TIMER_1_MS,
   END_TIMER
}eTimerName;

extern void InitTimers(void);
extern void SetTimerCallback(eTimerName name, timer_callback func);
extern void StartTimer(eTimerName name);
extern void StopTimer(eTimerName name);
extern void ReloadTimer3(unsigned int count);
#endif //_TIMER_DRV_H_

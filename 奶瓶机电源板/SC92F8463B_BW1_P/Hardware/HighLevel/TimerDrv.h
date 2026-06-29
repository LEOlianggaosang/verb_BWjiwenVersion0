/**
 *******************************************************************************
 * Copyright (c) 20250423
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
   TIMER_IOUART,
   //TIMER_BUZZER,
   END_TIMER
}eTimerName;

extern void InitTimers(void);
extern void SetTimerCallback(eTimerName name, timer_callback func);
extern void StartTimer(eTimerName name);
extern void StopTimer(eTimerName name);
//*******************************************************************************
extern void sleep(UINT nops);
extern void delay(void);
//extern void delay_ms(UINT_XDATA ms);
//extern UINT_XDATA delay_ms_value;
#endif //_TIMER_DRV_H_

/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    TimerDrv.c
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
#include "TimerDrv.h"



Timer_InitTypeDef xdata tTimers[END_TIMER] = {
	#ifdef SC95F8616B_ENABLED
	{TIMER0, TIMER0_MODE_1, 32000, TIMER0_INPUT_FSYS, TIMER0_LOW_PRIORITY, 0},
	#endif
};

void SetTimerCallback(eTimerName name, timer_callback func)
{
	#ifdef SC95F8616B_ENABLED
	Timer_Set_Callback(tTimers[name].name, func);
	#endif
}

void InitTimers(void)
{
	int i = 0;
	#ifdef SC95F8616B_ENABLED
	for (i = 0; i < END_TIMER; i++)
	{
		Timer_Init(&tTimers[i]);
	}
	#endif
}

void StartTimer(eTimerName name)
{
	#ifdef SC95F8616B_ENABLED
	Timer_Start(tTimers[name].name);
	#endif
}

void StopTimer(eTimerName name)
{
	#ifdef SC95F8616B_ENABLED
	Timer_Stop(tTimers[name].name);
	#endif
}

void ReloadTimer3(unsigned int count)
{
	#ifdef SC95F8616B_ENABLED
	TM3_Reload(count);
	#endif
}

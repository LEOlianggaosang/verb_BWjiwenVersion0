/**
 *******************************************************************************
 * Copyright (c) 20250423
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
#include "Hardware_Config.h"
#include "product_config.h"
#include "TimerDrv.h"

#ifdef SC92F8463B_ENABLED
Timer_InitTypeDef tTimers[END_TIMER] = {
	{TIMER0, TIMER0_MODE_1, 1000, TIMER0_INPUT_FSYS_DIVIDE_12, TIMER0_LOW_PRIORITY, 0},
	{TIMER1, TIMER1_MODE_1, IOBAUD_VALUE, TIMER1_INPUT_FSYS_DIVIDE_12, TIMER1_LOW_PRIORITY, 0},//IOBAUD_VALUE
};
#endif

void SetTimerCallback(eTimerName name, timer_callback func)
{
	Timer_Set_Callback(tTimers[name].name, func);
}

void InitTimers(void)
{
	int i = 0;
#ifdef SC92F8463B_ENABLED
	for (i = 0; i < END_TIMER; i++)
	{
		Timer_Init(&tTimers[i]);
	}
#endif
}

void StartTimer(eTimerName name)
{
#ifdef SC92F8463B_ENABLED
	Timer_Start(tTimers[name].name);
#endif
}

void StopTimer(eTimerName name)
{
#ifdef SC92F8463B_ENABLED
	Timer_Stop(tTimers[name].name);
#endif
}

void sleep(UINT nops)
{
	UINT i;
	for(i=0;i<nops;i++)
	{
		NOP();
	}
}

void delay(void)
{
//	NOP();
//	NOP();
//	UCHAR_XDATA i;
//	for(i=0;i<5;i++);
	
}

//void delay_ms(UINT_XDATA ms)
//{
//	delay_ms_value = ms;
//	while(delay_ms_value);
//}
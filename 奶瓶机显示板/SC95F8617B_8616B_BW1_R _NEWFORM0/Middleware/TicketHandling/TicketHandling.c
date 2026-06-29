/**
 *******************************************************************************
 * Copyright (c) 2024.8.5
 *  
 * @file    TicketHandling.c
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
#include "TicketHandling.h"
/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
WordFlag Timer_Flags = {0};
/*
********************************************************************************
**  Static define
********************************************************************************
*/
static UCHAR Timer_Cnt1ms = 0;
//Base Tick 1ms
void TicketHandling(void)
{
	static UCHAR Timer_Cnt10ms_1ms = 0;
	static UCHAR Timer_Cnt100ms_1ms = 0;
	static UCHAR Time500ms_100ms = 0;
	static UCHAR Time1s_100ms = 0;

	F_Base1ms = 1;
	
	if(++Timer_Cnt10ms_1ms >= 10 ) 
	{
		Timer_Cnt10ms_1ms = 0;
		F_Base10ms = !F_Base10ms;
	}
	
	if(++Timer_Cnt100ms_1ms >= 100)
	{
		Timer_Cnt100ms_1ms = 0;
		F_Base100ms = !F_Base100ms;
		if(++Time500ms_100ms >= 5)
		{
			Time500ms_100ms = 0;
			F_Blink500ms = !F_Blink500ms;
		}
		if(++Time1s_100ms >= 10)
		{
			Time1s_100ms = 0;
			F_Base1s = !F_Base1s;
		}
	}
}

void Init_TicketHandling(void)
{
	SetTimerCallback(TIMER_1_MS, TicketHandling);
	StartTimer(TIMER_1_MS);
}

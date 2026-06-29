/**
 *******************************************************************************
 * Copyright (c) 20250117
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
#include "GpioDrv.h"
#include "TimerDrv.h"
#if (CONFIG_INT_CHECK&&NEWTYPE1)
#include "ExternalIntDrv.h"
#endif
#include "LoadDrive\LoadDrive.h"
#include "WashDish\WashDish.h"//F_InLetting//FlowMPreSecErrCnt
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
static unsigned char L_FlowScan = 0;
static void	FlowMScanSub(void);
#if (CONFIG_INT_CHECK&&NEWTYPE1)
static unsigned char L_FeedbackScan = 0;
static void	FeedbackSub(void);
static unsigned char L_FB100smCnt = 0;
static UCHAR_XDATA Feedback_100smCnt[10];
#endif

//Base Tick 1ms
void TicketHandling(void)
{
	static UCHAR Timer_Cnt10ms_1ms = 0;
	static UCHAR Timer_Cnt100ms_1ms = 0;
	static UCHAR Time500ms_100ms = 0;
	static UCHAR Time1s_100ms = 0;

	F_Base1ms = 1;
	FlowMScanSub();
	
	if(++Timer_Cnt10ms_1ms >= 10 ) 
	{
		Timer_Cnt10ms_1ms = 0;
		F_Base10ms = !F_Base10ms;
	}
	
	if(++Timer_Cnt100ms_1ms >= 100)
	{
		Timer_Cnt100ms_1ms = 0;
		F_Base100ms = !F_Base100ms;
		#if (CONFIG_INT_CHECK&&NEWTYPE1)
		FeedbackSub();
		#endif
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

#if (CONFIG_INT_CHECK&&NEWTYPE1)
//Base Int
void IntHandling(void)
{
	if(0==P07)
	{
		Flow_FlagBuf = 1;
	}
	else
	{
		if(Flow_FlagBuf)
		{
			L_FlowScan++; //INT23产生中断,上升沿触发
			Flow_FlagBuf = 0;
		}
	}

	if(0==P06)
	{
		Feedback_FlagBuf = 1;
	}
	else
	{
		if(Feedback_FlagBuf)
		{
			L_FeedbackScan++; //INT22产生中断,上升沿触发
			Feedback_FlagBuf = 0;
		}
	}
}

static void	FeedbackSub(void)
{
	static unsigned char i = 0;
	Feedback_100smCnt[L_FB100smCnt] = L_FeedbackScan;
	L_FeedbackScan = 0;

	if(++L_FB100smCnt >= 10)
	{
		L_FB100smCnt = 0;
	}

	FeedBackCnt = 0;
	for (i = 0; i < 10; i++)
	{
		FeedBackCnt += Feedback_100smCnt[i];
	}
}
#endif

static void FlowMScanSub(void)
{
	#if NEWTYPE1
		#if CONFIG_INT_CHECK
	if(L_FlowScan)
	{
		if(F_IsInLetting)
		{
			FlowMCnt+=L_FlowScan;
		}
		else if(!F_InLetMovement)
		{
			FlowMErrCnt+=L_FlowScan;
		}
		L_FlowScan = 0;
	}
		#else
    if(0 == P07)
    {
		Flow_FlagBuf = 1;
	}
	else
	{
		if(Flow_FlagBuf)
		{
			Flow_FlagBuf = 0;
			if(F_IsInLetting)
			{
				FlowMCnt++;
			}
			else if(!F_InLetMovement)
			{
				FlowMErrCnt++;
			}
		}
	}
		#endif
	#else
	if(0 == P05)
    {
		if(++L_FlowScan >= 2)
		{
			Flow_FlagBuf = 1;
		}
	}
	else
	{
		L_FlowScan = 0;
		if(Flow_FlagBuf)
		{
			Flow_FlagBuf = 0;
			if(F_IsInLetting)
			{
				FlowMCnt++;
			}
			else if(!F_InLetMovement)
			{
				FlowMErrCnt++;
			}
		}
	}
	#endif
}

void Init_TicketHandling(void)
{
	TimerFlag = 0;
	SetTimerCallback(TIMER_1_MS, TicketHandling);
	StartTimer(TIMER_1_MS);
	#if (CONFIG_INT_CHECK&&NEWTYPE1)
	SetEXIntCallback(FM_Int, IntHandling);//INT2初始化同时包含FM(INT23)与FB(INT22)
	StartEXInt(FM_Int);
	#endif
}
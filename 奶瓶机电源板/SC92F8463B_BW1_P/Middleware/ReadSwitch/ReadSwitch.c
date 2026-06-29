/**
 *******************************************************************************
 * Copyright (c) 20250117
 * 
 * @file    ReadSwitch.c
 * @author  lianggaosang@qq.com
 * @brief   开关状态控制 
 *
 *******************************************************************************
 */
#include "ReadSwitch.h"
#include "GpioDrv.h"
#include "TicketHandling\TicketHandling.h"
#include "WashDish\WashDish.h"//F_ErrIaqs//F_IaqsCntRelaod

/*
********************************************************************************
**  Static define
********************************************************************************
*/
// static unsigned char L_IssCnt, L_InputCnt, L_IaqsCnt, L_DoorCnt, L_IsbCnt, L_PreCnt;
// static unsigned char Iaqs2s_10ms = 0;
static unsigned char L_InputCnt, L_DoorCnt;
/*
********************************************************************************
**  Global define
********************************************************************************
*/
ByteFlag Switch_Flags = {0};

void Init_Switch(void)
{
	SwitchFlag = 0;
}

void Read_Switch(void)
{
		if (Read_Timer10ms != F_Base10ms)
		{
			Read_Timer10ms = F_Base10ms;

			// if(GetPin(IAQS))
			// {
			// 	++L_IaqsCnt;//低电平断路-高电平短路溢流
			// }

			// if(GetPin(SALT))
			// {
			// 	++L_IssCnt;//高电平断路-低电平短路缺盐
			// }
			
			// if(GetPin(RINS))
			// {
			// 	++L_IsbCnt;//高电平断路-低电平短路缺剂
			// }
			
			if(GetPin(DOOR))
			{
				++L_DoorCnt;//高电平断路开门-低电平短路
			}
			
			// if(GetPin(PRE))
			// {
			// 	++L_PreCnt;//高电平断路
			// }

			if(++L_InputCnt >= C_TOTAL_CNT)
			{
				// if(L_IssCnt >= C_HIGH_CNT)
				// {
				// 	Signal_IssSwitch = 0;
				// }
				// else if(L_IssCnt <= C_LOW_CNT)
				// {
				// 	Signal_IssSwitch = 1;						//lack salt
				// }

				// if(L_IsbCnt >= C_HIGH_CNT)
				// {
				// 	Signal_IsbSwitch = 0;
				// }
				// else if(L_IsbCnt <= C_LOW_CNT)
				// {
				// 	Signal_IsbSwitch = 1;						//lack Rins
				// }

				if(L_DoorCnt >= C_HIGH_CNT)
				{
					Signal_DoorSwitch = 1;					//Door Switch
				}
				else if(L_DoorCnt <= C_LOW_CNT)
				{
					Signal_DoorSwitch = 0;					
				}

				// if(L_PreCnt >= C_HIGH_CNT)
				// {
				// 	Signal_PreSwitch = 0;
				// }
				// else if(L_PreCnt <= C_LOW_CNT)
				// {
				// 	Signal_PreSwitch = 1;								
				// }
				
				// if(L_IaqsCnt >= C_HIGH_CNT)
				// {
				// 	Signal_IaqsSwitch = 1;					//Over Flow
				// }
				// else if(L_IaqsCnt <= C_LOW_CNT)
				// {
				// 	Signal_IaqsSwitch = 0;								
				// }

				// L_InputCnt = L_IssCnt = L_IsbCnt  = L_DoorCnt  = L_PreCnt = L_IaqsCnt = 0;
				L_InputCnt = L_DoorCnt = 0;
			}
			
			// if(F_IaqsCntRelaod)
			// {
			// 	Iaqs2s_10ms = 0;
			// 	Signal_ErrIaqs = 0;//20250328 2s
			// }
			// else
			// {
			// 	if(Signal_IaqsSwitch)
			// 	{
			// 		if(++Iaqs2s_10ms >= 200)
			// 		{
			// 			Iaqs2s_10ms = 0;
			// 			Signal_ErrIaqs = 1;
			// 		}
			// 	}
			// 	else
			// 	{
			// 		Signal_ErrIaqs = 0;
			// 		Iaqs2s_10ms = 0;
			// 	}
			// }
		}

}

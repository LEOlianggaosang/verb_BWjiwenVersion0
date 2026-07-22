	/**
 *******************************************************************************
 * Copyright (c) 2025.5.12
 * 
 * @file    Key.c
 * @author  lianggaosang@qq.com
 * @brief   8616b奶瓶机显示板
 *
 *******************************************************************************
 */

/* Includes head files ------------------------------------------------------ */
#include "Key.h"

#include "Display\Display.h"
#include "TicketHandling\TicketHandling.h"
#include "Power\Power.h"
#include "Work\Work.h"
#include "ErrorHandling\Error.h"
/* Macro define ------------------------------------------------------------- */
/* Variables define --------------------------------------------------------- */
static UCHAR_XDATA Key_Code_Buf = 0;
static KeyActionType Key_ActionType_Buf = KEY_ACTION_LEAVE;
UCHAR_XDATA FctKeyCnt = 0;
UCHAR_XDATA TestKeyCnt = 0;
#if NEWTPE1
WordFlag TestKeyAction_Flags = {0};
WordFlag FctKeyAction_Flags = {0};
#else
WordFlag TestKeyAction_Flags = {0};
WordFlag FctKeyAction_Flags = {0};
#endif
/* Function define ---------------------------------------------------------- */
static void Key_MonitorAction(void);
static void Fct_MonitorAction(void);
static void SetTestStage(UCHAR stage);
#if CONFIG_DISPLAY_DEBUG
static void Key_Debug(void);
#endif
#if CONFIG_POWER_TEST//20260509
#include "Light\Light.h"
static void Key_PowerTest(void);
#endif
/* Void --------------------------------------------------------- */
void Init_Key(void)
{
	Key_Code_Buf = Key_Code = 0;
	Key_ActionType_Buf = Key_ActionType = KEY_ACTION_LEAVE;
}

/* Monitor the key action and call the key action deal function */
void Key_Control(void)
{
	TK_ReadValue();

	if((Key_Code != Key_Code_Buf)||(Key_ActionType != Key_ActionType_Buf))
	{
		Key_Code_Buf = Key_Code;
		Key_ActionType_Buf = Key_ActionType;
		#if CONFIG_POWER_TEST//20260509
		Key_PowerTest();
		#else
		if(Fcting)
		{
			Work_KeyboardIsLocked = 0;
			Fct_MonitorAction();
		}
		else if(Power_IsCommunicating)
		{
			#if CONFIG_LOCK_ENABLE
			if(Work_KeyboardIsLocked)
			{
				if(KEY_LOCK&&KEY_ACT_LONG)
				{
					Work_KeyboardIsLocked = 0;
					BeepState = BUZZ_KEY_VALID;
					Key_ActionType = KEY_ACTION_RELEASING;
				}
			}
			else
			#endif
			{
				Key_MonitorAction();
			}
		}
		#endif
	}
}

static void Key_MonitorAction(void)
{
	switch(Work_CurrentState)
	{
		case STATE_POWER:
			if(KEY_POWER&&KEY_ACT_LONG)
			{
				Work_GotoStandbyInit = MD_TRUE;
				Key_ActionType = KEY_ACTION_RELEASING;
			}

			//! NEWFORM1 #3-3 检测功能冲突
			#if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
			if(Test_WaitKeyActionCount>0)
			{
				if(KEY_TEST&&KEY_ACT_LONG)
				{
					Work_CurrentState  = STATE_TESTING;
					BeepState = BUZZ_ENTERCHECK;
					Test_CurrentOption = TEST_1;
				}
			}
			#endif
			break;
		/* --------------------------------------------------------- */
		case STATE_DRAIN:
			//! NEWFORM1 #3-2 参数显示功能冲突
			// #if (CONFIG_EXTRA_INFORMATION&&NEWTPE1)
			// //20251105 1、增加特殊数据显示按键调试功能
			// if(KEY_SELFCLEAN&&KEY_ACT_SHORT)
			// {
			// 	Work_ClosePowerInit	= MD_TRUE;
			// }
			// else
			// #endif
			if((!KEY_NULL)&&(KEY_ACT_SHORT||KEY_ACT_LONG))
			{
				BeepState = BUZZ_KEY_INVALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			break;
		/* --------------------------------------------------------- */
		case STATE_STANDBY:
			if(KEY_POWER&&KEY_ACT_LONG)
			{
				#if NEWFORM0//20251110 NEWFORM0 8.2
				Work_ClosePowerInit	= MD_TRUE;
				#else
				Work_CurrentState  = STATE_DRAIN;
				DrainCnt = 0;
				#endif
				BeepState = BUZZ_KEY_VALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			//! NEWFORM1 #4-1 待机按键直接切换程序，无法更改叠加功能
			if(Test_WaitKeyActionCount>0)
			{//20251011 厂测模式
				if(KEY_TEST&&KEY_ACT_LONG)
				{
					Work_CurrentState  = STATE_TESTING;
					BeepState = BUZZ_ENTERCHECK;
					Test_CurrentOption = TEST_1;
					Key_ActionType = KEY_ACTION_RELEASING;
				}
			}
			
			if(KEY_FAST&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				BeepState = BUZZ_KEY_VALID;
				Work_CurrentMenu  = MENU_FAST;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			else
			if(KEY_STANDARD&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				BeepState = BUZZ_KEY_VALID;
				Work_CurrentMenu  = MENU_STANDARD;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			else
			if(KEY_STEAM&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				BeepState = BUZZ_KEY_VALID;
				Work_CurrentMenu  = MENU_STEAM;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			else
			if(KEY_DRY&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				BeepState = BUZZ_KEY_VALID;
				Work_CurrentMenu  = MENU_DRY;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			else
			if(KEY_START&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				//! NEWFORM1 #1-2 启动判断开门
				if(Power_DoorIsOpend)
				{
					BeepState = BUZZ_KEY_INVALID;
				}
				else
				{
					BeepState = BUZZ_KEY_VALID;
					Work_IsSteamMode = 0;//只能运行更改
					Work_IsDryMode = 1;//无法更改
					Work_SaveMode = 1;//只能运行更改
					ight_IsWorking = 0;//无法更改
					Work_InletMode = 0;//无法更改
					Work_DoorOpenDelaySecondCount = 1;
					Work_CurrentState  = STATE_WASHING;
					Work_NextStepHandler  = Work_NextStep;
					Work_CurrentStep = 0;
					Work_NextStep();
				}
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			//! 
			// //! NEWFORM1 #3-3 检测功能冲突
			// #if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
			// if(Test_WaitKeyActionCount>0)
			// {//20251011 厂测模式
			// 	if(KEY_TEST&&KEY_ACT_LONG)
			// 	{
			// 		Work_CurrentState  = STATE_TESTING;
			// 		BeepState = BUZZ_ENTERCHECK;
			// 		Test_CurrentOption = TEST_1;
			// 	}
			// }
			// #endif
			// 
			// if(KEY_FAST&&KEY_ACT_SHORT)
			// {
			// 	BeepState = BUZZ_KEY_VALID;
			// 	//! NEWFORM1 #3-3 检测功能冲突
			// 	#if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
			// 	if(MENU_FAST == Work_CurrentMenu)
			// 	{
			// 		Work_CurrentMenu  = MENU_NULL;
			// 	}
			// 	else
			// 	#endif
			// 	{
			// 		Work_CurrentMenu  = MENU_FAST;
			// 	}
			// }
			// 
			// if(KEY_STANDARD&&KEY_ACT_SHORT)
			// {
			// 	BeepState = BUZZ_KEY_VALID;
			// 	//! NEWFORM1 #3-3 检测功能冲突
			// 	#if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
			// 	if(MENU_STANDARD == Work_CurrentMenu)
			// 	{
			// 		Work_CurrentMenu  = MENU_NULL;
			// 	}
			// 	else
			// 	#endif
			// 	{
			// 		Work_CurrentMenu  = MENU_STANDARD;
			// 	}
			// }
			// 
			// //! NEWFORM1 #3-3 检测功能冲突
			// #if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
			// if(KEY_STEAM&&KEY_ACT_SHORT)
			// {
			// 	if(MenuList[Work_CurrentMenu].steamModeEnable)
			// 	{
			// 		Work_IsSteamMode = !Work_IsSteamMode;
			// 		BeepState = BUZZ_KEY_VALID;
			// 	}
			// 	else
			// 	{
			// 		BeepState = BUZZ_KEY_INVALID;
			// 	}
			// }
			// 
			// if(KEY_DRY&&KEY_ACT_SHORT)
			// {
			// 	if(MenuList[Work_CurrentMenu].dryModeEnable)
			// 	{
			// 		Work_IsDryMode = !Work_IsDryMode;
			// 		BeepState = BUZZ_KEY_VALID;
			// 	}
			// 	else
			// 	{
			// 		BeepState = BUZZ_KEY_INVALID;
			// 	}
			// }
			// #endif
			// 
			//! NEWFORM1 #3-1 屏蔽按键
			// #if NEWTPE1
			// if(KEY_LIGHT&&KEY_ACT_SHORT)
			// {
			// 	BeepState = BUZZ_KEY_VALID;
			// 	Light_IsWorking = !Light_IsWorking;
			// }
			// 
			// if(KEY_SELFCLEAN&&KEY_ACT_SHORT)
			// {
			// 	BeepState = BUZZ_KEY_VALID;
			//! NEWFORM1 #3-3 检测功能冲突
			// 	#if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
			// 	if(MENU_SELFCLEAN == Work_CurrentMenu)
			// 	{
			// 		Work_CurrentMenu  = MENU_NULL;
			// 	}
			// 	else
			// 	#endif
			// 	{
			// 		Work_CurrentMenu  = MENU_SELFCLEAN;
			// 	}
			// }
			// #else
			// if(KEY_INLET&&KEY_ACT_SHORT)
			// {
			// 	BeepState = BUZZ_KEY_VALID;
			// 	Work_InletMode = !Work_InletMode;
			// }
			// #endif
			// 
			// if(KEY_START&&KEY_ACT_SHORT)
			// {
			// 	//! NEWFORM1 #3-3 检测功能冲突
			// 	#if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
			// 	if(MENU_NULL == Work_CurrentMenu)
			// 	{
			// 		if(Work_IsSteamMode)
			// 		{
			// 			//Work_IsPaused = Power_DoorIsOpend;//20251110 NEWFORM0	4、
			// 			Work_DoorOpenDelaySecondCount = 1;//20251110 NEWFORM0 4、
			// 			Work_CurrentState  = STATE_WASHING;
			// 			Work_CurrentMenu = MENU_STEAM;
			// 			Work_IsSteamMode = 0;
			// 			BeepState = BUZZ_KEY_VALID;
			// 			Work_NextStepHandler  = Work_NextStep;
			// 			Work_CurrentStep = 0;
			// 			Work_NextStep();
			// 			// Work_MemoryWrite = MD_TRUE;//20251110 NEWFORM0 3、
			// 		}
			// 		else if(Work_IsDryMode)
			// 		{
			// 			//Work_IsPaused = Power_DoorIsOpend;//20251110 NEWFORM0 4、
			// 			Work_DoorOpenDelaySecondCount = 1;//20251110 NEWFORM0 4、
			// 			Work_CurrentState  = STATE_WASHING;
			// 			Work_CurrentMenu = MENU_DRY;
			// 			Work_IsDryMode = 0;
			// 			BeepState = BUZZ_KEY_VALID;
			// 			Work_NextStepHandler  = Work_NextStep;
			// 			Work_CurrentStep = 0;
			// 			Work_NextStep();
			// 			// Work_MemoryWrite = MD_TRUE;//20251110 NEWFORM0 3、
			// 		}
			// 		else
			// 		{
			// 			BeepState = BUZZ_KEY_INVALID;
			// 		}
			// 	}
			// 	else 
			// 	#endif
			// 	if(MENU_FAST == Work_CurrentMenu)
			// 	{
			// 		//Work_IsPaused = Power_DoorIsOpend;//20251110 NEWFORM0 4、
			// 		Work_DoorOpenDelaySecondCount = 1;//20251110 NEWFORM0 4、
			// 		Work_CurrentState  = STATE_WASHING;
			// 		BeepState = BUZZ_KEY_VALID;
			// 		Work_NextStepHandler  = Work_NextStep;
			// 		Work_CurrentStep = 0;
			// 		Work_NextStep();
			// 		// Work_MemoryWrite = MD_TRUE;//20251110 NEWFORM0 3、
			// 	}
			// 	//! NEWFORM1 #3-3 检测功能冲突
			// 	#if (0 == CONFIG_IQC_TEST)//20260117
			// 	else if(MENU_STANDARD == Work_CurrentMenu)
			// 	{
			// 		//Work_IsPaused = Power_DoorIsOpend;//20251110 NEWFORM0 4、
			// 		Work_DoorOpenDelaySecondCount = 1;//20251110 NEWFORM0 4、
			// 		Work_CurrentState  = STATE_WASHING;
			// 		BeepState = BUZZ_KEY_VALID;
			// 		Work_NextStepHandler  = Work_NextStep;
			// 		Work_CurrentStep = 0;
			// 		Work_NextStep();
			// 		// Work_MemoryWrite = MD_TRUE;//20251110 NEWFORM0 3、
			// 	}
			// 	#endif
			//! NEWFORM1 #3-1 屏蔽按键
			// #if NEWTPE1
			// else if(MENU_SELFCLEAN == Work_CurrentMenu)
			// {
			// 	//Work_IsPaused = Power_DoorIsOpend;//20251110 NEWFORM0 4、
			// 	Work_DoorOpenDelaySecondCount = 1;//20251110 NEWFORM0 4、
			// 	Work_CurrentState  = STATE_WASHING;
			// 	BeepState = BUZZ_KEY_VALID;
			// 	Work_NextStepHandler  = Work_NextStep;
			// 	Work_CurrentStep = 0;
			// 	Work_NextStep();
			// 	// Work_MemoryWrite = MD_TRUE;//20251110 NEWFORM0 3、
			// }
			// #endif
			// }
			break;
		/* --------------------------------------------------------- */
		case STATE_WASHING:
			//! NEWFORM1 #4-1 烘干菜单特有分支：关机不强排，无法取消保管
			//! 增加按键无效提示，取消按键改变叠加功能更新总时间
			//! 蒸汽阶段前可配置叠加蒸汽,保管前可配置叠加保管
			if(KEY_POWER&&KEY_ACT_LONG)
			{
				if(MENU_DRY == Work_CurrentMenu)
				{
					Work_ClosePowerInit	= MD_TRUE;
				}
				else
				{
					Work_CurrentState  = STATE_DRAIN;
					DrainCnt = 0;
				}
				BeepState = BUZZ_KEY_VALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			else
			if((KEY_FAST||KEY_STANDARD)&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				BeepState = BUZZ_KEY_INVALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			else
			if(KEY_STEAM&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				if((Work_CurrentStage < STAGE_STEAM)&&(MenuList[Work_CurrentMenu].steamModeEnable))
				{
					BeepState = BUZZ_KEY_VALID;
					Work_IsSteamMode = !Work_IsSteamMode;
					Key_ActionType = KEY_ACTION_RELEASING;
				}
				else
				{
					BeepState = BUZZ_KEY_INVALID;
					Key_ActionType = KEY_ACTION_RELEASING;
				}
			}
			else
			if(KEY_DRY&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				if((Work_CurrentStage < STAGE_COMPLETE)&&(MenuList[Work_CurrentMenu].dryModeEnable))
				{
					BeepState = BUZZ_KEY_VALID;
					Work_SaveMode = !Work_SaveMode;
					Key_ActionType = KEY_ACTION_RELEASING;
				}
				else
				{
					BeepState = BUZZ_KEY_INVALID;
					Key_ActionType = KEY_ACTION_RELEASING;
				}
			}
			else
			if(KEY_START&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				BeepState = BUZZ_KEY_VALID;
				Work_IsPaused = !Work_IsPaused;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			//!
			// if(KEY_POWER&&KEY_ACT_LONG)
			// {
			// 	Work_CurrentState  = STATE_DRAIN;
			// 	DrainCnt = 0;
			// 	BeepState = BUZZ_KEY_VALID;
			// 	Key_ActionType = KEY_ACTION_RELEASING;
			// }
			// //! NEWFORM1 #3-3 检测功能冲突
			// #if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
			// if(KEY_STEAM&&KEY_ACT_SHORT)
			// {
			// 	if((Work_CurrentStage < STAGE_STEAM)&&(MenuList[Work_CurrentMenu].steamModeEnable))
			// 	{
			// 		BeepState = BUZZ_KEY_VALID;
			// 		if(Work_IsSteamMode)
			// 		{
			// 			Work_IsSteamMode = 0;
			// 			Work_LeftMinToEnd -= Work_StageStartTimeMode[(UCHAR)MENU_STEAM][Work_CurrentStage];
			// 		}
			// 		else
			// 		{
			// 			Work_IsSteamMode = 1;
			// 			Work_LeftMinToEnd += Work_StageStartTimeMode[(UCHAR)MENU_STEAM][Work_CurrentStage];
			// 		}
			// 	}
			// 	else
			// 	{
			// 		BeepState = BUZZ_KEY_INVALID;
			// 	}
			// }
			// if(KEY_DRY&&KEY_ACT_SHORT)
			// {
			// 	if((Work_CurrentStage < STAGE_DRY)&&(MenuList[Work_CurrentMenu].dryModeEnable))
			// 	{
			// 		BeepState = BUZZ_KEY_VALID;
			// 		if(Work_IsDryMode)
			// 		{
			// 			Work_IsDryMode = 0;
			// 			Work_LeftMinToEnd -= Work_StageStartTimeMode[(UCHAR)MENU_DRY][Work_CurrentStage];
			// 			if(Work_TempCompensation)
			// 			{
			// 				Work_LeftMinToEnd -= 10;
			// 			}
			// 		}
			// 		else
			// 		{
			// 			Work_IsDryMode = 1;
			// 			Work_LeftMinToEnd += Work_StageStartTimeMode[(UCHAR)MENU_DRY][Work_CurrentStage];
			// 			if(Work_TempCompensation)
			// 			{
			// 				Work_LeftMinToEnd += 10;
			// 			}
			// 		}
			// 	}
			// 	else
			// 	{
			// 		BeepState = BUZZ_KEY_INVALID;
			// 	}
			// }
			// #endif
			// if(KEY_START&&KEY_ACT_SHORT)
			// {
			// 	BeepState = BUZZ_KEY_VALID;
			// 	Work_IsPaused = !Work_IsPaused;
			// }
			// //! NEWFORM1 #3-1 屏蔽按键
			// #if NEWTPE1
			// if(KEY_LIGHT&&KEY_ACT_SHORT)
			// {
			// 	BeepState = BUZZ_KEY_VALID;
			// 	Light_IsWorking = !Light_IsWorking;
			// }
			// #endif
			break;
		/* --------------------------------------------------------- */
		case STATE_ERROR:
			if(KEY_POWER&&KEY_ACT_LONG)
			{
				Error_CurrentCode = ERROR_NULL;//20251110 NEWFORM0 6、
				Work_CurrentState = STATE_DRAIN;
				DrainCnt = 0;
				BeepState = BUZZ_KEY_VALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			//! NEWFORM1 #4-1 增加无效音
			if(KEY_START&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				if(Inlet_Lack)
				{
					BeepState = BUZZ_KEY_VALID;
					Inlet_Lack = 0;
					Key_ActionType = KEY_ACTION_RELEASING;
				}
				else
				{
					BeepState = BUZZ_KEY_INVALID;
					Key_ActionType = KEY_ACTION_RELEASING;
				}
			}
			else
			if((KEY_FAST||KEY_STANDARD||KEY_STEAM||KEY_DRY)&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				BeepState = BUZZ_KEY_INVALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			break;
		/* --------------------------------------------------------- */
		case STATE_FINISHED:
			//! NEWFORM1 #4-1 增加无效音，结束无法操作自动退出
			if((!KEY_NULL)&&(KEY_ACT_SHORT||KEY_ACT_LONG))
			{
				// Work_GotoStandbyInit = MD_TRUE;
				// BeepState = BUZZ_KEY_VALID;
				BeepState = BUZZ_KEY_INVALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			break;
		/* --------------------------------------------------------- */
		case STATE_SAVING:
			if(KEY_POWER&&KEY_ACT_LONG)
			{
				#if NEWFORM0//20251110 NEWFORM0 8.2
				Work_ClosePowerInit	= MD_TRUE;
				#else
				Work_CurrentState  = STATE_DRAIN;
				DrainCnt = 0;
				#endif
				BeepState = BUZZ_KEY_VALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			//! NEWFORM1 #4-1 增加无效音，无法暂停，只对开门反应
			if((KEY_FAST||KEY_STANDARD||KEY_STEAM||KEY_DRY||KEY_START)&&(KEY_ACT_LONG||KEY_ACT_SHORT))
			{
				BeepState = BUZZ_KEY_INVALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}
			// #if (0==NEWFORM0)//20251110 NEWFORM0 8.3(20251127 更改)
			// if(KEY_START&&KEY_ACT_SHORT)
			// {//20250929
			// 	BeepState = BUZZ_KEY_VALID;
			// 	Work_IsPaused = !Work_IsPaused;
			// }
			// #endif
			//! NEWFORM1 #3-1 屏蔽按键
			// #if NEWTPE1
			// if(KEY_LIGHT&&KEY_ACT_SHORT)
			// {//20251010
			// 	BeepState = BUZZ_KEY_VALID;
			// 	Light_IsWorking = !Light_IsWorking;
			// }
			// #endif
			break;
		/* --------------------------------------------------------- */
		case STATE_TESTING://20251011 厂测模式
			if(KEY_POWER&&KEY_ACT_LONG)
			{
				Work_CurrentState = STATE_DRAIN;
				DrainCnt = 0;
				BeepState = BUZZ_KEY_VALID;
				Key_ActionType = KEY_ACTION_RELEASING;
			}

			if(Test_Entered)
			{
				#if CONFIG_TESTENTER_CHECK
				if(Key_TestEnter)
				{//显示按键测试模式，数码管显示按键数，所有按键灭后正式进入厂测模式
					if(KEY_FAST && KEY_ACT_SHORT && Key_FastMune)
					{
						BeepState = BUZZ_KEY_VALID;
						Key_FastMune = 0;
						TestKeyCnt++;
					}

					if(KEY_STANDARD && KEY_ACT_SHORT && Key_SrandardMune)
					{
						BeepState = BUZZ_KEY_VALID;
						Key_SrandardMune = 0;
						TestKeyCnt++;
					}

					if(KEY_STEAM && KEY_ACT_SHORT && Key_SteamFunc)
					{
						BeepState = BUZZ_KEY_VALID;
						Key_SteamFunc = 0;
						TestKeyCnt++;
					}

					if(KEY_DRY && KEY_ACT_SHORT && Key_DryFunc)
					{
						BeepState = BUZZ_KEY_VALID;
						Key_DryFunc = 0;
						TestKeyCnt++;
					}
					
					//! NEWFORM1 #3-1 按键取消
					// if(KEY_INLET && KEY_ACT_SHORT && Key_InletCommand)
					// {
					// 	BeepState = BUZZ_KEY_VALID;
					// 	Key_InletCommand = 0;
					// 	TestKeyCnt++;
					// }
					// #if NEWTPE1
					// if(KEY_SELFCLEAN && KEY_ACT_SHORT && Key_SelfCleanMune)
					// {
					// 	BeepState = BUZZ_KEY_VALID;
					// 	Key_SelfCleanMune = 0;
					// 	TestKeyCnt++;
					// }
					// #endif

					if(KEY_START && KEY_ACT_SHORT && Key_StartCommand)
					{
						BeepState = BUZZ_KEY_VALID;
						Key_StartCommand = 0;
						TestKeyCnt++;
					}

					if(KEY_POWER && KEY_ACT_SHORT && Key_PowerCommand)
					{
						BeepState = BUZZ_KEY_VALID;
						Key_PowerCommand = 0;
						TestKeyCnt++;
					}
				}
				else
				#endif
				{//正式进入厂测模式，跳步与暂停
					//! NEWFORM1 #4-1 按键更改
					if((KEY_STEAM||KEY_STANDARD)&&KEY_ACT_SHORT)
					// if((KEY_DRY||KEY_STANDARD)&&KEY_ACT_SHORT)
					{//下一步
						if((Test_CurrentStage>0)&&(Test_CurrentStage<Test_MaxStage))
						{
							BeepState = BUZZ_KEY_VALID;
							if(KEY_STANDARD)
							{//上一步
								SetTestStage(Test_CurrentStage - 1);
							}
							else
							{
								SetTestStage(Test_CurrentStage + 1);
							}
						}
						else
						{
							BeepState = BUZZ_KEY_INVALID;
						}
					}
					
					if(KEY_START&&KEY_ACT_SHORT)
					{
						BeepState = BUZZ_KEY_VALID;
						Work_IsPaused = !Work_IsPaused;
					}
					//! NEWFORM1 #3-1 按键取消
					// //20251110 NEWFORM0 13.4 20251127 更改
					// #if NEWTPE1
					// if(KEY_LIGHT&&KEY_ACT_SHORT)
					// {//20251010
					// 	BeepState = BUZZ_KEY_VALID;
					// 	Light_IsWorking = !Light_IsWorking;
					// }
					// #else
					// if(KEY_INLET&&KEY_ACT_SHORT)
					// {
					// 	BeepState = BUZZ_KEY_VALID;
					// 	Work_InletMode = !Work_InletMode;
					// }
					// #endif

				}
			}
			else
			{//进入厂测后先显示版本号，短按启动后进入显示按键测试模式，同时恢复出厂设置
				if(KEY_START&&KEY_ACT_SHORT)
				{
					BeepState = BUZZ_KEY_VALID;
					#if CONFIG_TESTENTER_CHECK
					Key_TestEnter = Key_FastMune = Key_SrandardMune = Key_SteamFunc = Key_DryFunc = Key_StartCommand = Key_PowerCommand = 1;
					//! NEWFORM1 #3-1 按键取消
					// Key_TestEnter = Key_FastMune = Key_SrandardMune = Key_SteamFunc = Key_DryFunc = Key_InletCommand = Key_StartCommand = Key_PowerCommand = 1;
					// #if NEWTPE1
					// Key_SelfCleanMune = 1;
					// #endif
					#endif
					Test_Entered = 1;
					TestKeyCnt = 0;
					//恢复出厂设置
					//! NEWFORM1 #2-1 保管标志位初始化
					Work_SaveMode = 1;
					Work_CurrentMenu = Work_LastMenu = INIT_MENU;
					Work_IsDryMode = 1;
					Work_IsSteamMode = 0;
					Work_InletMode = Light_IsWorking = 0;	
					// Work_IsDryMode = Work_IsSteamMode = 1;
					// Work_InletMode = 0;
					// Light_IsWorking = 1;
					//! NEWFORM1 #2-2 屏蔽写动作
					// Work_MemoryWrite = 1;
				}
			}
			break;
		default://STATE_RESET
			break;
	}
}

static void SetTestStage(UCHAR stage)
{//20251011 厂测模式
	do
	{
		if(Test_CurrentStage>stage)
		{
			Test_CurrentStep-=2;
		}
		Test_NextStep();
	}while ((Test_CurrentStage != stage)&&(Test_CurrentStage>0)&&(Test_CurrentStage<Test_MaxStage));
}

static void Fct_MonitorAction(void)
{
	if(KEY_FAST&&KEY_ACT_SHORT)
	{
		BeepState = BUZZ_KEY_VALID;
		FctKeyCnt = 0;
		FctActionFlag = 0;
		Fcting = 1;
		Fct_FastMune = 1;
	}
	if(KEY_POWER&&KEY_ACT_SHORT)
	{
		BeepState = BUZZ_KEY_VALID;
		FctKeyCnt = 0;
		FctActionFlag = 0;
		Fcting = 1;
		Fct_PowerCommand = 1;
	}
	if(KEY_STEAM&&KEY_ACT_SHORT)
	{
		BeepState = BUZZ_KEY_VALID;
		FctKeyCnt = 0;
		FctActionFlag = 0;
		Fcting = 1;
		Fct_SteamFunc = 1;
	}
	//! NEWFORM1 #3-1 按键取消
	// #if NEWTPE1
	// if(KEY_SELFCLEAN&&KEY_ACT_SHORT)
	// {
	// 	BeepState = BUZZ_KEY_VALID;
	// 	FctKeyCnt = 0;
	// 	FctActionFlag = 0;
	// 	Fcting = 1;
	// 	Fct_SelfCleanMune = 1;
	// }
	// #endif
	// if(KEY_INLET&&KEY_ACT_SHORT)
	// {
	// 	BeepState = BUZZ_KEY_VALID;
	// 	FctKeyCnt = 0;
	// 	FctActionFlag = 0;
	// 	Fcting = 1;
	// 	Fct_InletCommand = 1;
	// }
	if(KEY_STANDARD&&KEY_ACT_SHORT)
	{
		BeepState = BUZZ_KEY_VALID;
		FctKeyCnt = 0;
		FctActionFlag = 0;
		Fcting = 1;
		Fct_SrandardMune = 1;
	}
	if(KEY_DRY&&KEY_ACT_SHORT)
	{
		BeepState = BUZZ_KEY_VALID;
		FctKeyCnt = 0;
		FctActionFlag = 0;
		Fcting = 1;
		Fct_DryFunc = 1;
	}
	if(KEY_START&&KEY_ACT_SHORT)
	{
		BeepState = BUZZ_KEY_VALID;
		FctKeyCnt = 0;
		FctActionFlag = 0;
		Fcting = 1;
		Fct_StartCommand = 1;
	}
}

#if CONFIG_POWER_TEST//20260509
static void Key_PowerTest(void)
{
	static bit Buf_Led_Light = 0;
	#if NEWTPE1
	if(KEY_POWER&&KEY_ACT_SHORT)
	{//开关键//20260702
		BeepState = BUZZ_POWERON;
		if(F_Led_Power)
		{
			F_Led_Power = 0;
		}
		else
		{
			Trant_LED_Index(DIGITAL_ALL_OFF);
			Trant_LED_Index(LED_ALL_OFF);
			F_Led_Power = 1;
		}
	}

	if(KEY_START&&KEY_ACT_SHORT&&(!F_Led_Power))
	{//启动键//20260702
		BeepState = BUZZ_KEY_VALID;
		F_Led_Start = !F_Led_Start;
	}

	if(KEY_SELFCLEAN&&KEY_ACT_SHORT&&(!F_Led_Power))
	{//进水键
		if(!(F_Led_Light&&(F_Led_Fast||F_Led_Srandard||F_Led_Sterilize||F_Led_Save)))
		{//功能键自锁
			BeepState = BUZZ_KEY_VALID;
			F_Lack = F_Led_SelfClean = !F_Led_SelfClean;
		}
	}

	if(KEY_FAST&&KEY_ACT_SHORT&&(!F_Led_Power))
	{//排水键
		if(!(F_Led_Light&&(F_Led_SelfClean||F_Led_Srandard||F_Led_Sterilize||F_Led_Save)))
		{//功能键自锁
			BeepState = BUZZ_KEY_VALID;
			F_Lack_Rad = F_Led_Fast = !F_Led_Fast;
		}
	}

	if(KEY_STANDARD&&KEY_ACT_SHORT&&(!F_Led_Power))
	{//洗涤键
		if(!(F_Led_Light&&(F_Led_SelfClean||F_Led_Fast||F_Led_Sterilize||F_Led_Save)))
		{//功能键自锁
			BeepState = BUZZ_KEY_VALID;
			F_Wsah = F_Led_Srandard = !F_Led_Srandard;
		}
	}

	if(KEY_STERILIZE&&KEY_ACT_SHORT&&(!F_Led_Power))
	{//加热键//20260702
		if(!(F_Led_Light&&(F_Led_SelfClean||F_Led_Fast||F_Led_Srandard||F_Led_Save)))
		{//功能键自锁
			BeepState = BUZZ_KEY_VALID;
			F_Sterilize = F_Led_Sterilize = !F_Led_Sterilize;
		}
	}

	if(KEY_SAVE&&KEY_ACT_SHORT&&(!F_Led_Power))
	{//风机键//20260702
		if(!(F_Led_Light&&(F_Led_SelfClean||F_Led_Fast||F_Led_Srandard||F_Led_Sterilize)))
		{//功能键自锁
			BeepState = BUZZ_KEY_VALID;
			F_Save = F_Led_Save = !F_Led_Save;
		}
	}

	if(KEY_LIGHT&&KEY_ACT_SHORT&&(!F_Led_Power))
	{//功能键//20260702
		BeepState = BUZZ_KEY_VALID;
		Buf_Led_Light = !F_Led_Light;
		Trant_LED_Index(DIGITAL_ALL_OFF);
		Trant_LED_Index(LED_ALL_OFF);
		F_Led_Light = Buf_Led_Light;
	}
	#endif
}
#endif
/**
*******************************************************************************
 * Copyright (c) 2025.5.9
 * 
* @file    Work.c
* @author  lianggaosang@qq.com
* @brief   
* 
*******************************************************************************
*/
/* Includes head files ------------------------------------------------------ */
#include "Work.h"
#include "FuctionSteps_Sheet.h"
#include "Key\Key.h"
// #include "Test\Self_Test.h"
#include "Save\Save.h"
#include "ErrorHandling\Error.h"
#include "Display\Display.h"
#include "TicketHandling\TicketHandling.h"
#include "PowerLostMemory\PowerLostMemory.h"
// #include "Relays\Relays.h"//"Power\Power.h"
// #include "Signals\Signals.h"//"Power\Power.h"
// #include "Temperatures\Temperatures.h"//"Power\Power.h"
// #include "InletValveRotation\InletValveRotation.h"//"Power\Power.h"
// #include "Buzzer\Buzzer.h"//"Power\Power.h"
#include "Power\Power.h"
#if CONFIG_AUTO_WASH
#include "Turbidity\Turbidity.h"
#endif
#if CONFIG_AUTO_DOOR  
#include "AutoDoor\AutoDoor.h"
#endif
#if CONFIG_WASH_IN_TURN
#include "UpDownPipeSwitch\UpDownPipeSwitch.h"
#endif
#if CONFIG_DEBUG_PRINT
#include "DebugPrintf\DebugPrintf.h"
#endif
#if CONFIG_BLAM_ENABLE
#include "BldcMotor\BldcMotor.h"
#endif
/* const define ------------------------------------------------------------- */
const stMenuPara  MenuList[] = 
{
	{MENU_FAST,		0,		1,		0,		1, 		1},
	{MENU_STANDARD, 0,		1,		0,		1, 		1},
	{MENU_STEAM, 	1,		0,		0,		1, 		1},
	{MENU_DRY,		0,		0,		1,		0, 		1},
	{MENU_SELFCLEAN,0,		0,		0,		NEWFORM0,NEWTPE1},//NEWTPE1//20251110 NEWFORM0 11.6
	{MENU_NULL,		0,		1,		0,		1,		0}
};
const UCHAR_XDATA Work_StageStartTimeMode[MAX_MENU_NUMBER][STAGE_END+1]=
{					//(20251127 1-0-1-66-end)
					// {19,18,10,7,1,1,0},//MENU_FAST
					// {29,28,15,10,1,1,0},//MENU_STANDARD
					// {10,10,10,10,10,1,0},//MENU_STEAM
					// {35,35,35,35,35,35,0},//MENU_DRY//45
					// #if NEWTPE1
					// {10,10,5,2,1,1,0}//MENU_SELFCLEAN
					// #endif
#if CONFIG_LIFE_TEST//20251204
	//20251110 NEWFORM0 10.6
	{2,2,0,0,0,0,0,0},//MENU_FAST
	{255,255,0,0,0,0,0,0},//MENU_STANDARD
	{10,10,10,10,10,0,0,0},//MENU_STEAM
	{40,40,40,40,40,40,0,0},//MENU_DRY//45//35//20251110 NEWFORM0 11.3
	#if NEWTPE1
	{80,80,0,0,0,0,0}//MENU_SELFCLEAN
	#endif
#elif CONFIG_IQC_TEST//20260117
	{1,1,0,0,0,0,0,0},//MENU_FAST
	{255,255,0,0,0,0,0,0},//MENU_STANDARD
	{10,10,10,10,10,0,0,0},//MENU_STEAM
	{40,40,40,40,40,40,0,0},//MENU_DRY//45//35//20251110 NEWFORM0 11.3
	#if NEWTPE1
	{1,1,0,0,0,0,0}//MENU_SELFCLEAN
	#endif
#else
	//20251110 NEWFORM0 10.6
	{19,19,10,7,0,0,0,0},//MENU_FAST
	// {29,29,15,10,0,0,0,0},//MENU_STANDARD
	// {10,10,10,10,10,0,0,0},//MENU_STEAM
	// {40,40,40,40,40,40,0,0},//MENU_DRY//45//35//20251110 NEWFORM0 11.3

	#if CONFIG_T2_STANDARD//20251211//20260421 版本0
	{32,32,19,15,0,0,0,0},//MENU_STANDARD
	#else
	{29,29,15,10,0,0,0,0},//MENU_STANDARD
	#endif

	#if CONFIG_T2_STEAMDRY//20251211//20260421 版本0
	{12,12,12,12,12,0,0,0},//MENU_STEAM//20251216
	{38,38,38,38,38,38,0,0},//MENU_DRY//45//35//20251110 NEWFORM0 11.3//20251216
	#else
	{10,10,10,10,10,0,0,0},//MENU_STEAM
	{40,40,40,40,40,40,0,0},//MENU_DRY//45//35//20251110 NEWFORM0 11.3
	#endif

	#if NEWTPE1
	{10,10,5,3,0,0,0}//MENU_SELFCLEAN
	#endif
#endif
	//20251126 少于配时扣足配时，大于配时不再走时，非进水最大延时跳步，阶段走时上下限
};


// const UCHAR_XDATA Work_StageStartTimeInSteamMode[MAX_MENU_NUMBER][STAGE_COMPLETE+1]=
// {
// 	{19+10,18+10,10+10,7+10,1+10,1,0},//MENU_FAST
// 	{29+10,28+10,15+10,10+10,1+10,1,0},//MENU_STANDARD
// 	{10,10,10,10,10,1,0},//MENU_STEAM
// 	{45+10,45+10,45+10,45+10,45+10,45,0}//MENU_DRY
// };


// const UCHAR_XDATA Work_StageStartTimeInDryMode[MAX_MENU_NUMBER][STAGE_COMPLETE+1] =
// {
// 	{19+45,18+45,10+45,7+45,1+45,1+45,0},//MENU_FAST
// 	{29+45,28+45,15+45,10+45,1+45,1+45,0},//MENU_STANDARD
// 	{10+45,10+45,10+45,10+45,10+45,1+45,0},//MENU_STEAM
// 	{45,45,45,45,45,45,0}//MENU_DRY
// };

// const UCHAR_XDATA Work_StageStartTimeInSteam_DryMode[MAX_MENU_NUMBER][STAGE_COMPLETE+1] =
// {
// 	{19+55,18+55,10+55,7+55,1+55,1+45,0},//MENU_FAST
// 	{29+55,28+55,15+55,10+55,1+55,1+45,0},//MENU_STANDARD
// 	{10+45,10+45,10+45,10+45,10+45,1+45,0},//MENU_STEAM
// 	{45+10,45+10,45+10,45+10,45+10,45,0}//MENU_DRY
// };

const StepInfo (*steps[]) =
{
    fastSteps,
    standardSteps,
    steamSteps,
    drySteps,
	#if NEWTPE1
	selfcleanSteps,
	#endif
};

const TestInfo (*t_steps[]) =
{//20251011 厂测模式
    Test1Steps,
	Test2Steps,
};


/* Variables define --------------------------------------------------------- */                        
WorkState    Work_CurrentState;
MenuOption   Work_CurrentMenu;
MenuOption   Work_LastMenu;
UCHAR_XDATA  Work_CurrentStage;
UCHAR_XDATA  Work_CurrentStep = 0xff;
UCHAR_XDATA  Work_CurrentFnIndex;
USHORT_XDATA Work_CurrentArg;
USHORT_XDATA Work_UsedSecondInCurrentStep = 0;
FunctionPt   Work_NextStepHandler = NULL;
WorkState    Work_BufferState;
//Flags
WordFlag WorkAction_Flags = {0};
WordFlag WorkFuction_Flags = {0};
//Cnt
UCHAR_XDATA  Work_LeftMinToEnd;
UCHAR_XDATA EndCnt = 0;//结束状态计时//jieshujishu
UINT_XDATA 	SleepCnt = 0;//待机休眠倒计时
UCHAR_XDATA DrainCnt = 0;
USHORT_XDATA currentStepMaxDuationSecond = 0;
USHORT_XDATA currentFunctionUnitUsedSeconds = 0;
UCHAR_XDATA runSecCount = 0;
UCHAR_XDATA  Test_WaitKeyActionCount = 0;
UCHAR_XDATA  Work_DoorOpenDelaySecondCount = 0;
UINT_XDATA 	FlowMCntSet = 0;
UINT_XDATA 	FlowMCnt = 0;
#if CONFIG_LIFE_TEST//20251204
UINT_XDATA LifeTestCnt = 0;
#endif
//20251011 厂测模式
TestOption  Test_CurrentOption;//20251011 厂测模式
UCHAR_XDATA Test_CurrentStep = 0;//20251011 厂测模式
UCHAR_XDATA Test_CurrentStage = 0;//20251011 厂测模式
UCHAR_XDATA Test_MaxStage = 0;//20251011 厂测模式
/* static define --------------------------------------------------------- */ 
static bit checkLackError(void);
static UINT_XDATA FlowMCntBuf = 0;
static UCHAR_XDATA LackTimer = 0;
static void checkHeatError(void);
static UINT_XDATA heat_error_count = 0;
static UCHAR_XDATA temperature_buf = 0;
static UINT_XDATA Work_ExtraHeatSecondCount = 0;
static void checkRTError(void);
static bit checkHeatEnable(void);
#if CONFIG_FB_CHECK//20251204
static bit checkPtcEnable(void);
#endif
static void checkStepTemperatureIsReach(USHORT Arg);
static void checkStepRotationIsReach(USHORT Arg);
static void checkStepTimerIsReach(USHORT Arg);
static UINT_XDATA Work_SpecialSecondInCurrentStage = 0;
static UCHAR_XDATA Work_MinHeatTemp = 0;	
static void runMinCountDown(void);
#if CONFIG_DELAY_ENABLE
static void delayHoursCountDown(void);
#endif
static void Init_Variable_When_Close_Power(void);
static void Init_Variable_When_Goto_Standby(void);
static UCHAR_XDATA ResetTimer = 0;
/* Void --------------------------------------------------------- */
bit IsSteamStep(StepInfo *step_info)
{
	bit ret = MD_TRUE;
#if CONFIG_STEAM_ENABLE==1
	ret = (step_info->SteamMask || (step_info->SteamSwitch && Work_IsSteamMode));
#endif
	return ret;//固有步骤或匹配设置路径
}

bit IsDryStep(StepInfo *step_info)
{
	bit ret = MD_TRUE;
#if CONFIG_DRY_ENABLE==1
	ret = (step_info->dryMask || (step_info->drySwitch && Work_IsDryMode));
#endif
	return ret;//固有步骤或匹配设置路径
}

bit IsNormalMune(MenuOption Mune)
{
	#if NEWTPE1
		if ((MENU_FAST==Mune)||(MENU_STANDARD==Mune)||(MENU_SELFCLEAN==Mune))
	#else	
		if ((MENU_FAST==Mune)||(MENU_STANDARD==Mune))
	#endif
	{
		return MD_TRUE;
	}
	else
	{
		return MD_FALSE;
	}
}
bit IsSteamMune(MenuOption Mune)
{
	if(((Work_IsSteamMode)&&(MenuList[Mune].steamModeEnable))||(MenuList[Mune].steamMode))
	{
		return MD_TRUE;
	}
	else
	{
		return MD_FALSE;
	}
}
bit IsDryMune(MenuOption Mune)
{
	if (((Work_IsDryMode)&&(MenuList[Mune].dryModeEnable))||(MenuList[Mune].dryMode))
	{
		return MD_TRUE;
	}
	else
	{
		return MD_FALSE;
	}
}

void Work_NextStep(void)
{
	StepInfo step_info;

	unsigned int remainSeconds;
	unsigned int leftTotalSeconds;

	Work_UsedSecondInCurrentStep = 0;
	Inlet_IsInLetting = 0;
	Work_ExtraHeatSecondCount = 0;
	do {
		Work_CurrentStep ++;
		step_info = steps[(UCHAR)Work_CurrentMenu][Work_CurrentStep];
	} 
	while (!(IsSteamStep(&step_info) && IsDryStep(&step_info)));//2个函数均判断为1时不跳过
	#if CONFIG_DEBUG_PRINT
	LOG_PRINTF("run step %d\n", Work_CurrentStep);
	#endif
	if (step_info.clearStepDataEnable)
	{//20251126 少于配时扣足配时，大于配时不再走时，非进水最大延时跳步，阶段走时上下限
		if (currentStepMaxDuationSecond > currentFunctionUnitUsedSeconds)
		{
			remainSeconds = currentStepMaxDuationSecond - currentFunctionUnitUsedSeconds;//还没消耗完的剩余时间
			//leftTotalSeconds = (unsigned int)((Work_LeftMinToEnd+1)*60 - runSecCount - remainSeconds);
			leftTotalSeconds = (unsigned int)(Work_LeftMinToEnd);
			leftTotalSeconds = (unsigned int)((leftTotalSeconds+1)*60);
			if(leftTotalSeconds > (remainSeconds + runSecCount))
			{//(//20251126 Work_NextStep=>Work_LeftMinToEnd负数)
				leftTotalSeconds -= runSecCount + remainSeconds;
				Work_LeftMinToEnd = (UCHAR)(leftTotalSeconds / 60);
				runSecCount = (UCHAR)(60 - (leftTotalSeconds % 60));
			}
			else
			{
				Work_LeftMinToEnd = 1;
			}
		}
		currentFunctionUnitUsedSeconds = 0;
		Work_TimeHaltEnable = MD_FALSE;
	}


	if((Work_CurrentStage != step_info.stage)||(STAGE_PRE == step_info.stage)||(STAGE_COMPLETE == step_info.stage))
	{
		Work_SpecialSecondInCurrentStage = 0;
		Work_DrainAllFail = MD_FALSE;//20251110 NEWFORM0 10.1(3) 20251126
		Work_SteamLack = MD_FALSE;
		#if CONFIG_MENORY_WASHDATA
		Work_MemoryWrite = MD_TRUE;
		Work_IsPowerLostMemory = MD_TRUE;
		#endif
		Work_HasHeat = MD_FALSE;
		Work_HeatOk = MD_FALSE;
		heat_error_count = 0;
		LackTimer = 0;
		Inlet_ErrReload = MD_TRUE;
		Work_MinHeatTemp = 0;
		Work_CurrentStage = step_info.stage;
	}
	FlowMCntBuf = 0;//2025.9.23
	FlowMCnt = 0;//20251007
	Work_CurrentFnIndex = step_info.fnIndex;
	Work_CurrentArg = step_info.arg;
	currentStepMaxDuationSecond = step_info.maxDuration;
	//current_parameter = step_info.speed;
#if CONFIG_DEBUG_PRINT
	LOG_PRINTF("Info:Work step info:%u, %u\n", Work_CurrentStage, Work_CurrentFnIndex);
#endif
}

void Test_NextStep(void)
{//20251011 厂测模式
	TestInfo test_info;

	Work_UsedSecondInCurrentStep = 0;
	Inlet_IsInLetting = 0;
	Work_ExtraHeatSecondCount = 0;
	Test_CurrentStep ++;
	test_info = t_steps[(UCHAR)Test_CurrentOption][Test_CurrentStep];
  Test_MaxStage = test_info.stage>>4;

	if((Test_CurrentStage != (test_info.stage & 0x0f))||(test_info.clearStepDataEnable))
	{
		Test_CurrentStage = (test_info.stage & 0x0f);
		#if CONFIG_MENORY_WASHDATA
		Work_IsPowerLostMemory = MD_TRUE;
		#endif
		Work_SpecialSecondInCurrentStage = 0;
		Work_DrainAllFail = MD_FALSE;//20251110 NEWFORM0 10.1(3) 20251126
		Work_SteamLack = MD_FALSE;
		Work_HasHeat = MD_FALSE;
		Work_HeatOk = MD_FALSE;
		heat_error_count = 0;
		LackTimer = 0;
		Work_MinHeatTemp = 0;
		currentFunctionUnitUsedSeconds = 0;
		if(test_info.clearStepDataEnable)
		{
			Inlet_ErrReload = MD_TRUE;
		}
	}
	FlowMCntBuf = 0;//2025.9.23
	FlowMCnt = 0;//20251007
	Work_CurrentFnIndex = test_info.fnIndex;
	Work_CurrentArg = test_info.arg;
	currentStepMaxDuationSecond = test_info.maxDuration;
	//current_parameter = test_info.speed;
#if CONFIG_DEBUG_PRINT
	LOG_PRINTF("Info:Test step info:%u, %u\n", Test_CurrentStage, Work_CurrentFnIndex);
#endif
}

void Work_Control(void)
{
	//1sCnt
	Work_TimerTick1s = MD_FALSE;
	Init_Variable_When_Close_Power();
	Init_Variable_When_Goto_Standby();
		#if (CONFIG_LIFE_TEST||CONFIG_IQC_TEST)//20251204//20260117
	    Work_IsSteamMode = 0;
        Work_IsDryMode = 0;
		#endif
	if (F_Work1s != F_Base1s)
	{
		F_Work1s = F_Base1s;
		Work_TimerTick1s = MD_TRUE;
		CHECK_DEC(Work_DoorOpenDelaySecondCount);
		CHECK_DEC(Test_WaitKeyActionCount);
	}
	//Output
	RelayEnable = 0;
	OutputEnable = 0;
	Work_EndConditionIsTemperature = MD_FALSE;
	FlowMCntSet = 0;

	if(Fcting)
	{
		return;
	}
	//State
	switch(Work_CurrentState)
	{
		case STATE_RESET:
			if(Work_TimerTick1s)
			{
				if(++ResetTimer >= 2)
				{//20251016 增加功能
					ResetTimer = 0;
					Work_CurrentState = STATE_POWER;
					Test_WaitKeyActionCount = 60;//20251016 增加功能
				}
			}
			break;
		case STATE_POWER:
			break;
		case STATE_DRAIN:
			if(Work_TimerTick1s)
			{
				DrainCnt++;
			}

			#if CONFIG_MP_ENABLE
			if(DrainCnt >= 42)
			#else
			if(DrainCnt >= 32)
			#endif
			{
				Work_ClosePowerInit	= MD_TRUE;
				DrainCnt = 0;
			}
			else
			{
				#if CONFIG_MP_ENABLE
				if(DrainCnt >= 32)
				{
					Output_MP = MD_TRUE;
				}
				else
				#endif
				if((DrainCnt!=15)||(DrainCnt!=16))
				{
					Relay_DP = MD_TRUE;
				}
			}
			break;
		case STATE_STANDBY:
			if(IsNormalMune(Work_CurrentMenu))
			{
				Work_LeftMinToEnd = Work_StageStartTimeMode[(UCHAR)Work_CurrentMenu][0];
			}
			else
			{
				Work_LeftMinToEnd = 0;
			}

			if(IsSteamMune(Work_CurrentMenu))
			{
				Work_LeftMinToEnd += Work_StageStartTimeMode[(UCHAR)MENU_STEAM][0];
			}
			if(IsDryMune(Work_CurrentMenu))
			{
				Work_LeftMinToEnd += Work_StageStartTimeMode[(UCHAR)MENU_DRY][0];
			}

			if(Work_TimerTick1s)
			{
				if(++SleepCnt >= 300)
				{
					Work_CurrentState = STATE_POWER;
					SleepCnt = 0;
				}

				#if (0 == CONFIG_TEST_ERROR)
					#if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
				checkRTError();
					#endif
				#endif
			}
			break;
		case STATE_WASHING:
			Work_NextStepHandler  = Work_NextStep;
			if((!Error_IsHandling)&&(!Work_IsPaused)&&(0==Work_DoorOpenDelaySecondCount))
			{
				(*functions[Work_CurrentFnIndex])();

				if(Work_TimerTick1s)
				{
					#if (CONFIG_LIFE_TEST||CONFIG_IQC_TEST)//20251204//20260117
					if(MENU_STANDARD == Work_CurrentMenu)
					#endif
					{
						checkRTError();
					}

					Work_UsedSecondInCurrentStep++;
					currentFunctionUnitUsedSeconds ++;
					CHECK_DEC(Work_SpecialSecondInCurrentStage);
					//20251126 少于配时扣足配时，大于配时不再走时，非进水最大延时跳步，阶段走时上下限
					if (currentFunctionUnitUsedSeconds > currentStepMaxDuationSecond)
					{
						Work_TimeHaltEnable = MD_TRUE;
						if((!Inlet_IsInLetting)&&(currentStepMaxDuationSecond > 0))
						{//#if NEWFORM0//20251110 NEWFORM0 10.6
							if (Work_EndConditionIsTemperature)
							{//#if NEWFORM0//20251110 NEWFORM0 10.6
								Work_ExtraHeatSecondCount ++;
								if (Work_ExtraHeatSecondCount >= 300)
								{//#if NEWFORM0//20251110 NEWFORM0 10.6
									(*Work_NextStepHandler)();
								}
							}
							else
							{
								if (currentFunctionUnitUsedSeconds > (currentStepMaxDuationSecond + 120))
								{//#if NEWFORM0//20251110 NEWFORM0 10.6
									(*Work_NextStepHandler)();
								}
							}
						}
					}
					#if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
					checkHeatError();
					#endif
				}

				runMinCountDown();//(20251127 1-0-1-66-end)
			}
			break;
		#if CONFIG_DELAY_ENABLE
		case STATE_DELAY:
			if(Work_TimerTick1s)
			{
				delayHoursCountDown();
			}
			break;
		#endif
		case STATE_ERROR:
			break;
		case STATE_FINISHED:
			if(Work_TimerTick1s)
			{
				if(++EndCnt >= 10)
				{
					// Work_CurrentState  = STATE_DRAIN;
					Work_ClosePowerInit	= MD_TRUE;
					EndCnt = 0;
				}
			}
			break;
		case STATE_SAVING:
			Save_Control(F_Base1s);
			if(Get_Save_PtcState())
			{
				Relay_PTC = checkPtcEnable();//#if CONFIG_FB_CHECK//20251204
				#if CONFIG_O3_ENABLE
				Output_O3 = checkPtcEnable();//20260421 版本0 臭氧功能
				#endif
			}
			Output_FAN_IN = Get_Save_FanState();
			Output_UV = Get_Save_LedState();
			break;
		case STATE_TESTING://20251011 厂测模式
			
			if(Test_Entered)
			{
				#if CONFIG_TESTENTER_CHECK
				if(Key_TestEnter)
				{
					if(0==(TestKeyActionFlag>>1))
					{
						Key_TestEnter = 0;
						//Work_IsPaused = Power_DoorIsOpend;//20251110 NEWFORM0 4、
						Work_DoorOpenDelaySecondCount = 1;//20251110 NEWFORM0 4、
						Work_NextStepHandler  = Test_NextStep;
						Test_CurrentStep = 0;
						Test_NextStep();
						// Work_MemoryWrite = MD_TRUE;//20251110 NEWFORM0 3、
						
					}
				}
				else
				#endif
				{
					Work_NextStepHandler  = Test_NextStep;
					if((!Error_IsHandling)&&(!Work_IsPaused)&&(0==Work_DoorOpenDelaySecondCount))
					{
						(*functions[Work_CurrentFnIndex])();

						if(Work_TimerTick1s)
						{

							checkRTError();

							Work_UsedSecondInCurrentStep++;
							currentFunctionUnitUsedSeconds ++;
							//20251126 少于配时扣足配时，大于配时不再走时，非进水最大延时跳步，阶段走时上下限
							if (currentFunctionUnitUsedSeconds > currentStepMaxDuationSecond)
							{
								// Work_TimeHaltEnable = MD_TRUE;
								if((!Inlet_IsInLetting)&&(currentStepMaxDuationSecond > 0))
								{//#if NEWFORM0//20251110 NEWFORM0 10.6
									if (Work_EndConditionIsTemperature)
									{//#if NEWFORM0//20251110 NEWFORM0 10.6
										Work_ExtraHeatSecondCount ++;
										if (Work_ExtraHeatSecondCount >= 300)
										{//#if NEWFORM0//20251110 NEWFORM0 10.6
											(*Work_NextStepHandler)();
										}
									}
									else
									{
										if (currentFunctionUnitUsedSeconds > (currentStepMaxDuationSecond + 120))
										{//#if NEWFORM0//20251110 NEWFORM0 10.6
											(*Work_NextStepHandler)();
										}
									}
								}
							}
						}

						checkHeatError();
					}

					// runMinCountDown();
				}
			}
			break;
		default:
		break;
	}
}

//                            __________________________
//                           |                          |
//                           | private functions define |
//                           |__________________________|
//

//------------
//Check Errors
//------------
/**
  * @brief  进水故障检测 
  * @detail 10秒内脉冲数小于5且未达到设定水量
  * @param  无 
  * @retval 无 
  */
static bit checkLackError(void) //故障修改 
{
	if(((P_FlowMCnt + FlowMCnt) >= FlowMCntSet)||((P_FlowMCnt + FlowMCnt) >= (FlowMCntBuf+5)))
	{//20251007
		FlowMCntBuf = P_FlowMCnt + FlowMCnt;//20251007
		LackTimer = 0;
	}	

	if(Work_TimerTick1s)
	{
		if(++LackTimer >= 10)
		{
			LackTimer = 0;//(20251127 更改最大延时60->90)
			return 1;//Error_SetCode(ERROR_LACK);
		}

	}

	if ((Work_UsedSecondInCurrentStep >= 120)&&(DRAIN_ALL != Work_CurrentFnIndex))
	{//20251016 增加功能//(20251127 更改最大延时60->90)
		LackTimer = 0;
		return 1;//Error_SetCode(ERROR_LACK);
	}

	return 0;
}
/**
  * @brief  加热器故障检测 
  * @detail 连续加热（允许中断5s）5分钟，温度上升不足3度。 
  * @param  无 
  * @retval 无 
  */
static void checkHeatError(void)
{
	static UCHAR_XDATA heat_error_clear_count = 0;
  
	if (Relay_HEAT)
	{
		heat_error_clear_count = 5;

		if ((++heat_error_count > 300)&&(temperature_buf<Temperature_Value))
		{
			if ((Temperature_Value - temperature_buf) < 3)
		  	{
				Err_Heat = 1;
		  	}
		  	else
		  	{
				heat_error_count = 0;
				temperature_buf = Temperature_Value;
		  	}
		}
		else
		{
			heat_error_count = 0;
			temperature_buf = Temperature_Value;
		}
	}
	else
	{
		if (heat_error_clear_count)
		{
		  	heat_error_clear_count --;
		}
		else
		{
		  	heat_error_count = 0;
		  	temperature_buf = Temperature_Value;
		}
	}

	#if CONFIG_TEST_ERROR
	if(Test_Entered)
	{
		if (Err_Heat)
		{
			Error_SetCode(ERROR_HEATER);
		}
	}
	#else
		#if CONFIG_END_ERROR
		if(STAGE_COMPLETE == Work_CurrentStage)
		#endif
		{
			if (Err_Heat)
			{
				Error_SetCode(ERROR_HEATER);
			}
		}
	#endif
}
/**
  * @brief  NTC故障检测 
  * @detail 
  * @param  
  * @retval 无 
  * @note   
  */
static void checkRTError(void)
{
	#if CONFIG_TEST_ERROR
	if(Test_Entered)
	{
		if (AdErr_ReShort||AdErr_ReOpen)
		{
			Error_SetCode(ERROR_RT);
		}
	}
	#else
		#if CONFIG_END_ERROR
	if(STAGE_COMPLETE == Work_CurrentStage)
		#endif
	{
		if (AdErr_ReShort||AdErr_ReOpen)
		{
			Error_SetCode(ERROR_RT);
		}
	}
	#endif
}

/**
  * @brief  加热开启检测 
  * @detail 结束报警前不开加热管
  * @param  无 
  * @retval 无 
  */
static bit checkHeatEnable(void)
{
	if(AdErrFlag||Work_HeatOk||Err_Heat)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

#if CONFIG_FB_CHECK//20251204
/**
  * @brief  PTC开启检测 
  * @detail 风机不动不开PTC
  * @param  无 
  * @retval 无 
  */
static bit checkPtcEnable(void)
{
	return (!Err_FanFeedBack);
}
#endif

//------------
//Check Over
//------------
static void checkStepTimerIsReach(USHORT Arg)
{
    if (0 == Arg)//Work_CurrentArg
    {
        return;
    }


	if (Work_UsedSecondInCurrentStep >= Arg)//Work_CurrentArg
	{
		if (Test_Entered)
		{
			BeepState = BUZZ_KEY_VALID;
		}

		if(DRY_TEMP_WORK == Work_CurrentFnIndex)//2025.9.20 时序 NEWTPE1
		{
			Work_TempCompensation = MD_FALSE;//20250920
		}
				
		Work_EndConditionIsTemperature = MD_FALSE;
		Work_DrainAllFail = MD_FALSE;//20251110 NEWFORM0 10.1(3) 20251126
		Work_HasHeat = MD_FALSE;
		Work_HeatOk = MD_FALSE;
		Work_MinHeatTemp = 0;

		(*Work_NextStepHandler)();
	}
}
static void checkStepTemperatureIsReach(USHORT Arg)
{
	if (Temperature_Value >= Arg)//Work_CurrentArg
	{
		Work_HeatOk = MD_TRUE;
		if(Work_EndConditionIsTemperature)
		{
			Work_EndConditionIsTemperature = MD_FALSE;
			(*Work_NextStepHandler)();
		}
	}
}
static void checkStepRotationIsReach(USHORT Arg)
{
	if ((P_FlowMCnt + FlowMCnt) >= Arg)//Work_CurrentArg
	{
		Work_SteamLack = 0;
		if(P_FlowMErrCnt)
		{
			Inlet_ErrReload = 1;
		}
		#if CONFIG_SOFT_ENABLE
		if(Work_CurrentStage == STAGE_RINSE)
		{		
			eepromRestoreData(Work_EEPROM_Datas, EEPROM_MAX_LENTH);
			soft_run = Work_EEPROM_Datas[1];
			soft_run++;
			Work_EEPROM_Datas[1] = (UCHAR)soft_run;
			eepromSaveData(Work_EEPROM_Datas, EEPROM_MAX_LENTH);
		}
		#endif
		#if CONFIG_FLOW_CHECK
		Inlet_FlowCheck = 1;
		if(Inlet_FlowChecking)
		{
			Inlet_FlowCheckInit = 0;
			Inlet_FlowCheck = 0;
			if(Inlet_FlowCheckOk)
			{
				(*Work_NextStepHandler)();
			}
		}
		else
		{
			Inlet_FlowCheckInit = 1;
		}
		#else
		(*Work_NextStepHandler)();
		#endif
	}
	else
	{

		if(Work_InletMode)
		{
			Output_IV = MD_TRUE;
		}
		else
		{
			Output_IP = MD_TRUE;
		}
	}
	FlowMCntSet = Arg;//2025.9.23
}

//------------
//functions
//------------
/*
暂停一定时间  
*/
static void pause_timer(void)
{
  	checkStepTimerIsReach(Work_CurrentArg);
}
/*
排水动作一定时间  
*/
static void drain_timer(void)
{
	Relay_DP = MD_TRUE;
	checkStepTimerIsReach(Work_CurrentArg);
}
/*
蠕动泵动作一定时间  
*/
static void Move_timer(void)
{
	#if CONFIG_MP_ENABLE
	Output_MP = MD_TRUE;
	checkStepTimerIsReach(Work_CurrentArg);
	#else
	(*Work_NextStepHandler)();
	#endif
}
/*
进水一定转数  
*/ 
static void inlet_rotation(void)
{
	#if CONFIG_SOFT_ENABLE
    if(Work_CurrentStage==STAGE_DRY)
    {
		if(soft_run>=Soft_Open[soft_set])
        {
			if(Work_InletMode)
			{
				Output_IV = MD_TRUE;
			}
			else
			{
				Output_IP = MD_TRUE;
			}			
            checkStepRotationIsReach(Work_CurrentArg);
			if(checkLackError())
			{
				FlowMCnt += P_FlowMCnt;//20251007
				Error_SetCode(ERROR_LACK);
				Inlet_Lack = 1;
				Inlet_IsInLetting = 0;
			}
        }
        else
        {
            if(!Work_TimerTick1s)
            {
                return;
            }
            waitTimerToSkipInlet++;
            if(waitTimerToSkipInlet==15)
            {
                waitTimerToSkipInlet=0;
                (*Work_NextStepHandler)();
            }
        }
    }
    else
	#endif
    {
		Inlet_IsInLetting = 1;
		if(P_FlowMErrCnt)
		{
			Inlet_ErrReload = 1;
		}
		#if (EMC_TEST_NO_INLET == 1)
			checkStepRotationIsReach(3);
		#else			
        checkStepRotationIsReach(Work_CurrentArg);
		#endif
		if(checkLackError())
		{
			FlowMCnt += P_FlowMCnt;//20251007
			Error_SetCode(ERROR_LACK);
			Inlet_Lack = 1;
			Inlet_IsInLetting = 0;
		}
    }
}
/*
漂洗阶段进水
*/
static void inlet_rinse(void)
{
	Inlet_IsInLetting = 1;
	if(P_FlowMErrCnt)
	{
		Inlet_ErrReload = 1;
	}
	#if (EMC_TEST_NO_INLET == 1)
	checkStepRotationIsReach(3);
	#else			
	checkStepRotationIsReach(Work_CurrentArg);
	#endif 
	if(checkLackError())
	{
		if((P_FlowMCnt + FlowMCnt) >= C_LITER*6)//600ml
		{
			(*Work_NextStepHandler)();
		}
		else
		{
			FlowMCnt += P_FlowMCnt;//20251007
			Error_SetCode(ERROR_LACK);
			Inlet_Lack = 1;
		}
		Inlet_IsInLetting = 0;
	}
	
}
/*
进水一定时间 
*/
static void inlet_timer(void)
{ 
	Inlet_IsInLetting = 1;
	if(P_FlowMErrCnt)
	{
		Inlet_ErrReload = 1;
	}
	if(Work_InletMode)
	{
		Output_IV = MD_TRUE;
	}
	else
	{
		Output_IP = MD_TRUE;
	}
	#if (EMC_TEST_NO_INLET == 1)
	checkStepTimerIsReach(Work_CurrentArg);
	#else			
	checkStepTimerIsReach(Work_CurrentArg);
	if(checkLackError())
	{
		FlowMCnt += P_FlowMCnt;//20251007
		Error_SetCode(ERROR_LACK);
		Inlet_Lack = 1;
		Inlet_IsInLetting = 0;
	}
	#endif 
}
/*
蒸汽阶段进水
*/
static void inlet_steam(void)
{ 
	Inlet_IsInLetting = 1;
	if(P_FlowMErrCnt)
	{
		Inlet_ErrReload = 1;
	}
	#if (EMC_TEST_NO_INLET == 1)
	checkStepRotationIsReach(3);
	Work_SteamLack = 0;
	#else			
	checkStepRotationIsReach((C_LITER*25)/10);//250ml
	#endif 
	if(checkLackError())
	{
		Inlet_IsInLetting = 0;
		// if((P_FlowMCnt + FlowMCnt) < C_LITER*2)//200ml
		// {
		// 	Work_SteamLack = 1;//如果蒸汽使能且蒸汽开启，缺水跳过蒸汽步骤
		// }
		if((P_FlowMCnt + FlowMCnt) < C_LITER*2)//200ml
		{//20251007
			FlowMCnt += P_FlowMCnt;//20251007
			Error_SetCode(ERROR_LACK);
			Inlet_Lack = 1;
			Inlet_IsInLetting = 0;
		}
		else
		{
			Work_SteamLack = 1;//蒸汽阶段水量不足判断，改为执行短程时序
			(*Work_NextStepHandler)();
		}
	}
}
/*
洗涤泵工作一定时间
*/
static void wash_timer(void)
{
	Output_WP = MD_TRUE;
  	checkStepTimerIsReach(Work_CurrentArg);
}
/*
阶段总洗涤时间设置
*/
static void stage_wash_time_set(void)
{
	Work_SpecialSecondInCurrentStage = Work_CurrentArg;
	(*Work_NextStepHandler)();
}
/*
*/
static void stage_wash_time(void)
{
	Output_WP = MD_TRUE;
	if (0 == Work_SpecialSecondInCurrentStage)
	{
		(*Work_NextStepHandler)();
	}
}
/*
定温加热，温达剩洗
*/
static void wash_heat_temp1(void)
{
	Output_WP = MD_TRUE;
	checkStepTemperatureIsReach(Work_CurrentArg);
	Relay_HEAT = checkHeatEnable();
	#if (0==NEWFORM0)//20251110 NEWFORM0 8.7(20251127 更改)
	if(Work_HeatOk)
	#endif
	{
		checkStepTimerIsReach(currentStepMaxDuationSecond);
	}
}
/*
定温加热，温达跳步
*/
static void wash_heat_temp2(void)
{
	Output_WP = MD_TRUE;
	Relay_HEAT = checkHeatEnable();
	Work_EndConditionIsTemperature = MD_TRUE;
	checkStepTemperatureIsReach(Work_CurrentArg);
}
/*
定温加热，温达维持
*/
#if CONFIG_LIFE_TEST//20251204
static void wash_heat_temp3(void)
{
	Output_WP = MD_TRUE;
	if(Work_HasHeat)
	{
		if(Temperature_Value < Work_MinHeatTemp)
		{
			// Relay_HEAT = checkHeatEnable();
			Relay_HEAT = MD_TRUE;
			Work_HasHeat = MD_FALSE;
			checkStepTimerIsReach(currentStepMaxDuationSecond);
		}
	}
	else
	{
		if (Temperature_Value >= Work_CurrentArg)
		{
			Work_HasHeat = MD_TRUE;
		}
		else
		{
			// Relay_HEAT = checkHeatEnable();
			Relay_HEAT = MD_TRUE;
		}
	}
	// checkStepTimerIsReach(currentStepMaxDuationSecond);
}
#else
static void wash_heat_temp3(void)
{
	Output_WP = MD_TRUE;
	if(Work_HasHeat)
	{
		if(Temperature_Value < Work_MinHeatTemp)
		{
			Relay_HEAT = checkHeatEnable();
			Work_HasHeat = MD_FALSE;
		}
	}
	else
	{
		if (Temperature_Value >= Work_CurrentArg)
		{
			Work_HasHeat = MD_TRUE;
		}
		else
		{
			Relay_HEAT = checkHeatEnable();
		}
	}
	checkStepTimerIsReach(currentStepMaxDuationSecond);
}
#endif
/*
温度维持设置
*/
static void wash_heat_temp_set(void)
{
	Work_HasHeat = MD_FALSE;
	Work_MinHeatTemp = Work_CurrentArg;
	(*Work_NextStepHandler)();
}
/*
蒸汽阶段加热管工作一定时间
*/
static void heat_timer(void)
{
	// if(Work_SteamLack)
	// {//20251007
	// 	(*Work_NextStepHandler)();
	// }
	// else
	{
		#if CONFIG_STEAM_FAN//20251211 
		if(!Work_IsDryMode)//20251021
		{//2025.9.20 蒸汽功能需要同时打开PTC，单独蒸汽功能不打开PTC
			Output_FAN_IN = MD_TRUE;//20251021
		}
		else
		{//20251021
			Relay_PTC = checkPtcEnable();//#if CONFIG_FB_CHECK//20251204
			#if CONFIG_O3_ENABLE
			Output_O3 = checkPtcEnable();//20260421 版本0 臭氧功能
			#endif
			Output_FAN_IN = MD_TRUE;
		}
		#endif
		
		Relay_HEAT = checkHeatEnable();
		#if (0==NEWFORM0)//20251110 NEWFORM0 8.8(20251127 更改)
		if(Work_SteamLack)
		{
			checkStepTimerIsReach(360);//20251007
		}
		else
		#endif
		{
			checkStepTimerIsReach(Work_CurrentArg);
		}
	}
}
/*
蒸汽阶段加热管工作最后两分钟
*/
static void heat_steam(void)
{
	
	// if(Work_SteamLack)
	// {//20251007
	// 	(*Work_NextStepHandler)();
	// }
	// else
	{
		#if CONFIG_STEAM_FAN////20251211 
		if(!Work_IsDryMode)//20251021
		{//2025.9.20 蒸汽功能需要同时打开PTC，单独蒸汽功能不打开PTC
			Output_FAN_IN = MD_TRUE;//20251021
		}
		else
		{//20251021
			Relay_PTC = checkPtcEnable();//#if CONFIG_FB_CHECK//20251204
			#if CONFIG_O3_ENABLE
			Output_O3 = checkPtcEnable();//20260421 版本0 臭氧功能
			#endif
			Output_FAN_IN = MD_TRUE;
		}
		#endif
		
		if((Work_UsedSecondInCurrentStep%30)>=10)
		{
			Relay_HEAT = checkHeatEnable();
		}
  		checkStepTimerIsReach(Work_CurrentArg);
	}
}
// /*
// 蒸汽阶段结束排水判断
// */
// static void drain_steam(void)
// {
// 	if(!Work_SteamLack)
// 	{
// 		if(Temperature_Value < Work_CurrentArg)//20250929
// 		{
// 			(*Work_NextStepHandler)();
// 		}
// 	}
// 	else
// 	{
// 		(*Work_NextStepHandler)();
// 	}
// 	checkStepTimerIsReach(currentStepMaxDuationSecond);//20250929
// }
/*
/*
排空水箱
*/
static void drain_all(void)
{//20250930 如果流量计有反应，从水箱一直进水，同时一直排水，直至水箱存水排空
	//20251110 NEWFORM0 10.1 去掉10s排水步骤，排水1min内检查是否排完，没排完最多排120s，再补30s排水步骤保证内胆排空
	if(!Test_Entered)
	{//(20251127 更改最大延时60->90)
		if(IsDryMune(Work_CurrentMenu))
		{
			Relay_PTC = checkPtcEnable();//#if CONFIG_FB_CHECK//20251204
			#if CONFIG_O3_ENABLE
			Output_O3 = checkPtcEnable();//20260421 版本0 臭氧功能
			#endif
			Output_FAN_IN = MD_TRUE;
		}
		else if(IsSteamMune(Work_CurrentMenu))
		{
			Output_FAN_IN = MD_TRUE;
		}
	}

	Relay_DP = MD_TRUE;
	//(20251127 更改最大延时60->90)
	if(Work_CurrentArg)
	{
		if(Work_DrainAllFail)
		{//20251110 NEWFORM0 10.1(3) 20251126 只有120s没排完才排30s
			checkStepTimerIsReach(Work_CurrentArg);
		}
		else
		{
			(*Work_NextStepHandler)();
		}
		
	}
	else
	{
		if(P_FlowMErrCnt)
		{
			Inlet_ErrReload = MD_TRUE;
		}
		FlowMCntSet = 0xffff;
		Inlet_IsInLetting = MD_TRUE;
		Output_IP = MD_TRUE;
		if(checkLackError())
		{
			checkStepTimerIsReach(currentStepMaxDuationSecond);
		}
		else
		{
			if (Work_UsedSecondInCurrentStep >= currentStepMaxDuationSecond+90)
			{//20251110 NEWFORM0 10.1(3) 20251126 只有120s没排完才排30s//(20251127 更改最大延时60->90)
				Work_DrainAllFail = MD_TRUE;
				(*Work_NextStepHandler)();
			}
		}
	}
}

/*
风机工作一段时间
*/
static void fan_timer(void)
{
	Output_FAN_IN = MD_TRUE;
	checkStepTimerIsReach(Work_CurrentArg);
}

/*
风机与风机工作一段时间
*/
static void fan_Ptc_timer(void)
{
	Relay_PTC = checkPtcEnable();//#if CONFIG_FB_CHECK//20251204
	#if CONFIG_O3_ENABLE
	Output_O3 = checkPtcEnable();//20260421 版本0 臭氧功能
	#endif
	Output_FAN_IN = MD_TRUE;
	checkStepTimerIsReach(Work_CurrentArg);
}

/*
静置//20251021
*/
static void fan_Ptc_steam(void)
{
	if(!Work_IsDryMode)
	{//开不开PTC取决于烘干连续性，有无静置取决于有无蒸汽，若有蒸汽无烘干且无缺水跳过，有烘干
		if(Work_SteamLack)
		{ 
			Output_FAN_IN = MD_TRUE;
			checkStepTimerIsReach(Work_CurrentArg);
		}
		else
		{
			(*Work_NextStepHandler)();
		}
	}
	else
	{
		Relay_PTC = checkPtcEnable();//#if CONFIG_FB_CHECK//20251204
		#if CONFIG_O3_ENABLE
		Output_O3 = checkPtcEnable();//20260421 版本0 臭氧功能
		#endif
		Output_FAN_IN = MD_TRUE;
		checkStepTimerIsReach(Work_CurrentArg);
	}
}


/*
预洗温度补偿检查
*/
static void Pre_Temp_Check(void)//2025.9.20 时序 NEWTPE1
{
	if(Temperature_Value < 20)
	{
		Work_TempCompensation = MD_TRUE;
		if(IsDryMune(Work_CurrentMenu))
		{
			Work_LeftMinToEnd += 10;//预洗温度补偿10分钟
		}
	}
	else
	{
		Work_TempCompensation = MD_FALSE;
	}

	(*Work_NextStepHandler)();
}

/*
烘干温度补偿
*/
static void Dry_Temp_Work(void)//2025.9.20 时序 NEWTPE1
{
	if(Work_TempCompensation)
	{
		Relay_PTC = checkPtcEnable();//#if CONFIG_FB_CHECK//20251204
		#if CONFIG_O3_ENABLE
		Output_O3 = checkPtcEnable();//20260421 版本0 臭氧功能
		#endif
		Output_FAN_IN = MD_TRUE;
		checkStepTimerIsReach(Work_CurrentArg);
	}
	else
	{
		(*Work_NextStepHandler)();
	}
}
/*
完成步骤  
*/
static void complete(void)
{
	Inlet_IsInLetting = MD_FALSE;
	Inlet_ErrReload = MD_TRUE;
	Inlet_Lack = MD_FALSE;
	FlowMCntBuf = 0;//20251007
	FlowMCnt = 0;
	LackTimer = 0;
	runSecCount = 0;
	//Err_Heat = MD_FALSE;
	Err_FanFeedBack = 0;//#if CONFIG_FB_CHECK//20251204
	fanfbCount = 0;//#if CONFIG_FB_CHECK//20251204
	SleepCnt = 0;
	DrainCnt = 0;
	EndCnt = 0;
	temperature_buf = 0;
    Work_LeftMinToEnd =0;
	Work_UsedSecondInCurrentStep = 0;
    Work_ExtraHeatSecondCount = 0;
	Work_SpecialSecondInCurrentStage = 0;
	currentStepMaxDuationSecond = 0;
    currentFunctionUnitUsedSeconds = 0;
	Work_DoorOpenDelaySecondCount = 0;
	heat_error_count = 0;
	Work_MinHeatTemp = 0;
	Work_HeatOk = MD_FALSE;
    Work_HasHeat = MD_FALSE;
	Work_SteamLack = MD_FALSE;
	Work_DrainAllFail = MD_FALSE;//20251110 NEWFORM0 10.1(3) 20251126
    Work_TimeHaltEnable = MD_FALSE;
	Work_TempCompensation = MD_FALSE;//20251204
	Work_CurrentStage = 0;
	Work_CurrentArg = 0;
	Work_CurrentFnIndex = 0;
	BeepState = BUZZ_END;
	Test_Entered = FALSE;
	TestKeyCnt = 0;
	Work_KeyboardIsLocked = MD_FALSE;
	Work_IsPaused = MD_FALSE;
	Work_LastMenu = Work_CurrentMenu;//20250920
	Work_NextStepHandler  = Work_NextStep;
	#if CONFIG_LIFE_TEST//20251204
	Work_CurrentStep = 0;
	if(++LifeTestCnt>=999)
	{
		LifeTestCnt = 999;
	}
	(*Work_NextStepHandler)();
	Work_LeftMinToEnd = Work_StageStartTimeMode[(UCHAR)Work_CurrentMenu][0];
	#elif CONFIG_IQC_TEST//20260117
	Work_CurrentStep = 0;
	(*Work_NextStepHandler)();
	Work_LeftMinToEnd = Work_StageStartTimeMode[(UCHAR)Work_CurrentMenu][0];
	Work_IsPaused = 1;
	#else
	Work_CurrentStep = 0xff;
	if(Work_SaveEnter)
	{
		Work_CurrentState = STATE_SAVING;
		Work_SaveEnter = MD_FALSE;
		Save_InitSet();
	}
	else
	{
		Work_CurrentState = STATE_FINISHED;
	}
	Work_MemoryWrite = MD_TRUE;//20251110 NEWFORM0 2.4
	#endif
	//20251011 厂测模式
	Test_CurrentOption = TEST_NULL;
	Test_CurrentStep = Test_MaxStage = 0xff;
	Test_CurrentStage = 0;
}
/*
厂测完成步骤  
*/
static void complete_Save(void)
{
	Work_SaveEnter = MD_TRUE;
	(*Work_NextStepHandler)();
}
//------------
//const
//------------
const FunctionPt functions[] = 
{
  pause_timer,			//  0
  drain_timer,			//  1
  Move_timer,			//  2
  inlet_rotation,		//  3
  inlet_rinse,			//  4
  inlet_timer,			//  5
  inlet_steam,			//  6
  wash_timer,			//  7
  stage_wash_time_set,	//  8
  stage_wash_time,		//  9
  wash_heat_temp1,		//  10
  wash_heat_temp2,		//  11
  wash_heat_temp3,		//  12
  wash_heat_temp_set,	//  13
  heat_timer,			//  14
  heat_steam,			//  15
//   drain_steam,			//  16
  drain_all,			//  16
  fan_timer,			//  17
  fan_Ptc_timer,		//  18
  fan_Ptc_steam,		//  19
  Pre_Temp_Check,		//  20
  Dry_Temp_Work,		//  21
  complete_Save,		//  22
  complete,				//  23
//   inlet_rotation2,		//  25
//   fan_fan2_timer,		//  26
};
//------------
//Static Void
//------------
#if CONFIG_DELAY_ENABLE
static void delayHoursCountDown(void)
{//Work_TimerTick1s
  delaySecCount ++;

  if (delaySecCount >= 60)
  {
    delaySecCount = 0;
    delayMinCount --;
  }

  if (delayMinCount == 0)
  {
    delayMinCount = 60;
    Work_DelayHours --;
    if (Work_DelayHours == 0)
    {
	   (*Work_NextStepHandler)();//故障修改  
       Work_CurrentState = STATE_WASHING;
       Display_BrightnessLevel = LEVEL4;
       Buzz_SetType(BUZZ_KEY_VALID);
    }
  }
}
#endif
static void runMinCountDown(void)
{//Work_TimerTick1s
	UCHAR upperRangeTimeInCurrentStage;
	UCHAR lowerRangeTimeInCurrentStage;

	// if(Work_CurrentStage < STAGE_COMPLETE)
	// {//(20251127 1-0-1-66-end)
		if (IsNormalMune(Work_CurrentMenu))
		{
			upperRangeTimeInCurrentStage = Work_StageStartTimeMode[(UCHAR)Work_CurrentMenu][Work_CurrentStage];
			lowerRangeTimeInCurrentStage = Work_StageStartTimeMode[(UCHAR)Work_CurrentMenu][Work_CurrentStage + 1];
		}
		else
		{
			upperRangeTimeInCurrentStage = lowerRangeTimeInCurrentStage = 0;
		}

		if(IsSteamMune(Work_CurrentMenu))
		{
			upperRangeTimeInCurrentStage += Work_StageStartTimeMode[(UCHAR)MENU_STEAM][Work_CurrentStage];
			lowerRangeTimeInCurrentStage += Work_StageStartTimeMode[(UCHAR)MENU_STEAM][Work_CurrentStage + 1];
		}

		if(IsDryMune(Work_CurrentMenu))
		{
			upperRangeTimeInCurrentStage += Work_StageStartTimeMode[(UCHAR)MENU_DRY][Work_CurrentStage];
			lowerRangeTimeInCurrentStage += Work_StageStartTimeMode[(UCHAR)MENU_DRY][Work_CurrentStage + 1];
			if(Work_TempCompensation)
			{
				if(Work_CurrentStage < STAGE_COMPLETE)
				{	
					upperRangeTimeInCurrentStage += 10;
				}

				if(Work_CurrentStage < STAGE_DRY)
				{	
					lowerRangeTimeInCurrentStage += 10;
				}
			}
		}
		//20251126 少于配时扣足配时，大于配时不再走时，非进水最大延时跳步，阶段走时上下限
		if (Work_LeftMinToEnd > upperRangeTimeInCurrentStage)
		{
			Work_LeftMinToEnd = upperRangeTimeInCurrentStage;
		}
		else //(20251127 1-0-1-66-end)
		if (Work_LeftMinToEnd > lowerRangeTimeInCurrentStage)
		{
			if((!Work_TimeHaltEnable)&&(Work_TimerTick1s))//(20251127 1-0-1-66-end)
			{//20251110 NEWFORM0 13.2 20251126
				if (++runSecCount >= 60)
				{
					runSecCount = 0;
					Work_LeftMinToEnd --;
				}
			}
		}
		else
		{
			Work_LeftMinToEnd = lowerRangeTimeInCurrentStage;
			//20251110 NEWFORM0 13.2 20251126
		}
	// }

	if(Work_LeftMinToEnd <= 1)
	{//20251110 NEWFORM0 10.6//(20251127 1-0-1-66-end)
		Work_LeftMinToEnd = 1;
	}
}

static void Init_Variable_When_Goto_Standby(void)
{
	if(Work_GotoStandbyInit)
	{
		BeepState = BUZZ_POWERON;
		Work_GotoStandbyInit = MD_FALSE;
		Work_CurrentState = STATE_STANDBY;
		//20251110 NEWFORM0 2.4
		//Work_IsSteamMode//Work_IsDryMode//Work_MemoryRead
		if(MENU_STEAM == Work_LastMenu)
		{//20251110 NEWFORM0 3、
			Work_CurrentMenu = MENU_NULL;
			Work_IsSteamMode = 1;
		}
		else if(MENU_DRY == Work_LastMenu)
		{//20251110 NEWFORM0 3、
			Work_CurrentMenu = MENU_NULL;
			Work_IsDryMode = 1;
		}
		else
		{
			Work_CurrentMenu = Work_LastMenu;
		}
		Work_LeftMinToEnd = 0;
		SleepCnt = 0;
		DrainCnt = 0;
		EndCnt = 0;
		drainCount = 0;
		TestKeyCnt = 0;
		Test_Entered = FALSE;
		Work_KeyboardIsLocked = MD_FALSE;
		Work_IsPaused = MD_FALSE;
		Work_CurrentStage = 0;
		Work_CurrentArg = 0;
		Work_CurrentStep = 0xff;
		Work_CurrentFnIndex = 0;
		#if CONFIG_DELAY_ENABLE
		Work_DelayHours = 0;        
		delaySecCount = 0;
		delayMinCount = 60;
		#endif
		Inlet_IsInLetting = MD_FALSE;
		FlowMCntBuf = 0;
		FlowMCnt = 0;//20251007
		LackTimer = 0;
		Inlet_Lack = MD_FALSE;
		Err_Heat = MD_FALSE;
		runSecCount = 0;
		Err_FanFeedBack = 0;//#if CONFIG_FB_CHECK//20251204
		fanfbCount = 0;//#if CONFIG_FB_CHECK//20251204
		temperature_buf = 0;
		Work_UsedSecondInCurrentStep = 0;
		Work_ExtraHeatSecondCount = 0;
		currentStepMaxDuationSecond = 0;
		currentFunctionUnitUsedSeconds = 0;
		Work_SpecialSecondInCurrentStage = 0;
		Work_DoorOpenDelaySecondCount = 0;
		heat_error_count = 0;
		Work_MinHeatTemp = 0;
		Work_HeatOk = MD_FALSE;
		Work_HasHeat = MD_FALSE;
		Work_SteamLack = MD_FALSE;
		Work_DrainAllFail = MD_FALSE;//20251110 NEWFORM0 10.1(3) 20251126
		Work_TimeHaltEnable = MD_FALSE;
		Work_SaveEnter = MD_FALSE;
		Work_TempCompensation = MD_FALSE;//20251204
		// temperatureDisplayCount = 0;
    	// time_WaitKeyActionCount = 0;
		// lockFlashCount = 0;
		// addedWaterSecond = 0;
		//20251011 厂测模式
		Test_CurrentOption = TEST_NULL;
		Test_CurrentStep = Test_MaxStage = 0xff;
		Test_CurrentStage = 0;
		Work_NextStepHandler  = Work_NextStep;
		#if CONFIG_LIFE_TEST//20251204
		LifeTestCnt = 0;
		#endif
	}
}

static void Init_Variable_When_Close_Power(void)
{
	if(Work_ClosePowerInit)
	{
		BeepState = BUZZ_POWERON;//
		Work_ClosePowerInit = MD_FALSE;
		Work_CurrentState = STATE_POWER;
		Work_LastMenu = Work_CurrentMenu;
		//20251110 NEWFORM0 2.4
		//Work_CurrentMenu = MENU_NULL;
		// Work_IsSteamMode = MD_FALSE;
		// Work_IsDryMode = MD_FALSE;
		Test_Entered = MD_FALSE;
		Work_KeyboardIsLocked = MD_FALSE;
		Work_IsPaused = MD_FALSE;
		Work_HeatOk = MD_FALSE;
		Work_HasHeat = MD_FALSE;
		Work_SteamLack = MD_FALSE;
		Work_DrainAllFail = MD_FALSE;//20251110 NEWFORM0 10.1(3) 20251126
		Work_TempCompensation = MD_FALSE;//20251204
		Error_CurrentCode = ERROR_NULL;
		Work_CurrentFnIndex = 0;
		Inlet_IsInLetting = MD_FALSE;
		Inlet_ErrReload = MD_TRUE;
		FlowMCntBuf = 0;
		FlowMCnt = 0;//20251007
		LackTimer = 0;
		Inlet_Lack = MD_FALSE;
		Err_Heat = MD_FALSE;
		runSecCount = 0;
		Err_FanFeedBack = 0;//#if CONFIG_FB_CHECK//20251204
		fanfbCount = 0;//#if CONFIG_FB_CHECK//20251204
		SleepCnt = 0;
		DrainCnt = 0;
		EndCnt = 0;
		drainCount = 0;
		TestKeyCnt = 0;
		// Work_CurrentHalfMode = HALF_BY_TURNS;
		// Half_CurrentPoint = T_UNKNOWN;
		// Pipe_CurrentState = PIPE_STATE_UNKNOWN;
		//20251011 厂测模式
		Test_CurrentOption = TEST_NULL;
		Test_CurrentStep = Test_MaxStage = 0xff;
		Test_CurrentStage = 0;
		Work_NextStepHandler  = Work_NextStep;
		#if CONFIG_IAPADDR_DEVICE	
		Work_MemoryWrite = MD_TRUE;//20251110 NEWFORM0 2.4//20251126 关机记忆时间太长
		#endif
		
		#if CONFIG_LIFE_TEST//20251204
		LifeTestCnt = 0;
		#endif
	}
}
//---------------------------------------------------------------------------------



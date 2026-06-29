/**
 *******************************************************************************
 * Copyright (c) 20250606
 *
 * @file    LoadDrive.c
 * @author  lianggaosang@qq.com
 * @brief   继电器控制
 *
 *******************************************************************************
 */
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "LoadDrive.h"
#include "GpioDrv.h"
#include "ReadSwitch\ReadSwitch.h"
#include "TicketHandling\TicketHandling.h"
#include "Temperatures\Temperatures.h"
#include "WashDish\WashDish.h"//FlowMCntSet//F_InLetErrReload
#include "Buzzer\Buzzer.h"
#include "IoUart_Simulate\IoUart_Simulate.h"
/*
********************************************************************************
**  Static define
********************************************************************************
*/
static void CheckFillErr(void);
static void OutputEn(void);
UCHAR_XDATA	FlowMPreSecErrCnt = 0;
static UCHAR_XDATA	L_InLetCloseDelayTime = 0;
static UCHAR_XDATA	L_FlowMSecWithErrCnt_1S = 0;
static UCHAR_XDATA	L_InLetMovementOffTime = 0;
static UCHAR_XDATA	L_InLetMovementOnTime = 0;
static UCHAR_XDATA	L_FlowMPreSecTime = 0;
// static UCHAR_XDATA	L_EdOpenOnceTime = 0;
/*
********************************************************************************
**  Global define
********************************************************************************
*/
WordFlag Load_Enables = {0};
/*
********************************************************************************
**  Function define
********************************************************************************
*/
void Init_Load(void)
{
 	LoadEnable = 0;
}

void Load_Driver(void)
{
	static UCHAR_XDATA	L_CommunicatErrTime = 0;
	if(Flow_Timer100ms != F_Base100ms)
	{
		Flow_Timer100ms = F_Base100ms;

		if(F_FlowCheckEn)
		{
			if(F_FlowCheck)
			{
				CHECK_DEC(L_InLetCloseDelayTime);//24.2.23 
				CHECK_DEC(L_InLetMovementOnTime);//24.2.23
				CHECK_DEC(L_InLetMovementOffTime);//24.2.23
				CHECK_DEC(L_FlowMPreSecTime);//24.2.23
			}
		}
		
		// if(F_EdOpenOnce)
		// {
		// 	if(++L_EdOpenOnceTime >= 3)
		// 	{
		// 		F_EdCloseOnce = 1;
		// 	}
		// }
		// else
		// {
		// 	L_EdOpenOnceTime = 0;
		// 	F_EdCloseOnce = 0;
		// }
		
		if(F_WDIsCommunicating||F_FCTing)
		{
			if(L_CommunicatErrTime)
			{
				L_CommunicatErrTime = 0;
			}
		}
		else
		{
			if(++L_CommunicatErrTime >= 100)
			{
				L_CommunicatErrTime = 0;
				if(!F_IsBuzzing)
				{
					Buzz_SetType(BUZZ_KEY_INVALID);
				}
			}
		}
	}
	
	if(F_FlowCheckEn)
	{
		CheckFillErr();
	}
	else
	{
		if(!F_IsInLetting)
		{
			FlowMCnt = 0;
		}
	}
	
	if(Load_Timer10ms != F_Base10ms)
	{
		Load_Timer10ms = F_Base10ms;

		OutputEn();

		SetPin(HEAT, Load_R);
		SetPin(PS, Load_Ps);
		SetPin(PTC, Load_Ptc);
		SetPin(WP, Load_Ml);
		SetPin(INP, Load_Ip);//SetPin(INP, 1);
		SetPin(IV, Load_Ev1);
		//厂测IO驱动，非厂测优先模拟串口驱动
		#if NEWTYPE1
		SetPin(FAN, Load_Fan);
		if(F_FCTing)
		{
			SetPin(LED, Load_Led);
		}
		else
		{
			#if (0 == CONFIG_UARTSIMULATE)
			SetPin(LED, Load_Led);
			#endif
		}
		#else
		SetPin(MP, Load_Mp);
		SetPin(FAN_IN, Load_Fan);
		SetPin(FAN_OUT, Load_Fan2);
		SetPin(UV, Load_Led);
		#endif
	}
	
}
/**
 *------------------------------------------------------------------------------
 * private functions
 *------------------------------------------------------------------------------
 */
static void CheckFillErr(void)
{
	if(F_IsInLetting)
	{
		if(F_FlowCheck)
		{
			if(!F_FlowCheckInit)
			{
				F_FlowChecking = 0;
				F_FlowCheckOK = 0;
				F_InLetMovement = 0;
				F_FlowCheckInit = 1;
				L_InLetCloseDelayTime = 9;
				L_FlowMSecWithErrCnt_1S = 0;
				L_FlowMPreSecTime = 0;
				L_InLetMovementOnTime = 0;
				L_InLetMovementOffTime = 0;
			}
			
			if(L_InLetMovementOnTime)
			{
				F_FlowChecking = 0;
				F_InLetMovement = 1;
				L_InLetMovementOffTime = 45;
			}
			else if(L_InLetCloseDelayTime > 0)
			{
				F_FlowChecking = 0;
				F_InLetMovement = 0;
				L_FlowMPreSecTime = 10;
				FlowMPreSecErrCnt = 3;
			}
			else
			{
				F_FlowChecking = 1;
				F_InLetMovement = 0;
				if(0==L_FlowMPreSecTime)
				{
					L_FlowMPreSecTime = 10;
					if(0==FlowMPreSecErrCnt)
					{
						L_FlowMSecWithErrCnt_1S++;
							
						if((L_FlowMSecWithErrCnt_1S >= 2)&&(0==L_InLetMovementOffTime))
						{
							L_InLetMovementOnTime = 5;
						}
					}
					else
					{
						L_FlowMSecWithErrCnt_1S = 0;
						F_FlowCheckOK = 1;
					}
					FlowMPreSecErrCnt = 3;
				}
			}
		}
	}
	else
	{
		F_FlowCheck = F_FlowCheckInit = F_InLetMovement = F_FlowCheckOK = F_FlowChecking = 0;
		FlowMCnt = 0;
	}
	
	if(F_ErrReload)
	{
		FlowMErrCnt = 0;
	}
}

static void OutputEn(void)
{
	if(F_WDIsCommunicating && F_WDHasCommunicated)
	{
		//发热盘驱动
		Load_R = F_RelayHEAT;
		//排水泵驱动
		Load_Ps = F_RelayDP;
		//PTC驱动
		Load_Ptc = F_RelayPTC;
		//洗涤泵驱动//限制洗涤时开门喷水
		if(GetPin(DOOR))
		{//20251203 if(Signal_DoorSwitch)//20251213 if(GetPin(DOOR))
			Load_Ml = 0;
		}
		else
		{
			Load_Ml = F_OutputWP;
		}
		//进风机驱动
		Load_Fan = F_OutputFANIN;
		//蠕动泵驱动//限制蠕动泵配置
		Load_Mp = F_OutputMP & F_MovePumpEn;
		//进水驱动//限制流量检测//限制进水方式//Load_Ip = F_OutputIP;
		if((F_IsInLetting && (FlowMCnt <= FlowMCntSet))||F_InLetMovement)
		{
			Load_Ev1 = F_OutputIV & F_IvEn;
			Load_Ip = F_OutputIP & F_IpEn;
		}
		else
		{
			Load_Ip = 0;
			Load_Ev1 = 0;	
		}
		//排风机驱动//限制排风机配置
		Load_Fan2 = F_OutputFANOUT & F_OutFanEn;
		//筒灯驱动//限制夜灯配置//兼容夜灯驱动筒灯
		if(F_NlEn)
		{
			if(NL_State!=0)
			{
				Load_Led = 1;
			}
			else
			{
				Load_Led = 0;
			}
		}
		else
		{
			Load_Led = F_OutputUV;
		}
		//臭氧驱动//限制臭氧配置//限制进水阀共用//20260430
		if((F_O3En)&&(0==F_IvEn))
		{
			Load_Ev1 = F_OutputO3;
		}
	}
	else if(F_FCTing)
	{
		switch(Test_FctingActionCount0)
		{
			case 0://20251115
				Load_Ps = 0;
				Load_R = 0;
				Load_Ptc = 0;
			case 1://??1
				Load_Ps = 1;
				Load_R = 0;
				Load_Ptc = 0;
				break;
			case 2://??2
				Load_Ps = 1;//20251115
				Load_R = 1;
				Load_Ptc = 0;
				break;
			case 3://??3
				Load_Ps = 1;//20251115
				Load_R = 1;//20251115
				Load_Ptc = 1;
				break;
			default://20251115
				Load_Ps = 1;
				Load_R = 1;
				Load_Ptc = 1;
				break;
		}

		if(Test_FctingActionCount1 < 6)
		{
			switch(Test_FctingActionCount1)
			{//D1~D5
				case 1:
					Load_Ml = 1;
					Load_Ip = 0;
					Load_Fan = 0;
					IoUart_TxOutput = Load_Led = 0;
					Load_Ev1 = 0;
					break;
				case 2:
					Load_Ml = 1;
					Load_Ip = 1;
					Load_Fan = 0;
					IoUart_TxOutput = Load_Led = 0;
					Load_Ev1 = 0;
					break;
				case 3:
					Load_Ml = 1;
					Load_Ip = 1;
					Load_Fan = 1;
					IoUart_TxOutput = Load_Led = 0;
					Load_Ev1 = 0;
					break;
				case 4:
					Load_Ml = 1;
					Load_Ip = 1;
					Load_Fan = 1;
					IoUart_TxOutput = Load_Led = 1;
					Load_Ev1 = 0;
					break;
				case 5:
					Load_Ml = 1;
					Load_Ip = 1;
					Load_Fan = 1;
					IoUart_TxOutput = Load_Led = 1;
					Load_Ev1 = 1;
					break;
				default:
					Load_Ml = 0;
					Load_Ip = 0;
					Load_Fan = 0;
					IoUart_TxOutput = Load_Led = 0;
					Load_Ev1 = 0;
					break;
			}
		}
		else
		{
			Load_Ml = !P06;
			Load_Ip = !P07;
			Load_Fan = !P24;
			IoUart_TxOutput = Load_Led = F_WDIsCommunicating;
			if((Temperature_AdValue>80)&&(Temperature_AdValue<90))
			{
				Load_Ev1 = 1;
			}
			else
			{
				Load_Ev1 = 0;
			}
		}

	}
	else
	{
		Load_R = 0;
		Load_Ps = 0;
		Load_Ptc = 0;
		Load_Ml = 0;
		Load_Ip = 0;
		Load_Mp = 0;
		Load_Ev1 = 0;
		Load_Fan = 0;
		Load_Fan2 = 0;
		Load_Led = 0;		
		F_IsInLetting = 0;
		F_BuzzReceived = 0;
	}
}

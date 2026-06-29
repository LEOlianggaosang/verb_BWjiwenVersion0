/**
*******************************************************************************
 * Copyright (c) 20250606
 * 
* @file    WashDish.c
* @author  lianggaosang@qq.com
* @brief   奶瓶机机串口通信
* 
*******************************************************************************
*/
#include "WashDish.h"
#include "SerialDrv.h"
#include "Buzzer\Buzzer.h"//Buzz_IsBuzzing//Buzz_IsCompleted
#include "LoadDrive\LoadDrive.h"//LoadEnable
#include "ReadSwitch\ReadSwitch.h"//SwitchFlag
#include "Temperatures\Temperatures.h"//AdErrFlag
#include "TicketHandling\TicketHandling.h"
#include "IoUart_Simulate\IoUart_Simulate.h"
//*******************************************************************************
/*
SendDatasBuf[0] = 0xaa;
SendDatasBuf[1] = 0x55;
SendDatasBuf[2] = 0x40;
SendDatasBuf[3] = len;
SendDatasBuf[4] = C_RECE;
SendDatasBuf[5] = Relay;
SendDatasBuf[6] = Output;
SendDatasBuf[7] = PowerFlag;
SendDatasBuf[8] = AdErrFlag;
SendDatasBuf[9] = Temperature_Value;
SendDatasBuf[10] = Temperature_AdValue>>8;
SendDatasBuf[11] = (unsigned char)Temperature_AdValue;
SendDatasBuf[12] = P_AdValue>>8;
SendDatasBuf[13] = (unsigned char)P_AdValue;
SendDatasBuf[14] = P_FlowMCnt>>8;
SendDatasBuf[15] = (unsigned char)P_FlowMCnt;
SendDatasBuf[16] = P_FlowMErrCnt>>8;
SendDatasBuf[17] = (unsigned char)P_FlowMErrCnt;
SendDatasBuf[18] = Power_CheckSum;
*/
/*
ReceiveDatasBuf[0] = 0xa5;
ReceiveDatasBuf[1] = 0x5a;
ReceiveDatasBuf[2] = 0x04;
ReceiveDatasBuf[3] = len;
ReceiveDatasBuf[4] = C_TRANS;
ReceiveDatasBuf[5] = RelayEnable;
ReceiveDatasBuf[6] = OutputEnable;
ReceiveDatasBuf[7] = BeepState;
ReceiveDatasBuf[8] = InletEnable;
ReceiveDatasBuf[9] = Power_CheckSum;
//Work_CurrentState
//Work_CurrentMenu
//Work_CurrentStage
//Work_CurrentStep
//Work_CurrentFnIndex
//Work_CurrentArg
//Work_UsedSecondInCurrentStep
//Work_LeftMinToEnd
//currentFunctionUnitUsedSeconds
//currentStepMaxDuationSecond
//WorkActionFlag
//WorkFuctionFlag
*/
/*
 *------------------------------------------------------------------------------
 * status:
 * 
 *------------------------------------------------------------------------------
 */

static     	ByteFlag 			MiddleData_Flags = {0};
#define		MiddleData			MiddleData_Flags.f_byte
#define		F_MiddleData_0		MiddleData_Flags.f_bits.no0
#define		F_MiddleData_1		MiddleData_Flags.f_bits.no1
#define		F_MiddleData_2		MiddleData_Flags.f_bits.no2
#define		F_MiddleData_3		MiddleData_Flags.f_bits.no3
#define		F_MiddleData_4		MiddleData_Flags.f_bits.no4
#define		F_MiddleData_5		MiddleData_Flags.f_bits.no5
#define		F_MiddleData_6		MiddleData_Flags.f_bits.no6
#define		F_MiddleData_7		MiddleData_Flags.f_bits.no7
static UCHAR_XDATA  ReceiveDatasBuf[MESSAGE_DATA_LENGTH] = {0};
static UCHAR_XDATA  SendDatasBuf[MESSAGE_DATA_LENGTH] = {0};
#if CONFIG_FCT_UART
static UCHAR_XDATA  Fct_ReceiveDatasBuf[MESSAGE_DATA_LENGTH] = {0};//20251025
static UCHAR_XDATA  Fct_SendDatasBuf[MESSAGE_DATA_LENGTH] = {0};//20251025
#endif
static UCHAR_XDATA  NL_SendDatasBuf[NIGHTLIGHT_DATA_LENGTH] = {0};//20251020
static UCHAR_XDATA  NL_ReceiveDatasBuf[NIGHTLIGHT_DATA_LENGTH] = {0};//20251020
static UCHAR_XDATA	WashDish_CurrentState = 0;
static UCHAR_XDATA	WashDish_CurrentMenu = 0;
static UCHAR_XDATA	WashDish_CurrentStage = 0;
static UCHAR_XDATA	WashDish_CurrentStep = 0;
static UCHAR_XDATA	WashDish_CurrentFnIndex = 0;
static UINT_XDATA	WashDish_CurrentArg = 0;
static UINT_XDATA	WashDish_UsedSecondInCurrentStep = 0;
static UINT_XDATA	WashDish_LeftMinToEnd = 0;
static UINT_XDATA	WashDish_currentFunctionUnitUsedSeconds = 0;
static UINT_XDATA	WashDish_currentStepMaxDuationSecond = 0;
static UCHAR_XDATA	WashDish_WorkActionFlag = 0;
static UCHAR_XDATA	WashDish_WorkFuctionFlag = 0;
static UCHAR_XDATA	WashDish_Error_CurrentCode = 0;
static UCHAR_XDATA	NightLight_R = 0;
static UCHAR_XDATA	NightLight_G = 0;
static UCHAR_XDATA	NightLight_B = 0;
static UCHAR_XDATA	NightLight_TYPE = 0;
/*
*------------------------------------------------------------------------------
*/
UCHAR_XDATA	Current_W_State = C_TRANS_NONE;
UCHAR_XDATA	Current_D_State = C_RECE_NONE;
UCHAR_XDATA	WD_Version_Number = 0;
UCHAR_XDATA	P_Options[3] = {0};
UCHAR_XDATA	D_Options[3] = {0};
ByteFlag U_WashDishFlag = {0};
ByteFlag U_RelayEnables = {0};
ByteFlag U_OutputEnables = {0};
ByteFlag U_InletEnables = {0};
ByteFlag U_Options_0 = {0};
ByteFlag U_Options_1 = {0};
ByteFlag U_Options_2 = {0};
UCHAR_XDATA	WD_BeepState = 0;
UINT_XDATA	FlowMCntSet = 0;
UINT_XDATA	FlowMCnt = 0;
UINT_XDATA	FlowMErrCnt = 0;
UCHAR_XDATA	NL_State = 0;
UCHAR_XDATA Test_WaitFctActionCount = 0;
UCHAR_XDATA Test_FctingActionCount0 = 0;
UCHAR_XDATA Test_FctingActionCount1 = 0;
UINT_XDATA	FeedBackCnt = 0;//20251203
/*
*------------------------------------------------------------------------------
*/
static void WashDish_ReceiveDatas(void);
static void WashDish_FleshDatas(void);
static void WashDish_SandDatas(void);
static void Get_Options(void);
static void NightLight_FleshDatas(void);
static void NightLight_SandDatas(void);
#if CONFIG_FCT_UART
static void Fct_SendDatas(void);
#endif
/*
*------------------------------------------------------------------------------
*/
void Init_WashDish(void)
{
	Uart_ReceiveData(SERIAL_DISPLAY, ReceiveDatasBuf, MESSAGE_DATA_LENGTH);//重置缓存数组指针，打开接收允许
	Uart_Start(SERIAL_DISPLAY);
	#if CONFIG_FCT_UART
	Uart_ReceiveData(SERIAL_FCT, Fct_ReceiveDatasBuf, MESSAGE_DATA_LENGTH);
	Uart_Start(SERIAL_FCT);
	#endif
	WashDishFlag = 0;
	Test_WaitFctActionCount = 60;
}
//每次接收一组数据后关闭，需要手动打开接收允许
/*
*------------------------------------------------------------------------------
*/
void WashDish_Control(void)
{
	static UCHAR_XDATA DispError_100msCnt = 0;
	static UCHAR_XDATA FctError_100ms_cnt = 0;
	static UCHAR_XDATA NightLight_100ms = 0;
	static UCHAR_XDATA i;
	static UCHAR_XDATA bSUM = 0;
	//----------------------------------------------
	if(Uart_IsReceivedDataDone(SERIAL_DISPLAY))
	{
		DispError_100msCnt = 0;
		if((ReceiveDatasBuf[3]>0)&&(ReceiveDatasBuf[3]<MESSAGE_DATA_LENGTH))
		{
			bSUM = 0;
			for(i=0;i<(ReceiveDatasBuf[3]-1);i++)
			{
				bSUM += ReceiveDatasBuf[i];
			}
			//通信状态处理
			if(bSUM == ReceiveDatasBuf[ReceiveDatasBuf[3]-1])
			{
				DispError_100msCnt = 0;
				F_WDIsCommunicating = TRUE;
				if((0xa5==ReceiveDatasBuf[0])&&(0x5a==ReceiveDatasBuf[1])&&(0x04==ReceiveDatasBuf[2]))
				{
					WashDish_ReceiveDatas();
					F_WDReplyAsking = TRUE;
				}
			}
		}
		Uart_ReceiveData(SERIAL_DISPLAY, ReceiveDatasBuf, MESSAGE_DATA_LENGTH);
	}
	#if CONFIG_FCT_UART
	if(Uart_IsReceivedDataDone(SERIAL_FCT))
	{
//		if((!F_WDIsCommunicating)&&(!F_FCTing))
//		{//连接
//			F_WDHasCommunicated = 0;
		if((!F_WDHasCommunicated)&&(!F_FCTing))
		{//短接
			Buzz_SetType(BUZZ_ENTERCHECK);
			F_FCTing = 1;
			Test_FctingActionCount0 = 1;
			Test_FctingActionCount1 = 0;
		}
		FctError_100ms_cnt = 0;
		Uart_ReceiveData(SERIAL_FCT, Fct_ReceiveDatasBuf, MESSAGE_DATA_LENGTH);
	}
	#endif
	//----------------------------------------------
	if(Disp_Timer100ms != F_Base100ms)
	{
		Disp_Timer100ms = F_Base100ms;
		if(++DispError_100msCnt >= 10)
		{
			DispError_100msCnt = 0;
			if(F_WDHasCommunicated)
			{
				Buzz_SetType(BUZZ_ALARM);
				F_WDHasCommunicated = FALSE;
				Current_W_State = C_TRANS_NONE;
				WD_BeepState = BUZZ_NONE;
			}
			F_WDIsCommunicating = FALSE;
			F_WDReplyAsking = 1;
		}
		if(F_WDReplyAsking)
		{
			WashDish_FleshDatas();
			WashDish_SandDatas();
			F_WDReplyAsking = 0;
		}
		#if CONFIG_FCT_UART
		if(F_FCTing||(Test_WaitFctActionCount>0))
		{
			Fct_SendDatas();
			if(++FctError_100ms_cnt > 10)
			{
				if(F_FCTing)
				{//20251124
					F_WDHasCommunicated = FALSE;
					F_WDIsCommunicating = FALSE;
				}
				F_FCTing = 0;
				FctError_100ms_cnt = 0;
				Uart_ReceiveData(SERIAL_FCT, Fct_ReceiveDatasBuf, MESSAGE_DATA_LENGTH);
			}
		}
		#endif

		NightLight_FleshDatas();
	
		if(++NightLight_100ms >= 10)
		{
			NightLight_100ms = 0;
			CHECK_DEC(Test_WaitFctActionCount);
			if(F_FCTing)
			{
				if(++Test_FctingActionCount0 >= 4)
				{
					Test_FctingActionCount0 = 4;//20251115
				}
				if(++Test_FctingActionCount1 >= 6)//20251114
				{
					Test_FctingActionCount1 = 6;
				}
			}
			else
			{
				NightLight_SandDatas();
			}
		}
	}
//#endif
}
// FlowMCntSet = COMBINE_2BYTE(ReceiveDatasBuf[14],ReceiveDatasBuf[13]);
// WashDish_ErrorDeal_Priority = (ReceiveDatasBuf[21] & 0xf0)>>4;
static void WashDish_ReceiveDatas(void)
{
	/* Current_D_State */
	//----------------------------------------------
	Current_D_State = (ReceiveDatasBuf[4]>>4);
	if(C_TRANS_FIRST == Current_D_State)
	{
		F_WDHasCommunicated = 1;
	}
	else if(C_TRANS_NONE == Current_D_State)
	{
		F_WDHasCommunicated = 0;
	}
	/* Current_W_State */
	//----------------------------------------------
	switch (ReceiveDatasBuf[4]&0x0f)
	{
		case C_RECE_FIRST://#define		C_RECE_FIRST	0x09
			WD_Version_Number = ReceiveDatasBuf[5];
			P_Options[0] = ReceiveDatasBuf[6];
			P_Options[1] = ReceiveDatasBuf[7];
			P_Options[2] = ReceiveDatasBuf[8];
			Get_Options();
			Current_W_State = C_TRANS_FIRST;
			break;
		case C_RECE_NORMAL:
			RelayEnable = ReceiveDatasBuf[5];
			OutputEnable = ReceiveDatasBuf[6];
			WD_BeepState = ReceiveDatasBuf[7];
			if(0xff == WD_BeepState)
			{
				F_BuzzReceived = 0;
			}
			else
			{
				if((!F_BuzzReceived)||(!F_IsBuzzing)||(BUZZ_SILENCE == WD_BeepState))//WD_BeepState!=0xff且F_BuzzReceived==0
				{
					
					F_BuzzReceived = 1;
					Buzz_SetType(WD_BeepState);
				}
				
//				if(F_IsBuzzing&&(BUZZ_SILENCE != WD_BeepState))
//				{
//					F_BuzzReceived = 1;
//				}
//				else
//				{
//					if(!F_BuzzReceived)
//					{
//						F_BuzzReceived = 1;
//						Buzz_SetType(WD_BeepState);
//					}
//				}
			}
			MiddleData = ReceiveDatasBuf[8];
			F_IsInLetting = F_MiddleData_0;
			F_ErrReload = F_MiddleData_1;
			F_Lack = F_MiddleData_2;
			F_FlowCheck = F_MiddleData_3;
			F_FlowCheckInit = F_MiddleData_4;
			FlowMCntSet = COMBINE_2BYTE(ReceiveDatasBuf[10], ReceiveDatasBuf[9]);
			NL_State = ReceiveDatasBuf[11];

			if(F_MoreMessageEn && (ReceiveDatasBuf[3] > 15))
			{
				WashDish_CurrentState = ReceiveDatasBuf[11];
				WashDish_CurrentMenu = ReceiveDatasBuf[12];
				WashDish_CurrentStage = ReceiveDatasBuf[13];
				WashDish_CurrentStep = ReceiveDatasBuf[14];
				WashDish_CurrentFnIndex = ReceiveDatasBuf[15];
				WashDish_CurrentArg = COMBINE_2BYTE(ReceiveDatasBuf[17], ReceiveDatasBuf[16]);
				WashDish_UsedSecondInCurrentStep = COMBINE_2BYTE(ReceiveDatasBuf[19], ReceiveDatasBuf[18]);
				WashDish_LeftMinToEnd = COMBINE_2BYTE(ReceiveDatasBuf[21], ReceiveDatasBuf[20]);
				WashDish_currentFunctionUnitUsedSeconds = COMBINE_2BYTE(ReceiveDatasBuf[23], ReceiveDatasBuf[22]);
				WashDish_currentStepMaxDuationSecond = COMBINE_2BYTE(ReceiveDatasBuf[25], ReceiveDatasBuf[24]);
				WashDish_WorkActionFlag = ReceiveDatasBuf[26];
				WashDish_WorkFuctionFlag = ReceiveDatasBuf[27];
				WashDish_Error_CurrentCode = ReceiveDatasBuf[28];
			}

			if(F_WDHasCommunicated)
			{
				Current_W_State = C_TRANS_NORMAL;
			}
			else
			{
				Current_W_State = C_TRANS_FIRST;
			}
			break;
		case C_RECE_FCT:
			Current_W_State = C_TRANS_FCT;
			if(!F_FCTing)
			{
				F_FCTing = 1;
			}
			break;
		default:
			Current_W_State = C_TRANS_NONE;
			break;
	}
	return;
}


static void WashDish_FleshDatas(void)
{
	static UCHAR_XDATA i;

    /* start byte */
	SendDatasBuf[0] = 0xaa;
	SendDatasBuf[1] = 0x55;
	/* number of Equipment */
	SendDatasBuf[2] = 0x40;
	//----------------------------------------------
	SendDatasBuf[4] = 0;
	switch(Current_W_State)
	{
		case C_TRANS_FIRST://#define		C_TRANS_FIRST	0x01
			SendDatasBuf[3] = 10;
			SendDatasBuf[4] |= (unsigned char)(ReceiveDatasBuf[4]<<4);
			SendDatasBuf[4] |= C_TRANS_FIRST;
			SendDatasBuf[5] = (unsigned char)VERSION_NUMBER;
			SendDatasBuf[6] = D_Options[0];
			SendDatasBuf[7] = D_Options[1];
			SendDatasBuf[8] = D_Options[2];
			break;
		case C_TRANS_NORMAL://#define		C_TRANS_NORMAL	0x02
			SendDatasBuf[3] = 21;//20251203
			SendDatasBuf[4] |= (ReceiveDatasBuf[4]<<4);
			SendDatasBuf[4] |= C_TRANS_NORMAL;
			MiddleData = 0;
			F_MiddleData_2 = F_IsBuzzing;
			F_MiddleData_3 = F_BuzzReceived;
			F_MiddleData_4 = Signal_DoorSwitch;
			F_MiddleData_5 = F_InLetMovement;
			F_MiddleData_6 = F_FlowCheckOK;
			F_MiddleData_7 = F_FlowChecking;
			SendDatasBuf[7] = MiddleData;
			SendDatasBuf[8] = AdErrFlag;
			SendDatasBuf[9] = Temperature_Value;
			SendDatasBuf[10] = (unsigned char)(Temperature_AdValue>>8);
			SendDatasBuf[11] = (unsigned char)Temperature_AdValue;
			// SendDatasBuf[13] = (unsigned char)(P_AdValue>>8);
			// SendDatasBuf[12] = (unsigned char)P_AdValue;
			SendDatasBuf[14] = (unsigned char)(FlowMCnt>>8);
			SendDatasBuf[15] = (unsigned char)FlowMCnt;
			SendDatasBuf[16] = (unsigned char)(FlowMErrCnt>>8);
			SendDatasBuf[17] = (unsigned char)FlowMErrCnt;
			SendDatasBuf[18] = (unsigned char)(FeedBackCnt>>8);//20251203
			SendDatasBuf[19] = (unsigned char)FeedBackCnt;//20251203
			break;
		// case C_TRANS_FCT://#define		C_TRANS_FCT	0x04
		// 	Power_SendDatasBuf[3] = 10;
		// 	Power_SendDatasBuf[4] = C_TRANS_FCT;
		// 	break;
		default://使电源板重新握手//#define		C_TRANS_NONE	0x00
			SendDatasBuf[3] = 10;
			SendDatasBuf[4] = C_TRANS_FIRST;
			SendDatasBuf[5] = (unsigned char)VERSION_NUMBER;
			SendDatasBuf[6] = D_Options[0];
			SendDatasBuf[7] = D_Options[1];
			SendDatasBuf[8] = D_Options[2];
			break;
	}
	//----------------------------------------------
	/* Sum */
	SendDatasBuf[SendDatasBuf[3]-1]	= 0;
	for(i=0;i<(SendDatasBuf[3]-1);i++)
	{
		SendDatasBuf[SendDatasBuf[3]-1] += SendDatasBuf[i];
	}
	return;

}

static void WashDish_SandDatas(void)
{
	Uart_SendData(SERIAL_DISPLAY, SendDatasBuf, SendDatasBuf[3]);
	return;
}

#if CONFIG_FCT_UART
static void Fct_SendDatas(void)
{
	unsigned char i = 0;

 	Fct_SendDatasBuf[0] = 0xaa;
	Fct_SendDatasBuf[1] = 0x55;
	Fct_SendDatasBuf[2] = 0x40;
	Fct_SendDatasBuf[3] = 6;         
	Fct_SendDatasBuf[4] = C_TRANS_FCT;
	if(F_FCTing)
	{
		Fct_SendDatasBuf[4] |= (UCHAR)(C_RECE_FCT<<4);
	}

	Fct_SendDatasBuf[Fct_SendDatasBuf[3]-1] = 0;
	for(i = 0; i < (Fct_SendDatasBuf[3]-1); i++)
	{
		Fct_SendDatasBuf[Fct_SendDatasBuf[3]-1] += Fct_SendDatasBuf[i];
	}
	Uart_SendData(SERIAL_FCT, Fct_SendDatasBuf, Fct_SendDatasBuf[3]);
}
 /* ----------------------------------------------------- */
#endif


static void Get_Options(void)
{
	Option0 = P_Options[0];
	Option1 = P_Options[1];
	Option2 = P_Options[2];
}

static void NightLight_FleshDatas(void)
{
	if(F_WDIsCommunicating && F_WDHasCommunicated)
	{
		switch(NL_State&0x0f)
		{
			case RGB_OFF:
				NightLight_R = 0;
				NightLight_G = 0;
				NightLight_B = 0;
				break;
			case RGB_RED:
				NightLight_R = 255;
				NightLight_G = 0;
				NightLight_B = 0;
				break;
			case RGB_GREEN:
				NightLight_R = 0;
				NightLight_G = 255;
				NightLight_B = 0;
				break;
			case RGB_BLUE:
				NightLight_R = 0;
				NightLight_G = 0;
				NightLight_B = 255;
				break;
			case RGB_WHITE:
				NightLight_R = 255;
				NightLight_G = 255;
				NightLight_B = 255;
				break;
			case RGB_YELLOW:
				NightLight_R = 255;
				NightLight_G = 255;
				NightLight_B = 0;
				break;
			case RGB_CYAN:
				NightLight_R = 0;
				NightLight_G = 255;
				NightLight_B = 255;
				break;
			case RGB_PURPLE:
				NightLight_R = 255;
				NightLight_G = 0;
				NightLight_B = 255;
				break;
			case RGB_ORANGE:
				NightLight_R = 255;
				NightLight_G = 100;
				NightLight_B = 0;
				break;
			case RGB_PINK:
				NightLight_R = 255;
				NightLight_G = 0;
				NightLight_B = 100;
				break;
			case RGB_SPRING:
				NightLight_R = 100;
				NightLight_G = 255;
				NightLight_B = 0;
				break;
			case RGB_SKY:
				NightLight_R = 0;
				NightLight_G = 255;
				NightLight_B = 100;
				break;
			case RGB_VIOLET:
				NightLight_R = 100;
				NightLight_G = 0;
				NightLight_B = 255;
				break;
			case RGB_INDIGO:
				NightLight_R = 0;
				NightLight_G = 100;
				NightLight_B = 255;
				break;
			case RGB_WARM:
				NightLight_R = 255;
				NightLight_G = 100;
				NightLight_B = 100;
				break;
			case RGB_COLD:
				NightLight_R = 100;
				NightLight_G = 100;
				NightLight_B = 255;
				break;
			default:
				NightLight_R = 255;
				NightLight_G = 255;
				NightLight_B = 255;
				break;			
		}

		NightLight_TYPE = NL_State>>4;
	}
	else
	{
		NightLight_R = 0;
		NightLight_G = 0;
		NightLight_B = 0;
		// NightLight_R = 255;
		// NightLight_G = 255;
		// NightLight_B = 255;
		NightLight_TYPE = 0;
	}
}


static void NightLight_SandDatas(void)
{
	static UCHAR_XDATA i;
	/* start byte */
	NL_SendDatasBuf[0] = 0xaa;
	NL_SendDatasBuf[1] = 0x04;
	//----------------------------------------------
	NL_SendDatasBuf[2] = NightLight_R;
	NL_SendDatasBuf[3] = NightLight_G;
	NL_SendDatasBuf[4] = NightLight_B;
	NL_SendDatasBuf[5] = NightLight_TYPE;
	//----------------------------------------------
	/* Sum */
	NL_SendDatasBuf[6]	= 0;
	for(i=2;i<NIGHTLIGHT_DATA_LENGTH-1;i++)
	{
		NL_SendDatasBuf[6] += NL_SendDatasBuf[i];
	}
	#if (CONFIG_NIGHTLIGHT&&CONFIG_UARTSIMULATE)
	if((!IoUart_RxStart)&&(!(IoUart_TxStart&&(!IoUart_TxHasSand))))
	{
		IoUart_SandEnable(NL_SendDatasBuf, NIGHTLIGHT_DATA_LENGTH);
	}
	#endif
	return;
}
/**
*******************************************************************************
 * Copyright (c) 2025.5.17
 * 
* @file    Power.c
* @author  lianggaosang@qq.com
* @brief   8616b奶瓶机显示板
* 
*******************************************************************************
*/
#include "Power.h"
#include "Work\Work.h"
#include "TicketHandling\TicketHandling.h"
#include "key\key.h"
#include "Display\Display.h"
#include "Light\Light.h"
//*******************************************************************************
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
static UCHAR_XDATA 	P_Relay = 0;
static UCHAR_XDATA 	P_Output = 0;
static UINT_XDATA 	P_AdValue = 0;
static UCHAR_XDATA  Power_ReceiveDatasBuf[POWER_DATA_LENGTH] = {0};
static UCHAR_XDATA  Power_SendDatasBuf[POWER_DATA_LENGTH] = {0};
#if CONFIG_FCT_UART
static UCHAR_XDATA  Fct_ReceiveDatasBuf[POWER_DATA_LENGTH] = {0};
static UCHAR_XDATA  Fct_SendDatasBuf[POWER_DATA_LENGTH] = {0};
#endif
static unsigned char Display_CheckSum(void);
/*
*------------------------------------------------------------------------------
*/
ByteFlag 			Power_Flags = {0};//t
ByteFlag 			Relay_Enables = {0};//t
ByteFlag 			Output_Enables = {0};//t
ByteFlag 			Inlet_Enables = {0};//t
ByteFlag 			AdErr_Flags = {0};//r
UCHAR_XDATA 		P_Version_Number = 0;
UCHAR_XDATA 		Temperature_Value = 0;//r
UINT_XDATA 			Temperature_AdValue = 0;//r
UINT_XDATA 			P_FlowMCnt = 0;//r
UINT_XDATA 			P_FlowMErrCnt = 0;//r
UINT_XDATA 			P_FeedBackCnt = 0;//20251203
UCHAR_XDATA 		BeepState = BUZZ_NONE;//t
UCHAR_XDATA 		P_Options[3] = {0};
UCHAR_XDATA 		D_Options[3] = {0};
/*
*------------------------------------------------------------------------------
*/
static void Power_ReceiveDatas(void);
static void Power_SendDatas(void);
static unsigned char Power_CheckSum(void);
#if CONFIG_FCT_UART
static void Fct_SendDatas(void);
static unsigned char Fct_CheckSum(void);
#endif
/*
*------------------------------------------------------------------------------
*/
void Init_Power(void)
{
	Uart_ReceiveData(SERIAL_POWER, Power_ReceiveDatasBuf, POWER_DATA_LENGTH);//重置缓存数组指针，打开接收允许
	Uart_Start(SERIAL_POWER);
	#if CONFIG_FCT_UART
	Uart_ReceiveData(SERIAL_FCT, Fct_ReceiveDatasBuf, POWER_DATA_LENGTH);
	Uart_Start(SERIAL_FCT);
	#endif
	Power_IsCommunicating = Power_hasCommunicated = 0;
	Power_BuzzReceived = 1;
}		
//每次接收一组数据后关闭，需要手动打开接收允许
/*
*------------------------------------------------------------------------------
*/
void Power_Control(void)
{
	static UCHAR_XDATA PowerErr_100ms_cnt = 0;
	static UCHAR_XDATA FctErr_100ms_cnt = 0;
	static UCHAR_XDATA PowerIndex_100ms_cnt = 0;
	//-----------------------------------------------
	if(Uart_IsReceivedDataDone(SERIAL_POWER))
	{
		Power_IsCommunicating = 1;
		if((0xaa == Power_ReceiveDatasBuf[0])&&(0x55 == Power_ReceiveDatasBuf[1])&&(0x40 == Power_ReceiveDatasBuf[2]))
		{
			Power_ReceiveDatas();
		}
		PowerErr_100ms_cnt = 0;
		Uart_ReceiveData(SERIAL_POWER, Power_ReceiveDatasBuf, POWER_DATA_LENGTH);
	}

	#if CONFIG_FCT_UART
	if(Uart_IsReceivedDataDone(SERIAL_FCT))
	{
//		if((!Power_IsCommunicating)&&(!Fcting))
//		{//连接
//			Power_hasCommunicated = 0;
		if((!Power_hasCommunicated)&&(!Fcting))
		{//短接
			BeepState = BUZZ_ENTERCHECK;
			FctActionFlag = 0;
			Fcting = 1;
			FctKeyCnt = 10;
		}
		FctErr_100ms_cnt = 0;
		Uart_ReceiveData(SERIAL_FCT, Fct_ReceiveDatasBuf, POWER_DATA_LENGTH);
	}
	#endif
	//----------------------------------------------
	if(F_Power100ms != F_Base100ms)
	{
		F_Power100ms = F_Base100ms;
		if(++PowerIndex_100ms_cnt >= 2)
		{
			PowerIndex_100ms_cnt = 0;
			Power_SendDatas();
		}


		#if CONFIG_FCT_UART
		if(Fcting||(Test_WaitKeyActionCount>0))
		{
			Fct_SendDatas();
			if(++FctErr_100ms_cnt > 30)
			{
				if(Fcting)
				{//20251124
					Power_IsCommunicating = 0;
					Power_hasCommunicated = 0;
				}
				Fcting = 0;

				FctErr_100ms_cnt = 0;
				Uart_ReceiveData(SERIAL_FCT, Fct_ReceiveDatasBuf, POWER_DATA_LENGTH);
			}
		}
		#endif
		if(++PowerErr_100ms_cnt > 30)
		{
			PowerErr_100ms_cnt = 0;
			Power_IsCommunicating = 0;
			Power_hasCommunicated = 0;
			Power_BuzzReceived = 1;
			Uart_ReceiveData(SERIAL_POWER, Power_ReceiveDatasBuf, POWER_DATA_LENGTH);
		}
	}
}
 /* ----------------------------------------------------- */
/*
Power_ReceiveDatasBuf[0] = 0xaa;
Power_ReceiveDatasBuf[1] = 0x55;
Power_ReceiveDatasBuf[2] = 0x40;
Power_ReceiveDatasBuf[3] = len;
Power_ReceiveDatasBuf[4] = C_RECE;
Power_ReceiveDatasBuf[5] = Relay;
Power_ReceiveDatasBuf[6] = Output;
Power_ReceiveDatasBuf[7] = PowerFlag;
Power_ReceiveDatasBuf[8] = AdErrFlag;
Power_ReceiveDatasBuf[9] = Temperature_Value;
Power_ReceiveDatasBuf[10] = Temperature_AdValue>>8;
Power_ReceiveDatasBuf[11] = (unsigned char)Temperature_AdValue;
Power_ReceiveDatasBuf[12] = P_AdValue>>8;
Power_ReceiveDatasBuf[13] = (unsigned char)P_AdValue;
Power_ReceiveDatasBuf[14] = P_FlowMCnt>>8;
Power_ReceiveDatasBuf[15] = (unsigned char)P_FlowMCnt;
Power_ReceiveDatasBuf[16] = P_FlowMErrCnt>>8;
Power_ReceiveDatasBuf[17] = (unsigned char)P_FlowMErrCnt;
Power_ReceiveDatasBuf[18] = Power_CheckSum;
*/
static void Power_ReceiveDatas(void)
{//根据接收类型进行回复
	switch(Power_ReceiveDatasBuf[4]&0x0f)
	{
		case C_RECE_FIRST://#define		C_RECE_FIRST	0x01
			P_Version_Number = Power_ReceiveDatasBuf[5];
			P_Options[0] = Power_ReceiveDatasBuf[6];
			P_Options[1] = Power_ReceiveDatasBuf[7];
			P_Options[2] = Power_ReceiveDatasBuf[8];
			break;
			
		case C_RECE_NORMAL://#define		C_RECE_NORMAL	0x02
			P_Relay = Power_ReceiveDatasBuf[5];
			P_Output = Power_ReceiveDatasBuf[6];
			MiddleData = Power_ReceiveDatasBuf[7];
			Power_IsBuzzing = F_MiddleData_2;
			Power_BuzzReceived = F_MiddleData_3;
			Power_DoorIsOpend = F_MiddleData_4;
			Inlet_InLetMovement = F_MiddleData_5;
			Inlet_FlowCheckOk = F_MiddleData_6;
			Inlet_FlowChecking = F_MiddleData_7;
			MiddleData = Power_ReceiveDatasBuf[8];
			AdErr_ErrRe = F_MiddleData_0;
			AdErr_ReShort = F_MiddleData_1;
			AdErr_ReOpen = F_MiddleData_2;
			// AdErrFlag = Power_ReceiveDatasBuf[8];
			Temperature_Value = Power_ReceiveDatasBuf[9];
			Temperature_AdValue = (Power_ReceiveDatasBuf[10]<<8) + Power_ReceiveDatasBuf[11];
			P_AdValue = (Power_ReceiveDatasBuf[12]<<8) + Power_ReceiveDatasBuf[13];
			P_FlowMCnt = (Power_ReceiveDatasBuf[14]<<8) + Power_ReceiveDatasBuf[15];
			P_FlowMErrCnt = (Power_ReceiveDatasBuf[16]<<8) + Power_ReceiveDatasBuf[17];
			if(Power_ReceiveDatasBuf[3] > 19)
			{
				P_FeedBackCnt = (Power_ReceiveDatasBuf[18]<<8) + Power_ReceiveDatasBuf[19];//20251203
			}
			break;
			
		case C_RECE_FCT://#define		C_RECE_FCT		0x04
			Power_hasCommunicated = 0;
			if(!Fcting)
			{//17.FCT模式
				BeepState = BUZZ_ENTERCHECK;
				Fcting = 1;
			}
			break;
		default:
			Power_hasCommunicated = 0;
			break;
	}
}
 /* ----------------------------------------------------- */
/*
Power_SendDatasBuf[0] = 0xa5;
Power_SendDatasBuf[1] = 0x5a;
Power_SendDatasBuf[2] = 0x04;
Power_SendDatasBuf[3] = len;
Power_SendDatasBuf[4] = C_TRANS;
Power_SendDatasBuf[5] = RelayEnable;
Power_SendDatasBuf[6] = OutputEnable;
Power_SendDatasBuf[7] = BeepState;
Power_SendDatasBuf[8] = InletEnable;
Power_SendDatasBuf[9] = Power_CheckSum;
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
//Error_CurrentCode
*/
static void Power_SendDatas(void)
{//默认回复握手，只有握手完成后才进入正常通信
 	Power_SendDatasBuf[0] = 0xa5;
	Power_SendDatasBuf[1] = 0x5a;
	Power_SendDatasBuf[2] = 0x04;
	Power_SendDatasBuf[4] = (unsigned char)(Power_ReceiveDatasBuf[4]<<4);;
	if(Power_hasCommunicated)
	{
		Power_SendDatasBuf[3] = 13;
		Power_SendDatasBuf[4] |= C_TRANS_NORMAL;
		if(Power_BuzzReceived)
		{
			Power_BuzzReceived = 0;
			BeepState = BUZZ_NONE;
		}
		Power_SendDatasBuf[5] = (unsigned char)RelayEnable;
		Power_SendDatasBuf[6] = (unsigned char)OutputEnable;
		Power_SendDatasBuf[7] = (unsigned char)BeepState;
		Power_SendDatasBuf[8] = (unsigned char)(InletEnable&0x1f);
		Power_SendDatasBuf[9] = (unsigned char)FlowMCntSet;
		Power_SendDatasBuf[10] = (unsigned char)(FlowMCntSet>>8);
		Power_SendDatasBuf[11] = (unsigned char)((NightLight_ColorType&0x0f)|(NightLight_ActionType&0xf0));//CONFIG_NIGHT_LIGHT
	}
	else
	{
		Power_SendDatasBuf[3] = 10;
		Power_SendDatasBuf[4] |= C_TRANS_FIRST;
		Power_SendDatasBuf[5] = (unsigned char)VERSION_NUMBER;
		D_Options[0] = (unsigned char)(CONFIG_UART_MORE<<0);
		D_Options[1] = ((unsigned char)(CONFIG_MP_ENABLE<<0))|((unsigned char)(CONFIG_FAN2_ENABLE<<1))|((unsigned char)(CONFIG_FM2_ENABLE<<2))\
		|((unsigned char)(CONFIG_IP_ENABLE<<3))|((unsigned char)(CONFIG_IV_ENABLE<<4))|((unsigned char)(CONFIG_NIGHT_LIGHT<<5)|((unsigned char)(CONFIG_O3_ENABLE<<6)));//20260421 版本0 臭氧功能
		D_Options[2] = ((unsigned char)(CONFIG_FLOW_CHECK<<0))|((unsigned char)(CONFIG_INLET_MODE<<1));
		Power_SendDatasBuf[6] = D_Options[0];
		Power_SendDatasBuf[7] = D_Options[1];
		Power_SendDatasBuf[8] = D_Options[2];
		if((C_TRANS_FIRST==(Power_ReceiveDatasBuf[4]>>4))&&(0x40 == Power_ReceiveDatasBuf[2]))
		{
			Power_hasCommunicated = 1;
		}
	}

	Power_SendDatasBuf[(Power_SendDatasBuf[3]-1)] = Power_CheckSum();
	Uart_SendData(SERIAL_POWER, Power_SendDatasBuf, Power_SendDatasBuf[3]);
}
 /* ----------------------------------------------------- */
static unsigned char Power_CheckSum(void)
{
	unsigned char CheckSum = 0;
	unsigned char i = 0;
	for(i = 0; i < (Power_SendDatasBuf[3]-1); i++)
	{
		CheckSum += Power_SendDatasBuf[i];
	}
	return CheckSum;
}
 /* ----------------------------------------------------- */
#if CONFIG_FCT_UART
static void Fct_SendDatas(void)
{//默认回复握手，只有握手完成后才进入正常通信
 	Fct_SendDatasBuf[0] = 0xa5;
	Fct_SendDatasBuf[1] = 0x5a;
	Fct_SendDatasBuf[2] = 0x04;
	Fct_SendDatasBuf[3] = 6;         
	Fct_SendDatasBuf[4] = C_TRANS_FCT;
	if(Fcting)
	{
		Fct_SendDatasBuf[4] |= (UCHAR)(C_RECE_FCT<<4);
	}

	Fct_SendDatasBuf[(Fct_SendDatasBuf[3]-1)] = Fct_CheckSum();
	Uart_SendData(SERIAL_FCT, Fct_SendDatasBuf, Fct_SendDatasBuf[3]);
}
 /* ----------------------------------------------------- */
static unsigned char Fct_CheckSum(void)
{
	unsigned char CheckSum = 0;
	unsigned char i = 0;
	for(i = 0; i < (Fct_SendDatasBuf[3]-1); i++)
	{
		CheckSum += Fct_SendDatasBuf[i];
	}
	return CheckSum;
}
 /* ----------------------------------------------------- */
#endif

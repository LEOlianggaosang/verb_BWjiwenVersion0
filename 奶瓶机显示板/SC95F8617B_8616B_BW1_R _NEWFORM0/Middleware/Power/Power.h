/**
*******************************************************************************
 * Copyright (c) 2025.5.17
 * 
* @file    Power.h
* @author  lianggaosang@qq.com
* @brief   8616b奶瓶机显示板
* 
*******************************************************************************
*/
#ifndef POWER_H
#define POWER_H

#include "SerialDrv.h"
#include "product_config.h"

#define POWER_DATA_LENGTH   30
#define		C_RECE_FIRST	0x01
#define		C_RECE_NORMAL	0x02
#define		C_RECE_FCT		0x04
#define		C_TRANS_NONE	0x08
#define		C_TRANS_FIRST	0x09
#define		C_TRANS_NORMAL	0x0a
#define		C_TRANS_FCT		0x0c
//*************************************************
#define 	BUZZ_POWERON 		0
#define 	BUZZ_ENTERCHECK 	1
#define 	BUZZ_KEY_VALID 		2
#define 	BUZZ_KEY_INVALID 	3
#define 	BUZZ_ALARM 		    4
#define 	BUZZ_END 		    5
#define 	BUZZ_OPENDOOR 		6
#define 	BUZZ_SILENCE 		7
#define 	BUZZ_NONE 		    0xff
//*************************************************
extern ByteFlag Power_Flags;
#define  PowerFlag                  Power_Flags.f_byte
#define  Power_IsCommunicating      Power_Flags.f_bits.no0
#define  Power_hasCommunicated      Power_Flags.f_bits.no1
#define  Power_IsBuzzing            Power_Flags.f_bits.no2
#define  Power_BuzzReceived         Power_Flags.f_bits.no3
#define  Power_DoorIsOpend          Power_Flags.f_bits.no4
extern ByteFlag Relay_Enables;
#define  RelayEnable                Relay_Enables.f_byte
#define  Relay_HEAT                 Relay_Enables.f_bits.no0
#define  Relay_DP                   Relay_Enables.f_bits.no1
#define  Relay_PTC                  Relay_Enables.f_bits.no2
extern ByteFlag Output_Enables;
#define  OutputEnable               Output_Enables.f_byte
#define  Output_WP                  Output_Enables.f_bits.no0
#define  Output_IP                  Output_Enables.f_bits.no1
#define  Output_MP                  Output_Enables.f_bits.no2
#define  Output_IV                  Output_Enables.f_bits.no3
#define  Output_FAN_IN              Output_Enables.f_bits.no4
#define  Output_FAN_OUT             Output_Enables.f_bits.no5
#define  Output_UV                  Output_Enables.f_bits.no6
#define  Output_O3                  Output_Enables.f_bits.no7//20260421 版本0 臭氧功能
extern ByteFlag Inlet_Enables;
#define  InletEnable                Inlet_Enables.f_byte
#define  Inlet_IsInLetting          Inlet_Enables.f_bits.no0
#define  Inlet_ErrReload            Inlet_Enables.f_bits.no1
#define  Inlet_Lack                 Inlet_Enables.f_bits.no2
#define  Inlet_FlowCheck            Inlet_Enables.f_bits.no3
#define  Inlet_FlowCheckInit        Inlet_Enables.f_bits.no4
#define  Inlet_InLetMovement        Inlet_Enables.f_bits.no5
#define  Inlet_FlowCheckOk          Inlet_Enables.f_bits.no6
#define  Inlet_FlowChecking         Inlet_Enables.f_bits.no7
//*************************************************
// extern ByteFlag Singal_Flags;
// #define  SingalFlag                  Singal_Flags.f_byte
// #define  Signal_DoorIsOpend          Singal_Flags.f_bits.no0
// #define  Signal_SaltIsLack           Singal_Flags.f_bits.no1
// #define  Signal_RinesIsLack          Singal_Flags.f_bits.no2
// #define  Signal_WaterIsOver          Singal_Flags.f_bits.no3
// #define  Signal_WaterIsReached       Singal_Flags.f_bits.no4
// #define  Signal_InletValve           Singal_Flags.f_bits.no5
// #define  Signal_PmamPosition         Singal_Flags.f_bits.no6
extern ByteFlag AdErr_Flags;
#define  AdErrFlag                 AdErr_Flags.f_byte
#define  AdErr_ErrRe               AdErr_Flags.f_bits.no0
#define  AdErr_ReShort             AdErr_Flags.f_bits.no1
#define  AdErr_ReOpen              AdErr_Flags.f_bits.no2
#define  Err_Heat                  AdErr_Flags.f_bits.no3
#define  Err_FanFeedBack           AdErr_Flags.f_bits.no4//#if CONFIG_FB_CHECK//20251204
//*************************************************
extern UCHAR_XDATA 		P_Version_Number;
extern UCHAR_XDATA 		Temperature_Value;
extern UINT_XDATA 		Temperature_AdValue;
// extern UCHAR_XDATA 		P_AdTurb;/*自动洗*/
// extern UCHAR_XDATA 		P_AdIaqs;
// extern UCHAR_XDATA 		P_AdDoor;
// extern UCHAR_XDATA 		P_AdErrFlag;
extern UINT_XDATA 		P_FlowMCnt;
extern UINT_XDATA 		P_FlowMErrCnt;
extern UINT_XDATA 		P_FeedBackCnt;//20251203
extern UCHAR_XDATA 		BeepState;
extern UCHAR_XDATA 		P_Options[3];
extern UCHAR_XDATA 		D_Options[3];
//*************************************************
void Init_Power(void);
void Power_Control(void);

#endif

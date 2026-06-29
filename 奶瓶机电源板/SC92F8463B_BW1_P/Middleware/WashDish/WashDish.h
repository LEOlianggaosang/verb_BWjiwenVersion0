/**
*******************************************************************************
 * Copyright (c) 20250606
 * 
* @file    WashDish.h
* @author  lianggaosang@qq.com
* @brief   洗碗机串口通信
* 
*******************************************************************************
*/
#ifndef WASHDISH_H
#define WASHDISH_H

#include "product_config.h"
//*************************************************
#define		C_RECE_NONE		0x08
#define		C_RECE_FIRST	0x09
#define		C_RECE_NORMAL	0x0a
#define		C_RECE_THIRD	0x0b
#define		C_RECE_FCT		0x0c

#define		C_TRANS_NONE	0x00
#define		C_TRANS_FIRST	0x01
#define		C_TRANS_NORMAL	0x02
#define		C_TRANS_THIRD	0x03
#define		C_TRANS_FCT		0x04
//*************************************************
#define STATE_POWER		0
#define STATE_DRAIN		1
#define STATE_STANDBY   2
#define STATE_WASHING   3
#define STATE_ERROR     4
#define STATE_FINISHED	5
#define STATE_SAVING	6
#define STATE_TESTING   7
#define STATE_RESET     8
//*************************************************
#define STAGE_PRE       0
#define STAGE_MAIN      1
#define STAGE_RINSE1    2
#define STAGE_RINSE2    3
#define STAGE_STEAM     4
#define STAGE_DRY       5
#define STAGE_COMPLETE	6
//*************************************************
#define  PAUSE_TIMER                          0
#define  DRAIN_TIMER                          1
#define  MOVE_TIMER                           2
#define  INLET_ROTATION                       3
#define  INLET_RINSE                          4
#define  INLET_TIMER                          5
#define  INLET_STEAM                          6
#define  WASH_TIMER                           7
#define  STAGE_WASH_TIME_SET                  8
#define  STAGE_WASH_TIME                      9
#define  WASH_HEAT_TEMP1                      10
#define  WASH_HEAT_TEMP2                      11
#define  WASH_HEAT_TEMP3                      12
#define  WASH_HEAT_TEMP_SET                   13
#define  HEAT_TIMER                           14
#define  HEAT_STEAM                           15
#define  DRAIN_STEAM                          16
#define  FAN_TIMER                            17
#define  FAN_PTC_TIMER                        18
#define  COMPLETE                             19
#define  COMPLETE_SAVE                        20
//*************************************************
#define  MENU_FAST                             0
#define  MENU_STANDARD                         1	
#define  MENU_STEAM                            2
#define  MENU_DRY                              3
#define  MENU_NULL                             4
//*************************************************
#define  MESSAGE_DATA_LENGTH                   30
#define  NIGHTLIGHT_DATA_LENGTH                7
//*************************************************
void Init_WashDish(void);
void WashDish_Control(void);

extern ByteFlag U_WashDishFlag;
#define  WashDishFlag			U_WashDishFlag.f_byte
#define  F_WDIsCommunicating	U_WashDishFlag.f_bits.no0
#define  F_WDHasCommunicated	U_WashDishFlag.f_bits.no1
#define  F_WDReplyAsking		U_WashDishFlag.f_bits.no2
#define  F_FCTing				U_WashDishFlag.f_bits.no3
#define  F_IsBuzzing			U_WashDishFlag.f_bits.no4
#define  F_BuzzReceived         U_WashDishFlag.f_bits.no5

extern ByteFlag U_RelayEnables;
#define  RelayEnable			U_RelayEnables.f_byte
#define  F_RelayHEAT			U_RelayEnables.f_bits.no0
#define  F_RelayDP				U_RelayEnables.f_bits.no1
#define  F_RelayPTC				U_RelayEnables.f_bits.no2

extern ByteFlag U_OutputEnables;
#define  OutputEnable			U_OutputEnables.f_byte
#define  F_OutputWP				U_OutputEnables.f_bits.no0
#define  F_OutputIP				U_OutputEnables.f_bits.no1
#define  F_OutputMP				U_OutputEnables.f_bits.no2
#define  F_OutputIV				U_OutputEnables.f_bits.no3
#define  F_OutputFANIN          U_OutputEnables.f_bits.no4
#define  F_OutputFANOUT         U_OutputEnables.f_bits.no5
#define  F_OutputUV				U_OutputEnables.f_bits.no6
#define  F_OutputO3				U_OutputEnables.f_bits.no7//20260430


extern ByteFlag U_InletEnables;
#define  InletEnable			U_InletEnables.f_byte
#define  F_IsInLetting			U_InletEnables.f_bits.no0
#define  F_ErrReload			U_InletEnables.f_bits.no1
#define  F_Lack					U_InletEnables.f_bits.no2
#define  F_FlowCheck			U_InletEnables.f_bits.no3
#define  F_FlowCheckInit        U_InletEnables.f_bits.no4
#define  F_InLetMovement        U_InletEnables.f_bits.no5
#define  F_FlowCheckOK          U_InletEnables.f_bits.no6
#define  F_FlowChecking         U_InletEnables.f_bits.no7


extern ByteFlag U_Options_0;
#define  Option0                U_Options_0.f_byte
#define  F_MoreMessageEn        U_Options_0.f_bits.no0

extern ByteFlag U_Options_1;
#define  Option1                U_Options_1.f_byte
#define  F_MovePumpEn           U_Options_1.f_bits.no0
#define  F_OutFanEn             U_Options_1.f_bits.no1
#define  F_Fm2En                U_Options_1.f_bits.no2
#define  F_IpEn                 U_Options_1.f_bits.no3
#define  F_IvEn                 U_Options_1.f_bits.no4
#define  F_NlEn                 U_Options_1.f_bits.no5
#define  F_O3En                 U_Options_1.f_bits.no6//20260430

extern ByteFlag U_Options_2;
#define  Option2                U_Options_2.f_byte
#define  F_FlowCheckEn          U_Options_2.f_bits.no0
#define  F_InletModeEn          U_Options_2.f_bits.no1
#define  F_IoUartEn             U_Options_2.f_bits.no1

extern UCHAR_XDATA	WD_Version_Number;
extern UCHAR_XDATA Current_W_State;
extern UCHAR_XDATA Current_D_State;
extern UCHAR_XDATA	P_Options[3];
extern UCHAR_XDATA	D_Options[3];
extern UCHAR_XDATA	WD_BeepState;
extern UINT_XDATA	FlowMCntSet;
extern UINT_XDATA	FlowMCnt;
extern UINT_XDATA	FlowMErrCnt;
extern UCHAR_XDATA	NL_State;
extern UCHAR_XDATA  Test_WaitFctActionCount;
extern UCHAR_XDATA  Test_FctingActionCount0;
extern UCHAR_XDATA  Test_FctingActionCount1;
extern UINT_XDATA	FeedBackCnt;//20251203

typedef enum
{
    RGB_OFF = 0,//0/0/0
    RGB_RED = 1,//100/0/0
    RGB_GREEN = 2,//0/100/0
    RGB_BLUE = 3,//0/0/100
    RGB_YELLOW = 4,//100/100/0
    RGB_CYAN = 5,//0/100/100
    RGB_PURPLE = 6,//100/0/100
    RGB_ORANGE = 7,//100/50/0
    RGB_PINK = 8,//100/0/50
    RGB_SPRING = 9,//50/100/0
    RGB_SKY = 10,//0/100/50
    RGB_VIOLET = 11,//50/0/100
    RGB_INDIGO = 12,//0/50/100
    RGB_WARM = 13,//100/50/50
    RGB_COLD = 14,//50/50/100
    RGB_WHITE = 0x0f,//100/100/100
    NLCOLOR_END
}NL_ColorType;

#endif
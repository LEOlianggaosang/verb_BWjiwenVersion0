/**
*******************************************************************************
 * Copyright (c) 2025.5.24
 * 
* @file    Save.h
* @author  lianggaosang@qq.com
* @brief   
* 
*******************************************************************************
*/
#ifndef _SAVE_H
#define _SAVE_H
#include "product_config.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#if NEWFORM0
#define 	SAVE_ST_IN_CNT       0//加强烘干算不算进总时间//20251110 NEWFORM0 
#define 	SAVE_ST_PTC_FIRST    0//加强烘干PTC先开//20251110 NEWFORM0
#define 	SAVE_ST_FIRST_CNT   10//加强烘干先开10min//20251110 NEWFORM0
#define 	SAVE_PRE_MIN        30//30*60s
#define 	SAVE_CYC_CNT        36//112*120min=72h
#define 	SAVE_CYC_MIN        120//120*60s
#define 	SAVE_RUN_MIN        10//10*60s
#define 	SAVE_RUN_PTC        570//10*60s-30s
#define 	SAVE_RUN_LED        600//
#define 	SAVE_RUN_FAN        30//结束循环PTC
// //202509202、保管：每120分钟工作10分钟，PTC全功率加热提前30s关+风扇换气；加强烘干：10分钟冷风+20分钟热风
#else
#define 	SAVE_ST_IN_CNT      1//加强烘干算不算进总时间//20251110 NEWFORM0 
#define 	SAVE_ST_PTC_FIRST   1//加强烘干PTC先开//20251110 NEWFORM0
#define 	SAVE_ST_FIRST_CNT   15//加强烘干先开15min//20251110 NEWFORM0
#define 	SAVE_PRE_MIN        30//30*60s
#define 	SAVE_CYC_CNT        112//112*90min=10080min=168h
#define 	SAVE_CYC_MIN        90//90*60s
#define 	SAVE_RUN_MIN        15//15*60s
#define 	SAVE_RUN_PTC        900//15*60s
#define 	SAVE_RUN_LED        900//
#define 	SAVE_RUN_FAN        0//结束循环PTC
// //202509202、保管：每90分钟工作15分钟，PTC全功率加热+风扇换气；加强烘干：15分钟热风+15分钟冷风
#endif
/***********************************************************************************************************************
Global variable
***********************************************************************************************************************/
extern ByteFlag Save_Flags;
#define  SaveFlag               Save_Flags.f_byte
#define  Save_InitFlag          Save_Flags.f_bits.no0
#define  Save_Timer1s           Save_Flags.f_bits.no1
#define  Save_WaitFlag          Save_Flags.f_bits.no2
#define  Save_SaveFlag          Save_Flags.f_bits.no3
#define  Save_RunFlag           Save_Flags.f_bits.no4
#define  Save_PtcFlag           Save_Flags.f_bits.no5
#define  Save_LedFlag           Save_Flags.f_bits.no6
#define  Save_ReloadFlag        Save_Flags.f_bits.no7
/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void Save_InitSet(void);
/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void Save_Control(bit Tick);
/**
 * @brief 
 * 
 * @param 
 * @return 
 */
bit Get_Save_FanState(void);
/**
 * @brief 
 * 
 * @param 
 * @return 
 */
bit Get_Save_PtcState(void);
/**
 * @brief 
 * 
 * @param 
 * @return 
 */
bit Get_Save_LedState(void);
/**
 * @brief 
 * 
 * @param 
 * @return 
 */
UCHAR Get_Save_Hours(void);
#endif 

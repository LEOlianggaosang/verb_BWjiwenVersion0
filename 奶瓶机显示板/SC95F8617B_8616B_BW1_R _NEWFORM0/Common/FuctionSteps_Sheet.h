/**
 *******************************************************************************
 * 
 * @file    FuctionSteps_Sheet.h
 * @author  
 * @version 1.0
 * @date    2025.5.9
 * @brief   
 * 
 * 
 * 
 * 
 *******************************************************************************
 */
#ifndef _FUCTIONSTEPS_SGEET_H_
#define _FUCTIONSTEPS_SGEET_H_

#include "product_config.h"

// static const StepInfo fastSteps[]=
// {
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			20,		0},

// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*8),		60},//800ml
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0,			42,		9*60},//42度温达剩洗
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},

// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_TIMER,			0, 		 	90,		3*60},
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_RINSE1,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_RINSE1,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},

// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	INLET_RINSE,		0, (C_LITER*7),		30},//700ml
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	70,		6*60},//75度温达剩洗
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_RINSE2,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_RINSE2,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	
// 	{STAGE_STEAM,	0,	1,  1,	0,	1,	INLET_STEAM,		0, 			0,		10*60},//250ml
// 	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_TIMER,			0,			8*60,	10*60},//定时加热8分钟
// 	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	10*60},//间歇加热2分钟
// 	// {STAGE_STEAM,	0,	1,  1,	0,	1,	DRAIN_STEAM,		0,			80,		2*60},//排水动作组S0
// 	// {STAGE_STEAM,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	// {STAGE_STEAM,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	// {STAGE_STEAM,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	// #if CONFIG_MP_ENABLE
// 	// {STAGE_STEAM,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	// #endif

// 	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_STEAM,		0, 		 4*60,		4*60},//静置
// 	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   10,		60},//排空//20251110 NEWFORM0 时序表
// 	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		30*60,		30*60},//45
// 	{STAGE_DRY,		1,	0,  0,	1,	1,	COMPLETE_SAVE,		0, 			0,		0},
// 	// {STAGE_DRY,		1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// 	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// };

#if CONFIG_LIFE_TEST//20251204
static const StepInfo fastSteps[]=
{
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*10),	60},//1000ml
	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			30,		60},

	{STAGE_MAIN,	1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},//20251128
};
#elif CONFIG_IQC_TEST//20260117
static const StepInfo fastSteps[]=
{//RGB灯三色显示
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			1,		0},
	
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			7,		0},

	{STAGE_MAIN,	1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},//20251128
};
#else
static const StepInfo fastSteps[]=
{//20251110 NEWFORM0 11
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			0,		0},
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},//*未加入温度补偿//*执行排水动作组
//--------------
	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*8),		30},//800ml*配时非0故障恢复无限延时
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0,			42,		450},//42度温达剩洗*不延时
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			90,		90},//*42度左右洗涤补足9分钟
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
//--------------
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_RINSE1,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_RINSE1,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml*配时非0故障恢复无限延时
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	42,		3*60},//42度温达剩洗*不延时
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
//--------------
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_RINSE2,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_RINSE2,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml*配时非0故障恢复无限延时//*不使用二漂进水步骤
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	72,		6*60},//72度温达剩洗*不延时
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
//--------------
	{STAGE_STEAM,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_STEAM,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_STEAM,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_STEAM,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_STEAM,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_STEAM,	0,	1,  1,	0,	1,	INLET_STEAM,		0, 			0,		10*60},//250ml
	
	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_TIMER,			0,			10*60,	12*60},//定时加热10分钟//20251216
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	12*60},//间歇加热2分钟//20251216
	#else
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_TIMER,			0,			8*60,	10*60},//定时加热8分钟
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	10*60},//间歇加热2分钟
	#endif
//--------------
	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_STEAM,		0, 		 4*60,		4*60},//静置
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		    0,		60},//排空//20251110 NEWFORM0 时序表
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   30,		0},//排空*//(20251127 更改最大延时60->90)
	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		33*60,		33*60},//20251216
	#else
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		35*60,		35*60},//45*改为40
	#endif
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_TIMER,			0,		   30,		0},//*提前30s关闭改为附加风机30s
	{STAGE_DRY,		1,	0,  0,	1,	1,	COMPLETE_SAVE,		0, 			0,		0},
//--------------
	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
};
		#endif

// static const StepInfo standardSteps[]=
// {
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			20,		0},
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	PRE_TEMP_CHECK,		0,			0,		0},//预洗温度补偿检查//20250920

// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*8),		60},//800ml
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	STAGE_WASH_TIME_SET,0,		 14*60,		14*60},//设定阶段洗涤总时间
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	WASH_HEAT_TEMP2,	0,			42,		14*60},//42度温达跳步
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	WASH_TIMER,			0,			300,	14*60},//洗涤5分钟
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	WASH_HEAT_TEMP2,	0,			55,		14*60},//55度温达跳步
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	STAGE_WASH_TIME,	0,		  	0,		14*60},//剩余时间洗涤
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},

// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	50,		5*60},//50度温达剩洗
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_RINSE1,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_RINSE1,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},

// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	INLET_RINSE,		0, (C_LITER*7),		30},//700ml
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP_SET,	0, 		 	70,		9*60},//80度温达剩洗
// 	{STAGE_RINSE2,	1,	0,  1,	0,	0,	WASH_HEAT_TEMP3,	0, 		 	75,		9*60},//85度温度维持
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_RINSE2,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_RINSE2,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	
// 	{STAGE_STEAM,	0,	1,  1,	0,	1,	INLET_STEAM,		0, 			0,		10*60},//250ml
// 	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_TIMER,			0,			8*60,	10*60},//定时加热8分钟
// 	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	10*60},//间歇加热2分钟
// 	// {STAGE_STEAM,	0,	1,  1,	0,	1,	DRAIN_STEAM,		0,			80,		2*60},//排水动作组S0
// 	// {STAGE_STEAM,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	// {STAGE_STEAM,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	// {STAGE_STEAM,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	// #if CONFIG_MP_ENABLE
// 	// {STAGE_STEAM,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	// #endif

// 	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_STEAM,		0, 		 4*60,		4*60},//静置
// 	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   10,		60},//排空//20251110 NEWFORM0 时序表
// 	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		30*60,		30*60},//45
// 	{STAGE_DRY,		1,	0,  0,	1,	1,	DRY_TEMP_WORK,		0, 		10*60,		10*60},//20250920//20250929
// 	{STAGE_DRY,		1,	0,  0,	1,	1,	COMPLETE_SAVE,		0, 			0,		0},
// 	// {STAGE_DRY,		1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// 	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// };

#if CONFIG_LIFE_TEST//20251204
static const StepInfo standardSteps[]=
{
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP_SET,	0, 			65,		255*60},
	{STAGE_MAIN,	1,	0,  1,	0,	0,	WASH_HEAT_TEMP3,	0,			75,		255*60},

	{STAGE_MAIN,	1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},//20251128
};
#elif CONFIG_IQC_TEST//20260117
static const StepInfo standardSteps[]=
{//屏蔽
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP_SET,	0, 			65,		255*60},
	{STAGE_MAIN,	1,	0,  1,	0,	0,	WASH_HEAT_TEMP3,	0,			75,		255*60},

	{STAGE_MAIN,	1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},//20251128
};
#else
	#if CONFIG_T2_STANDARD//20251211
static const StepInfo standardSteps[]=
{//20251110 NEWFORM0 11
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			0,		0},
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},//*执行排水动作组
//--------------
	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PRE_TEMP_CHECK,		0,			 0,		0},//预洗温度补偿检查*改主洗
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*8),		30},//800ml*配时非0故障恢复无限延时
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0,			42,		450},//42度温达剩洗*不延时
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_TIMER,			0,		    90,		90},//*42度左右洗涤补足10分钟//20251211
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0,			55,		240},//55度温达剩洗*不延时*改机制区分快速
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
//--------------
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_RINSE1,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_RINSE1,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml*配时非0故障恢复无限延时
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	55,		4*60},//55度温达剩洗*不延时*改机制区分快速//20251211
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
//--------------
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_RINSE2,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_RINSE2,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml*配时非0故障恢复无限延时//*不使用二漂进水步骤
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s

	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP2,	0, 		 	82,		14*60},//72度温达剩洗*不延时*改机制区分快速//20251211

	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			10,		0},//20251211
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
//--------------
	{STAGE_STEAM,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_STEAM,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_STEAM,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_STEAM,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_STEAM,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_STEAM,	0,	1,  1,	0,	1,	INLET_STEAM,		0, 			0,		10*60},//250ml

	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_TIMER,			0,			10*60,	12*60},//定时加热10分钟//20251216
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	12*60},//间歇加热2分钟//20251216
	#else
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_TIMER,			0,			8*60,	10*60},//定时加热8分钟
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	10*60},//间歇加热2分钟
	#endif
//--------------
	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_STEAM,		0, 		 4*60,		4*60},//静置
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		    0,		60},//排空//20251110 NEWFORM0 时序表
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   30,		0},//排空*//(20251127 更改最大延时60->90)
	
	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		33*60,		33*60},//20251216
	#else
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		35*60,		35*60},//45*改为40
	#endif

	{STAGE_DRY,		1,	0,  0,	1,	1,	DRY_TEMP_WORK,		0, 		10*60,		10*60},//*加入温度补偿
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_TIMER,			0,		   30,		0},//*提前30s关闭改为附加风机30s
	{STAGE_DRY,		1,	0,  0,	1,	1,	COMPLETE_SAVE,		0, 			0,		0},
//--------------
	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
};	
	#else
static const StepInfo standardSteps[]=
{//20251110 NEWFORM0 11
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			0,		0},
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},//*执行排水动作组
//--------------
	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PRE_TEMP_CHECK,		0,			 0,		0},//预洗温度补偿检查*改主洗
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*8),		30},//800ml*配时非0故障恢复无限延时
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0,			42,		450},//42度温达剩洗*不延时
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_TIMER,			0,		   150,		150},//*42度左右洗涤补足10分钟
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0,			55,		240},//55度温达剩洗*不延时*改机制区分快速
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
//--------------
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_RINSE1,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_RINSE1,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml*配时非0故障恢复无限延时
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	55,		5*60},//55度温达剩洗*不延时*改机制区分快速
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
//--------------
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_RINSE2,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_RINSE2,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml*配时非0故障恢复无限延时//*不使用二漂进水步骤
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	72,		9*60},//72度温达剩洗*不延时*改机制区分快速
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
//--------------
	{STAGE_STEAM,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_STEAM,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_STEAM,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_STEAM,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_STEAM,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_STEAM,	0,	1,  1,	0,	1,	INLET_STEAM,		0, 			0,		10*60},//250ml
	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_TIMER,			0,			10*60,	12*60},//定时加热10分钟//20251216
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	12*60},//间歇加热2分钟//20251216
	#else
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_TIMER,			0,			8*60,	10*60},//定时加热8分钟
	{STAGE_STEAM,	0,	1,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	10*60},//间歇加热2分钟
	#endif
//--------------
	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_STEAM,		0, 		 4*60,		4*60},//静置
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		    0,		60},//排空//20251110 NEWFORM0 时序表
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   30,		0},//排空*//(20251127 更改最大延时60->90)
	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		33*60,		33*60},//20251216
	#else
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		35*60,		35*60},//45*改为40
	#endif
	{STAGE_DRY,		1,	0,  0,	1,	1,	DRY_TEMP_WORK,		0, 		10*60,		10*60},//*加入温度补偿
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_TIMER,			0,		   30,		0},//*提前30s关闭改为附加风机30s
	{STAGE_DRY,		1,	0,  0,	1,	1,	COMPLETE_SAVE,		0, 			0,		0},
//--------------
	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
};
	#endif
#endif

// static const StepInfo steamSteps[]=
// {
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},//20251110 NEWFORM0 时序表
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			20,		0},//20251110 NEWFORM0 时序表
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	PRE_TEMP_CHECK,		0,			0,		0},//预洗温度补偿检查//20250920

// 	{STAGE_STEAM,	1,	0,  1,	0,	1,	INLET_STEAM,		0, 			0,		10*60},//250ml
// 	{STAGE_STEAM,	1,	0,  1,	0,	0,	HEAT_TIMER,			0,			8*60,	10*60},//定时加热8分钟
// 	{STAGE_STEAM,	1,	0,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	10*60},//间歇加热2分钟
// 	// {STAGE_STEAM,	1,	0,  1,	0,	1,	DRAIN_STEAM,		0,			80,		2*60},//排水动作组S0
// 	// {STAGE_STEAM,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	// {STAGE_STEAM,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	// {STAGE_STEAM,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	// #if CONFIG_MP_ENABLE
// 	// {STAGE_STEAM,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	// #endif

// 	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_STEAM,		0, 		 4*60,		4*60},//静置
// 	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   10,		60},//排空//20251110 NEWFORM0 时序表
// 	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		30*60,		30*60},//45
// 	{STAGE_DRY,		1,	0,  0,	1,	1,	DRY_TEMP_WORK,		0, 		10*60,		10*60},//20250920//20250929
// 	{STAGE_DRY,		1,	0,  0,	1,	1,	COMPLETE_SAVE,		0, 			0,		0},
// 	// {STAGE_DRY		,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// 	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// };
static const StepInfo steamSteps[]=
{//20251110 NEWFORM0 11
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			0,		0},
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},//*执行排水动作组
//--------------
	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PRE_TEMP_CHECK,		0,			 0,		0},//预洗温度补偿检查*改主洗
//--------------
	{STAGE_STEAM,	1,	0,  1,	0,	1,	INLET_STEAM,		0, 			0,		10*60},//250ml//*mod*
	{STAGE_STEAM,	1,	0,  1,	0,	0,	HEAT_TIMER,			0,			8*60,	10*60},//定时加热8分钟//*mod
	{STAGE_STEAM,	1,	0,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	10*60},//间歇加热2分钟//*mod

	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_STEAM,	1,	0,  1,	0,	0,	HEAT_TIMER,			0,			10*60,	12*60},//定时加热10分钟//20251216
	{STAGE_STEAM,	1,	0,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	12*60},//间歇加热2分钟//20251216
	#else
	{STAGE_STEAM,	1,	0,  1,	0,	0,	HEAT_TIMER,			0,			8*60,	10*60},//定时加热8分钟
	{STAGE_STEAM,	1,	0,  1,	0,	0,	HEAT_STEAM,			0,			2*60,	10*60},//间歇加热2分钟
	#endif
//--------------
	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_STEAM,		0, 		 4*60,		4*60},//静置
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		    0,		60},//排空//20251110 NEWFORM0 时序表
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   30,		0},//排空*//(20251127 更改最大延时60->90)
	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		33*60,		33*60},//20251216
	#else
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		35*60,		35*60},//45*改为40
	#endif
	{STAGE_DRY,		1,	0,  0,	1,	1,	DRY_TEMP_WORK,		0, 		10*60,		10*60},//*加入温度补偿
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_TIMER,			0,		   30,		0},//*提前30s关闭改为附加风机30s
	{STAGE_DRY,		1,	0,  0,	1,	1,	COMPLETE_SAVE,		0, 			0,		0},
//--------------
	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
};

// static const StepInfo drySteps[]=
// {
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},//20251110 NEWFORM0 时序表
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			20,		0},//20251110 NEWFORM0 时序表
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	PRE_TEMP_CHECK,		0,			0,		0},//预洗温度补偿检查//20250920
	
// 	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_TIMER,		0, 		35*60,		35*60},//45
// 	{STAGE_DRY,		1,	0,  1,	0,	1,	DRY_TEMP_WORK,		0, 		10*60,		10*60},//20250920//20250929
// 	{STAGE_DRY,		1,	0,  1,	0,	1,	COMPLETE_SAVE,		0, 			0,		0},
// 	// {STAGE_DRY,		1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// 	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// };
static const StepInfo drySteps[]=
{//20251110 NEWFORM0 11
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			0,		0},
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},//*执行排水动作组
//--------------
	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PRE_TEMP_CHECK,		0,			 0,		0},//预洗温度补偿检查*改主洗
//--------------
	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_TIMER,		0, 		38*60,		38*60},//20251216
	#else
	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_TIMER,		0, 		40*60,		40*60},//45*改为40*无静置排空//*mod
	#endif
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRY_TEMP_WORK,		0, 		10*60,		10*60},//*加入温度补偿//*mod
	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_TIMER,			0,		   30,		0},//*提前30s关闭改为附加风机30s//*mod
	{STAGE_DRY,		1,	0,  1,	0,	1,	COMPLETE_SAVE,		0, 			0,		0},//*mod
//--------------
	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
};

#if NEWTPE1
// static const StepInfo selfcleanSteps[]=
// {
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
// 	{STAGE_PRE,		1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			30,		0},

// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*8),		60},//800ml
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0,			50,		5*60},//55度温达剩洗
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},

// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	30,		2*60},//加热到时间结束
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_RINSE1,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_RINSE1,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},

// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	INLET_RINSE,		0, (C_LITER*7),		30},//700ml
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	40        ,		3*60},//55度温达剩洗
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1
// 	{STAGE_RINSE2,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
// 	{STAGE_RINSE2,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
// 	#if CONFIG_MP_ENABLE
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
// 	#endif
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			10,		10},
// 	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
// 	// {STAGE_RINSE2,	1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// 	{STAGE_STEAM,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
// 	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   10,		60},//排空//20251110 NEWFORM0 时序表
// 	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
// };

#if CONFIG_LIFE_TEST//20251204
static const StepInfo selfcleanSteps[]=
{
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	FAN_PTC_TIMER,		0, 			3600,	60*60},//20251128
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0, 			1200,	20*60},//20251128


	{STAGE_MAIN,	1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},//20251128
};
#elif CONFIG_IQC_TEST//20260117
static const StepInfo selfcleanSteps[]=
{//开风机检测风机故障
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	FAN_TIMER,			0, 			20,		20},

	{STAGE_MAIN,	1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
};
#else
static const StepInfo selfcleanSteps[]=
{//20251110 NEWFORM0 11
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			0,		0},
	{STAGE_PRE,		1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},//*执行排水动作组
//--------------
	{STAGE_MAIN,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_MAIN,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_MAIN,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_MAIN,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	// {STAGE_MAIN,	1,	0,  1,	0,	1,	PRE_TEMP_CHECK,		0,			 0,		0},//预洗温度补偿检查*改主洗
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
	{STAGE_MAIN,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*8),		30},//800ml*配时非0故障恢复无限延时
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_MAIN,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0,			42,		5*60},//42度温达剩洗*不延时*自洁
	{STAGE_MAIN,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
//--------------
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_RINSE1,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_RINSE1,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml*配时非0故障恢复无限延时
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	42,		2*60},//42度温达剩洗*不延时*自洁
	{STAGE_RINSE1,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			 2,		0},
//--------------
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	DRAIN_TIMER,		0,			15,		32},//排水动作组S1//*配时非0*并入
	{STAGE_RINSE2,	1,	0,  1,	0,	0,	PAUSE_TIMER,		0,			 2,		32},//排水动作组S2
	{STAGE_RINSE2,	1,	0,  1,	0,	0,	DRAIN_TIMER,		0,			15,		32},//排水动作组S3
	#if CONFIG_MP_ENABLE
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	MOVE_TIMER,			0, 			10,		10},//排水动作组S4
	#endif
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	INLET_ROTATION,		0, (C_LITER*7),		30},//700ml*配时非0故障恢复无限延时//*不使用二漂进水步骤
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_TIMER,			0,			20,		0},//*热洗之前冷洗20s
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	WASH_HEAT_TEMP1,	0, 		 	55,		3*60},//55度温达剩洗*不延时*自洁
	{STAGE_RINSE2,	1,	0,  1,	0,	1,	PAUSE_TIMER,		0,			2,		0},
//--------------
	{STAGE_DRY,		1,	0,  1,	0,	1,	FAN_PTC_STEAM,		0, 		 4*60,		4*60},//静置
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		    0,		60},//排空//20251110 NEWFORM0 时序表
	{STAGE_DRY,		1,	0,  1,	0,	1,	DRAIN_ALL,			0,		   30,		0},//排空*//(20251127 更改最大延时60->90)

	#if CONFIG_T2_STEAMDRY//20251211
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		33*60,		33*60},//20251216
	#else
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_PTC_TIMER,		0, 		35*60,		35*60},//45*改为40
	#endif
	// {STAGE_DRY,		1,	0,  0,	1,	1,	DRY_TEMP_WORK,		0, 		10*60,		10*60},//*加入温度补偿
	{STAGE_DRY,		1,	0,  0,	1,	1,	FAN_TIMER,			0,		   30,		0},//*提前30s关闭改为附加风机30s
	{STAGE_DRY,		1,	0,  0,	1,	1,	COMPLETE_SAVE,		0, 			0,		0},
//--------------
	{STAGE_COMPLETE,1,	0,  1,	0,	1,	COMPLETE,			0,			0,		0},
};
		#endif
#endif
//20251011 厂测模式
static const TestInfo Test1Steps[]=
{//20251110 NEWFORM0 11
	{0x60,	0,	PAUSE_TIMER,		0,	0,				0},
	{0x60,	1,	PAUSE_TIMER,		0,	2,				2},

	{0x61,	0,	INLET_ROTATION,		0,	(C_LITER*8),	60},//43s

	{0x62,	0,	WASH_HEAT_TEMP1,	0,	72,				12*60},//9min 66度//11min 71度(20251127 更改)//22度加热到72度11分40秒

	{0x63,	0,	DRAIN_TIMER,		0,	15,				15},
	{0x63,	0,	PAUSE_TIMER,		0,	2,				2},
	{0x63,	0,	DRAIN_TIMER,		0,	15,				15},
	#if CONFIG_MP_ENABLE
	{0x53,	0,	MOVE_TIMER,			0,	10,				10},
	#endif

	{0x64,	0,	FAN_PTC_TIMER,		0,	6*60,			6*60},//6min

	{0x65,	0,	DRAIN_ALL,			0,	0,				60},//2min满箱剩1/5 *//(20251127 更改最大延时60->90)
	{0x65,	0,	DRAIN_ALL,			0,	30,				0},

	{0x66,	1,	PAUSE_TIMER,		0,	2,				2},
	{0x66,	0,	COMPLETE,			0,	0,				0},
};
static const TestInfo Test2Steps[]=
{//20251110 NEWFORM0 11
	{0x20,	0,	PAUSE_TIMER,		0,	0,				0},
	{0x20,	1,	PAUSE_TIMER,		0,	2,				2},

	{0x21,	0,	DRAIN_ALL,			0,	0,				60},
	{0x21,	0,	DRAIN_ALL,			0,	30,				0},

	{0x22,	1,	PAUSE_TIMER,		0,	2,				2},
	{0x22,	0,	COMPLETE,			0,	0,				0},
};
#endif

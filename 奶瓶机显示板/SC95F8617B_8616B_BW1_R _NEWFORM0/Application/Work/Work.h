/**
*******************************************************************************
 * Copyright (c) 2025.5.9
 * 
* @file    Work.h
* @author  lianggaosang@qq.com
* @brief   
* 
*******************************************************************************
*/
#ifndef WORK_H_
#define WORK_H_

#include "product_config.h"

typedef enum
{
  STATE_POWER,
  STATE_DRAIN,
  STATE_STANDBY,
  STATE_WASHING,
  STATE_ERROR,
  STATE_FINISHED,
  STATE_SAVING,
  STATE_TESTING,
  STATE_RESET
}WorkState;

typedef struct
{//时序表结构体
	  unsigned char stage:3;
    #if CONFIG_STEAM_ENABLE
    unsigned char SteamMask:1;
    unsigned char SteamSwitch:1;   
    #endif 
    #if CONFIG_DRY_ENABLE
    unsigned char dryMask:1;      
    unsigned char drySwitch:1;      
    #endif  
    unsigned char clearStepDataEnable:1;
    unsigned char fnIndex;

	  unsigned char speed;//CONFIG_BLAM_ENABLE

    unsigned short arg;              
    unsigned short maxDuration;
}StepInfo;

#define STAGE_PRE       0
#define STAGE_MAIN      1
#define STAGE_RINSE1    2
#define STAGE_RINSE2    3
#define STAGE_STEAM     4
#define STAGE_DRY       5//判断是否有蒸汽并排空水箱，判断是否进入热烘保管
#define STAGE_COMPLETE	6
#define STAGE_END       7//(20251127 1-0-1-66-end)

/**
* 
*/
#define  PAUSE_TIMER                          0//定时
#define  DRAIN_TIMER                          1//定时排水
#define  MOVE_TIMER                           2//定时蠕动泵
#define  INLET_ROTATION                       3//定量进水
#define  INLET_RINSE                          4//漂洗2进水检测600ml
#define  INLET_TIMER                          5//定时进水
#define  INLET_STEAM                          6//蒸汽步骤专用，缺水跳过
#define  WASH_TIMER                           7//定时洗涤
#define  STAGE_WASH_TIME_SET                  8//设定阶段洗涤总时间
#define  STAGE_WASH_TIME                      9//设定阶段洗涤时间    
#define  WASH_HEAT_TEMP1                      10//定温加热，温达剩洗
#define  WASH_HEAT_TEMP2                      11//定温加热，温达跳步
#define  WASH_HEAT_TEMP3                      12//定温加热，温度维持
#define  WASH_HEAT_TEMP_SET                   13//设定维持最小温度
#define  HEAT_TIMER                           14//定时加热
#define  HEAT_STEAM                           15//蒸汽步骤专用，停10启20，两分钟
// #define  DRAIN_STEAM                          16//检查是否进行过蒸汽
#define  DRAIN_ALL                            16//排空水箱
#define  FAN_TIMER                            17//定时风机
#define  FAN_PTC_TIMER                        18//定时热风
#define  FAN_PTC_STEAM                        19//静置
#define  PRE_TEMP_CHECK                       20//预洗温度补偿检查
#define  DRY_TEMP_WORK                        21//烘干温度补偿
#define  COMPLETE_SAVE                        22//完成进入保管
#define  COMPLETE                             23//完成
// #define  INLET_ROTATION2                      25//进水阀专用流量计（预留）
// #define  FAN_FAN2_TIMER                       26//定时新风风机（预留）
///
#if NEWTPE1
#define  MAX_MENU_NUMBER	6
#else
#define  MAX_MENU_NUMBER	4
#endif
typedef enum
{
  MENU_FAST,
  MENU_STANDARD,
  MENU_STEAM,
  MENU_DRY,
  #if NEWTPE1
  MENU_SELFCLEAN,//NEWTPE1
  #endif
  MENU_NULL
}MenuOption;



typedef struct 
{//功能菜单结构体
  MenuOption menuName:4;
  unsigned int steamMode:1;
  unsigned int steamModeEnable:1;
  unsigned int dryMode:1;
  unsigned int dryModeEnable:1;
  unsigned int functionTableMask:1;     
}stMenuPara;

extern WorkState    Work_CurrentState;
extern MenuOption   Work_CurrentMenu;
extern MenuOption   Work_LastMenu;
extern UCHAR_XDATA  Work_CurrentStage;
extern UCHAR_XDATA  Work_CurrentStep;
extern UCHAR_XDATA  Work_CurrentFnIndex;
extern USHORT_XDATA Work_CurrentArg;
extern USHORT_XDATA Work_UsedSecondInCurrentStep;
extern FunctionPt   Work_NextStepHandler;
extern WorkState    Work_BufferState;
extern  const FunctionPt functions[];
//Cnt
extern UCHAR_XDATA  Work_LeftMinToEnd;
extern UCHAR_XDATA  EndCnt;
extern UINT_XDATA   SleepCnt;
extern UCHAR_XDATA  DrainCnt;
extern USHORT_XDATA currentFunctionUnitUsedSeconds;
extern USHORT_XDATA currentStepMaxDuationSecond;
extern UCHAR_XDATA  Test_WaitKeyActionCount;
extern UCHAR_XDATA  Work_DoorOpenDelaySecondCount;
extern UCHAR_XDATA  runSecCount;
extern UINT_XDATA   FlowMCntSet;
extern UINT_XDATA   FlowMCnt;
#if CONFIG_LIFE_TEST//20251204
extern UINT_XDATA  LifeTestCnt;
#endif

// extern UCHAR_XDATA RT_CN;
// extern UINT_XDATA heat_count;
// extern UCHAR_XDATA OVER_DR;
// extern UCHAR_XDATA DRY_OVER_DR;
//Flags
extern WordFlag WorkAction_Flags;
#define  WorkActionFlag                 WorkAction_Flags.f_word
#define  Work_KeyboardIsLocked          WorkAction_Flags.f_bits.no0
#define  Work_IsPaused                  WorkAction_Flags.f_bits.no1
#define  Test_Entered                   WorkAction_Flags.f_bits.no2
#define  Work_IsSteamMode               WorkAction_Flags.f_bits.no3//Work_IsTripleMode
#define  Work_IsDryMode                 WorkAction_Flags.f_bits.no4//Work_IsHalfMode
#define  Work_InletMode                 WorkAction_Flags.f_bits.no5
#define  Light_IsWorking                WorkAction_Flags.f_bits.no6//CONFIG_NIGHT_LIGHT
#define  Error_IsHandling               WorkAction_Flags.f_bits.no7
#define  Work_MemoryRead                WorkAction_Flags.f_bits.no8
#define  Work_MemoryWrite               WorkAction_Flags.f_bits.no9
#define  ResetFlagAfterPowerup          WorkAction_Flags.f_bits.no10
#define  Work_IsPowerLostMemory         WorkAction_Flags.f_bits.no11//CONFIG_MENORY_WASHDATA
#define  Work_TimerTick1s               WorkAction_Flags.f_bits.no12
#define  Work_ForceDrain                WorkAction_Flags.f_bits.no13
//! NEWFORM1 #2-1 分离保管与烘干控制
#define  Work_SaveMode                  WorkAction_Flags.f_bits.no14
extern WordFlag WorkFuction_Flags;
#define  WorkFuctionFlag                WorkFuction_Flags.f_word
#define  Work_EndConditionIsTemperature WorkFuction_Flags.f_bits.no0
#define  Work_HasHeat                   WorkFuction_Flags.f_bits.no1//Work_MinHeatTemp
#define  Work_TempCompensation          WorkFuction_Flags.f_bits.no2//Work_TimerTick1s
#define  Work_TimeHaltEnable            WorkFuction_Flags.f_bits.no3//timeHaltEnable
#define  Work_SteamLack                 WorkFuction_Flags.f_bits.no4
#define  Work_SaveEnter                 WorkFuction_Flags.f_bits.no5
#define  Work_ClosePowerInit            WorkFuction_Flags.f_bits.no6
#define  Work_GotoStandbyInit           WorkFuction_Flags.f_bits.no7
#define  Work_HeatOk                    WorkFuction_Flags.f_bits.no8
#define  Work_DrainAllFail              WorkFuction_Flags.f_bits.no9//20251110 NEWFORM0 10.1(3) 20251126

extern const stMenuPara MenuList[];
extern const UCHAR_XDATA Work_StageStartTimeMode[MAX_MENU_NUMBER][STAGE_END+1];//(20251127 1-0-1-66-end)
//extern const UCHAR_XDATA Work_StageStartTimeInSteamMode[MAX_MENU_NUMBER][STAGE_COMPLETE+1];
//extern const UCHAR_XDATA Work_StageStartTimeInDryMode[MAX_MENU_NUMBER][STAGE_COMPLETE+1];
//extern const UCHAR_XDATA Work_StageStartTimeInSteam_DryMode[MAX_MENU_NUMBER][STAGE_COMPLETE+1];
extern const StepInfo (*steps[]);

void checkHeatError(void);
void addWater(void);
bit IsNormalMune(MenuOption Mune);
bit IsSteamMune(MenuOption Mune);
bit IsDryMune(MenuOption Mune);

/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void Work_NextStep(void);
/**
 * @brief 
 * 
 * @param 
 * @return 
 */
void Work_Control(void);
/**
 * @brief 
 * 
 * @param 
 * @return 
 */


//20251011 厂测模式
typedef enum
{//20251011 厂测模式
  TEST_1,
  TEST_2,
  TEST_NULL
}TestOption;
typedef struct
{//20251011 厂测模式
    unsigned char stage:7;
    unsigned char clearStepDataEnable:1;
    unsigned char fnIndex;
	  unsigned char speed;//CONFIG_BLAM_ENABLE
    unsigned short arg;              
    unsigned short maxDuration;
}TestInfo;
extern TestOption  Test_CurrentOption;//20251011 厂测模式
extern UCHAR_XDATA Test_CurrentStep;//20251011 厂测模式
extern UCHAR_XDATA Test_CurrentStage;//20251011 厂测模式
extern UCHAR_XDATA Test_MaxStage;//20251011 厂测模式
extern const TestInfo (*t_steps[]);//20251011 厂测模式
void Test_NextStep(void);//20251011 厂测模式

#endif

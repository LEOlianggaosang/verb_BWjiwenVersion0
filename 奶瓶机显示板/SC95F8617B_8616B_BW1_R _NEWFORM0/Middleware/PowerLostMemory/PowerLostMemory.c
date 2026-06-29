/**
 *******************************************************************************
 * Copyright (c) 2025.5.17
 * 
 * @file    PowerLostMemory.c
 * @author  lianggaosang@qq.com
 * @brief   掉电记忆控制
 *
 *******************************************************************************
 */

#include "PowerLostMemory.h"

#include "Display\Display.h"
#include "Work\Work.h"
#include "Key\Key.h"
// #include "InletValveRotation\InletValveRotation.h"
//#include "Signals\Signals.h"
//#include "Outputs\Outputs.h"
#if CONFIG_IAPADDR_DEVICE	
#include "IapAddrDevice\IapAddrDevice.h"
#endif
/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
UCHAR_XDATA Work_EEPROM_Datas[EEPROM_MAX_LENTH] = {0};
/*
*******************************************************************************
**  Static define
*******************************************************************************
*/
static bit CheckEepDateOk(void);
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
/*
********************************************************************************
**  Function define
********************************************************************************
*/
void Init_PowerLostMemory(void)
{
    #if CONFIG_IAPADDR_DEVICE	
    IapAddrDevice_Init();
    #endif
}

void Recovery_Power_Lost_Memory(bit memaryEnable)
{//20251110 NEWFORM0 2.4
    if ((Work_MemoryRead)||(ResetFlagAfterPowerup))
    {
        if(memaryEnable)
        {
            eepromRestoreData(Work_EEPROM_Datas, EEPROM_MAX_LENTH);
        }
        
        if((Work_EEPROM_Datas[2]==0xa0 &&Work_EEPROM_Datas[3]==0xb0)&&CheckEepDateOk())
        {
            MiddleData = Work_EEPROM_Datas[0];
            Work_IsSteamMode = F_MiddleData_3;
            Work_IsDryMode = F_MiddleData_4;
            #if NEWTPE1
            Light_IsWorking = F_MiddleData_6;
            Work_InletMode = 0;//默认水泵进水，无法更改
            #else
            Work_InletMode = F_MiddleData_5;
            Light_IsWorking = 1;//默认开灯，无法更改
            #endif
            Work_LastMenu = Work_EEPROM_Datas[1];
            Work_CurrentState = INIT_STATE;
            #if CONFIG_MENORY_WASHDATA
            if((((UCHAR)STATE_WASHING)==Work_EEPROM_Datas[4])&&(!F_MiddleData_1)&&(!F_MiddleData_7))
            {//判断是否需要恢复洗涤
                Work_CurrentMenu = Work_EEPROM_Datas[1];
                Work_CurrentState = STATE_WASHING;
                Test_CurrentOption = TEST_NULL;
                Work_CurrentStage = Work_EEPROM_Datas[6];
                Work_CurrentStep = Work_EEPROM_Datas[7];
                Work_CurrentFnIndex = Work_EEPROM_Datas[8];
                Work_CurrentArg = ((UCHAR)Work_EEPROM_Datas[9]<<8)|(UCHAR)Work_EEPROM_Datas[10];
                Work_UsedSecondInCurrentStep = ((UCHAR)Work_EEPROM_Datas[11]<<8)|(UCHAR)Work_EEPROM_Datas[12];
                Work_LeftMinToEnd = ((UCHAR)Work_EEPROM_Datas[13]<<8)|(UCHAR)Work_EEPROM_Datas[14];
                currentFunctionUnitUsedSeconds = ((UCHAR)Work_EEPROM_Datas[15]<<8)|(UCHAR)Work_EEPROM_Datas[16];
                currentStepMaxDuationSecond = ((UCHAR)Work_EEPROM_Datas[17]<<8)|(UCHAR)Work_EEPROM_Datas[18];
                WorkActionFlag = Work_EEPROM_Datas[4];
                WorkFuctionFlag = Work_EEPROM_Datas[5];
                Work_NextStepHandler  = Work_NextStep;
            }
            else if((((UCHAR)STATE_TESTING)==Work_EEPROM_Datas[4])&&(!F_MiddleData_2)&&(!F_MiddleData_7))
            {
                Test_Entered = 1;
                Work_CurrentMenu = MENU_NULL;
                Work_CurrentState = STATE_TESTING;
                Work_CurrentStage = Work_EEPROM_Datas[6];
                Work_CurrentStep = Work_EEPROM_Datas[7];
                Work_CurrentFnIndex = Work_EEPROM_Datas[8];
                Work_CurrentArg = ((UCHAR)Work_EEPROM_Datas[9]<<8)|(UCHAR)Work_EEPROM_Datas[10];
                Work_UsedSecondInCurrentStep = ((UCHAR)Work_EEPROM_Datas[11]<<8)|(UCHAR)Work_EEPROM_Datas[12];
                Work_LeftMinToEnd = ((UCHAR)Work_EEPROM_Datas[13]<<8)|(UCHAR)Work_EEPROM_Datas[14];
                currentFunctionUnitUsedSeconds = ((UCHAR)Work_EEPROM_Datas[15]<<8)|(UCHAR)Work_EEPROM_Datas[16];
                currentStepMaxDuationSecond = ((UCHAR)Work_EEPROM_Datas[17]<<8)|(UCHAR)Work_EEPROM_Datas[18];
                WorkActionFlag = Work_EEPROM_Datas[4];
                WorkFuctionFlag = Work_EEPROM_Datas[5];
                Test_CurrentOption = Work_EEPROM_Datas[25];
                Test_CurrentStep = Work_EEPROM_Datas[26];
                Test_MaxStage = Work_EEPROM_Datas[27];
                Test_CurrentStage = Work_EEPROM_Datas[28];
                Work_NextStepHandler  = Test_NextStep;
            }
            else ifelse if((((UCHAR)STATE_ERROR)==Work_EEPROM_Datas[4])&&(F_MiddleData_7))
            {
                Error_SetCode(Work_EEPROM_Datas[30]);
            }
            #endif
            Work_KeyboardIsLocked = 0;
            Work_IsPaused = 0;
            Work_IsPowerLostMemory = 0;

            Work_MemoryRead = 0;
            ResetFlagAfterPowerup = 0;
        }
        else
        {
            if(Work_MemoryRead)
            {
                MiddleData = Work_EEPROM_Datas[0];
                Work_IsSteamMode = F_MiddleData_3;
                Work_IsDryMode = F_MiddleData_4;
                #if NEWTPE1
                Light_IsWorking = F_MiddleData_6;
                Work_InletMode = 0;//默认水泵进水，无法更改
                #else
                Work_InletMode = F_MiddleData_5;
                Light_IsWorking = 1;//默认开灯，无法更改
                #endif
                Work_LastMenu = Work_EEPROM_Datas[1];
                Work_MemoryRead = 0;
            }

            if(ResetFlagAfterPowerup)
            {//无记忆的初始化
                Work_CurrentState = INIT_STATE;
                Work_LastMenu = INIT_MENU;
                Work_IsSteamMode = 1;
                Work_IsDryMode = 1;
                Work_NextStepHandler  = Work_NextStep;
                Light_IsWorking = 1;//默认开灯，无法更改
                Work_InletMode = 0;//默认水泵进水，无法更改
                ResetFlagAfterPowerup = 0;
            }
        }
    }
}

void Work_PowerDownDeal(bit memaryEnable)
{//20251110 NEWFORM0 2.4
    unsigned char i;
    //掉电记忆 ------------------------------------------------------------
    //WordFlag  WorkAction_Flags;
    //MenuOption Work_LastMenu;
    //WorkState Work_CurrentState;
    //WordFlag WorkFuction_Flags;
    //
    if(Work_MemoryWrite)
    {
        Work_EEPROM_Datas[0] = (UCHAR)WorkActionFlag;
        Work_EEPROM_Datas[1] = (UCHAR)Work_LastMenu;
        if (memaryEnable)
        {
            Work_EEPROM_Datas[2] = 0xa0;
            Work_EEPROM_Datas[3] = 0xb0;
        }

        #if CONFIG_MENORY_WASHDATA
        if(Work_IsPowerLostMemory)
        {
            Work_EEPROM_Datas[4] = (UCHAR)Work_CurrentState;
            Work_EEPROM_Datas[5] = (UCHAR)WorkFuctionFlag;
            Work_EEPROM_Datas[6] = Work_CurrentStage;
            Work_EEPROM_Datas[7] = Work_CurrentStep;
            Work_EEPROM_Datas[8] = Work_CurrentFnIndex;
            Work_EEPROM_Datas[9] = (UCHAR)(Work_CurrentArg>>8);
            Work_EEPROM_Datas[10] = (UCHAR)(Work_CurrentArg);
            Work_EEPROM_Datas[11] = (UCHAR)(Work_UsedSecondInCurrentStep>>8);
            Work_EEPROM_Datas[12] = (UCHAR)(Work_UsedSecondInCurrentStep);
            Work_EEPROM_Datas[13] = (UCHAR)(Work_LeftMinToEnd>>8);
            Work_EEPROM_Datas[14] = (UCHAR)(Work_LeftMinToEnd);
            Work_EEPROM_Datas[15] = (UCHAR)(currentFunctionUnitUsedSeconds>>8);
            Work_EEPROM_Datas[16] = (UCHAR)(currentFunctionUnitUsedSeconds);
            Work_EEPROM_Datas[17] = (UCHAR)(currentStepMaxDuationSecond>>8);
            Work_EEPROM_Datas[18] = (UCHAR)(currentStepMaxDuationSecond);
            if(Test_Entered)
            {
                Work_EEPROM_Datas[25] = (UCHAR)(Test_CurrentOption);
                Work_EEPROM_Datas[26] = Test_CurrentStep;
                Work_EEPROM_Datas[27] = Test_MaxStage;
                Work_EEPROM_Datas[28] = Test_CurrentStage;
            }
            if(Error_IsHandling)
            {
                Work_EEPROM_Datas[30] = (UCHAR)(Error_CurrentCode);
            }
        }
        #endif
        Work_IsPowerLostMemory = 0;
        Work_EEPROM_Datas[EEPROM_MAX_LENTH-1] = 0;
        for (i = 0; i < (EEPROM_MAX_LENTH-1); i++)
        {
            Work_EEPROM_Datas[EEPROM_MAX_LENTH-1] += Work_EEPROM_Datas[i];
        }
        
        if (memaryEnable)
        {
            eepromSaveData(Work_EEPROM_Datas, EEPROM_MAX_LENTH);
        }
        Work_MemoryWrite = 0;
    }
}

static bit CheckEepDateOk(void)
{
    unsigned char i;
    unsigned char sum;
    sum = 0;
    for (i = 0;i < (EEPROM_MAX_LENTH-1);i++)
    {
        sum += Work_EEPROM_Datas[i];
    }
    //判断数据是否正确
    if (sum == Work_EEPROM_Datas[EEPROM_MAX_LENTH-1])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

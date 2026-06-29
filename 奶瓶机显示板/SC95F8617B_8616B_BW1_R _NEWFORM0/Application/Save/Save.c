/**
*******************************************************************************
 * Copyright (c) 2025.5.24
 * 
* @file    Save.c
* @author  lianggaosang@qq.com
* @brief   
* 
*******************************************************************************
*/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Save.h"
#include "TicketHandling\TicketHandling.h"
#include "Work\Work.h"
#include "Power\Power.h"
/***********************************************************************************************************************
global
***********************************************************************************************************************/
ByteFlag Save_Flags = {0};
/***********************************************************************************************************************
static
***********************************************************************************************************************/
static UINT_XDATA Save_Prepare_Seconds = 0;
static UCHAR_XDATA Save_CycCnt = 0;
static UINT_XDATA Save_Cyc_Seconds = 0;
static UINT_XDATA Save_Save_Seconds = 0;
static UINT_XDATA Save_Run_Seconds = 0;
static UINT_XDATA Save_Ptc_Seconds = 0;
static UINT_XDATA Save_Fun_Seconds = 0;
static UINT_XDATA Save_Led_Seconds = 0;
static void Save_ActionDeal(void);
/***********************************************************************************************************************
Function
***********************************************************************************************************************/
void Save_InitSet(void)
{
    Save_InitFlag = 1;
}

void Save_Control(bit Tick)
{
    if(Save_InitFlag)
    {
        Save_InitFlag = 0;
        Save_Prepare_Seconds = SAVE_PRE_MIN* 60;
        Save_CycCnt = SAVE_CYC_CNT;
        //Work_IsPaused = Power_DoorIsOpend;//20251110 NEWFORM0
        Work_DoorOpenDelaySecondCount = 1;//20251110 NEWFORM0 4、
        Save_Cyc_Seconds = 0;//20251110 NEWFORM0
        Save_Save_Seconds = 0;//20251110 NEWFORM0
        Save_WaitFlag = 1;
    }

    if(Save_ReloadFlag)
    {
        Save_ReloadFlag = 0;
        #if SAVE_ST_IN_CNT//20251110 NEWFORM0
        if((SAVE_CYC_CNT-1)==Save_CycCnt)
        {//20251010
            Save_Cyc_Seconds = (SAVE_CYC_MIN - SAVE_PRE_MIN) * 60;
            Save_Save_Seconds = (SAVE_CYC_MIN - SAVE_PRE_MIN - SAVE_RUN_MIN) * 60;
        }
        else
        #endif
        {
            Save_Cyc_Seconds = SAVE_CYC_MIN * 60;
            Save_Save_Seconds = (SAVE_CYC_MIN - SAVE_RUN_MIN) * 60;
        }

        Save_SaveFlag = 1;
        Save_RunFlag = Save_LedFlag = Save_PtcFlag = 0;
    }

    if((!Error_IsHandling)&&(!Work_IsPaused)&&(0==Work_DoorOpenDelaySecondCount))
    {//20250929//20251110 NEWFORM0 4、
        if(Tick != Save_Timer1s)
        {
            Save_Timer1s = Tick;
            CHECK_DEC(Save_Prepare_Seconds);
            CHECK_DEC(Save_Cyc_Seconds);
            CHECK_DEC(Save_Run_Seconds);
            CHECK_DEC(Save_Save_Seconds);
            CHECK_DEC(Save_Ptc_Seconds);
            CHECK_DEC(Save_Fun_Seconds);
            CHECK_DEC(Save_Led_Seconds);
        }

        Save_ActionDeal();
    }
}

bit Get_Save_FanState(void)
{
    bit ret = 0;
    if((!Error_IsHandling)&&(!Work_IsPaused)&&(0==Work_DoorOpenDelaySecondCount))
    {//20250929//20251110 NEWFORM0 4、
        ret = Save_RunFlag;
    }
    return ret;
}

bit Get_Save_PtcState(void)
{
    bit ret = 0;
    if((!Error_IsHandling)&&(!Work_IsPaused)&&(0==Work_DoorOpenDelaySecondCount))
    {//20250929//20251110 NEWFORM0 4、
        ret = Save_PtcFlag;
    }
    return ret;
}

bit Get_Save_LedState(void)
{
    bit ret = 0;
    if((!Error_IsHandling)&&(!Work_IsPaused)&&(0==Work_DoorOpenDelaySecondCount))
    {//20250929//20251110 NEWFORM0 4、
        ret = Save_LedFlag;
    }
    return ret;
}

UCHAR Get_Save_Hours(void)
{
    static UINT ret = 0;
    if(Save_WaitFlag)
    {
        ret = (Save_CycCnt*SAVE_CYC_MIN)/60;//h//20251110 NEWFORM0 13.3 20251126
    }
    else if(Save_CycCnt)
    {
        ret = Save_CycCnt*SAVE_CYC_MIN+Save_Cyc_Seconds/60;//min
        ret = (ret/60)+1;//h//先减一轮后补一小时向上对齐
    }
    else
    {
        ret = 1;
    }
    return (UCHAR)ret;
}
/***********************************************************************************************************************
private
***********************************************************************************************************************/
static void Save_ActionDeal(void)
{
    if(Save_WaitFlag)
    {
        Save_RunFlag = 1;
        Save_LedFlag = 1;
        if(Save_Prepare_Seconds >= (SAVE_PRE_MIN-SAVE_ST_FIRST_CNT)*60)//20251110 NEWFORM0
        {//20250920
            Save_PtcFlag = SAVE_ST_PTC_FIRST;//20251110 NEWFORM0
        }
        else
        {
            Save_PtcFlag = !SAVE_ST_PTC_FIRST;//20251110 NEWFORM0
        }
        if(0 == Save_Prepare_Seconds)
        {
            Save_WaitFlag = 0;
            Save_Cyc_Seconds = 0;//20251110 NEWFORM0
            Save_Save_Seconds = 0;//20251110 NEWFORM0
        }
    }
    else
    {
        if(0 == Save_Cyc_Seconds)
        {
            Save_ReloadFlag = 1;
            if(Save_CycCnt)
            {//20250929
                Save_CycCnt--;
            }
            else
            {
                Work_ClosePowerInit	= MD_TRUE;
            }
        }
        else
        {
            if(Save_SaveFlag)
            {
                if(0 == Save_Save_Seconds)
                {
                    Save_SaveFlag = 0;
                    Save_RunFlag = 1;
                    Save_PtcFlag = 1;
                    Save_LedFlag = 0;
                    Save_Run_Seconds = SAVE_RUN_MIN * 60;
                    Save_Ptc_Seconds = SAVE_RUN_PTC;
                }
            }

            if(Save_RunFlag)
            {
                if(SAVE_RUN_LED > Save_Run_Seconds)
                {
                    Save_LedFlag = 1;
                }

                if(Save_PtcFlag)
                {
                    if(0 == Save_Ptc_Seconds)
                    {
                        Save_PtcFlag = 0;
                        Save_Fun_Seconds = SAVE_RUN_FAN;
                    }
                    else
                    {
                        if(0 == Save_Fun_Seconds)
                        {
                            Save_PtcFlag = 1;
                            Save_Fun_Seconds = SAVE_RUN_PTC;
                        }
                    }
                }    
            }
        }
    }
}






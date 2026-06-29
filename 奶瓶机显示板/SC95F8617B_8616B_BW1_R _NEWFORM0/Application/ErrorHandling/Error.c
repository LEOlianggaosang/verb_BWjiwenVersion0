/**
*******************************************************************************
* 
* @file    Error.c
* @author  lianggaosang@qq.com
* @version 1.0
* @date    22:5:2025   
* @brief   故障处理模块实现
* 
*/

#include "TicketHandling\TicketHandling.h"
// #include "Relays\Relays.h"
// #include "Signals\Signals.h"
// #include "Buzzer\Buzzer.h"
// #include "InletValveRotation\InletValveRotation.h"
// #include "Temperatures\Temperatures.h"
// #include "Test\Self_Test.h"
#include "Key\Key.h"
#include "Work\Work.h"
#include "Power\Power.h"

#include "Error.h"
// #include "product_data.h"
///故障
typedef struct  
{
    unsigned char priority;   ///
    FunctionPt errorHandler;  ///
}Error;

static void errorRecovery(void);
static void errorNoHandler(void);
static void errorLackHandler(void);
static void errorInletHandler(void);
static void errorTdsHandler(void);//20251110 NEWFORM0 8.5
static void errorHeaterHandler(void);
static void errorRtHandler(void);
static void errorSerialHandler(void);
static void errorDoorHandler(void);
static void errorFanHandler(void);//#if CONFIG_FB_CHECK//20251204
// static void errorDrainHandler(void);
// static void errorOverHandler(void);
// static void errorPmamHandler(void);

static const Error errors[] =

{
    {0,errorNoHandler},
    {1,errorTdsHandler},//20251110 NEWFORM0 8.5
    {4,errorInletHandler},  
    {3,errorHeaterHandler}, 
    {3,errorRtHandler},
    {5,errorSerialHandler},
    {2,errorDoorHandler},  
    {1,errorLackHandler},   //20251110 NEWFORM0 8.5
    {3,errorFanHandler},    //#if CONFIG_FB_CHECK//20251204
    // {4,errorDrainHandler},       
    // {4,errorPmamHandler},           
    // {5,errorOverHandler},            
};

ErrorCode Error_CurrentCode = ERROR_NULL;
static UCHAR_XDATA rebuzCount = 0;
UCHAR_XDATA fanfbCount = 0;
UCHAR_XDATA drainCount = 0;

void Error_SetCode(ErrorCode errorCode)
{
    if (Work_CurrentState == STATE_RESET)
    {
        return;
    }
    if (errors[errorCode].priority > errors[Error_CurrentCode].priority)
    {
        Error_CurrentCode = errorCode;
        BeepState = BUZZ_ALARM;
        rebuzCount = 60;
    }
}

void Error_Handling(void)
{
    if (F_Error1s != F_Base1s)
    {
        F_Error1s = F_Base1s;
        CHECK_DEC(rebuzCount);
        CHECK_DEC(drainCount);

        if(Fcting)
        {
            return;
        }
        
        if(!Power_IsCommunicating)
        { 
            Error_SetCode(ERROR_SERIAL);
        }
        else 
        {
            #if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
            if (Power_DoorIsOpend)
            {
                if(((STATE_WASHING==Work_CurrentState)||(STATE_SAVING==Work_CurrentState)\
                ||(STATE_TESTING==Work_CurrentState)||(STATE_DRAIN==Work_CurrentState))&&(Work_IsPaused == MD_FALSE)&&(0==Work_DoorOpenDelaySecondCount))
                {//20251110 NEWFORM0 7、
                    Work_DoorOpenDelaySecondCount = 3;
                    Error_SetCode(ERROR_DOOR);
                }
            }
            #endif

            if(P_FlowMErrCnt >= C_ERR_LITER)
            {
                #if CONFIG_TEST_ERROR
                if(STATE_TESTING==Work_CurrentState)
                {
                    Error_SetCode(ERROR_INLET);
                    drainCount = 0;
                }
                else
                {
                    Inlet_ErrReload = 1;
                }
                #else
                Error_SetCode(ERROR_INLET);
                drainCount = 0;
                #endif
            }

            #if CONFIG_FB_CHECK//20251204
            if((Output_FAN_IN)&&(P_FeedBackCnt < 50))
            {//1500r(220==>6600r/额定5300r)
                if(++fanfbCount>10)
                {
                    fanfbCount = 10;
                    Err_FanFeedBack = 1;
                    #if CONFIG_TEST_ERROR
										if(STATE_TESTING==Work_CurrentState)
										{
											Error_SetCode(ERROR_FAN);
										}
											#if CONFIG_IQC_TEST//20260117
										else if(MENU_SELFCLEAN == Work_CurrentMenu)
										{
											Error_SetCode(ERROR_FAN);
										}
											#endif
										#else
										Error_SetCode(ERROR_FAN);
                    #endif
                }
            }
            else
            {
                fanfbCount = 0;
                Err_FanFeedBack = 0;
            }
            #endif
        }
    }

    if (Test_Entered==FALSE)
    {
        if((Work_CurrentState == STATE_POWER)&&(Error_CurrentCode != ERROR_NULL))
        {
            Error_CurrentCode = ERROR_NULL;
            BeepState = BUZZ_SILENCE;
        }
    }
    
    if ((Error_CurrentCode == ERROR_NULL)&&(STATE_ERROR != Work_CurrentState))
    {
        Error_IsHandling = MD_FALSE;
        Work_BufferState = Work_CurrentState;
        return;
    }

    Error_IsHandling = MD_TRUE;
    Work_CurrentState = STATE_ERROR;

    RelayEnable = 0;
    OutputEnable = 0;
    (*errors[Error_CurrentCode].errorHandler)();

    if (0==rebuzCount)
    {
        rebuzCount = 60;
        if(Power_DoorIsOpend)
        {
            BeepState = BUZZ_KEY_VALID;
        }
        else
        {
            BeepState = BUZZ_KEY_INVALID;
        }
    }
}

static void errorRecovery(void)
{
    Error_CurrentCode = ERROR_NULL;
    if(STATE_WASHING == Work_BufferState)
    {
        BeepState = BUZZ_KEY_VALID;
    }
    else
    {
        BeepState = BUZZ_SILENCE;
    }
    Work_CurrentState = Work_BufferState;
    //Work_IsPaused = Power_DoorIsOpend;//20251110 NEWFORM0 4、
    Work_DoorOpenDelaySecondCount = 1;//20251110 NEWFORM0 4、
}

static void errorNoHandler(void)
{
    //do nothing
}
static void errorLackHandler(void)
{
    if(!Inlet_Lack)
    {//20251007
        errorRecovery();
        Work_UsedSecondInCurrentStep = 0;//20251016 增加功能
    }
}
static void errorInletHandler(void)
{
    if(0==drainCount)
    {
        drainCount = 40;
    }

    if(drainCount>20)
    {
        Relay_DP = MD_TRUE;
    }
    else
    {
        Relay_DP = MD_FALSE;
    }
}

static void errorHeaterHandler(void)
{
    //无需处理 不能恢复
}

static void errorTdsHandler(void)
{//20251110 NEWFORM0 8.5
    //无需处理 不能恢复
}

static void errorRtHandler(void)
{   //自动恢复
    // if(!AdErr_ErrRe)
    // {
    //     errorRecovery();
    // }

    //无需处理 不能恢复
}

static void errorFanHandler(void)
{//#if CONFIG_FB_CHECK//20251204
    //无需处理 不能恢复
}

static void errorSerialHandler(void)
{//自动恢复
    if(Power_hasCommunicated)
    {
        errorRecovery();
    }
}

static void errorDoorHandler(void)
{//自动恢复
    if(!Power_DoorIsOpend)
    {
        errorRecovery();
    }
}

/* Include files ------------------------------------------------------- */
#include "Test\Self_Test.h"
#include "product_data.h"
#include "Work\Work.h"
#include "Key\Key.h"
#include "TicketHandling\TicketHandling.h"
#include "Buzzer\Buzzer.h"
#include "Display\Display.h"
#include "ErrorHandling\Error.h"
#include "Relays\Relays.h"
#include "Temperatures\Temperatures.h"
#include "Turbidity\Turbidity.h"
#include "Signals\Signals.h"
#include "Leds\Leds.h"
#include "Fan\Fan.h"
#include "InletValveRotation\InletValveRotation.h"

BOOL_XDATA Test_Entered = MD_FALSE;
UCHAR_XDATA Test_WaitKeyActionCount = 0;
UCHAR_XDATA Test_CurrentStep = 0;
UCHAR_XDATA Test_CurrentStage;
BOOL_XDATA Timer1s= MD_FALSE;//

/* Machine Test step information data */
typedef struct  
{
    UCHAR fnIndex;  /* Function index */
    UCHAR stage;    /* Stage ID */
    USHORT arg;     /* parameter used by function */
}TestStepInfo;

#ifdef __C51__
static const TestStepInfo  code testSteps[] =
#else
static const TestStepInfo  testSteps[] =
#endif
{
	{PAUSE_TIMER,                     0,  0},   //step 0

	{INLET_PS,                        1,  0},   //step 1
	{INLET_ROTATION,                  1,  500}, //step 2
	{PAUSE_TIMER,                     1,  0},   //step 3

	{DIVIDE_TIMER,                    2,  60},  //step 4
#if CONFIG_WASH_IN_TURN==1
	{WASH_UP_TIMER,                   3,  30},  //step 5
	{WASH_DOWN_TIMER,                 3,  30},  //step 6
#else
	{WASH_TIMER,                   3,  5},  //step 5
#endif
	{PAUSE_TIMER,                     3,  5},   //step 7

	{CHECK_LEAK,                      4,  3},   //step 8
	{HEAT_TEMPERATURE,                4,  60},  //step 9
	{PAUSE_TIMER,                     4,  0},   //step 10

	{DRAIN_PS,                        5,  0},   //step 11
	{DRAIN_TIMER,                     5,  30},  //step 12
	{PAUSE_TIMER,                     5,  0},   //step 13

	{INLET_PS,                        6,  0},   //step 14
	{INLET_ROTATION,                  6,  500}, //step 15
	{PAUSE_TIMER,                     6,  0},   //step 16
#if CONFIG_WASH_IN_TURN==1
	{WASH_UP_TIMER,                   7,  30}, //step 17
	{WASH_DOWN_TIMER,                 7,  30}, //step 18
#else
	{WASH_TIMER,                   7,  180}, //step 17
#endif
	{PAUSE_TIMER,                     7,  5},   //step 19
	{PAUSE_TIMER,                     7,  0},   //step 20

	{SOFT_TIMER,                      8,  90},  //step 21
	{PAUSE_TIMER,                     8,  0},   //step 22

	{DRAIN_PS,                        9,  0},   //step 23
	{DRAIN_TIMER,                     9,  30},  //step 24
	{PAUSE_TIMER,                     9,  0},   //step 25

	{FAN_TIMER,                       10, 60},   //step 26
	{COMPLETE_CHECK,                  10,  0},  // step 27

};

static FunctionPt  currentTestFn = NULL;

//static void encodeActionDealInMachineTest(void);
static void keyActionDealInMachineTest(void);

static void displayControlInMachineTest(void);
static void systemControlInMachineTest(void);

void nextTestStep(void);
static void setTestStage(unsigned char stage);

void Test_Machine(void)
{
    static UCHAR_XDATA processIndex = 0;

    Key_ActionHandler = keyActionDealInMachineTest;
    Work_NextStepHandler = nextTestStep;

    while (1)
    {
        RestartWatchdog();

        if (Timer_Tick4ms)
        {
            Timer_Tick4ms = MD_FALSE;

            processIndex ++;

            Flash_Control();
            Signal_Capture();

            switch (processIndex)
            {
            case 1:
                Buzz_Control();
                Temperature_Read();
#if CONFIG_AUTO_WASH                 
				zhuodu_Read();
#endif 
                break;
            case 2:
                displayControlInMachineTest();
                break;
            case 3:
                Display_Fresh();
                Work_PowerDownDeal(0);
                break;
            case 4:
                Key_ReadDatas();
                Key_MonitorAction();
                break;
            case 5:
                Error_Handling();
				Relay_Drive_4ms_do();//故障修改2.16  继电器闭合和断开延时
                if (Test_Entered)
                {
                    systemControlInMachineTest();
                }
                else
                {
                    Test_WaitKeyActionCount ++;
                }

                processIndex = 0;
                break;
            default:
                break;
            }
        }

        if (Test_WaitKeyActionCount > 6)
        {
            Test_WaitKeyActionCount = 0;
            Key_ActionHandler     = Key_ActionDealInUserMode;//没有这个的话，自检结束后按键会没反应
            Work_NextStepHandler  = Work_NextStep;//没有这个的话，自检结束后按键会没反应
            Test_CurrentStep = 0;
            Test_CurrentStage = 0;
            break;
        }
    }
}

static void keyActionDealInMachineTest(void)
{
    if (Test_Entered)
    {
        if (Key_Code == KEY_CODE_POWER)
        {
            Work_CurrentState = STATE_POWER;
            Error_CurrentCode = ERROR_NULL;
            Buzz_SetType(BUZZ_POWERON);
            Test_WaitKeyActionCount = 20;
            Test_Entered=FALSE;
			addedWaterSecond = 0; //故障修改
        }
        
        if (Error_IsHandling || IsDoorOpened()){return;};

        if (Key_Code == (KEY_CODE_PROGRAM | KEY_CODE_DELAY) && 
            Key_ActionType == KEY_ACTION_LONG_LONG)
        {
            temperatureDisplayCount = 10;
			Buzz_SetType(BUZZ_KEY_VALID);
        }

        if (Key_ActionType != KEY_ACTION_SHORT)
        {
            return;
        }
        
        if (Key_Code == KEY_CODE_PROGRAM)
        {
            switch (Test_CurrentStage)
            {
            case 0:
            case 6:
            case 8:
                setTestStage(Test_CurrentStage + 1);
                break;
            case 2:
            case 3:
            case 4:
                setTestStage(5);
                break;
			case 10:
				Work_CurrentState = STATE_FINISHED;
				Test_WaitKeyActionCount = 20;
				Test_Entered = FALSE;//故障修改1.2  不清的话，自检结束，能报E4，
				Work_CurrentStep = 0xff;
				Buzz_SetType(BUZZ_POWERON);
            default:
                return;
            }
            Buzz_SetType(BUZZ_KEY_VALID);
        }
        else if (Key_Code == KEY_CODE_DELAY)
        {
            switch (Test_CurrentStage)
            {
            case 1:
            case 5:
            case 7:
            case 9:
				setTestStage(Test_CurrentStage + 1);
				Buzz_SetType(BUZZ_KEY_VALID);
				break;
            }
        }
    }
    else
    {
        if (Key_Code == (KEY_CODE_DELAY | KEY_CODE_POWER) && Key_ActionType == KEY_ACTION_LITE_LONG)
        {
            Test_Entered = MD_TRUE;
			/*soft_set=4;
			soft_run=0;           
			Work_EEPROM_Datas[0]=(UCHAR)(soft_set);
			Work_EEPROM_Datas[1]=(UCHAR)(soft_run);
			eepromSaveData(Work_EEPROM_Datas, EEPROM_MAX_LENTH);*/
            nextTestStep();
            Buzz_SetType(BUZZ_ENTERCHECK);
        }
    }
}

static void displayControlInMachineTest(void)
{
    static ULONG_XDATA Timer_MonotonicClockBuf = 0;
    BOOL timerTick1s = MD_FALSE;

    if (Timer_MonotonicClock - Timer_MonotonicClockBuf >= OneSecondCount)
    {
        Timer_MonotonicClockBuf = Timer_MonotonicClock;
        timerTick1s = MD_TRUE;
    }

    Display_ClearDatas();
    Display_BrightnessLevel = HIGHT_LIGHTING_LEVEL;//进自检高亮
    if (Test_Entered == MD_FALSE)
    {
        return;
    }

    /* Always display in machine check mode */
    if (Signal_SaltIsLack)
    {
        turnOnLedSalt;
    }
    if (Signal_RinesIsLack)
    {
       turnOnLedRines;
    }
    /* Error display */
    if (Error_IsHandling)
    {
		if(Flash_Enable)
		{
           Display_ShowErrorCode();
		}

		Display_BIT_Control();
        return;
    }
    /* Temperature display */
    if (timerTick1s)
    {
        if (temperatureDisplayCount)
        {
            temperatureDisplayCount --;
        }
    }
    if (temperatureDisplayCount)
    {
        Display_ShowTemperature();
	    Display_BIT_Control();
        return;
    }

   if (Test_CurrentStage == 1)
    {
		if (Test_CurrentStep==3)
		{
#if CONFIG_AUTO_WASH        
            Display_Showzhuodudianya();//显示即时浊度电压
#else
            Display_ShowNum(9);
#endif
		}
		else
		{
			Display_ShowNum(9);
		}
	}
	else if (Test_CurrentStage)
	{
		Display_ShowNum(10 - Test_CurrentStage);
	}
    else
    {
        Display_SetAllDatas();
    }

    Display_BIT_Control();
}

static void systemControlInMachineTest(void)
{
    static ULONG_XDATA Timer_MonotonicClockBuf = 0;
    static ULONG_XDATA Timer_buff2 = 0;
    Relay_Enables.f_byte = 0;
    Disable_Fan_In();
	Set_Led(FLOOR_LED, MD_FALSE);
    if (Error_IsHandling)
    {
        return;
    }

    if (IsDoorOpened())
    {
        Relay_Drive();
        return;
    }

    Timer1s = MD_FALSE;//
    if (Timer_buff1 - Timer_buff2 >= OneSecondCount)
    {
        Timer_buff2 = Timer_buff1;
        Timer1s = MD_TRUE;
    }//
    (*currentTestFn)();
#if CONFIG_WASH_IN_TURN==1
	if (!Work_IsHalfMode && RELAY_WP_ENABLE == 1 && RELAY_HALF_ENABLE == MD_FALSE)
	{
		halfRelayControl();
	}
#endif
    if (Timer_MonotonicClock - Timer_MonotonicClockBuf > OneSecondCount)
    {
        Timer_MonotonicClockBuf = Timer_MonotonicClock;
        Work_UsedSecondInCurrentStep ++;
        checkHeatError();
    }

    Relay_Drive();
}

void nextTestStep(void)
{
    Work_UsedSecondInCurrentStep = 0;
    Signal_CurrentStepRotationCount = 0;

    Test_CurrentStep ++;

    Work_CurrentArg = testSteps[Test_CurrentStep].arg;

    Work_CurrentFnIndex = testSteps[Test_CurrentStep].fnIndex;
    currentTestFn = functions[Work_CurrentFnIndex];

    Test_CurrentStage = testSteps[Test_CurrentStep].stage;
}

static void setTestStage(unsigned char stage)
{
    if (stage <= Test_CurrentStage || stage > 10)
    {
        return;
    }

    do 
    {
        nextTestStep();
    } while (Test_CurrentStage < stage);
}

/* Includes head files */

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


UCHAR_XDATA boardCheckkeyCount = 0;
UCHAR_XDATA boardCheckkeywaitSecondCount = 0;
UCHAR_XDATA boardCheckSecondCount = 0;
BOOL_XDATA workshop_Entered = MD_FALSE;

//static void encodeActionDealInBoardTest(void);
static void keyActionDealInBoardTest(void);

static void displayControlInBoardTest(void);
static void systemControlInBoardTest(void);

void Test_Board(void)
{
    static UCHAR_XDATA processIndex = 0;

   // Encoder_ActionHandler = encodeActionDealInBoardTest;
    Key_ActionHandler = keyActionDealInBoardTest;

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
                displayControlInBoardTest();
               // Encoder_MonitorAction();
                break;
            case 3:
                Display_Fresh();
				Work_PowerDownDeal(CONFIG_EEPROM_ENABLE);             
                break;
            case 4:
                Key_ReadDatas();
                Key_MonitorAction();
                break;
            case 5:
                systemControlInBoardTest();
				Relay_Drive_4ms_do();//故障修改2.16  继电器闭合和断开延时

                if (!Test_Entered){Test_WaitKeyActionCount ++;};

                processIndex = 0;
                break;
            default:
                break;
            }
        }

        if (Test_WaitKeyActionCount > 6 )
        {
            Test_Entered = 0;//
						workshop_Entered = FALSE;
            Test_WaitKeyActionCount = 0;
            Test_CurrentStep = 0;
            Test_CurrentStage = 0;
            //用户模式下,为按键动作分配处理函数
            Key_ActionHandler = Key_ActionDealInUserMode;
            //用户模式下,为跳入下个工作时序分配具体实现
            Work_NextStepHandler = Work_NextStep;
						
					SetPin(FAN_OUTPUT, MD_FALSE);
					SetPin(FLOOR_LIGHT_OUTPUT, MD_FALSE);
					SetPin(DOOR_LIGHT_OUTPUT, OFF);
					SetPin(TURB_LIGHT_OUTPUT, OFF);
					SetPin(AUTO_DOOR_OPEN_OUTPUT, OFF);
					SetPin(AUTO_DOOR_CLOSE_OUTPUT, OFF);
						
            break;
        }
    }
}

static void keyActionDealInBoardTest(void)
{
    if (Key_ActionType != KEY_ACTION_SHORT){return;};

    if (Test_Entered)
    {
        if (Key_Code ==KEY_CODE_POWER)
        {
            Test_WaitKeyActionCount = 20;//20*20毫秒。刚上电时，400毫秒内检测是否进整机或车间自检。
        }
        else
        {
            Buzz_SetType(BUZZ_KEY_VALID);
        }
				if (boardCheckSecondCount >= ( 4 + boardCheckkeyCount))
				{
					if (Key_Code ==KEY_CODE_PROGRAM)
					{
						boardCheckkeywaitSecondCount = 0;
						boardCheckkeyCount++ ;
					}
				}
				if (Key_Code ==KEY_CODE_START)
				{
					boardCheckkeywaitSecondCount = 0;
					boardCheckkeyCount = 0;
					boardCheckSecondCount = 0;
				}
				if (boardCheckSecondCount > 4)
				{
					if (Key_Code ==KEY_CODE_DELAY)
					{
						boardCheckkeywaitSecondCount = 0;
						boardCheckkeyCount --;
						boardCheckSecondCount --;
					}
				}
    }
    else
    {
        if (Key_Code == KEY_CODE_BOARD_CHECK && Key_ActionType == KEY_ACTION_SHORT)
        {
            Test_Entered = MD_TRUE;
			workshop_Entered = MD_TRUE;
			soft_set=4;
			soft_run=0;           
			Work_EEPROM_Datas[0]=(UCHAR)(soft_set);
			Work_EEPROM_Datas[1]=(UCHAR)(soft_run);
			eepromSaveData(Work_EEPROM_Datas, EEPROM_MAX_LENTH);
            Buzz_SetType(BUZZ_KEY_VALID);
        }
    }
}

static void displayControlInBoardTest(void)
{
    Display_ClearDatas();
    if (!Test_Entered)
    {
        return;
    }

    if (boardCheckSecondCount < 2)
    {
        /* Display all */
        Display_SetAllDatas();
    }
    else if (boardCheckSecondCount < 4)
    {
        /* Version display */
#if CONFIG_AUTO_WASH        
        Display_Showzhuodudianya();//显示即时浊度电压 
#else
        Display_ShowNum(VERSION_NUMBER);
#endif
    }
    else
    {
			Display_ShowNum(boardCheckSecondCount - 4);
//        if (Flash_Enable)
//        {
//           //Display_ShowNum(VERSION_NUMBER); /* Version display(flash) */
//        }
        /* Input signal state display */

        if (Signal_InletValve)
        {
            LED_INLET_VALVE_SIGNAL;
        }
		if (Signal_PmamPosition)
		{
			LED_PMAM_POSITION_SIGNAL;
		}

        if (Signal_SaltIsLack)
        {
            LED_SALT_SIGNAL;
        }
        if (Signal_RinesIsLack)
        {
            LED_RINES_SIGNAL;
        }
        if (!IsDoorOpened())
        {
            LED_DOOR_SIGNAL; 
        }
        if (Signal_WaterIsOver)
        {
            LED_WATER_IS_OVER_SIGNAL; 
        }
        if (Temperature_AdValue > TEMPERATURE_MAX_AD || 
            Temperature_AdValue < TEMPERATURE_MIN_AD)
        {

        }
        else
        {
						LED_TEMPERATURE_SIGNAL;
        }
         if (Signal_WaterIsReached)//此款没水位开关
         {
            LED_WATER_IS_REACH_SIGNAL;
         }
				 if (GetPin(AUTO_DOOR_OPENED_INPUT) == MD_TRUE)
				 {
					 Display_Datas[10] |= BIT4;//2 MENU_STANDARD
				 }
				 if (GetPin(AUTO_DOOR_CLOSED_INPUT) == MD_TRUE)
				 {
					 Display_Datas[4] |= BIT4;//5 SOAK
				 }
    }
    Display_BIT_Control();
}

static void systemControlInBoardTest(void)
{
    static ULONG_XDATA Timer_MonotonicClockBuf = 0;
    if (Timer_MonotonicClock - Timer_MonotonicClockBuf > OneSecondCount)
    {
        Timer_MonotonicClockBuf = Timer_MonotonicClock;
				if ((boardCheckSecondCount > 4  || boardCheckSecondCount < 12))
				{
						boardCheckkeywaitSecondCount ++;
				}
				if ((boardCheckSecondCount < ( 4 + boardCheckkeyCount)) || boardCheckSecondCount > 12)
				{
					boardCheckSecondCount ++;

				}
				if ( boardCheckkeywaitSecondCount > 5)
				{
					boardCheckkeyCount ++;
					boardCheckkeywaitSecondCount = 0;
				}
    }

    Relay_Enables.f_byte = 0;
		
//    Set_Led(IR_LED, MD_TRUE);
//    Disable_Fan_In();
//	Set_Led(FLOOR_LED, MD_FALSE);

    if (boardCheckSecondCount < 2)
    {

    }
    else if (boardCheckSecondCount < 4)
    {

    }
    else if (boardCheckSecondCount < 5)
    {
        RELAY_HEAT_ENABLE = MD_TRUE;
        //Display_ShowNum(0);
    }
    else if (boardCheckSecondCount < 6)
    {
        RELAY_WP_ENABLE = MD_TRUE;
        //Display_ShowNum(1);
    }
    else if (boardCheckSecondCount < 7)
    {
        RELAY_DR_ENABLE = MD_TRUE;
        //Display_ShowNum(2);
    }
    else if (boardCheckSecondCount < 8)
    {
        RELAY_IV_ENABLE = MD_TRUE;
        //Display_ShowNum(3);
    }
    else if (boardCheckSecondCount < 9)
    {
        RELAY_SV_ENABLE = MD_TRUE;
        //Display_ShowNum(4);
    }
    else if (boardCheckSecondCount < 10)
    {
        RELAY_DV_ENABLE = MD_TRUE;
        //Display_ShowNum(5);
    }
    else if (boardCheckSecondCount < 11)
    {
        RELAY_HALF_ENABLE = MD_TRUE;
        //Display_ShowNum(6);
    }
    else if (boardCheckSecondCount < 12)
    {
				RELAY_PTC_ENABLE = MD_TRUE;
        //Display_ShowNum(7);
    }
		else if (boardCheckSecondCount < 50)
    {
				SetPin(FAN_OUTPUT, MD_TRUE);
				SetPin(FLOOR_LIGHT_OUTPUT, MD_TRUE);
				SetPin(DOOR_LIGHT_OUTPUT, ON);
				SetPin(TURB_LIGHT_OUTPUT, ON);
				if (boardCheckSecondCount % 2 == 1)
				{
					SetPin(AUTO_DOOR_OPEN_OUTPUT, ON);SetPin(AUTO_DOOR_CLOSE_OUTPUT, OFF);
				}
				else
				{
					SetPin(AUTO_DOOR_OPEN_OUTPUT, OFF);SetPin(AUTO_DOOR_CLOSE_OUTPUT, ON);
				}
    }
    else if (boardCheckSecondCount > 50)
    {
        Test_WaitKeyActionCount = 20;
    }
    Relay_Drive();
    SetPin(HALF_OUTPUT, RELAY_HALF_ENABLE);
}

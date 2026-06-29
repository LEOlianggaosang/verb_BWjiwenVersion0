/* Includes files -------------------------------------------------------*/
#include "TicketHandling\TicketHandling.h"
#include "PowerLostMemory\PowerLostMemory.h"
#include "Initialization\Initialization.h"
#include "product_config.h"
#include "Display\Display.h"
#include "Key\Key.h"
#include "Work\Work.h"
#include "Power\Power.h"
#include "Light\Light.h"
#include "ErrorHandling\Error.h"
#if CONFIG_OTA
#include "OTA\OTA_Uart.h"
#endif
#include "WatchdogDrv.h"
#if CONFIG_TK_DEBUG
#include "SOC_DebugTouchKey_Lib\SOC_DebugTouchKey.h"
#endif
/* Function declare -----------------------------------------------------*/
#if CONFIG_POWER_TEST//20260509
static void Work_PowerTest(void);
#endif
/* Program Entry */

void  main(void)
{
  ResetFlagAfterPowerup = (bit)Initialization();
  // LOG_PRINTF("Info: Power on!\n");
  //BeepState = BUZZ_POWERON;
  /* Recovery to the power-downing state */ 
  Recovery_Power_Lost_Memory(CONFIG_MENORYENABLE);
  //LOG_PRINTF("Info:Enter working loop!\n");
	//Work_NextStepHandler  = Work_NextStep;//厂测模式不在开始启动
  /* System Working loop */  
  #if CONFIG_TK_DEBUG
	SOCAPI_DeBugTouchKey_Init();
  #endif
  while (1)
  {
    RestartWatchdog();

    TK_Scan();
    
    if (F_Base1ms)
    {
      F_Base1ms = 0;
      // Leds_Flesh();
      #if CONFIG_POWER_TEST//20260509
      Key_Control();
      Work_PowerTest();
      Display_Control();
      Power_Control();
      #else
      Key_Control();
      Work_PowerDownDeal(CONFIG_MENORYENABLE);
      Recovery_Power_Lost_Memory(CONFIG_MENORYENABLE);
      Work_Control();
      Error_Handling();
      Display_Control();
      Power_Control();
      #endif
    }
  }
}

#if CONFIG_POWER_TEST//20260509
static void Work_PowerTest(void)
{
	#if NEWTPE1
  Output_IP = Inlet_IsInLetting = F_Led_SelfClean;
  FlowMCntSet = 0xffff;
	#endif
	Relay_DP = F_Led_Fast;
  Output_WP = F_Led_Srandard;
}
#endif
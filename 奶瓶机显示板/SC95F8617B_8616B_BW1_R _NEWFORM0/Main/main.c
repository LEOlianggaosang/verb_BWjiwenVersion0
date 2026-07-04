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

  #if CONFIG_POWER_TEST//20260702
  F_Led_Power = 1;
	Com1_Buf = Com2_Buf = Com3_Buf = DISP_CHAR_NULL;
  #endif

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
{//负载驱动规则
	#if NEWTPE1
  if(F_Led_Power||F_Led_Start)
  {
    RelayEnable = RelayEnable =0;
    Inlet_IsInLetting = 0;
    FlowMCntSet = 0;
    Inlet_ErrReload = 1;
  }
  else
  {
    if(F_Led_Light)
    {//对流量、温度、转速控制作处理20260702
      RelayEnable = RelayEnable =0;
      Inlet_IsInLetting = 0;
      FlowMCntSet = 0;
      if(F_Led_SelfClean)
      {//进水800ml
        FlowMCntSet = 8*C_LITER;
        if(P_FlowMCnt<=FlowMCntSet)
        {
          Output_IP = Inlet_IsInLetting = 1;
        }
      }

      if(F_Led_Fast)
      {//排水箱
        Relay_DP = Output_IP = Inlet_IsInLetting = 1;
        FlowMCntSet = 0xffff;
      }

      if(F_Led_Srandard)
      {//加热洗涤到设定温度一次
        Output_WP = 1;
        if((Temperature_Value<=45)&&(!AdErr_ErrRe))
        {
          Relay_HEAT = 1;
        }
      }

      if(F_Led_Sterilize)
      {//进水250ml
        FlowMCntSet = (C_LITER*25)/10;
        if(P_FlowMCnt<=FlowMCntSet)
        {
          Output_IP = Inlet_IsInLetting = 1;
        }
      }

      if(F_Led_Save)
      {//PTC与臭氧检测转速
        Output_FAN_IN = 1;
        if(P_FeedBackCnt >= 50)
        {
          Relay_PTC = 1;
          #if CONFIG_O3_ENABLE
          Output_O3 = 1;
          #endif
        }
      }
    }
    else
    {
      Output_IP = Inlet_IsInLetting = F_Led_SelfClean;
      FlowMCntSet = 0xffff;
      Relay_DP = F_Led_Fast;
      Output_WP = F_Led_Srandard;
      Relay_HEAT = F_Led_Sterilize;
      Output_FAN_IN = F_Led_Save;
    }
  }
  #endif
}
#endif
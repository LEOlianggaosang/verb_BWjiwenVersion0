
/**
*******************************************************************************
 * Copyright (c) 2025.5.17
 * 
* @file    Display.c
* @author  lianggaosang@qq.com
* @brief   8616b奶瓶机显示板
* 
*******************************************************************************
*/
#include "Display.h"

#include "Light\Light.h"
#include "TicketHandling\TicketHandling.h"
#include "Key\Key.h"
#include "Save\Save.h"
#include "Work\Work.h"
#include "Power\Power.h"
#include "ErrorHandling\Error.h"
#if CONFIG_IAPADDR_DEVICE	
#include "IapAddrDevice\IapAddrDevice.h"
#endif
//static**************************************************************************
static void DigitalMinCount(void);
static void DigitalHourCount(UCHAR hour);
static void Display_Screen_888(UINT Value);
static void DigitalErrorCode(UCHAR cod);
static void DigitalShowEnd(void);
static void DigitalShowSave(void);//20250929
static void DigitalShowVersion(void);//20251011 厂测模式
static void DigitalShowTestStep(void);//20251011 厂测模式
static void DigitalShowTemperature(void);//20260421 版本0
static void DigitalShowTheSame(UCHAR same);//20260421 版本0
static void NightLight_Control(void);
static void Fct_Display(void);
#if CONFIG_POWER_TEST//20260509
static void Display_PowerTest(void);
#endif
//Init_Display********************************************************************
static UCHAR_XDATA NL_Index = 0;
static UINT_XDATA NL_DoorOpenCnt_100ms = 0;//20251110 NEWFORM0 10.2
UCHAR_XDATA  NightLight_ColorType = 0;//CONFIG_NIGHT_LIGHT
UCHAR_XDATA  NightLight_ActionType = 0;//CONFIG_NIGHT_LIGHT
//Display_Fresh*******************************************************************
void Display_Control(void)
{
	
	static UCHAR NL_100msCnt = 0;

	if(F_Display100ms != F_Base100ms)
	{
		F_Display100ms = F_Base100ms;
		
		//CHECK_DEC(Flash_Enable_100msCnt);

		#if CONFIG_POWER_TEST//20260509
		Display_PowerTest();
		#else
		if(Fcting)
		{
			Trant_LED_Index(DIGITAL_ALL_OFF);
			Trant_LED_Index(LED_ALL_OFF);
			Trant_LED_Index(LED_POWER_ON);//全亮指令
			Fct_Display();
		}
		else
		{
			//State
			switch(Work_CurrentState)
			{
				case STATE_RESET:
					Trant_LED_Index(DIGITAL_ALL_ON);
					Trant_LED_Index(LED_ALL_ON);
					break;
				/* --------------------------------------------------------- */
				case STATE_POWER:
					Trant_LED_Index(LED_POWER_OFF);//单独电源键半亮指令
					#if (CONFIG_EXTRA_INFORMATION&&NEWTPE1)
					//20251105 1、增加特殊数据显示按键调试功能
					if(KEY_SELFCLEAN)
					{
						if(Light_IsWorking)
						{
							Display_Screen_888(P_FlowMErrCnt);//20251110 NEWFORM0 1、/P_FlowMErrCnt/IapSectorCnt
						}
						else
						{
							Display_Screen_888(P_FeedBackCnt);//20251203 P_FeedBackCnt
						}
						F_Led_SelfClean = 1;
					}
					#endif
					break;
				/* --------------------------------------------------------- */
				case STATE_DRAIN:
					Trant_LED_Index(DIGITAL_NULL);
					Trant_LED_Index(LED_ALL_OFF);//MENU_NULL
					F_Led_Power = F_Blink500ms;
					#if NEWFORM0//20251110 NEWFORM0 8.2
					DigitalShowTheSame(DISP_CHAR_NULL);//20260421 版本0
					#else
					DigitalShowTheSame(DISP_CHAR_BAR);//20260421 版本0
					#endif
					break;
				/* --------------------------------------------------------- */
				case STATE_STANDBY:
					Trant_LED_Index(DIGITAL_STATE);
					Trant_LED_Index(LED_PROG_STANDBY);
					F_Led_Power = 1;
					F_Led_Start = 0;
					#if (CONFIG_EXTRA_INFORMATION&&NEWTPE1)
					//20251105 1、增加特殊数据显示按键调试功能
					if(KEY_SELFCLEAN)
					{
						if(Light_IsWorking)
						{
							Display_Screen_888(P_FlowMErrCnt);//20251110 NEWFORM0 1、/P_FlowMErrCnt/IapSectorCnt
						}
						else
						{
							Display_Screen_888(P_FeedBackCnt);//20251203 P_FeedBackCnt
						}
					}
					else
					#endif
					{
						DigitalMinCount();
					}
					break;
				/* --------------------------------------------------------- */
				case STATE_WASHING:
					#if CONFIG_LIFE_TEST//20251204
					if(++NL_100msCnt>10)
					{
						NL_100msCnt = 0;
						if(++NL_Index>=(UCHAR)RGB_WHITE)
						{
							NL_Index = 0;
						}
					}
					#elif CONFIG_IQC_TEST//20260117
					if(MENU_FAST == Work_CurrentMenu)
					{
						NL_Index = Work_UsedSecondInCurrentStep/2;
					}
					#endif
					Trant_LED_Index(DIGITAL_STATE);
					Trant_LED_Index(LED_PROG_WORK);
					#if (CONFIG_EXTRA_INFORMATION&&NEWTPE1)
					//20251105 1、增加特殊数据显示按键调试功能
					if(KEY_SELFCLEAN)
					{
								#if (CONFIG_STATE_FLESH&&CONFIG_EXTRA_INFORMATION&&NEWTPE1)
								//20251110 NEWFORM0 20251127 9.4
								if(Relay_HEAT)
								{
									F_Wsah = 1;
								}
								if(Relay_PTC)
								{
									F_Sterilize = 1;
								}
								if(Output_FAN_IN)
								{
									F_Save = 1;
								}
								#endif
						if(Inlet_IsInLetting)
						{
							Display_Screen_888(P_FlowMCnt);
						}
						else
						{
							if(Light_IsWorking)
							{
								DigitalShowTemperature();//20260421 版本0
							}
							else
							{
								Display_Screen_888(P_FeedBackCnt);//20251203//P_FlowMErrCnt/P_FlowMErrCnt/IapSectorCnt
							}
						}
						F_Led_SelfClean = 1;
					}
					else
					#endif
					{
						#if CONFIG_LIFE_TEST//20251204
						if(((MENU_FAST == Work_CurrentMenu)||(MENU_SELFCLEAN == Work_CurrentMenu))&&(F_Blink500ms))
						{//20251128
							Display_Screen_888(LifeTestCnt);
						}
						else if((MENU_STANDARD == Work_CurrentMenu)&&(F_Blink500ms))
						{
							DigitalShowTemperature();//20260421 版本0
						}
						else
						#elif CONFIG_IQC_TEST//20260117
						if((MENU_FAST == Work_CurrentMenu)||(MENU_SELFCLEAN == Work_CurrentMenu))
						{//20251128
							Display_Screen_888(Work_UsedSecondInCurrentStep);
						}
						else
						#endif
						{
							DigitalMinCount();
						}
					}
					break;
				/* --------------------------------------------------------- */
				case STATE_ERROR:
					Trant_LED_Index(DIGITAL_NULL);
					Trant_LED_Index(LED_ALL_OFF);
					F_Led_Power = 1;
					#if NEWTPE1
					if(Inlet_Lack)
					{
						#if NEWFORM0//20251110 NEWFORM0 9.3
						F_Lack_Rad = !F_Blink500ms;
						#else
						F_Lack_Rad = 1;
						#endif
					}
					else
					{
						F_Lack_Rad = 0;
					}
					#endif
					if(ERROR_LACK == Error_CurrentCode)
					{
						if(!F_Blink500ms)
						{//20251007
							F_Led_Start = 1;
						}
						else
						{
							F_Led_Start = 0;
						}
						#if (CONFIG_EXTRA_INFORMATION&&NEWTPE1)
						//20251105 1、增加特殊数据显示按键调试功能
						if(KEY_SELFCLEAN)
						{
							Display_Screen_888(P_FlowMErrCnt);//20251110 NEWFORM0 1、/P_FlowMErrCnt/IapSectorCnt
							F_Led_SelfClean = 1;
						}
						else
						#endif
						{
							#if	NEWFORM0//20251110 NEWFORM0 8.7
							if(Test_Entered)
							{
								DigitalShowTestStep();
							}
							else
							{
								DigitalMinCount();
							}
							#else
							DigitalErrorCode((UCHAR)Error_CurrentCode);
							#endif
						}
					}
					else
					{
						F_Led_Start = 0;
						#if (CONFIG_EXTRA_INFORMATION&&NEWTPE1)
						//20251105 1、增加特殊数据显示按键调试功能
						if(KEY_SELFCLEAN)
						{
							if(Light_IsWorking)
							{
								Display_Screen_888(P_FlowMErrCnt);//20251110 NEWFORM0 1、/P_FlowMErrCnt/IapSectorCnt
							}
							else
							{
								Display_Screen_888(P_FeedBackCnt);//20251203
							}
							F_Led_SelfClean = 1;
						}
						else
						#endif
						{
							DigitalErrorCode((UCHAR)Error_CurrentCode);
						}
					}
					break;
				/* --------------------------------------------------------- */
				case STATE_SAVING:
					//20251010
					Trant_LED_Index(DIGITAL_STATE);
					Trant_LED_Index(LED_PROG_WORK);
					#if (CONFIG_EXTRA_INFORMATION&&NEWTPE1)
					//20251105 1、增加特殊数据显示按键调试功能
					if(KEY_SELFCLEAN)
					{
								#if (CONFIG_STATE_FLESH&&CONFIG_EXTRA_INFORMATION&&NEWTPE1)
								//20251110 NEWFORM0 20251127 9.4
								if(Relay_HEAT)
								{
									F_Wsah = 1;
								}
								if(Relay_PTC)
								{
									F_Sterilize = 1;
								}
								if(Output_FAN_IN)
								{
									F_Save = 1;
								}
								#endif
						if(Light_IsWorking)
						{
							Display_Screen_888(P_FlowMErrCnt);//20251110 NEWFORM0 1、/P_FlowMErrCnt/IapSectorCnt
						}
						else
						{
							Display_Screen_888(P_FeedBackCnt);//20251203
						}
						F_Led_SelfClean = 1;
					}
					else
					#endif
					{
						DigitalHourCount(Get_Save_Hours());
					}
					/* ----------------------------- */
					// //20250929
					// Trant_LED_Index(DIGITAL_NULL);
					// Trant_LED_Index(LED_ALL_OFF);
					// F_Save = Save_RunFlag;
					// F_Led_Dry = 1;//保管键常亮
					// F_Led_Power = Work_IsPaused|Save_RunFlag;
					// F_Led_Start = Work_IsPaused&(!F_Blink500ms);
					// if((!Save_RunFlag)&&(!Work_IsPaused))
					// {
					// 	Com1_Buf = Com2_Buf = Com3_Buf = DISP_CHAR_NULL;
					// }
					// else
					// {
					// 	if(Save_WaitFlag)
					// 	{	
					// 		//数码管FAN
					// 		DigitalShowSave();
					// 	}
					// 	else
					// 	{
					// 		//数码管72H
					// 		DigitalHourCount(Get_Save_Hours());
					// 	}
					// }
					/* ----------------------------- */
					// if(Work_IsPaused)
					// {
					// 	//数码管闪烁，启停键闪烁，电源键、保管键常亮
					// 	if(Save_WaitFlag)
					// 	{	
					// 		//数码管FAN
					// 	}
					// 	else
					// 	{
					// 		//数码管72H
					// 	}
					// }
					// else
					// {
					// 	if(Save_RunFlag)
					// 	{//数码管、电源键、保管键常亮、启停键熄灭
					// 		if(Save_WaitFlag)
					// 		{	
					// 			//数码管FAN
					// 		}
					// 		else
					// 		{
					// 			//数码管72H
					// 		}
					// 	}
					// 	else
					// 	{
					// 		//数码管、电源键、启停键熄灭、保管键常亮
					// 	}
					// }
					break;
				/* --------------------------------------------------------- */
				case STATE_FINISHED://20250929
					Trant_LED_Index(DIGITAL_NULL);
					Trant_LED_Index(LED_ALL_OFF);
					F_Led_Power = 1;
					DigitalShowEnd();
					break;
				/* --------------------------------------------------------- */
				case STATE_TESTING://20251011 厂测模式
					if(++NL_100msCnt>10)
					{
						NL_100msCnt = 0;
						if(++NL_Index>=(UCHAR)RGB_WHITE)
						{
							NL_Index = 0;
						}
					}
					
					if(Test_Entered)
					{//正式进入

						#if CONFIG_TESTENTER_CHECK
						if(Key_TestEnter)
						{//按键显示测试
							Trant_LED_Index(LED_TESTTING);
						}
						else
						#endif
						{//厂测时序
							Trant_LED_Index(DIGITAL_NULL);
							Trant_LED_Index(LED_PROG_WORK);
							#if (CONFIG_DISPLAY_INLET&&NEWTPE1)
							if(Inlet_IsInLetting)
							{//20251110 NEWFORM0 13.4 20251127
								#if CONFIG_STATE_FLESH
								F_Lack = !F_Blink500ms;//20251110 NEWFORM0 9.3
								#else
								F_Lack = 1;
								#endif
							}
							#endif
							#if (CONFIG_EXTRA_INFORMATION&&NEWTPE1)
							//20251105 增加特殊数据显示按键调试功能
							if(KEY_SELFCLEAN)
							{//20251110 NEWFORM0 13.4 20251127
								if(Inlet_IsInLetting)
								{
									Display_Screen_888(P_FlowMCnt);
								}
								else
								{
									if(Light_IsWorking)
									{
										Display_Screen_888(P_FlowMErrCnt);//20251110 NEWFORM0 1、/P_FlowMErrCnt/IapSectorCnt
									}
									else
									{
										Display_Screen_888(P_FeedBackCnt);//20251203
									}
								}
								#if (CONFIG_STATE_FLESH&&CONFIG_EXTRA_INFORMATION&&NEWTPE1)
								//20251110 NEWFORM0 20251127 9.4
								if(Relay_HEAT)
								{
									F_Wsah = 1;
								}
								if(Relay_PTC)
								{
									F_Sterilize = 1;
								}
								if(Output_FAN_IN)
								{
									F_Save = 1;
								}
								#endif
								F_Led_SelfClean = 1;
							}
							else
							#endif
							{
								DigitalShowTestStep();
							}
						}
					}
					else
					{//未正式进入显示版本号
						Trant_LED_Index(DIGITAL_NULL);
						Trant_LED_Index(LED_ALL_OFF);
						F_Led_Power = 1;
						F_Led_Start = 1;
						DigitalShowVersion();
					}
					
					break;
				default:
					break;
			}


			if(STATE_POWER != Work_CurrentState)
			{
				Trant_LED_Index(LED_POWER_ON);//全亮指令
			}
		}
		#endif
		Leds_Flesh();
		NightLight_Control();
	}
}

static void DigitalMinCount(void)
{
	if(((STATE_STANDBY == Work_CurrentState)||Work_IsPaused)&&(F_Blink500ms))
	{//数码管显示总运行时间，闪烁
		Com1_Buf = Com2_Buf = Com3_Buf = DISP_CHAR_NULL;
	}
	else
	{
		#if NEWFORM0
		//20251110 NEWFORM0 8、三位数显示
		Com1_Buf = Work_LeftMinToEnd/100;
		if(0 == Com1_Buf)
		{
			Com1_Buf = DISP_CHAR_NULL;
		}
		Com2_Buf = (Work_LeftMinToEnd%100)/10;
		if(0 == Com2_Buf)
		{
			Com2_Buf = DISP_CHAR_NULL;
		}
		Com3_Buf = Work_LeftMinToEnd%10;
		#else
		Com1_Buf = Work_LeftMinToEnd / 60;
		Com2_Buf = (Work_LeftMinToEnd % 60) / 10;
		Com3_Buf = Work_LeftMinToEnd % 10;
		#endif
	}

	#if NEWFORM0
	//20251110 NEWFORM0 8、三位数显示
	Dot_Set(0);
	#else
	if((STATE_WASHING != Work_CurrentState)&&(!Work_IsPaused))
	{
		Dot_Set(1);
	}
	else
	{
		Dot_Set(!F_Blink500ms);
	}
	#endif
	
}

static void DigitalHourCount(UCHAR hour)
{
	if((Work_IsPaused)&&(F_Blink500ms))
	{//20250929
		Com1_Buf = Com2_Buf = Com3_Buf = DISP_CHAR_NULL;
	}
	else
	{
		if(hour/100)
		{//20250929
			Com1_Buf = (hour/100)%10;
			Com2_Buf = (hour/10)%10;
			Com3_Buf = hour%10;
		}
		else
		{
			Com1_Buf = hour/10;
			if(0 == Com1_Buf)
			{
				Com1_Buf = DISP_CHAR_NULL;
			}
			Com2_Buf = hour%10;
			Com3_Buf = DISP_CHAR_H;
		}
	}
	Dot_Set(0);
}

static void Display_Screen_888(UINT Value)
{
	if((Value/1000)&&F_Blink500ms)
	{
		Com1_Buf = DISP_CHAR_BAR;
		Com2_Buf = Value / 10000;
		Com3_Buf = (Value / 1000)%10;
	}
	else
	{
		Com1_Buf = (Value / 100)%10;
		Com2_Buf = (Value / 10)%10;
		Com3_Buf = Value % 10;
		if(0 == Com1_Buf)
		{
			Com1_Buf = DISP_CHAR_NULL;
			if(0 == Com2_Buf)
			{
				Com2_Buf = DISP_CHAR_NULL;
			}
		}
	}
	Dot_Set(0);
}

static void DigitalErrorCode(UCHAR cod)
{
	if(ERROR_DOOR == cod)
	{
		Com1_Buf = DISP_CHAR_O;
		Com2_Buf = DISP_CHAR_P;
		Com3_Buf = DISP_CHAR_E;
	}
	else
	{
		Com1_Buf = DISP_CHAR_NULL;
		Com2_Buf = DISP_CHAR_E;
		Com3_Buf = cod;
	}
	Dot_Set(0);	
}

static void DigitalShowEnd(void)
{
	Com1_Buf = DISP_CHAR_E;
	Com2_Buf = DISP_CHAR_n;
	Com3_Buf = DISP_CHAR_d;
	Dot_Set(0);
}

static void DigitalShowSave(void)
{//20250929
	if((Work_IsPaused)&&(F_Blink500ms))
	{
		Com1_Buf = Com2_Buf = Com3_Buf = DISP_CHAR_NULL;
	}
	else
	{
		Com1_Buf = DISP_CHAR_F;
		Com2_Buf = DISP_CHAR_A;
		Com3_Buf = DISP_CHAR_N;
	}
	Dot_Set(0);
}

static void DigitalShowVersion(void)
{//20251011 厂测模式
	if(F_Blink500ms)
	{//电源板版本号
		Com1_Buf = DISP_CHAR_P;
		Com2_Buf = (P_Version_Number % 100) / 10;
		Com3_Buf = P_Version_Number % 10;
	}
	else
	{//显示板版本号
		Com1_Buf = DISP_CHAR_b;
		Com2_Buf = (VERSION_NUMBER % 100) / 10;
		Com3_Buf = VERSION_NUMBER % 10;
	}
	Dot_Set(0);
}

static void DigitalShowTestStep(void)
{//20251011 厂测模式
	if((Work_IsPaused)&&(F_Blink500ms))
	{
		Com1_Buf = Com2_Buf = Com3_Buf = DISP_CHAR_NULL;
	}
	else if((2==Test_CurrentStage)&&(F_Blink500ms))
	{
		
		Com1_Buf = (Temperature_Value % 100) / 10;
		Com2_Buf = Temperature_Value % 10;
		Com3_Buf = DISP_CHAR_C;
	}
	else
	{
		Com1_Buf = DISP_CHAR_t;
		Com2_Buf = (Test_CurrentStage % 100) / 10;
		Com3_Buf = Test_CurrentStage % 10;
	}
	Dot_Set(0);
}

static void DigitalShowTemperature(void)
{//20260421 版本0
	Com1_Buf = (Temperature_Value % 100) / 10;
	Com2_Buf = Temperature_Value % 10;
	Com3_Buf = DISP_CHAR_C;
	Dot_Set(0);
}

static void DigitalShowTheSame(UCHAR same)
{//20260421 版本0
	Com1_Buf = Com2_Buf = Com3_Buf = same;
	Dot_Set(0);
}

static void NightLight_Control(void)
{
	#if CONFIG_NIGHT_LIGHT
	if(Light_IsWorking)
	{
		if(Power_IsCommunicating&&Power_DoorIsOpend)
		{
			if(++NL_DoorOpenCnt_100ms >= 6000)//600s
			{//20251110 NEWFORM0 10.2
				NL_DoorOpenCnt_100ms = 6000;
				NightLight_ColorType = RGB_OFF;	
				NightLight_ActionType = ON_RGB;
			}
			else
			{
				NightLight_ColorType = RGB_WHITE;
				if(Work_IsPaused)
				{//20260421 版本0
					NightLight_ActionType = BREATH_RGB;
				}
				else
				{
					NightLight_ActionType = ON_RGB;
				}
			}
		}
		#if CONFIG_LIFE_TEST//20251204
		else if((MENU_FAST == Work_CurrentMenu)||(MENU_FAST == Work_CurrentMenu)||(MENU_STANDARD ==  Work_CurrentMenu))
		{
			NightLight_ColorType = NL_Index;
			NightLight_ActionType = ON_RGB;
		}
		#elif CONFIG_IQC_TEST//20260117
		else if(MENU_FAST == Work_CurrentMenu)
		{
			NightLight_ColorType = NL_Index;
			NightLight_ActionType = ON_RGB;
		}
		#endif
		else
		{
			NL_DoorOpenCnt_100ms = 0;//20251110 NEWFORM0 10.2
			switch(Work_CurrentState)
			{
				case STATE_WASHING:
					switch(Work_CurrentStage)
					{
						case STAGE_STEAM:
							NightLight_ColorType = RGB_WARM;
							break;
						case STAGE_DRY:
							NightLight_ColorType = RGB_ORANGE;
							break;
						default:
							NightLight_ColorType = RGB_COLD;
							break;
					}

					if(Work_IsPaused)
					{//20260421 版本0
						NightLight_ActionType = BREATH_RGB;
					}
					else
					{
						NightLight_ActionType = ON_RGB;
					}

					break;
				case STATE_ERROR:
					NightLight_ColorType = RGB_RED;	
					NightLight_ActionType = FLESH1_RGB;
					break;
				case STATE_FINISHED:
					NightLight_ColorType = RGB_YELLOW;	
					NightLight_ActionType = BREATH_RGB;
					break;
				case STATE_SAVING:
					NightLight_ColorType = RGB_GREEN;	
					NightLight_ActionType = ON_RGB;
					break;
				case STATE_TESTING:
					NightLight_ColorType = NL_Index;
					NightLight_ActionType = ON_RGB;
					break;
				default://MENU_NULL
					NightLight_ColorType = RGB_OFF;	
					NightLight_ActionType = ON_RGB;
					break;
			}
		}
	}
	else
	#endif
	{
		NightLight_ColorType = RGB_OFF;	
		NightLight_ActionType = ON_RGB;
		NL_DoorOpenCnt_100ms = 0;//20251110 NEWFORM0 10.2
	}
}

static void Fct_Display(void)
{
			if(FctActionFlag>>1)
			{
				if(++FctKeyCnt >= 10)
				{
					FctKeyCnt = 0;
					FctActionFlag = 0;
					Fcting = 1;
				}
				
				if(Fct_FastMune)
				{
					Com1_Buf = Com2_Buf = Com3_Buf = 1;
					Dot_Set(1);
					F_Led_Fast = 1;
				}
				else if(Fct_PowerCommand)
				{
					Com1_Buf = Com2_Buf = Com3_Buf = 2;
					Dot_Set(1);
					F_Led_Power = 1;
				}
				else if(Fct_SteamFunc)
				{
					Com1_Buf = Com2_Buf = Com3_Buf = 3;
					Dot_Set(1);
					F_Led_Steam = 1;
				}
				#if NEWTPE1
				else if(Fct_SelfCleanMune)
				{
					Com1_Buf = Com2_Buf = Com3_Buf = 4;
					Dot_Set(1);
					F_Led_SelfClean = 1;
				}
				#endif
				else if(Fct_InletCommand)
				{
					F_Lack = 1;
					F_Led_Inlet = 1;
				}
				else if(Fct_SrandardMune)
				{
					F_Wsah = 1;
					F_Led_Srandard = 1;
				}
				else if(Fct_DryFunc)
				{
					F_Steam = 1;
					F_Led_Dry = 1;
				}
				else if(Fct_StartCommand)
				{
					F_Save = 1;
					F_Led_Start = 1;
				}
			}
			else
			{
				FctKeyCnt = 0;
				if(Power_IsCommunicating)
				{
					#if NEWTPE1
					F_Lack_Rad = 1;
					#endif
				}
			}
}

#if CONFIG_POWER_TEST//20260509
static void Display_PowerTest(void)
{
	Light_IsWorking = 0;
}
#endif
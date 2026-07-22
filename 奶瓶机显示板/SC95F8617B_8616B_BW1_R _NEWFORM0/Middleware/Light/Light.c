/**
*******************************************************************************
 * Copyright (c) 2025.4.28
 * 
* @file    Light.c
* @author  lianggaosang@qq.com
* @brief   8616b奶瓶机显示板
* 
*******************************************************************************
*/
#include "Light.h"
#include "Key\Key.h"
#include "Power\Power.h"
#include "Work\Work.h"
#include "TicketHandling\TicketHandling.h"
//static***********************************************************************
static      ByteFlag  xdata    LBB_Digital_Flags;
#define		Digital_Buf			LBB_Digital_Flags.f_byte
#define		LF_SEG_A		    LBB_Digital_Flags.f_bits.no0
#define     LF_SEG_B		    LBB_Digital_Flags.f_bits.no1
#define     LF_SEG_C		    LBB_Digital_Flags.f_bits.no2
#define     LF_SEG_D		    LBB_Digital_Flags.f_bits.no3
#define     LF_SEG_E		    LBB_Digital_Flags.f_bits.no4
#define     LF_SEG_F		    LBB_Digital_Flags.f_bits.no5
#define     LF_SEG_G		    LBB_Digital_Flags.f_bits.no6
#define     LF_SEG_DP		    LBB_Digital_Flags.f_bits.no7
static UCHAR_XDATA LedRamBuf[28] = {0};
// static void Leds_Test(void);
//Tab**************************************************************************
Led_NameTypeDef xdata tLeds[LED_END] = 
{
	#if NEWTPE1
	{0, RAM_SEG9,  RAM_COM3},//Com1_SegA
	{0, RAM_SEG8,  RAM_COM3},
	{0, RAM_SEG6,  RAM_COM3},
	{0, RAM_SEG4,  RAM_COM3},
	{0, RAM_SEG3,  RAM_COM3},
	{0, RAM_SEG2,  RAM_COM3},
	{0, RAM_SEG1,  RAM_COM3},

	{0, RAM_SEG9,  RAM_COM4},//Com2_SegA
	{0, RAM_SEG8,  RAM_COM4},
	{0, RAM_SEG6,  RAM_COM4},
	{0, RAM_SEG4,  RAM_COM4},
	{0, RAM_SEG3,  RAM_COM4},
	{0, RAM_SEG2,  RAM_COM4},
	{0, RAM_SEG1,  RAM_COM4},

	{0, RAM_SEG9,  RAM_COM5},//Com3_SegA
	{0, RAM_SEG8,  RAM_COM5},
	{0, RAM_SEG6,  RAM_COM5},
	{0, RAM_SEG4,  RAM_COM5},
	{0, RAM_SEG3,  RAM_COM5},
	{0, RAM_SEG2,  RAM_COM5},
	{0, RAM_SEG1,  RAM_COM5},

	{0, RAM_SEG9,  RAM_COM6},//Com4_SegA
	{0, RAM_SEG8,  RAM_COM6},
	{0, RAM_SEG6,  RAM_COM6},
	{0, RAM_SEG4,  RAM_COM6},
	{0, RAM_SEG3,  RAM_COM6},
	{0, RAM_SEG2,  RAM_COM6},
	{0, RAM_SEG1,  RAM_COM6},

	{0,RAM_SEG9,   RAM_COM7},//Com5_Led7
	{0,RAM_SEG8,   RAM_COM7},//Com5_Led3
	{0,RAM_SEG6,   RAM_COM7},//Com5_Led6
	{0,RAM_SEG4,   RAM_COM7},//Com5_Led4
	{0,RAM_SEG3,   RAM_COM7},//Com5_Led8
	{0,RAM_SEG2,   RAM_COM7},//Com5_Led1
	{0,RAM_SEG1,   RAM_COM7},//Com5_Led2
	{0,RAM_SEG10,  RAM_COM7},//Com5_Led5
	#else
	{0, RAM_SEG10, RAM_COM3},//1 6
	{0, RAM_SEG9,  RAM_COM3},//2
	{0, RAM_SEG8,  RAM_COM3},//3
	{0, RAM_SEG4,  RAM_COM3},//4
	{0, RAM_SEG3,  RAM_COM3},//8
	{0, RAM_SEG2,  RAM_COM3},//9
	{0, RAM_SEG1,  RAM_COM3},//10

	{0, RAM_SEG10, RAM_COM4},//1 5
	{0, RAM_SEG9,  RAM_COM4},
	{0, RAM_SEG8,  RAM_COM4},
	{0, RAM_SEG4,  RAM_COM4},
	{0, RAM_SEG3,  RAM_COM4},
	{0, RAM_SEG2,  RAM_COM4},
	{0, RAM_SEG1,  RAM_COM4},

	{0, RAM_SEG10, RAM_COM5},//1 4
	{0, RAM_SEG9,  RAM_COM5},
	{0, RAM_SEG8,  RAM_COM5},
	{0, RAM_SEG4,  RAM_COM5},
	{0, RAM_SEG3,  RAM_COM5},
	{0, RAM_SEG2,  RAM_COM5},
	{0, RAM_SEG1,  RAM_COM5},

	{0, RAM_SEG10, RAM_COM6},//1 3
	{0, RAM_SEG9,  RAM_COM6},
	{0, RAM_SEG8,  RAM_COM6},
	{0, RAM_SEG4,  RAM_COM6},
	{0,	RAM_SEG3,  RAM_COM6},
	{0, RAM_SEG2,  RAM_COM6},

	{0, RAM_SEG1,  RAM_COM7},
	{0, RAM_SEG2,  RAM_COM7},
	{0, RAM_SEG3,  RAM_COM7},
	{0, RAM_SEG4,  RAM_COM7},
	{0, RAM_SEG8,  RAM_COM7},
	{0, RAM_SEG9,  RAM_COM7},
	{0, RAM_SEG10, RAM_COM7},
	#endif
};
UCHAR code segNumsPart1[] =
{
    DISP_NUM0_PART1,//0
    DISP_NUM1_PART1,//1
    DISP_NUM2_PART1,//2
    DISP_NUM3_PART1,//3
    DISP_NUM4_PART1,//4
    DISP_NUM5_PART1,//5
    DISP_NUM6_PART1,//6
    DISP_NUM7_PART1,//7
    DISP_NUM8_PART1,//8
    DISP_NUM9_PART1,//9
	
    DISP_PART_NULL,//10
    DISP_CHAR_E_PART1,//11
    DISP_CHAR_H_PART1,//12
    DISP_CHAR_C_PART1,//13
    DISP_CHAR_BAR_PART1,//14
    DISP_CHAR_DOT_PART1,//15
    DISP_CHAR_n_PART1,//16
    DISP_CHAR_N_PART1,//17
    DISP_CHAR_u_PART1,//18
    DISP_CHAR_U_PART1,//19
    DISP_CHAR_d_PART1,//20
    DISP_CHAR_l_PART1,//21
    DISP_CHAR_L_PART1,//22
    DISP_CHAR_ll_PART1,//23
	DISP_CHAR_O_PART1,//24
    DISP_CHAR_P_PART1,//25
	DISP_CHAR_A_PART1,//26
	DISP_CHAR_F_PART1,//27
	DISP_CHAR_h_PART1,//28
	DISP_CHAR_b_PART1,//29
	DISP_CHAR_t_PART1//30
};
/* Variables define --------------------------------------------------------- */
UCHAR_XDATA  Com1_Buf = 0;
UCHAR_XDATA  Com2_Buf = 0;
UCHAR_XDATA  Com3_Buf = 0;
// UCHAR_XDATA  Com4_Buf = 0;
// UCHAR_XDATA  Leds_Buf = 0;
// //*******************************************************************************
void Leds_Flesh(void)
{
	unsigned char i = 0;
//	// if(F_Light10ms != F_Base10ms)
//	// {
//	// 	F_Light10ms = F_Base10ms;
		//Leds_Test();
		//! NEWFORM1 #3-1 从出口附加规则
		#if(0==CONFIG_POWER_TEST)
		F_Led_SelfClean = 0;
		F_Led_Light = 0;
		F_Lack = 0;
		#endif

		Digital_Buf = segNumsPart1[Com1_Buf];
		F_Com1_SegA = LF_SEG_A;
		F_Com1_SegB = LF_SEG_B;
		F_Com1_SegC = LF_SEG_C;
		F_Com1_SegD = LF_SEG_D;
		F_Com1_SegE = LF_SEG_E;
		F_Com1_SegF = LF_SEG_F;
		F_Com1_SegG = LF_SEG_G;

		Digital_Buf = segNumsPart1[Com2_Buf];
		F_Com2_SegA = LF_SEG_A;
		F_Com2_SegB = LF_SEG_B;
		F_Com2_SegC = LF_SEG_C;
		F_Com2_SegD = LF_SEG_D;
		F_Com2_SegE = LF_SEG_E;
		F_Com2_SegF = LF_SEG_F;
		F_Com2_SegG = LF_SEG_G;

		Digital_Buf = segNumsPart1[Com3_Buf];
		F_Com3_SegA = LF_SEG_A;
		F_Com3_SegB = LF_SEG_B;
		F_Com3_SegC = LF_SEG_C;
		F_Com3_SegD = LF_SEG_D;
		F_Com3_SegE = LF_SEG_E;
		F_Com3_SegF = LF_SEG_F;
		F_Com3_SegG = LF_SEG_G;
		

		for(i = 0; i < LED_END; i++)
		{
			if(tLeds[i].value)
			{
				LCDRAM[((UCHAR)tLeds[i].seg)] |= ((UCHAR)tLeds[i].com);
			}
			else
			{
				LCDRAM[((UCHAR)tLeds[i].seg)] &= ~((UCHAR)tLeds[i].com);
			}

//			// if(tLeds[i].value)
//			// {
//			// 	LedRamBuf[((UCHAR)tLeds[i].seg)] |= ((UCHAR)tLeds[i].com);
//			// }
//			// // else
//			// // {
//			// // 	LedRamBuf[((UCHAR)tLeds[i].seg)] &= ~((UCHAR)tLeds[i].com);
//			// // }
		}

//		// for(i = 0; i < 28; i++)
//		// {
//		// 	LedRamBuf[i] = 0x00;
//		// 	LCDRAM[i] = LedRamBuf[i];
//		// 	LedRamBuf[i] = 0;
//		// }

	// }
}
//*******************************************************************************
static void Digital_All_Off(void)
{
	Com1_Buf = Com2_Buf = Com3_Buf = DISP_CHAR_NULL;
	#if NEWTPE1
	F_Lack = F_Wsah = F_Dot1 = F_Dot2 = F_Sterilize = F_Save = F_Lack_Rad = 0;
	#else
	F_Lack = F_Dry = F_Dot1 = F_Dot2 = F_Steam = F_Save = 0;
	#endif
}

static void Digital_All_On(void)
{
	Com1_Buf = Com2_Buf = Com3_Buf = 8;
	#if NEWTPE1
	F_Lack = F_Wsah = F_Dot1 = F_Dot2 = F_Sterilize = F_Save = F_Lack_Rad = 1;
	#else
	F_Lack = F_Dry = F_Dot1 = F_Dot2 = F_Steam = F_Save = 1;
	#endif
}

static void Led_All_Off(void)
{
	#if NEWTPE1
	F_Led_Save = F_Led_Sterilize = F_Led_Srandard = F_Led_SelfClean = F_Led_Start = F_Led_Fast = F_Led_Power = F_Led_Light = 0;
	#else
	F_Led_Fast = F_Led_Srandard = F_Led_Steam = F_Led_Dry = F_Led_Inlet = F_Led_Start = F_Led_Power = 0;
	#endif
}

static void Led_All_On(void)
{
	#if NEWTPE1
	F_Led_Save = F_Led_Sterilize = F_Led_Srandard = F_Led_SelfClean = F_Led_Start = F_Led_Fast = F_Led_Power = F_Led_Light = 1;
	#else
	F_Led_Fast = F_Led_Srandard = F_Led_Steam = F_Led_Dry = F_Led_Inlet = F_Led_Start = F_Led_Power = 1;
	#endif
}

static void Digital_State(void)
{
	static bit buf = 0;

	#if CONFIG_STATE_FLESH
	buf = !F_Blink500ms;//20251110 NEWFORM0 9.3
	#else
	buf = 1;
	#endif

	if(Inlet_Lack)
	{//缺水故障
		F_Lack_Rad = buf;
	}
	else
	{//待机//运行//保管
		F_Lack_Rad = 0;
	}
	if(STAGE_STEAM == Work_CurrentStage)
	{//运行
		F_Sterilize = buf;
	}
	else
	{//待机
		F_Sterilize = 0;
	}
	if(STAGE_DRY == Work_CurrentStage)
	{//运行
		F_Wsah = buf;
	}
	else
	{//待机
		F_Wsah = 0;
	}
	if(STATE_SAVING == Work_CurrentState)
	{//保管
		F_Save = buf;
	}
	else
	{//待机//运行//故障
		F_Save = 0;
	}
//! NEWFORM1 #4-3 待机/运行/保管/故障调用，变更指示灯定义
// #if NEWTPE1
// 	if(Inlet_Lack)
// 	{
// 		F_Lack_Rad = buf;
// 	}
// 	else
// 	{
// 		F_Lack_Rad = 0;
// 	}
// 	#if (CONFIG_IV_ENABLE&&CONFIG_INLET_MODE)
// 	F_Lack = Work_InletMode;
// 	#else
// 	F_Lack = 0;
// 	#endif
// 	//! NEWFORM1 #3-4 屏蔽进水灯
// 	#if CONFIG_DISPLAY_INLET
// 	if(Inlet_IsInLetting)
// 	{//20251110 NEWFORM0 9.1
// 		F_Lack = buf;
// 	}
// 	else
// 	#endif
// 	{//20251110 NEWFORM0 9.2
// 		F_Lack = 0;
// 	}
// 	if((STAGE_MAIN == Work_CurrentStage)||(STAGE_RINSE1 == Work_CurrentStage)||(STAGE_RINSE2 == Work_CurrentStage))
// 	{
// 		F_Wsah = buf;
// 	}
// 	else
// 	{
// 		F_Wsah = 0;
// 	}
// 	if(STAGE_STEAM == Work_CurrentStage)
// 	{
// 		F_Sterilize = buf;
// 	}
// 	else
// 	{
// 		F_Sterilize = 0;
// 	}
// 	if(STAGE_DRY == Work_CurrentStage)
// 	{
// 		F_Save = buf;
// 	}
// 	else if(STATE_SAVING == Work_CurrentState)
// 	{
// 		F_Save = 1;
// 	}
// 	else
// 	{
// 		F_Save = 0;
// 	}
// #else
// 	if(Inlet_Lack)
// 	{
// 		F_Lack = buf;
// 	}
// 	else
// 	{
// 		F_Lack = 0;
// 	}
// 	#if CONFIG_INLET_MODE
// 	F_Led_Inlet = Work_InletMode;
// 	#endif
// 	if(STAGE_STEAM == Work_CurrentStage)
// 	{
// 		F_Steam = buf;
// 	}
// 	else
// 	{
// 		F_Steam = 0;
// 	}
// 	if(STAGE_DRY == Work_CurrentStage)
// 	{
// 		F_Dry = buf;
// 	}
// 	else
// 	{
// 		F_Dry = 0;
// 	}
// 	if(STATE_SAVING == Work_CurrentState)
// 	{
// 		F_Save = buf;
// 	}
// 	else
// 	{
// 		F_Save = 0;
// 	}
// #endif
}

static void Led_Testting(void)
{
	Com1_Buf = Com2_Buf = Com3_Buf = TestKeyCnt%10;
#if NEWTPE1
	//F_Lack = F_Wsah = F_Dot1 = F_Dot2 = F_Sterilize = F_Save = F_Lack_Rad = 1;
	F_Led_Fast = Key_FastMune;
	F_Led_Power = Key_PowerCommand;
	F_Led_Sterilize = Key_SterilizeFunc;
	F_Led_SelfClean = Key_SelfCleanMune;
	F_Led_Light = Key_LightCommand;
	F_Led_Srandard = Key_SrandardMune;
	F_Led_Save = Key_SaveFunc;
	F_Led_Start = Key_StartCommand;
#else
	//F_Lack = F_Dry = F_Dot1 = F_Dot2 = F_Steam = F_Save = 1;
	F_Led_Fast = Key_FastMune;
	F_Led_Srandard = Key_SrandardMune;
	F_Led_Steam = Key_SteamFunc;
	F_Led_Dry = Key_DryFunc;
	F_Led_Inlet = Key_InletCommand;
	F_Led_Start = Key_StartCommand;
	F_Led_Power = Key_PowerCommand;
#endif
}
static void Led_ProgramStandby(void)
{
	//! NEWFORM1 #3-1 屏蔽对应显示
	// #if NEWTPE1
	// Work_InletMode = 0;
	// F_Led_Light = Light_IsWorking;
	// #else
	// Light_IsWorking = 1;
	// F_Led_Inlet = Work_InletMode;
	// #endif
	//! NEWFORM1 #4-3 小时制显示
	// F_Led_Power = 1;
	// F_Led_Start = 0;
	// switch(Work_CurrentMenu)
	// {
	// 	case MENU_FAST:
	// 		F_Led_Fast = 1;
	// 		F_Led_Srandard = 0;
	// 		#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 		#endif
	// 		F_Led_Steam = Work_IsSteamMode;
	// 		F_Led_Dry = Work_IsDryMode;
	// 		break;
	// 	case MENU_STANDARD:
	// 		F_Led_Fast = 0;
	// 		F_Led_Srandard = 1;
	// 		#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 		#endif
	// 		F_Led_Steam = Work_IsSteamMode;
	// 		F_Led_Dry = Work_IsDryMode;
	// 		break;
	// 	#if NEWTPE1
	// 	case MENU_SELFCLEAN:
	// 		F_Led_Fast = F_Led_Srandard = F_Led_Steam = 0;
	// 		#if NEWFORM0
	// 		F_Led_Dry = Work_IsDryMode;
	// 		#else
	// 		F_Led_Dry = 0;
	// 		#endif
	// 		F_Led_SelfClean = 1;
	// 		break;
	// 	#endif
	// 	default://MENU_STEAM/MENU_DRY/MENU_NULL
	// 		F_Led_Fast = 0;
	// 		F_Led_Srandard = 0;
	// 		#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 		#endif
	// 		if((Work_IsSteamMode)||(MENU_STEAM == Work_CurrentMenu))
	// 		{
	// 			F_Led_Steam = 1;
	// 			F_Led_Dry = Work_IsDryMode;
	// 		}
	// 		else if((Work_IsDryMode)||(MENU_DRY == Work_CurrentMenu))
	// 		{
	// 			F_Led_Steam = 0;
	// 			F_Led_Dry = 1;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Steam = F_Led_Dry = 0;//20251110 NEWFORM0 3、
	// 		}
	// 		break;
	// }
}

static void Led_ProgramWork(void)
{
	//! NEWFORM1 #3-1 屏蔽对应显示
	// #if NEWTPE1
	// Work_InletMode = 0;
	// F_Led_Light = Light_IsWorking;
	// #else
	// Light_IsWorking = 1;
	// F_Led_Inlet = Work_InletMode;
	// #endif
	//! NEWFORM1 #4-3 取消运行过熄灭设定
	// F_Led_Power = 1;
	// F_Led_Start = !(Work_IsPaused & F_Blink500ms);
	// if(STATE_WASHING == Work_CurrentState)
	// {
	// 	switch(Work_CurrentMenu)
	// 	{//洗涤结束关机，程序运行过程中，每运行完一个阶段，则相应的按键指示灯熄灭
	// 	case MENU_FAST:
	// 		if(Work_CurrentStage < STAGE_STEAM)
	// 		{
	// 			F_Led_Fast = 1;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Fast = 0;
	// 		}
	// 		F_Led_Srandard = 0;
	// 		#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 		#endif
	// 		if(Work_CurrentStage < STAGE_DRY)
	// 		{
	// 			F_Led_Steam = Work_IsSteamMode;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Steam = 0;
	// 		}
	// 		if(Work_CurrentStage < STAGE_COMPLETE)
	// 		{
	// 			F_Led_Dry = Work_IsDryMode;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Dry = 0;
	// 		}
	// 		break;
	// 	case MENU_STANDARD:
	// 		if(Work_CurrentStage < STAGE_STEAM)
	// 		{
	// 			F_Led_Srandard = 1;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Srandard = 0;
	// 		}
	// 		F_Led_Fast = 0;
	// 		#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 		#endif
	// 		if(Work_CurrentStage < STAGE_DRY)
	// 		{
	// 			F_Led_Steam = Work_IsSteamMode;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Steam = 0;
	// 		}
	// 		if(Work_CurrentStage < STAGE_COMPLETE)
	// 		{
	// 			F_Led_Dry = Work_IsDryMode;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Dry = 0;
	// 		}
	// 		break;
	// 	case MENU_STEAM:
	// 		F_Led_Fast = F_Led_Srandard = 0;
	// 		#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 		#endif
	// 		if(Work_CurrentStage < STAGE_DRY)
	// 		{
	// 			F_Led_Steam = 1;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Steam = 0;
	// 		}
	// 		if(Work_CurrentStage < STAGE_COMPLETE)
	// 		{
	// 			F_Led_Dry = Work_IsDryMode;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Dry = 0;
	// 		}
	// 		break;
	// 	#if NEWTPE1
	// 	case MENU_SELFCLEAN:
	// 		F_Led_Fast = F_Led_Srandard = F_Led_Steam = 0;
	// 		#if NEWFORM0
	// 		if(Work_CurrentStage < STAGE_STEAM)
	// 		{
	// 			F_Led_SelfClean = 1;
	// 		}
	// 		else
	// 		{
	// 			F_Led_SelfClean = 0;
	// 		}
	// 		if(Work_CurrentStage < STAGE_COMPLETE)
	// 		{
	// 			F_Led_Dry = Work_IsDryMode;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Dry = 0;
	// 		}
	// 		#else
	// 		F_Led_Dry = 0;
	// 		F_Led_SelfClean = 1;
	// 		#endif
	// 		break;
	// 	#endif
	// 	case MENU_DRY:
	// 		F_Led_Fast = F_Led_Srandard = F_Led_Steam = 0;
	// 		#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 		#endif
	// 		if(Work_CurrentStage < STAGE_COMPLETE)
	// 		{
	// 			F_Led_Dry = 1;
	// 		}
	// 		else
	// 		{
	// 			F_Led_Dry = 0;
	// 		}
	// 		break;
	// 	default://MENU_NULL
	// 		F_Led_Fast = F_Led_Srandard = F_Led_Steam = F_Led_Dry = 0;
	// 	#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 	#endif
	// 		break;
	// 	}
	// }
	// else 
	// {
	// 	F_Led_Fast = F_Led_Srandard = F_Led_Steam = 0;
	// 	if(STATE_SAVING == Work_CurrentState)
	// 	{
	// 		F_Led_Dry = 1;//保管键常亮
	// 	}
	// 	else
	// 	{
	// 		F_Led_Dry = 0;
	// 	}
	// 	#if NEWTPE1
	// 		F_Led_SelfClean = 0;
	// 	#endif
	// }
}

static void Led_Power_Off(void)
{
	Digital_All_Off();
	Led_All_Off();
	F_Led_Power = 1;
	//! NEWFORM1 #3-4 屏蔽半亮
	// if(!(IOHCON0|IOHCON1))
	// {
	// 	Light_SetBrightness(3);//IOHCON0 = 0xC0;IOHCON1 = 0x00;
	// }
}

static void Led_Power_On(void)
{
	//! NEWFORM1 #3-4 屏蔽半亮
	// if(IOHCON0|IOHCON1)
	// {
	// 	IOHCON0 = 0x00;
	// 	IOHCON1 = 0x00;
	// }
}

static void Digital_Null(void)
{
	F_Lack = F_Wsah = F_Sterilize = F_Save = 0;
	//! NEWFORM1 #4-3 缺水与开门故障需要显示阶段
	#if NEWTPE1
	F_Lack_Rad = Inlet_Lack;
	#endif
}

const FunctionPt xdata LED_List[] = 
{
	Digital_All_Off,		//	0
	Digital_All_On,			//	1
	Led_All_Off,			//	2
	Led_All_On,				//	3
	Digital_State,			//	4
	Led_Testting,			//	5
	Led_ProgramStandby,		//	6
	Led_ProgramWork,		//	7
	Led_Power_Off,			//	8
	Led_Power_On,			//	9
	Digital_Null,			//	10
};

void	Trant_LED_Index(UCHAR_XDATA LED_Func_Index)
{
	(*LED_List[LED_Func_Index])();
}

void Dot_Set(bit value)
{
	F_Dot1 = F_Dot2 = value;
}

//// static void Leds_Test(void)
//// {
//// 	Com1_Buf = Com2_Buf = Com3_Buf = DISP_CHAR_NULL;
//// #if NEWTPE1
//// 	F_Lack = F_Wsah = F_Dot1 = F_Dot2 = F_Sterilize = F_Save = F_Lack_Rad = 0;
//// 	F_Led_Fast = F_Led_Srandard = F_Led_Sterilize = F_Led_SelfClean = F_Led_Start = F_Led_Power = F_Led_Light = 0;
//// 	if(KEY_FAST)
//// 	{
//// 		F_Led_Fast = 1;
//// 	}
//// 	if(KEY_POWER)
//// 	{
//// 		F_Led_Power = 1;
//// 	}
//// 	if(KEY_STERILIZE)
//// 	{
//// 		F_Led_Sterilize = 1;
//// 	}
//// 	if(KEY_SELFCLEAN)
//// 	{
//// 		F_Led_SelfClean = 1;
//// 	}
//// 	if(KEY_LIGHT)
//// 	{
//// 		F_Led_Light = 1;
//// 	}	
//// 	if(KEY_STANDARD)
//// 	{
//// 		F_Led_Srandard = 1;
//// 	}
//// 	if(KEY_SAVE)
//// 	{
//// 		F_Led_Save = 1;
//// 	}
//// 	if(KEY_START)
//// 	{
//// 		F_Led_Start = 1;
//// 	}
//// #else
//// 	F_Lack = F_Dry = F_Dot1 = F_Dot2 = F_Steam = F_Save = 0;
//// 	F_Led_Fast = F_Led_Srandard = F_Led_Steam = F_Led_Dry = F_Led_Inlet = F_Led_Start = F_Led_Power = 0;
//// 	if(KEY_FAST)
//// 	{
//// 		F_Led_Fast = 1;
//// 	}

//// 	if(KEY_STANDARD)
//// 	{
//// 		F_Led_Srandard = 1;
//// 	}

//// 	if(KEY_STEAM)
//// 	{
//// 		F_Led_Steam = 1;
//// 	}

//// 	if(KEY_DRY)
//// 	{
//// 		F_Led_Dry = 1;
//// 	}

//// 	if(KEY_INLET)
//// 	{
//// 		F_Led_Inlet = 1;
//// 	}

//// 	if(KEY_START)
//// 	{
//// 		F_Led_Start = 1;
//// 	}

//// 	if(KEY_POWER)
//// 	{
//// 		F_Led_Power = 1;
//// 	}
//// #endif
//// }
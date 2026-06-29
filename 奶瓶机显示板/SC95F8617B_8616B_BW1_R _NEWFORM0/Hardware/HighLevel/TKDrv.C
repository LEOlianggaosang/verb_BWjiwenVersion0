//************************************************************
//  Copyright (c) 深圳市赛元微电子有限公司
//	文件名称	: TKDrv.c （请参考触控库文件手册操作）
//	作者		: 
//	模块功能	: TouchKey 
//	局部函数列表:
//  最后更正日期:2025.4.29
// 	版本		: V1.0 8616b奶瓶机显示板
//***************************************************
#include "TKDrv.H"
unsigned long int xdata exKeyValueFlag = 0;   				//触控按键状态值
UCHAR xdata exKeyValue = 0;   							//由触控按键状态值所转换//按键值
/**************************************************
*函数名称：TK_Scan(void)
*函数功能：TK扫描
*入口参数：void	 
*出口参数：BOOL
*功能说明：请参考触控库使用手册进行操作
**************************************************/
void TK_Scan(void)
{
	#if CONFIG_TK_T2
	if(SOCAPI_TouchKeyStatus & 0x40)	//重要步骤1:  若按键个数大于 8 个，主程序通过查看全局变量 SOCAPI_ToucKeyStatus&0x40 来判定半轮触控按 键扫描是否完成
	{
		SOCAPI_TouchKeyStatus &= ~ (0x40);	//重要步骤3: 清除标志位， 需要外部清除。
		TouchKeyRestart();
	}
	else
	#endif
	if(SOCAPI_TouchKeyStatus & 0x80)	//重要步骤2:  触摸键扫描一轮标志，是否调用TouchKeyScan()一定要根据此标志位置起后
	{//扫描完成
		exKeyValueFlag = TouchKeyScan();
		exKeyValue = TK_Value(exKeyValueFlag);  		//键值转换
		SOCAPI_TouchKeyStatus &= ~ (0x80);	//重要步骤3: 清除标志位， 需要外部清除。
		TouchKeyRestart();
		#if	CONFIG_TK_NG_DEBUG
		if(exKeyValueFlag != NGKeyValueFlag)
		{
			NGKeyValueFlag = exKeyValueFlag;
			NGKeyValueRead();
		}
		#endif
		exKeyValueFlag = 0;
	}
}
/**************************************************
*函数名称：void TK_value(void)
*函数功能：键值转换函数
*入口参数：void	 
*出口参数：UCHAR
*功能说明：请参考触控库使用手册进行操作
**************************************************/
UCHAR TK_Value(unsigned long int Flag)
{
	UCHAR xdata Value = 0;
	switch (Flag)
	{
		#ifdef SC95F8616B_ENABLED
		#if NEWTPE1
		case KEY1CHANNAL22: Value=1; break;			//0x00400000//FAST_KEY
		case KEY2CHANNAL23: Value=2; break;			//0x00800000//POWER_KEY
		case KEY3CHANNAL18: Value=3; break;			//0x00040000//STERILIZE_KEY
		case KEY4CHANNAL21: Value=4; break;			//0x00200000//SELFCLEAN_KEY
		case KEY5CHANNAL15: Value=5; break;			//0x00008000//LIGHT_KEY
		case KEY6CHANNAL20: Value=6; break;			//0x00100000//STANDARD_KEY
		case KEY7CHANNAL16: Value=7; break;			//0x00010000//SAVE_KEY
		case KEY8CHANNAL17: Value=8; break;			//0x00020000//START_KEY
		case (KEY2CHANNAL23|KEY8CHANNAL17): Value=28; break;//TEST_KEY(POWER_KEY+START_KEY)
		case (KEY1CHANNAL22|KEY6CHANNAL20): Value=16; break;//VER_KEY(FAST_KEY+STANDARD_KEY)
		default: Value = 0; break;
		#else
		case KEY1CHANNAL24: Value=1; break;			//0x01000000//FAST_KEY
		case KEY2CHANNAL23: Value=2; break;			//0x00800000//STANDARD_KEY
		case KEY3CHANNAL22: Value=3; break;			//0x00400000//STEAM_KEY
		case KEY4CHANNAL20: Value=4; break;			//0x00100000//DRY_KEY
		case KEY5CHANNAL18: Value=5; break;			//0x00040000//INLET_KEY
		case KEY6CHANNAL16: Value=6; break;			//0x00010000//START_KEY
		case KEY7CHANNAL15: Value=7; break;			//0x00008000//POWER_KEY
		case (KEY6CHANNAL16|KEY7CHANNAL15): Value=67; break;//TEST_KEY(START_KEY+POWER_KEY)
		case (KEY1CHANNAL24|KEY2CHANNAL23): Value=12; break;//VER_KEY(FAST_KEY+STANDARD_KEY)
		default: Value = 0; break;
		#endif
		#endif
	}
	return Value;
}

#if	CONFIG_TK_NG_DEBUG
static void NGKeyValueRead(void)
{
	UCHAR xdata i = 0;
	NGKeyValue = 0;
	if(NGKeyValueFlag)
	{
		for (i = 0; i < 27; i++)
		{
			if((NGKeyValueFlag >> i) & 0x00000001)
			{
				NGKeyValue += i;
			}
		}
	}
	else
	{
		NGKeyValue = 999;
	}
}
#endif

void Init_TK(void)
{	 
	TouchKeyInit();
}
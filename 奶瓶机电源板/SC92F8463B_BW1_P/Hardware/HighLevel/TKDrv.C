//************************************************************
//  Copyright (c) 深圳市赛元微电子有限公司
//	文件名称	: TKDrv.c （请参考触控库文件手册操作）
//	作者		: 
//	模块功能	: TouchKey 
//	局部函数列表:
//  最后更正日期:
// 	版本		: V1.0
//***************************************************
#include "TKDrv.H"

UCHAR xdata exKeyValue = 0;   							//由触控按键状态值所转换//按键值
unsigned long int xdata exKeyValueFlag = 0;   				//触控按键状态值
#if	CONFIG_TK_NG_DEBUG
unsigned long	int xdata NGKeyValueFlag = 0;  
unsigned int xdata NGKeyValue = 0;  
static void NGKeyValueRead(void);
#endif

/**************************************************
*函数名称：TK_Scan(void)
*函数功能：TK扫描
*入口参数：void	 
*出口参数：BOOL
*功能说明：请参考触控库使用手册进行操作
**************************************************/
void TK_Scan(void)
{
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
#ifdef SC92F8545_ENABLED
					case TK1CHANNAL30: Value=1; break;			//TK1channal30
					case TK2CHANNAL29: Value=2; break;			//TK2channal29
					case TK3CHANNAL28: Value=3; break;			//TK3channal28
					case TK4CHANNAL27: Value=4; break;			//TK4channal27
					case TK5CHANNAL26: Value=5; break;			//TK5channal26
					case TK6CHANNAL25: Value=6; break;			//TK6channal25
					case TK7CHANNAL23: Value=7; break;			//TK7channal23
					case (TK4CHANNAL27|TK5CHANNAL26): Value=54; break;
					case (TK4CHANNAL27|TK7CHANNAL23): Value=47; break;
					case (TK2CHANNAL29|TK3CHANNAL28): Value=23; break;
					default: Value = 0; break;
#endif
#ifdef SC95F8575_ENABLED
					case TK1CHANNAL16: Value=1; break;			//TK1channal16
					case TK2CHANNAL15: Value=2; break;			//TK2channal15
					case TK3CHANNAL14: Value=3; break;			//TK3channal14
					case TK4CHANNAL13: Value=4; break;			//TK4channal13
					case TK5CHANNAL12: Value=5; break;			//TK5channal13
					case TK6CHANNAL11: Value=6; break;			//TK6channal11
					case TK7CHANNAL10: Value=7; break;			//TK7channal10
					case (TK4CHANNAL13|TK5CHANNAL12): Value=54; break;
					case (TK4CHANNAL13|TK7CHANNAL10): Value=47; break;
					case (TK2CHANNAL15|TK3CHANNAL14): Value=23; break;
					case (TK1CHANNAL16|TK7CHANNAL10): Value=17; break;
					default: Value = 0; break;
#endif	
#ifdef SC95F8675_ENABLED
					case TK1CHANNAL16: Value=1; break;			//TK1channal16
					case TK2CHANNAL15: Value=2; break;			//TK2channal15
					case TK3CHANNAL14: Value=3; break;			//TK3channal14
					case TK4CHANNAL13: Value=4; break;			//TK4channal13
					case TK5CHANNAL12: Value=5; break;			//TK5channal13
					case TK6CHANNAL11: Value=6; break;			//TK6channal11
					case TK7CHANNAL10: Value=7; break;			//TK7channal10
					case (TK4CHANNAL13|TK5CHANNAL12): Value=54; break;
					case (TK4CHANNAL13|TK7CHANNAL10): Value=47; break;
					case (TK2CHANNAL15|TK3CHANNAL14): Value=23; break;
					case (TK1CHANNAL16|TK7CHANNAL10): Value=17; break;
					default: Value = 0; break;
#endif	
				}
	return Value;
}

void TK_Init(void)
{	 
	TouchKeyInit();
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
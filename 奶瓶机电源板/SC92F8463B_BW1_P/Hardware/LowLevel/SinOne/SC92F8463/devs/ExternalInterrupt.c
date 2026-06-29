/**
 *******************************************************************************
 * Copyright (c) 20240607
 *  
 * @file    ExternalInterrupt.c
 * @author  lianggaosang@qq.com
 * @brief
 *******************************************************************************
 */
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#ifdef SC92F8463B_ENABLED
#include "SC92F846XB_C.H"
#endif
#include "ExternalInterrupt.h"


static volatile Intc_InitTypeDef intp[INT_ENUM_END];
//intc_callback intc_func;
static void INT0_Init( Intc_InitTypeDef* intc ); 
static void INT1_Init( Intc_InitTypeDef* intc );
static void INT2_Init( Intc_InitTypeDef* intc );

static void INT0_Start( void );
static void INT1_Start( void );
static void INT2_Start( void );

static void INT0_Stop( void );
static void INT1_Stop( void );
static void INT2_Stop( void );


/**
**-----------------------------------------------------------------------------
 * @brief 外部中断功能模块初始化
 * 兼容多个中断源
 * 
 * @param 无
 * @return 无
 *
**-----------------------------------------------------------------------------
*/

void Intc_Init(Intc_InitTypeDef*	intc)
{

	if (intc == NULL)
	{
		return;
	}

	intp[intc->name].name = intc->name;
	intp[intc->name].num = intc->num;
	intp[intc->name].fall = intc->fall;
	intp[intc->name].rise = intc->rise;
	intp[intc->name].priority = intc->priority;
	intp[intc->name].func = NULL;

	switch(intc->name)
	{
		case INT0:
			INT0_Init(intc);
			break;
		case INT1:
			INT1_Init(intc);
			break;
		case INT2:
			INT2_Init(intc);
			break;		
		default:
			break;
	}
}
///**
// * @brief 外部中断功能模块初始化
// * 不需显示的调用高函数.
// * 
// * @param 无
// * @return 无
// */
// 
//void INTP_Init( void )
//{
//	P0CON &= 0X7F;
//	P0PH  &= ~0x80;

//	INT0F = 0;
//	INT1F = 0;
//	
//	INT0R |= 0X80;
//	INT1R = 0;

//	//LOW PRIORITY
//	IPINT0 = 0;
//	
//	EINT0 = 1;
//	
//}


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts the ExternalInterrupt.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Intc_Start(eIntName intc)
{
	switch(intc)
	{
		case INT0:
			INT0_Start();
			break;
		case INT1:
			INT1_Start();
			break;
		case INT2:
			INT2_Start();
			break;
		default:
			break;

	}
}
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops the ExternalInterrupt.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Intc_Stop(eIntName intc)
{
	switch(intc)
	{
		case INT0:
			INT0_Stop();
			break;
		case INT1:
			INT1_Stop();
			break;
		case INT2:
			INT2_Stop();
			break;
		default:
			break;

	}
}
/**
 * @brief 外部中断函数指针回调函数
 * 
 * @param 无
 * @return 无
 */
void Intc_Set_Callback(eIntName intc, intc_callback func)
{
	intp[intc].func = func;
}
//void Intc_Set_Callback(intc_callback func)
//{
//	intc_func = func;
//}

static void INT0_Init( Intc_InitTypeDef* intc )
{
	if (NULL == intc)
	{
		return;
	}
	
	INT0F |= ((intc->fall)<<(intc->num));
	INT0R |= ((intc->rise)<<(intc->num));
	
	EINT0	=	DISABLE;
	if(intc->priority)
	{
		IPINT0	= ENABLE;
	}
	else
	{
		IPINT0	= DISABLE;
	}
}

static void INT1_Init( Intc_InitTypeDef* intc )
{
	if (NULL == intc)
	{
		return;
	}
	
	INT1F |= ((intc->fall)<<(intc->num));
	INT1R |= ((intc->rise)<<(intc->num));
	
	EINT1	=	DISABLE;
	if(intc->priority)
	{
		IPINT1	= ENABLE;
	}
	else
	{
		IPINT1	= DISABLE;
	}
}

static void INT2_Init( Intc_InitTypeDef* intc )
{
	if (NULL == intc)
	{
		return;
	}
	
	INT2F |= ((intc->fall)<<(intc->num));
	INT2R |= ((intc->rise)<<(intc->num));
	
	IE1	&=	~(0x08);
	if(intc->priority)
	{
		IP1	|= 0x08;
	}
	else
	{
		IP1	&=	~(0x08);
	}
}

static void INT0_Start( void )
{
	EINT0	=	ENABLE;
}
static void INT1_Start( void )
{
	EINT1	=	ENABLE;
}
static void INT2_Start( void )
{
	IE1	|= 0x08;
}

static void INT0_Stop( void )
{
	EINT0	=	DISABLE;
}
static void INT1_Stop( void )
{
	EINT1	=	DISABLE;
}
static void INT2_Stop( void )
{
	IE1	&=	~(0x08);
}

/**
 * @brief 外部中断向量
 * 
 * @param 无
 * @return 无
 */
void EX0() interrupt	0
{
	(*intp[INT0].func)();
}

void EX1() interrupt	2
{
	(*intp[INT1].func)();
}

void EX2() interrupt	10
{
	(*intp[INT2].func)();
}

//void EX0() interrupt	0
//{
//	(*intc_func)();
//}


// void EX_Init(void);
// uchar INT1_flag = 0x00;
// /*****************************************************
// *函数名称：void EXTI_Test(void)
// *函数功能：外部中断测试
// *入口参数：void
// *出口参数：void
// *****************************************************/
// void EXTI_Test(void)
// {
// 	EX_Init();
// 	while(1)
// 	{					
// 	}
// }
// /*****************************************************
// *函数名称：void EX_Init(void)
// *函数功能：外部中断初始化
// *入口参数：void
// *出口参数：void
// *****************************************************/
// void EX_Init(void)
// {	
// 	//配置中断口INT03、INT12/13、INT24/25
// 	P1CON &= 0X37;     //中断IO口设置为高阻输入
// 	P1PH  |= 0xC8;     //中断IO口设置为高阻带上拉
// 	P2CON &= 0XFC;     //中断IO口设置为高阻输入
// 	P2PH  |= 0x03;     //中断IO口设置为高阻带上拉
 
// 	//配置INT03上升沿中断、INT12/13下降沿中断、INT24/25双沿中断
//     //下降沿设置	
// 	INT0F = 0X00 ;    //xxxx 0000  0关闭 1使能
// 	INT1F = 0X0C ;    //xxxx xxxx  0关闭 1使能
//     INT2F = 0X30 ;    //0000 xxxx  0关闭 1使能
//     //上升沿设置	
// 	INT0R = 0X08 ;    //xxxx 0000  0关闭 1使能 
// 	INT1R = 0X00 ;    //xxxx xxxx  0关闭 1使能
// 	INT2R = 0X30 ;    //0000 xxxx  0关闭 1使能	
	
// 	//外部中断优先级设置
// 	IE  |= 0x05;	//0000 0x0x
// 	IE1 |= 0x08;	//0000 x000  INT2使能
// 	IP  |= 0X00;
// 	IP1 |= 0X00;
// 	EA = 1;
// }

// /*****************************************************
// *函数名称：void EX0/1/2() interrupt	0/2/10
// *函数功能：外部中断函数
// *入口参数：void
// *出口参数：void
// *****************************************************/
// void EX0() interrupt	0
// {
//     P24 = ~P24;
// }

// void EX1() interrupt	2
// {
//     P25= ~P25;
// 	if(P16 == 0)
// 	{
// 		INT1_flag = 0x10; //INT12产生中断
// 	}
// 	if(P17 == 0)
// 	{
// 		INT1_flag = 0x20; //INT13产生中断
// 	}
// }

// void EX2() interrupt	10
// {
//     P26 = ~P26;
// }


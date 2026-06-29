/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    Timer.c
 * @author  lianggaosang@qq.com
 * @brief   计时器模块驱动
 *
 *******************************************************************************
 */
 
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#ifdef SC92F8463B_ENABLED
#include "H/SC92F846XB_C.H"
#endif
#include "Timer.h"

static volatile Timer_InitTypeDef timers[TIMER_ENUM_END];

static void TM0_Init( Timer_InitTypeDef* tim ); 
static void TM1_Init( Timer_InitTypeDef* tim );
#ifdef SC92F8463B_ENABLED
static void TM2_Init( Timer_InitTypeDef* tim );
#endif

static void TM0_Start( void );
static void TM1_Start( void );
#ifdef SC92F8463B_ENABLED
static void TM2_Start( void );
#endif

static void TM0_Stop( void );
static void TM1_Stop( void );
#ifdef SC92F8463B_ENABLED
static void TM2_Stop( void );
#endif
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function configures the timer.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Timer_Init( Timer_InitTypeDef* tim )
{

	if (NULL == tim)
	{
		return;
	}

	timers[tim->name].name = tim->name;
	timers[tim->name].tmod = tim->tmod;
	timers[tim->name].count = tim->count;
	timers[tim->name].tmcon = tim->tmcon;
	timers[tim->name].priority = tim->priority;
	timers[tim->name].func = NULL;

	switch(tim->name)
	{
		case TIMER0:
			TM0_Init(tim);
			break;
		case TIMER1:
			TM1_Init(tim);
			break;
#ifdef SC92F8463B_ENABLED
		case TIMER2:
			TM2_Init(tim);
			break;
#endif		
		default:
			break;

	}

}
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts the timer.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Timer_Start(eName tim)
{
	switch(tim)
	{
		case TIMER0:
			TM0_Start();
			break;
		case TIMER1:
			TM1_Start();
			break;
#ifdef SC92F8463B_ENABLED
		case TIMER2:
			TM2_Start();
			break;
#endif		
		default:
			break;

	}
}
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops the timer.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Timer_Stop(eName tim)
{
	switch(tim)
	{
		case TIMER0:
			TM0_Stop();
			break;
		case TIMER1:
			TM1_Stop();
			break;
#ifdef SC92F8463B_ENABLED
		case TIMER2:
			TM2_Stop();
			break;		
#endif		
		default:
			break;

	}
}
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function set callback function of timer.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void Timer_Set_Callback(eName tim, timer_callback func)
{
	timers[tim].func = func;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function inits TM0.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
static void TM0_Init(Timer_InitTypeDef* tim)
{
	if (NULL == tim)
	{
		return;
	}

	/* 选择选择时钟*/
	TMCON |= tim->tmcon;

	/* 设置工作方式 */
	TMOD |= tim->tmod; 

	/* 溢出时间 */
	TL0 = (65536 - tim->count)%256;
	TH0 = (65536 - tim->count)/256;

	/* 优先级   */
	IP |= tim->priority;
	
	ET0 = DISABLE;//关闭定时器0中断
	TR0 = DISABLE;//禁止定时器0计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts TM0 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM0_Start( void )
{
	ET0 = ENABLE;//容许定时器0中断
	TR0 = ENABLE;//打开定时器0计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops TM0 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM0_Stop( void )
{
	ET0 = DISABLE;//关闭定时器0中断
	TR0 = DISABLE;//禁止定时器0计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		Timer interrupt
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/


void timer0() interrupt 1
{
	TL0 = (65536 - timers[TIMER0].count)%256;
	TH0 = (65536 - timers[TIMER0].count)/256;

		(*timers[TIMER0].func)();

}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function inits TM1.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
static void TM1_Init(Timer_InitTypeDef* tim)
{
	if (NULL == tim)
	{
		return;
	}

	/* 选择选择时钟*/
  TMCON |= tim->tmcon;

	/* 设置工作方式 */
	TMOD |= tim->tmod; 

	/* 溢出时间 */
	TL1 = (65536 - tim->count)%256;
	TH1 = (65536 - tim->count)/256;

	/* 优先级   */
  IP |= tim->priority;
	
	ET1 = DISABLE;//关闭定时器1中断
	TR1 = DISABLE;//禁止定时器1计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts TM1 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM1_Start( void )
{
	ET1 = ENABLE;//容许定时器1中断
	TR1 = ENABLE;//打开定时器1计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops TM1 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM1_Stop( void )
{
	ET1 = DISABLE;//关闭定时器1中断
	TR1 = DISABLE;//禁止定时器1计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		Timer interrupt
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void timer1() interrupt 3
{
	TL1 = (65536 - timers[TIMER1].count)%256;
	TH1 = (65536 - timers[TIMER1].count)/256;
	
		(*timers[TIMER1].func)();
}

#ifdef SC92F8463B_ENABLED
static void TM2_Init(Timer_InitTypeDef* tim)
{
	if (NULL == tim)
	{
		return;
	}

	/* 选择选择时钟*/
  TMCON |= tim->tmcon;

	/* 设置工作方式 */
	T2MOD |= tim->tmod; 
	//T2CON = 0X00;

	/* 溢出时间 */
	TL2 = RCAP2L = (65536 - tim->count)%256;
	TH2 = RCAP2H = (65536 - tim->count)/256;

	/* 优先级   */
  IP |= tim->priority;
	
	ET2 = DISABLE;//关闭定时器2中断
	TR2 = DISABLE;//禁止定时器2计数
}
//	//Timer2捕获功能
//	T2CON = 0X09; //使能EXT2，16位捕获模式
//	T2MOD = 0X00;
//	TH2 = 0X00;
//	TL2 = 0X00;
//	RCAP2H = 0X00;
//	RCAP2L = 0X00;
//	TR2 = 0;
//	ET2 = 1;//定时器2允许
//	TR2 = 1;//打开定时器2	
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts TM2 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM2_Start( void )
{
	ET2 = ENABLE;//容许定时器2中断
	TR2 = ENABLE;//打开定时器2计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops TM2 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM2_Stop( void )
{
	ET2 = DISABLE;//关闭定时器2中断
	TR2 = DISABLE;//禁止定时器2计数
}
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		Timer interrupt
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void timer2() interrupt 5
{
	(*timers[TIMER2].func)();	
}
#endif

///*****************************************************
//*函数名称：void Timer_Init(void)
//*函数功能：T0/T1/T2初始化
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void Timer_Init(void)
//{ 
//	TMCON = 0X07;    //------111 ;Timer0、Tiemr1和Tiemr2选择时钟Fsys
//	
//	//T0设置
//	TMOD |= 0x01;                 //0000 0001;Timer0设置工作方式1
//	TL0 = (65536 - 24000)%256;    //溢出时间：时钟为Fsys，则24000*（1/Fsys）=2ms;
//	TH0 = (65536 - 24000)/256;
//	TR0 = 0;
//	ET0 = 1;//定时器0允许
//	TR0 = 1;//打开定时器0
//	//T1设置
//	TMOD |= 0x20;            //0010 0000;Timer1设置工作方式2
//	TL1 = 256 - 240;   //溢出时间：时钟为Fsys，则240*（1/Fsys）=20us;
//	TH1 = 256 - 240;
//	TR1 = 0;
//	ET1 = 1;//定时器1允许
//	TR1 = 1;//打开定时器1
//	//T2设置
//	T2MOD = 0x00;
//	T2CON = 0x00;	 //设置为16位重载寄存器
//	RCAP2H = (65536-48000)/256;     //溢出时间：时钟为Fsys，则48000*（1/Fsys）=4ms;
//	RCAP2L = (65536-48000)%256;
//	TR2 = 0;
//	ET2 = 1;//定时器2允许
//	TR2 = 1;//打开定时器2		
//	/*
//	//Timer2捕获功能
//	T2CON = 0X09; //使能EXT2，16位捕获模式
//	T2MOD = 0X00;
//	TH2 = 0X00;
//	TL2 = 0X00;
//	RCAP2H = 0X00;
//	RCAP2L = 0X00;
//	TR2 = 0;
//	ET2 = 1;//定时器2允许
//	TR2 = 1;//打开定时器2	
//	*/
//	
//	EA = 1;	
//}
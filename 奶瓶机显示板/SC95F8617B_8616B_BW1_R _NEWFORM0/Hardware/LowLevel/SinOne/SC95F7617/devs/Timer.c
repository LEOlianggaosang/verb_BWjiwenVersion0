/**
 *******************************************************************************
 * Copyright (c) 2025.5.26
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
#ifdef SC95F8617_ENABLED
#include "..\SC95F861x_C.H"
#endif
#ifdef SC95F8616B_ENABLED
#include "..\SC95F861xB_C.H"
#endif
#include "Timer.h"

static volatile Timer_InitTypeDef xdata timers[TIMER_ENUM_END];

static void TM0_Init( Timer_InitTypeDef* tim ); 
static void TM1_Init( Timer_InitTypeDef* tim );
static void TM2_Init( Timer_InitTypeDef* tim );
static void TM3_Init( Timer_InitTypeDef* tim );
static void TM4_Init( Timer_InitTypeDef* tim );

static void TM0_Start( void );
static void TM1_Start( void );
static void TM2_Start( void );
static void TM3_Start( void );
static void TM4_Start( void );

static void TM0_Stop( void );
static void TM1_Stop( void );
static void TM2_Stop( void );
static void TM3_Stop( void );
static void TM4_Stop( void );

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

	if (tim == NULL)
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
		case TIMER2:
			TM2_Init(tim);
			break;
		case TIMER3:
			TM3_Init(tim);
			break;
		case TIMER4:
			TM4_Init(tim);
			break;											
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
		case TIMER2:
			TM2_Start();
			break;
		case TIMER3:
			TM3_Start();
			break;
		case TIMER4:
			TM4_Start();
			break;											
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
		case TIMER2:
			TM2_Stop();
			break;
		case TIMER3:
			TM3_Stop();
			break;
		case TIMER4:
			TM4_Stop();
			break;											
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
	if (tim == NULL)
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
	if (tim == NULL)
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

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function inits TM2.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
static void TM2_Init(Timer_InitTypeDef* tim)
{
	if (tim == NULL)
	{
		return;
	}

	TXINX = TIMER2_REGISTER_POINT_MASK;

	/* 选择选择时钟*/
  TXCON |= tim->tmcon;

	/* 设置工作方式 */
	TXMOD |= tim->tmod; 

	/* 溢出时间 */
	RCAPXL = (65536 - tim->count)%256;
	RCAPXH = (65536 - tim->count)/256;

	/* 优先级   */
  IP |= tim->priority;
	
	ET2 = DISABLE;//关闭定时器2中断
	TRX = DISABLE;//禁止定时器2计数
}
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
	TXINX = TIMER2_REGISTER_POINT_MASK;
	ET2 = ENABLE;//容许定时器2中断
	TRX = ENABLE;//打开定时器2计数
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
	TXINX = TIMER2_REGISTER_POINT_MASK;
	ET2 = DISABLE;//关闭定时器2中断
	TRX = DISABLE;//禁止定时器2计数
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
  TXINX = TIMER2_REGISTER_POINT_MASK;
  TFX = 0;	

}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function inits TM3.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
static void TM3_Init(Timer_InitTypeDef* tim)
{
	if (tim == NULL)
	{
		return;
	}

	TXINX = TIMER3_REGISTER_POINT_MASK;

	/* 选择选择时钟*/
  TXCON |= tim->tmcon;

	/* 设置工作方式 */
	TXMOD |= tim->tmod; 

	/* 溢出时间 */
	RCAPXL = (65536 - tim->count)%256;
	RCAPXH = (65536 - tim->count)/256;

	/* 优先级   */
  IP1 |= tim->priority;
	
	IE1 &= (~TIMER3_INTERRUPT_ENABLE);//关闭定时器3中断
	TRX = DISABLE;//禁止定时器3计数
}

void TM3_Reload(unsigned int count)
{
	TXINX = TIMER3_REGISTER_POINT_MASK;
	RCAPXL = (65536 - count)%256;
	RCAPXH = (65536 - count)/256;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts TM3 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM3_Start( void )
{
	TXINX = TIMER3_REGISTER_POINT_MASK;
	IE1 |= (TIMER3_INTERRUPT_ENABLE);//容许定时器3中断
	TRX = ENABLE;//打开定时器3计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops TM3 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM3_Stop( void )
{
	TXINX = TIMER3_REGISTER_POINT_MASK;
	IE1 &= (~TIMER3_INTERRUPT_ENABLE);//关闭定时器3中断
	TRX = DISABLE;//禁止定时器3计数
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
void timer3() interrupt 13
{
	TXINX = TIMER3_REGISTER_POINT_MASK;
	TFX = 0;	
	(*timers[TIMER3].func)();
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function inits TM4.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
static void TM4_Init(Timer_InitTypeDef* tim)
{
	if (tim == NULL)
	{
		return;
	}

	TXINX = TIMER4_REGISTER_POINT_MASK;

	/* 选择选择时钟*/
  TXCON |= tim->tmcon;

	/* 设置工作方式 */
	TXMOD |= tim->tmod; 

	/* 溢出时间 */
	RCAPXL = (65536 - tim->count)%256;
	RCAPXH = (65536 - tim->count)/256;

	/* 优先级   */
  IP1 |= tim->priority;
	
	IE1 &= (~TIMER4_INTERRUPT_ENABLE);//关闭定时器4中断
	TRX = DISABLE;//禁止定时器4计数
}
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function starts TM4 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM4_Start( void )
{
	TXINX = TIMER4_REGISTER_POINT_MASK;
	IE1 |= (TIMER4_INTERRUPT_ENABLE);//容许定时器4中断
	TRX = ENABLE;//打开定时器4计数
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function stops TM4 counter.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void TM4_Stop( void )
{
	TXINX = TIMER4_REGISTER_POINT_MASK;
	IE1 &= (~TIMER4_INTERRUPT_ENABLE);//关闭定时器4中断
	TRX = DISABLE;//禁止定时器4计数
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
void timer4() interrupt 14
{
  TXINX = TIMER4_REGISTER_POINT_MASK;
	TFX = 0;	
}

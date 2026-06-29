/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    Timer.h
 * @author  lianggaosang@qq.com
 * @brief   计时器模块驱动
 *
 *******************************************************************************
 */
 
#ifndef _TIMER_H_
#define _TIMER_H_

#ifndef NULL
#define NULL    0
#endif

#define ENABLE  1
#define DISABLE 0

typedef void (* timer_callback)(void);

typedef enum 
{
    TIMER0 = 0,
    TIMER1 = 1,
#ifdef SC92F8463B_ENABLED
    TIMER2 = 2,
#endif
    TIMER_ENUM_END
}eName;

//TMCON
#define TIMER0_INPUT_FSYS_DIVIDE_12  0X00
#define TIMER0_INPUT_FSYS            0X01
#define TIMER1_INPUT_FSYS_DIVIDE_12  0X00
#define TIMER1_INPUT_FSYS            0X02
#define TIMER2_INPUT_FSYS_DIVIDE_12  0X00
#define TIMER2_INPUT_FSYS            0X04

//TMOD
#define TIMER0_MODE_0                0X00
#define TIMER0_MODE_1                0X01
#define TIMER0_MODE_2                0X02
#define TIMER0_MODE_3                0X03
#define TIMER0_CNT_EX                0X04

#define TIMER1_MODE_0                0X00
#define TIMER1_MODE_1                0X10
#define TIMER1_MODE_2                0X20
#define TIMER1_MODE_3                0X30
#define TIMER1_CNT_EX                0X40

//IP
#define TIMER0_LOW_PRIORITY          0X00
#define TIMER0_HIGH_PRIORITY         0X02

#define TIMER1_LOW_PRIORITY          0X00
#define TIMER1_HIGH_PRIORITY         0X08

#define TIMER2_LOW_PRIORITY          0X00
#define TIMER2_HIGH_PRIORITY         0X20

#ifdef SC92F8463B_ENABLED
//T2CON
#define T2CON_TF2           	0X80
#define T2CON_EXF2           	0X40
#define T2CON_RCLK           	0X20
#define T2CON_TCLK           	0X10
#define T2CON_EXEN2           0X08
#define T2CON_TR2          		0X04
#define T2CON_CT2           	0X02
#define T2CON_CPRL2           0X01

//T2MOD
#define T2MOD_T2OE  					0X02
#define T2MOD_DCEN            0X01

//T2
#define TIMER2_MODE_1					0X00

#endif


typedef struct 
{
    /* data */
    eName name;
    unsigned char tmod;
    unsigned int  count;
    unsigned char tmcon;
    unsigned char priority;
    timer_callback  func;
}Timer_InitTypeDef;

//public functions
extern void Timer_Init(Timer_InitTypeDef* tim);
extern void Timer_Start(eName tim);
extern void Timer_Stop(eName tim);
extern void Timer_Set_Callback(eName tim, timer_callback func);
#endif

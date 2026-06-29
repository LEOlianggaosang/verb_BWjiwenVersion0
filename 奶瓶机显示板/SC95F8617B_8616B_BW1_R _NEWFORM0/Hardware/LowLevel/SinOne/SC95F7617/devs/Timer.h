/**
 *******************************************************************************
 * Copyright (c) 2025.4.26
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
    TIMER2 = 2,
    TIMER3 = 3,
    TIMER4 = 4,
    TIMER_ENUM_END
}eName;

//TMCON
#define TIMER0_INPUT_FSYS_DIVIDE_12  0X00
#define TIMER0_INPUT_FSYS            0X01
#define TIMER1_INPUT_FSYS_DIVIDE_12  0X00
#define TIMER1_INPUT_FSYS            0X02

//TMOD
#define TIMER0_MODE_0                0X00
#define TIMER0_MODE_1                0X01
#define TIMER0_MODE_2                0X02
#define TIMER0_MODE_3                0X03

#define TIMER1_MODE_0                0X00
#define TIMER1_MODE_1                0X10
#define TIMER1_MODE_2                0X20
#define TIMER1_MODE_3                0X30

//IP
#define TIMER0_LOW_PRIORITY          0X00
#define TIMER0_HIGH_PRIORITY         0X02

#define TIMER1_LOW_PRIORITY          0X00
#define TIMER1_HIGH_PRIORITY         0X08

#define TIMER2_LOW_PRIORITY          0X00
#define TIMER2_HIGH_PRIORITY         0X20

//TXINX
#define TIMER2_REGISTER_POINT_MASK           0X02
#define TIMER3_REGISTER_POINT_MASK           0X03
#define TIMER4_REGISTER_POINT_MASK           0X04

//TXMOD
#define TIMER234_INPUT_FSYS_DIVIDE_12  0X00
#define TIMER234_INPUT_FSYS            0X80

//IE1
#define TIMER3_INTERRUPT_ENABLE   0X40
#define TIMER4_INTERRUPT_ENABLE   0X80

//IP1
#define TIMER3_LOW_PRIORITY          0X00
#define TIMER3_HIGH_PRIORITY         0X40
#define TIMER4_LOW_PRIORITY          0X00
#define TIMER4_HIGH_PRIORITY         0X80

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
extern void TM3_Reload(unsigned int count);
#endif

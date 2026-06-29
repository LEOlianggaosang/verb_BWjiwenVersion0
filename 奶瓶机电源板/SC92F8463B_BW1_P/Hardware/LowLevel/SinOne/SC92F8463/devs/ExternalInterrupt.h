/**
 *******************************************************************************
 * Copyright (c) 20230731
 *  
 * @file    ExternalInterrupt.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _EXTERNAL_INTERRUPT_H_
#define _EXTERNAL_INTERRUPT_H_

#ifndef NULL
#define NULL    0
#endif

#define ENABLE  1
#define DISABLE 0

typedef void (* intc_callback)(void);
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
typedef enum 
{
    INT0 = 0,
    INT1 = 1,
    INT2 = 2,
    INT_ENUM_END
}eIntName;

/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
///*INT*/
//sfr   INT0F = 0XB4;  //INT0 下降沿中断控制寄存器
//sfr   INT0R = 0XBB;  //INT0 上降沿中断控制寄存器
//sfr   INT1F = 0XBC;  //INT1 下降沿中断控制寄存器
//sfr   INT1R = 0XBD;  //INT1 上降沿中断控制寄存器
//sfr   INT2F = 0XBE;  //INT2 下降沿中断控制寄存器
//sfr   INT2R = 0XBF;  //INT2 上降沿中断控制寄存器
///*IE*/
//sbit  EA    = IE^7;  //中断使能的总控制       0:关闭所有的中断      1:打开所有的中断
//sbit  EINT1 = IE^2;  //外部中断1中断使能控制  0:关闭外部中断1中断   1:打开外部中断1中断	
//sbit  EINT0 = IE^0;  //外部中断0中断使能控制  0:关闭外部中断0中断   1:打开外部中断0中断
///*IP*/
//sbit  IPINT1 = IP^2;  //INT1计数器中断优先权选择  0:设定 INT1的中断优先权是 “低”     1:设定 INT1的中断优先权是 “高”
//sbit  IPINT0 = IP^0;  //INT0计数器中断优先权选择  0:设定 INT0的中断优先权为 “低”     1: INT0中断优先权为高
///*IE1*/

#define INT_NUM_0  0//((unsigned char)0x01)
#define INT_NUM_1  1//((unsigned char)0x02)
#define INT_NUM_2  2//((unsigned char)0x04)
#define INT_NUM_3  3//((unsigned char)0x08)
#define INT_NUM_4  4//((unsigned char)0x10)
#define INT_NUM_5  5//((unsigned char)0x20)

#define INT_FALL_DISABLE     ((unsigned char)0x00)
#define INT_FALL_ENABLE    ((unsigned char)0x01)

#define INT_RISE_DISABLE     ((unsigned char)0x00)
#define INT_RISE_ENABLE     ((unsigned char)0x01)

#define INT_LOW_PRIORITY     ((unsigned char)0x00)
#define INT_HIGH_PRIORITY     ((unsigned char)0x01)

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
typedef struct 
{
    eIntName name;
    unsigned char num;
    unsigned char fall;
    unsigned char rise;
		unsigned char priority;
		intc_callback func;
}Intc_InitTypeDef;

void Intc_Init(Intc_InitTypeDef*	intc);
//void INTP_Init( void );
//extern intc_callback intc_func;
extern void Intc_Set_Callback(eIntName intc, intc_callback func);
extern void Intc_Start(eIntName intc);
extern void Intc_Stop(eIntName intc);


#endif

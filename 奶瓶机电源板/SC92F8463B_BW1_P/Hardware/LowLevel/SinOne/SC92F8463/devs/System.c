/**
 *******************************************************************************
 * Copyright (c) 20240614
 *  
 * @file    System.c
 * @author  lianggaosang@qq.com
 * @brief
 *******************************************************************************
 */
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#ifdef SC92F8463B_ENABLED
#include "SC92F846XB_C.H"
#endif
#include "System.h"

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function process of Reset.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
unsigned char CG_ReadResetSource( void )
{
  unsigned char resetflag = 0;
  /* Start user code. Do not edit comment generated here */
  return resetflag;
  /* End user code. Do not edit comment generated here */
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function inits the system.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
unsigned char System_Init(void)
{

	return CG_ReadResetSource();
}

//char Array[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
//typedef struct
//{
//  char a3;        //高位地址
//  char a2;        //次高地址
//  char a1;        //次低地址
//  char a0;        //低位地址
//} Value_Typedef;
//typedef union
//{
//  Value_Typedef reg;
//  unsigned long int result;  //最终结果
//} Result_Typedef;

//unsigned long int temp = 0x00;  //最终结果
//Result_Typedef CRC_Result;

//void CRC_Hardware_Init(void);
//void CRC_Software_Init(char array[]);
///*****************************************************
//*函数名称：void CRC_Hardware_Init(void)
//*函数功能：CRC硬件校验初始化
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void CRC_Hardware_Init(void)
//{
//  bit EABIT = EA;
//  EA = 0;
//  OPERCON |= 0x01;  //启动硬件校验
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();

//  CRCINX = 0x00;
//  CRC_Result.reg.a0 = CRCREG;   //低两byte结果存放
//  CRC_Result.reg.a1 = CRCREG;   //次低两byte结果存放
//  CRC_Result.reg.a2 = CRCREG;   //次高两byte结果存放
//  CRC_Result.reg.a3 = CRCREG;   //高两byte结果存放
//  temp = CRC_Result.result;     //最终运算结果
//  EA = EABIT;
//}

///*****************************************************
//*函数名称：void CRC_Software_Init(char array[])
//*函数功能：CRC软件校验初始化
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void CRC_Software_Init(char array[])
//{
//  int i = 0;
//  bit EABIT = EA;
//  EA = 0;
//  OPERCON |= 0x02;             //启动软件校验
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  _nop_();
//  for(i = 0; i < 16; i++)  //校验范围
//  {
//    CRCREG = array[i];   //把要校验的地址值放到寄存器
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//    _nop_();
//  }
//  CRCINX = 0x00;
//  CRC_Result.reg.a0 = CRCREG;   //低两byte结果存放
//  CRC_Result.reg.a1 = CRCREG;   //次低两byte结果存放
//  CRC_Result.reg.a2 = CRCREG;   //次高两byte结果存放
//  CRC_Result.reg.a3 = CRCREG;   //高两byte结果存放
//  temp = CRC_Result.result;     //最终运算结果
//  EA = EABIT;
//}

//void BTM_Init(void);
///*****************************************************
//*函数名称：void BTM_Init(void)
//*函数功能：BTM初始化
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void BTM_Init(void)
//{
////	BTMCON = 0x00;  //不开启
////	BTMCON = 0x80;  //每15.625ms产生一个中断
////	BTMCON = 0x81;	//每31.25ms产生一个中断
////	BTMCON = 0x82;	//每62.5ms产生一个中断
////	BTMCON = 0x83;	//每125ms产生一个中断
//	BTMCON = 0x84;	//每0.25s产生一个中断
////	BTMCON = 0x85;	//每0.5s产生一个中断
////	BTMCON = 0x86;	//每1s产生一个中断
////	BTMCON = 0x87;	//每2s产生一个中断
////  BTMCON = 0x88;	//每4s产生一个中断
//	IE1 |= 0x04;       //开启BTM中断
//	EA = 1;           //开启总中断

//}
///*****************************************************
//*函数名称：void BTM_Int(void) interrupt 9
//*函数功能：中断函数
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void BTM_Int(void) interrupt 9
//{
//		P01 = ~P01;	//IO口翻转
//}
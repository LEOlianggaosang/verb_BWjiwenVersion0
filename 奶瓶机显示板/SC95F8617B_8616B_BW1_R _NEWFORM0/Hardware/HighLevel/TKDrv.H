//************************************************************
//  Copyright (c) 深圳市赛元微电子有限公司
//	文件名称	: TKDrv.H
//	局部函数列表:
//  最后更正日期:2025.4.29
// 	版本		: V1.0 8616b奶瓶机显示板
// 	更改记录	: rom前256byte禁止查表,因此在编译的时候，设置keil->option for Target->BL51 Locate->Code Range:0x100
//*************************************************************
#ifndef _TKDRV_H_
#define _TKDRV_H_

//#ifdef SC95F8616B_ENABLED
//#include "..\SC95F861xB_C.H"
//#endif
#include "lib\SensorMethod.h"
#include "product_config.h"

#ifdef SC95F8616B_ENABLED
#if NEWTPE1
// 0x00800000
//+0x00400000
//+0x00200000
//+0x00100000
//+0x00040000
//+0x00020000
//+0x00010000
//+0x00008000=0x00F78000
#define KEY2CHANNAL23	0x00800000
#define KEY1CHANNAL22	0x00400000
#define KEY4CHANNAL21	0x00200000
#define KEY6CHANNAL20	0x00100000
#define KEY3CHANNAL18	0x00040000
#define KEY8CHANNAL17	0x00020000
#define KEY7CHANNAL16	0x00010000
#define KEY5CHANNAL15	0x00008000
#else
// 0x01000000
//+0x00800000
//+0x00400000
//+0x00100000
//+0x00040000
//+0x00010000
//+0x00008000=0x01D58000
#define KEY1CHANNAL24	0x01000000
#define KEY2CHANNAL23	0x00800000
#define KEY3CHANNAL22	0x00400000
#define KEY4CHANNAL20	0x00100000
#define KEY5CHANNAL18	0x00040000
#define KEY6CHANNAL16	0x00010000
#define KEY7CHANNAL15	0x00008000
#endif
#endif
#define CONFIG_TK_T2 0
extern BOOL xdata TKScanflag;
extern UCHAR xdata exKeyValue ;
extern unsigned long int xdata exKeyValueFlag;
#if	CONFIG_TK_NG_DEBUG
extern unsigned long	int xdata NGKeyValueFlag;  
extern unsigned int xdata NGKeyValue;  					
#endif 

void TK_Scan(void);              					// TK扫描
UCHAR TK_Value(unsigned long int Flag);   			// 键值转换函数      
void Init_TK(void);									// 引出的初始化放在sys
#endif

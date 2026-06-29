//************************************************************
//  Copyright (c) 深圳市赛元微电子有限公司
//	文件名称	: TKDrv.H
//	局部函数列表:
//  最后更正日期:
// 	版本		: V1.0
// 	更改记录	: rom前256byte禁止查表,因此在编译的时候，设置keil->option for Target->BL51 Locate->Code Range:0x100
//*************************************************************
#ifndef _TKDRV_H_
#define _TKDRV_H_

#ifdef SC92F8545_ENABLED
#include "Project\SC92F854x_C.H"
#endif
#ifdef SC95F8575_ENABLED
#include "SC95F857x_C.H"
#endif
#ifdef SC95F8675_ENABLED
#include "..\H\SC95F867x_C.H"
#endif
#include "lib\SensorMethod.h"
#include "user_define.h"
#include "product_config.h"
	
#ifdef SC92F8545_ENABLED
//0x7E800000
#define TK1CHANNAL30	0x40000000
#define TK2CHANNAL29	0x20000000
#define TK3CHANNAL28	0x10000000
#define TK4CHANNAL27	0x08000000
#define TK5CHANNAL26	0x04000000
#define TK6CHANNAL25	0x02000000
#define TK7CHANNAL23	0x00800000
#endif

#ifdef SC95F8575_ENABLED
//0x0001FC00
#define TK1CHANNAL16	0x00010000
#define TK2CHANNAL15	0x00008000
#define TK3CHANNAL14	0x00004000
#define TK4CHANNAL13	0x00002000
#define TK5CHANNAL12	0x00001000
#define TK6CHANNAL11	0x00000800
#define TK7CHANNAL10	0x00000400
#endif

#ifdef SC95F8675_ENABLED
//0x0001FC00
#define TK1CHANNAL16	0x00010000
#define TK2CHANNAL15	0x00008000
#define TK3CHANNAL14	0x00004000
#define TK4CHANNAL13	0x00002000
#define TK5CHANNAL12	0x00001000
#define TK6CHANNAL11	0x00000800
#define TK7CHANNAL10	0x00000400
#endif
extern UCHAR xdata exKeyValue ;
extern BOOL xdata TKScanflag;

#if	CONFIG_TK_NG_DEBUG
extern unsigned long	int xdata NGKeyValueFlag;  
extern unsigned int xdata NGKeyValue;  					
#endif 

void TK_Scan(void);              					// TK扫描                
UCHAR TK_Value(unsigned long int Flag);   					// 键值转换函数         
void TK_Init(void);												// 引出的初始化放在sys

#endif
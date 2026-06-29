/**
 *******************************************************************************
 * Copyright (c) 2025.4.29
 * 
 * @file    TK.h
 * @author  lianggaosang@qq.com
 * @brief   8616b奶瓶机显示板
 *
 *******************************************************************************
 */

#ifndef _TK_H_
#define _TK_H_
#include "TKDrv.H"

/* Key and Bit map ---------------------------------------------------------- */

/* Menu select key bit */

/* Key code define ---------------------------------------------------------- */
#if NEWTPE1
#define KEY_CODE_FAST      1 //KEY1//TK24
#define KEY_CODE_POWER     2 //KEY2//TK23
#define KEY_CODE_STERILIZE 3 //KEY3//TK18
#define KEY_CODE_SELFCLEAN 4 //KEY4//TK21
#define KEY_CODE_LIGHT     5 //KEY5//TK15
#define KEY_CODE_STANDARD  6 //KEY6//TK20
#define KEY_CODE_SAVE      7 //KEY7//TK15
#define KEY_CODE_START     8 //KEY8//TK17
#define KEY_CODE_BOTH_TEST 28 
#define KEY_CODE_BOTH_VER	 16
#else
#define KEY_CODE_FAST      1 //KEY1//TK24//K2
#define KEY_CODE_STANDARD  2 //KEY2//TK23//K3
#define KEY_CODE_STEAM     3 //KEY3//TK22//K4
#define KEY_CODE_DRY       4 //KEY4//TK20//K5
#define KEY_CODE_INLET     5 //KEY5//TK18//K7
#define KEY_CODE_START     6 //KEY6//TK16//K6
#define KEY_CODE_POWER     7 //KEY7//TK15//K1
#define KEY_CODE_BOTH_TEST 67 
#define KEY_CODE_BOTH_VER	 12
#endif

#define KEY_CODE_NONE						0
/* Key action type define ----------------------------------------------------*/

typedef enum
{ 
	KEY_ACTION_LEAVE,
  KEY_ACTION_RELEASING,
	KEY_ACTION_SHORT,
  KEY_ACTION_LONG,
  KEY_ACTION_LONG_LONG,
  KEY_ACTION_UNDEFINE
}KeyActionType;

#define KEY_IS_RELEASED	(Key_ActionType == KEY_ACTION_RELEASING)

///* Key code */
extern UCHAR_XDATA Key_Code;
extern KeyActionType xdata Key_ActionType;


/**
 * @brief 读取按键数据
 * 
 * @param 无
 * @return 无
 */
void TK_ReadValue(void);

#endif

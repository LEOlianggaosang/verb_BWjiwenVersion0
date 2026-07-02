/**
 *******************************************************************************
 * Copyright (c) 2025.4.29
 * 
 * @file    TK.c
 * @author  lianggaosang@qq.com
 * @brief   8616b奶瓶机显示板
 *
 *******************************************************************************
 */

/* Includes head files ------------------------------------------------------ */
#include "TK.h"
#include "Key\Key.h"
#include "Work\Work.h"
// #include "Display\Display.h"
#include "TicketHandling\TicketHandling.h"
/* static define ------------------------------------------------------------- */
static UCHAR_XDATA keyCodeBuf = 0;
static UINT_XDATA keyStateHoldCount = 0;
/* Variables define --------------------------------------------------------- */
UCHAR_XDATA Key_Code = 0;
KeyActionType xdata Key_ActionType = KEY_ACTION_UNDEFINE;
///* Function define ---------------------------------------------------------- */
static void TK_MonitorAction(void);
static void TK_TypeAction(void);

/* Read key datas from Touch */
void TK_ReadValue(void)
{
	if(F_TK10ms != F_Base10ms)
	{
		F_TK10ms = F_Base10ms;
		keyCodeBuf = exKeyValue;//按键改变缓存
		TK_MonitorAction();
	}
}
/**
 * @brief 监视按键动作
 * 
 * @param 无
 * @return 无
 */
/* Monitor the K9key action and call the key action deal function */
static void TK_MonitorAction(void)
{//按键动作改变函数主循环20ms调用一次
    if (Key_Code != keyCodeBuf)//按键改变 松开有效
    {
        if (((keyCodeBuf == 0)&&(keyStateHoldCount >= 2))&&(Key_ActionType == KEY_ACTION_UNDEFINE))
        {//40ms
			TK_TypeAction();
        }
		else
		{
			Key_Code = keyCodeBuf;
			Key_ActionType = KEY_ACTION_UNDEFINE;//按键动作识别中
		}
    }
    else//按键保持 按下有效
    {
        if (keyCodeBuf == 0)//无按键
        {
        	keyStateHoldCount = 0;
			Key_ActionType = KEY_ACTION_LEAVE;//无按键
        }		
        else//有按键
        {
			keyStateHoldCount ++;
			if((50 == keyStateHoldCount)&&KEY_POWER)
			{
				if((STATE_WASHING != Work_CurrentState)&&(STATE_ERROR != Work_CurrentState))
				{
					Key_ActionType = KEY_ACTION_LONG;
				}
			}

			if((keyStateHoldCount >= 300)&&(!KEY_IS_RELEASED))
			{
				//  Buzz_SetType(BUZZ_KEY_VALID);//长按蜂鸣提示
				Key_ActionType = KEY_ACTION_LONG;//长按3s生效 判断释放补丁 LONG类型只生效一次
			}

			if (keyStateHoldCount >= 500)
			{//按键保持5s 
				keyStateHoldCount = 500;
				if((!KEY_IS_RELEASED))
				{
					//  Buzz_SetType(BUZZ_KEY_VALID);//长按蜂鸣提示
					Key_ActionType = KEY_ACTION_LONG_LONG;//久按
				}
			}		 
		}
	}
}

static void TK_TypeAction(void)
{
	// if(Key_ActionType == KEY_ACTION_UNDEFINE)
	// {
		if (keyStateHoldCount < 300)
		{
			Key_ActionType = KEY_ACTION_SHORT;//短按
			keyStateHoldCount = 0;
		}
 	// else if ((keyStateHoldCount > 150)||(keyStateHoldCount < 250))
 	// {//按键保持3s 
   	// Key_ActionType = KEY_ACTION_LONG;//长按
	// 		keyStateHoldCount = 0;
 	// }
	// 	if (keyStateHoldCount >= 250)
	// 	{//按键保持5s 
	// 		Key_ActionType = KEY_ACTION_LONG_LONG;//久按
	// 		keyStateHoldCount = 0;
	// 	}
	// }
}

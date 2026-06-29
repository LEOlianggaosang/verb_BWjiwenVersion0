/**
 *******************************************************************************
 * Copyright (c) 2022
 *  
 * @file    UpDownPipeSwitch.h
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief   上下层洗控制
 *
 *******************************************************************************
 */
#ifndef _UP_DOWN_PIPE_SWITCH_H_
#define _UP_DOWN_PIPE_SWITCH_H_

#include "GpioDrv.h"
#include "user_define.h"
#include "Work\Work.h"
#include "Test\Self_Test.h"

typedef enum
{
    PIPE_DOWN,
    PIPE_UP
}Pipe;

typedef enum
{
    PIPE_DOWN_IS_OPEND,
    PIPE_UP_IS_OPENED,
    PIPE_STATE_UNKNOWN
}PipeState;

typedef enum
{   
	T_UNKNOWN,
	T_UP ,
	T_FULL,
	T_DOWN
}HalfWorkPoint;

extern BOOL_XDATA workshop_Entered;
#if __C51__
extern PipeState xdata Pipe_CurrentState;
extern HalfWorkPoint xdata Half_CurrentPoint;
#else
extern PipeState Pipe_CurrentState;
extern HalfWorkPoint Half_CurrentPoint;
#endif
extern void Pipe_Open(Pipe pipe);
extern void FindPipePoint(void);
extern void Init_UpDownPipeSwitch(void);
extern UINT_XDATA  PMAM_close_cnt;//lgx 20221201
#endif

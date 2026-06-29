/**
 *******************************************************************************
 * Copyright (c) 2022
 * 
 * @file    UpDownPipeSwitch.c
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief   上下层洗控制
 *
 *******************************************************************************
 */
/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "UpDownPipeSwitch.h"
#include "Signals\Signals.h"
#include "ErrorHandling\Error.h"
#include "Relays\Relays.h"


UINT_XDATA PMAM_close_cnt_buff=0;
UINT_XDATA  PMAM_close_cnt=0;
static BOOL_XDATA actionIsCompleted = MD_TRUE;
BOOL_XDATA Clearbug=0;

#if __C51__
PipeState xdata Pipe_CurrentState = PIPE_STATE_UNKNOWN;
HalfWorkPoint xdata Half_CurrentPoint=T_UNKNOWN;
Pipe xdata Pipe_T;
static PipeState xdata targetPipeState = PIPE_UP_IS_OPENED;
#else
PipeState Pipe_CurrentState = PIPE_STATE_UNKNOWN;
HalfWorkPoint Half_CurrentPoint=T_UNKNOWN;
Pipe Pipe_T;
static PipeState targetPipeState = PIPE_UP_IS_OPENED;
#endif
static BOOL_XDATA waitHighEnable = MD_FALSE;
static BOOL_XDATA waitlowEnable = MD_FALSE;
static UINT_XDATA actionDelay4msCount = 650;
static USHORT_XDATA PmamWorkCount = 0;

void Init_UpDownPipeSwitch(void)
{

}

#if CONFIG_WASH_IN_TURN==1

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
void Pipe_Open(Pipe pipe)
{
	if ((pipe == PIPE_UP && Pipe_CurrentState == PIPE_UP_IS_OPENED) ||
		(pipe == PIPE_DOWN && Pipe_CurrentState == PIPE_DOWN_IS_OPEND))
	{
		return;
	}
	actionIsCompleted = MD_FALSE;
	Pipe_CurrentState = PIPE_STATE_UNKNOWN;
	Clearbug=0;

	if (pipe == PIPE_DOWN )
	{
		Pipe_T = PIPE_DOWN;
		//actionDelay4msCount = 200;// 50 -- > 25 --> 75
		actionDelay4msCount = 0;
		targetPipeState = PIPE_DOWN_IS_OPEND;
	}
	else if(pipe == PIPE_UP)
	{
		//actionDelay4msCount = 800;
		Pipe_T = PIPE_UP;
		actionDelay4msCount = 0;
		targetPipeState = PIPE_UP_IS_OPENED;
		Half_CurrentPoint=T_UNKNOWN;
	}
}


void FindPipePoint(void)
{
  RELAY_HALF_ENABLE = MD_FALSE;
  if (RELAY_WP_ENABLE == 0||actionIsCompleted|| Work_IsPaused)//????,???,
  {

  }
  else
  {

	  RELAY_HALF_ENABLE = MD_TRUE;
	  if (Signal_PmamPosition == 0)//??????
	  {
			
		  Clearbug=1;
	  }    

	  if (Signal_PmamPosition == 1 && Clearbug==1)//????????
	  {
		  waitlowEnable = MD_TRUE;
		  PMAM_close_cnt_buff++;
	  }
	  if (waitlowEnable)
	  {
		  if (Signal_PmamPosition == 0)
		  {
			  PMAM_close_cnt=PMAM_close_cnt_buff;
			  waitlowEnable = MD_FALSE;
			  PMAM_close_cnt_buff=0;   

			  if (Half_CurrentPoint==T_FULL)//????,??????????,?????
			  {
				  Half_CurrentPoint=T_DOWN;
			  }
			  if (Half_CurrentPoint==T_UP)//??????,??????????,?????.
			  {
				  Half_CurrentPoint=T_FULL;
			  }             
			  if (PMAM_close_cnt>=625 )//??????2.5??,?????
			  {
				  Half_CurrentPoint=T_UP;
			  }
		  }
	  }

	  if (Half_CurrentPoint==T_UP && Pipe_T == PIPE_UP)
	  {
		  actionIsCompleted = MD_TRUE;
		  Pipe_CurrentState = targetPipeState;
		  PMAM_close_cnt_buff=0;
		  PMAM_close_cnt=0;
	  }
	  if (Half_CurrentPoint==T_DOWN && Pipe_T == PIPE_DOWN)
	  {
		  actionIsCompleted = MD_TRUE;
		  Pipe_CurrentState = targetPipeState;
		  PMAM_close_cnt_buff=0;
		  PMAM_close_cnt=0;
	  }

  }

  if (!workshop_Entered)
  {
	  SetPin(HALF_OUTPUT, RELAY_HALF_ENABLE);
  }

  if (RELAY_HALF_ENABLE)
  {
	  if (Test_Entered)//????????????
	  {
		  PmamWorkCount ++;
		  if (PmamWorkCount > (250 * 30))
		  {
			  Error_SetCode(ERROR_PMAM);
		  }
	  }

  }
  else
  {
	  PmamWorkCount = 0;
  }  
}
#else
void Pipe_Open(Pipe pipe)
{
	
}

#endif

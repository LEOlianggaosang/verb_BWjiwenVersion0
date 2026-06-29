/**
 *******************************************************************************
 * Copyright (c) 2022
 * 
 * @file    AutoDoor.c
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief
 *
 *******************************************************************************
 */

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "product_config.h"

#if (CONFIG_AUTO_DOOR==1)
#include "GpioDrv.h"
#include "AutoDoor.h"
#include "Signals\Signals.h"

//open door
#define		MOTOR_COROTATION	SetPin(AUTO_DOOR_OPEN_OUTPUT, ON);SetPin(AUTO_DOOR_CLOSE_OUTPUT, OFF)//PORT_INA = 1;PORT_INB = 0
//close door
#define		MOTOR_REVERSAL	 SetPin(AUTO_DOOR_OPEN_OUTPUT, OFF);SetPin(AUTO_DOOR_CLOSE_OUTPUT, ON)//PORT_INA = 0;PORT_INB = 1
#define		MOTOR_STANDBY			SetPin(AUTO_DOOR_OPEN_OUTPUT, OFF);SetPin(AUTO_DOOR_CLOSE_OUTPUT, OFF)//PORT_INA = 0;PORT_INB = 0
#define		MOTOR_PAUSE			SetPin(AUTO_DOOR_OPEN_OUTPUT, ON);SetPin(AUTO_DOOR_CLOSE_OUTPUT, ON)//PORT_INA = 1;PORT_INB = 1

/*
********************************************************************************
**  Global Functions Define
********************************************************************************
*/

AutoDoorMotorState gDoorState = AUTO_DOOR_STANDBY;
static UINT_XDATA gTimeCountForOpenDoor = 0;
static UCHAR_XDATA gClosedDoorDebounceCnt = 0;
static UCHAR_XDATA gDoorOpenToTheEndDebounceCnt = 0;

//
static UINT_XDATA gTimeCountOfOpenDoorInDry = 500;

//
static UINT_XDATA gOperationTime = 0;

#define AUTO_DOOR_DEBOUNCE_COUNT_MAX	3
void Init_Auto_Door(void)
{

}

BOOL IsAutoDoorClosed(void)
{
	BOOL 	rt = MD_FALSE;
	
	if (GetPin(AUTO_DOOR_CLOSED_INPUT) == MD_FALSE)
	{
		if (gClosedDoorDebounceCnt >= AUTO_DOOR_DEBOUNCE_COUNT_MAX)
		{
			rt = MD_TRUE;
		}
		else
		{
			gClosedDoorDebounceCnt++;
		}
	}
	else
	{
		if (gClosedDoorDebounceCnt > 0)
		{	
			gClosedDoorDebounceCnt--;
		}
	}
	
	return (rt);
}

BOOL IsAutoDoorOpenedToTheEnd(void)
{
	BOOL 	rt = MD_FALSE;
	
	if (GetPin(AUTO_DOOR_OPENED_INPUT) == MD_FALSE)
	{
		if (gDoorOpenToTheEndDebounceCnt >= AUTO_DOOR_DEBOUNCE_COUNT_MAX)
		{
			rt = MD_TRUE;
		}
		else
		{
			gDoorOpenToTheEndDebounceCnt++;
		}
	}
	else
	{
		if (gDoorOpenToTheEndDebounceCnt > 0)
		{	
			gDoorOpenToTheEndDebounceCnt--;
		}

#if (OPEN_DOOR_IN_SECONDS == 1)		
		// current PORT_FSS is fault, so just open door for 4 seconds				
		if (gTimeCountForOpenDoor < 1000)
		{
			gTimeCountForOpenDoor++;
		}
		else
		{
			rt = MD_TRUE;
		}
#endif		
		
	}
	
	return (rt);	
	
}

void Ctrl_Auto_Door(void)
{
	if (gOperationTime > 2500)
	{
		//Operation error, auto door open or close more than 10s
		gOperationTime = 0;
		if (gDoorState == AUTO_CLOSE_DOOR)
		{
			gDoorState = AUTO_DOOR_STANDBY;
		}
		else if (gDoorState == AUTO_OPEN_DOOR)
		{
			gDoorState = AUTO_CLOSE_DOOR;
		}
	}
	
	switch(gDoorState)
	{
		case AUTO_DOOR_STANDBY:
			gTimeCountForOpenDoor = 0;
		   gOperationTime = 0;
			MOTOR_STANDBY;
			break;
		case AUTO_OPEN_DOOR:
			if(IsAutoDoorOpenedToTheEnd())
			{
				MOTOR_PAUSE;
				//currently just open the door, and then close the door
				gDoorState = AUTO_CLOSE_DOOR;
				gOperationTime = 0;
			}
			else
			{
				MOTOR_COROTATION;
				gOperationTime++;
			}			
			break;
		case AUTO_CLOSE_DOOR:
			gTimeCountForOpenDoor = 0;
			if(IsAutoDoorClosed())
			{
				MOTOR_PAUSE;
				gOperationTime = 0;
				gDoorState = AUTO_DOOR_STANDBY;
			}
			else
			{
				MOTOR_REVERSAL;
				gOperationTime++;
			}				
			break;
		case AUTO_CLOSE_DOOR_AFTER_POWER_UP:
			gTimeCountForOpenDoor = 0;
			if(IsAutoDoorClosed())
			{
				MOTOR_PAUSE;
				gDoorState = AUTO_DOOR_STANDBY;				
				gOperationTime = 0;
			}
			else
			{
				MOTOR_REVERSAL;
				gOperationTime++;
			}
			break;		
		default:
			break;
	}
}

#endif

/**
 *******************************************************************************
 * Copyright (c) 2022
 * 
 * @file    AutoDoor.h
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief
 *
 *******************************************************************************
 */

#ifndef _AUTO_DOOR_H_
#define _AUTO_DOOR_H_

#include "user_define.h"

typedef enum
{
    AUTO_DOOR_STANDBY,
    AUTO_OPEN_DOOR,
    AUTO_CLOSE_DOOR,
		AUTO_CLOSE_DOOR_AFTER_POWER_UP
}AutoDoorMotorState;

void Ctrl_Auto_Door(void);

void Init_Auto_Door(void);

BOOL IsAutoDoorClosed(void);

extern AutoDoorMotorState gDoorState;

#endif

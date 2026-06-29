#ifndef BLAC_MOTOR_H
#define BLAC_MOTOR_H

#include "SerialDrv.h"
#include "user_define.h"
#include "product_config.h"
#include "Data.h"

#if CONFIG_BLAM_ENABLE

#define MESSAGE_DATA_LENGTH         8

#define SPEED_0_RMP     0
#define SPEED_2300_RMP  20
#define SPEED_2500_RMP  30
#define SPEED_2700_RMP  40
#define SPEED_2900_RMP  50
#define SPEED_3100_RMP  60
#define SPEED_3300_RMP  70
#define SPEED_3400_RMP  80
#define SPEED_3500_RMP  90
#define SPEED_3600_RMP  100

typedef enum
{
	COMMAND_NULL = 0,
	COMMAND_ACK = 0x11,
	COMMAND_NACK = 0x12,
	COMMAND_ST = 0x13,
	COMMAND_RSR = 0x15,
	COMMAND_RESET = 0x16,
}Command_t;

extern BOOL_XDATA USCI0_IsCommunicating;
extern Command_t  current_command;
extern UCHAR_XDATA current_parameter;

void Motor_SetData(Command_t command,unsigned char parameter);
void Motor_Control(void);

void Init_BldcMotor(void);
#endif

#endif
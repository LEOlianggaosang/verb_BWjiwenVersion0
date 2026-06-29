#include "BldcMotor.h"
#if CONFIG_BLAM_ENABLE
#include "TicketHandling\TicketHandling.h"
#include "Relays\Relays.h"
#include "Work\Work.h"
/**
 * ----------------------------- Message Format --------------------------------
 * 0x21     CMD     NPAR     PAR1     PAR2     …     CKS_H     CKS_L     0x42
 * -----------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * ACK
 * 0x21 0x11 0x02 status speed cks_h cks_l 0x42 
 * NACK
 * 0x21 0x12 0x02 status speed cks_h cks_l 0x42
 *------------------------------------------------------------------------------
 */

/*
 *------------------------------------------------------------------------------
 * status:
 * 
 *------------------------------------------------------------------------------
 */

static UCHAR_XDATA  SendDatasBuf[MESSAGE_DATA_LENGTH] = {0};

static BOOL_XDATA timerTick1s;
BOOL_XDATA USCI0_IsCommunicating = MD_FALSE;

Command_t  current_command = COMMAND_NULL;
UCHAR_XDATA current_parameter = 0;

void Init_BldcMotor(void)
{
#if (DEBUG_PRINT == 0)	
	Uart_Start(SERIAL_BLDC_FOR_DEBUG);
#endif	
}

void Motor_SetData(Command_t command,unsigned char parameter)
{
	current_command = command;
	current_parameter = parameter;
}

/**
 *------------------------------------------------------------------------------
 * Function :
 *          This function used to put the washing motor pump in rotation or 
 *          to change its rotational speed to reach the target speed with the 
 *          specified gradient.
 * Arguments:
 *          targetSpeed:The real target spped will be targetSpeed * 30 rpm.
 *          accelerationRamp:The real acceleration ramp will be accelerationRamp * 10 ms
 *          desideratedVoltageProfile:desiderated Voltage Profile.
 * Note     :
 *          when the motor pump rotate,The Motor can rotate at a speed within 
 *          the range 2400 rpm and 5100 rpm and to accelerate in minimum 150ms over 40Hz.
 *
 *          If the motor pump is in the STOP state, at the first START the 
 *          minimum will accelerate in the range from 750 to 900 ms depending on
 *          the speed. Subsequent changes in rotation speed pump will accelerate
 *          as the minimum possible 150ms.
 *          
 *          If a START/STOP command is issued exceeding the previous limits of
 *          allowed speed or acceleration, the AMCU puts the motor pump at the 
 *          maximum or at the minimum speed or acceleration and answers with ACK
 *          message.
 *
 *          When the motor pump is rotating, it must be used the same command 
 *          START/STOP with target speed parameter byte equal to 0x 00 to stop 
 *          the motor. The braking and the stopping of the motor pump are hold in
 *          practice as a change in the target speed. It is possible to set the 
 *          gradient equal to 0x 00: in this case the AMCU changes the rotational
 *          speed as fast as possible.
 *------------------------------------------------------------------------------
 */
static void Motor_Reset(void)
{
	SendDatasBuf[0] = 0x21;//头,固定为0x21 
	/* command */
	SendDatasBuf[1] = 0x13;//命令,启动或暂停 
	/* number of parameter */
	SendDatasBuf[2] = 0x03;//固定为0x03 
	/* parameter  */
	SendDatasBuf[3] = 0;//转速,占空比0%~100%，对应0~0x64 
	SendDatasBuf[4] = 0;//转速上升时间，0~15 秒，对应0~0x0F； 
	SendDatasBuf[5] = 0x01;//预留,固定为0x01 
	//校验 
	SendDatasBuf[6] = 0x13 ^ 0x03 ^ 0x00  ^ 0x00 ^ 0x01 ;   
	/* end byte */
	SendDatasBuf[7] = 0x42;
#if (DEBUG_PRINT == 0)
	Uart_SendData(SERIAL_BLDC_FOR_DEBUG, SendDatasBuf,8);
#endif	
}

static void Motor_St(void)
{
    /* start byte */
	SendDatasBuf[0] = 0x21;
	/* command */
	SendDatasBuf[1] = 0x13;
	/* number of parameter */
	SendDatasBuf[2] = 0x03;
	/* parameter 1 */
	SendDatasBuf[3] = current_parameter;//转速,占空比0%~100%，对应0~0x64 
	SendDatasBuf[4] = 0x07;//转速上升时间，0~15 秒，对应0~0x0F； 
	SendDatasBuf[5] = 0x01;//预留,固定为0x01 
	SendDatasBuf[6] = 0x13 ^ 0x03^ current_parameter ^ 0x07 ^ 0x01  ;   
	/* end byte */
	SendDatasBuf[7] = 0x42;
#if (DEBUG_PRINT == 0)
	Uart_SendData(SERIAL_BLDC_FOR_DEBUG, SendDatasBuf,8);
#endif	
}

static void Motor_Rsr(void)
{
	/* start byte */
	SendDatasBuf[0] = 0x21;
	/* command */
	SendDatasBuf[1] = 0x15;
	SendDatasBuf[2] = 0x03;
	/* parameter 1 */
	SendDatasBuf[3] = current_parameter;//转速,占空比0%~100%，对应0~0x64 
	SendDatasBuf[4] = 0x07;//转速上升时间，0~15 秒，对应0~0x0F； 
	SendDatasBuf[5] = 0x01;//预留,固定为0x01 
	SendDatasBuf[6] = 0x15 ^ 0x03 ^ 0x07^ current_parameter ^ 0x01 ;   
	/* end byte */
	SendDatasBuf[7] = 0x42;
#if (DEBUG_PRINT == 0)
	Uart_SendData(SERIAL_BLDC_FOR_DEBUG, SendDatasBuf,8);
#endif	
}

void Motor_Control(void)
{
// 	if (USCI0_IsCommunicating || current_command == COMMAND_NULL)
// 	{
// 		return;
// 	}
    /*USCI0_Start();*/
	static ULONG_XDATA Timer_MonotonicClockBuf = 0;
	
	timerTick1s = MD_FALSE;
	if (Timer_MonotonicClock - Timer_MonotonicClockBuf >= OneSecondCount)
	{
		Timer_MonotonicClockBuf = Timer_MonotonicClock;
		timerTick1s = MD_TRUE;
	}

	if (!timerTick1s)
	{
		return;
	}

#if (SIMULATION_SIGNAL_FOR_DEBUG_MOTOR == 1)
	Motor_SetData(COMMAND_ST,SPEED_3600_RMP);
	Motor_St();
#endif	
	
	if (RELAY_WP_ENABLE == 0) //洗涤没开时，不发送 
	{
		return;
	}


	if (Work_CurrentMenu != MENU_ECONOMIC)
	{
		if (Work_CurrentStage == STAGE_RINSE)
		{
			Motor_SetData(COMMAND_ST,SPEED_2500_RMP);
		}
		else
		{
			Motor_SetData(COMMAND_ST,SPEED_2700_RMP);
		}
	}

	if (Test_Entered)
	{
		Motor_SetData(COMMAND_ST,SPEED_3600_RMP);
	}

	switch (current_command)
	{	
	case COMMAND_RESET:
		Motor_Reset();
		break;
	case COMMAND_ST:
		Motor_St();
		break;
	case COMMAND_RSR:
		Motor_Rsr();
		break;
	}
}

#endif

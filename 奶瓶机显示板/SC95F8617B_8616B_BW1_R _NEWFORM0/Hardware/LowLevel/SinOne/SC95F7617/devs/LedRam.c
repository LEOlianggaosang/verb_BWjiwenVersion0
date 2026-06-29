/**
 *******************************************************************************
 * Copyright (c) 2025.4.28
 *  
 * @file    LedRam.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#ifdef SC95F8616B_ENABLED
#include "..\SC95F861xB_C.H"
#endif
#include "LedRam.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
unsigned char xdata LCDRAM[28]  _at_  0x2000;
/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function restart the LedRam.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
// /*****************************************************
// *function: void LED_Init(void)
// *brief: LED initialization
// *param: void
// *retval: void
// *****************************************************/
// void LED_Init(void)
// {
// 	unsigned int i;
// 	DDRCON = 0xC0;    //-xyy zzzz  x:LCD/LED mode    y:Duty 1/8:00 1/6:01 1/5:10 1/4:11    z:LCD voltage regulation
// 	PxVO_Init();
// 	OTCON |= 0x00;    //---- xxyz  x:LCD divider resistance   y:Multiplex pin selection   z:LCD bias voltage
// 	for(i=0; i<8; i++)
// 	{
// 		LCDRAM[i] = 0xff;
// 	}
// }
void SegRam_Init(SegRam_InitTypeDef *SegRam)
{
	if (SegRam == NULL)
	{
		return;
	}

	switch(SegRam->port)
	{
		case PVO0:
			P0VO |= (SegRam->pin);
			break;
        case PVO1:
            P1VO |= (SegRam->pin);
            break;  
        case PVO2:
            P2VO |= (SegRam->pin);
            break;
        case PVO3:
            P3VO |= (SegRam->pin);
            break;
		default:
			break;												
	}
}
// /*****************************************************
// *function: void PxVO_Init(void)
// *brief: Display Driver Output initialization
// *param: void
// *retval: void
// *****************************************************/
// void PxVO_Init(void)
// {
// 	P0VO = 0xFF;
// 	P1VO = 0xFF;
// 	P2VO = 0xFF;
// 	P3VO = 0xFF;
// }

void SegRam_Clear(void)
{
	unsigned int i;
	for(i=0; i<28; i++)
	{
		LCDRAM[i] = 0x00;//0xff
	}
}
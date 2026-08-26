/**
 *******************************************************************************
 * Copyright (c) 20250606
 * 
 * @file    Buzzer.c
 * @author  lianggaosang@qq.com
 * @brief 
 * 
 *******************************************************************************
 */
#include "Buzzer.h"
#include "PclBuzDrv.h"
#include "GpioDrv.h"
#include "TicketHandling\TicketHandling.h"
#include "WashDish\WashDish.h"//F_IsBuzzing//F_BuzzReceived

#ifdef	SC92F8463B_ENABLED

struct BuzzInfo
{
  unsigned char buzzTimes;
  unsigned char buzzOnNum;
  unsigned char buzzOffNum;
};
static const struct BuzzInfo buzzDatas[] =
{
  {1, 20, 50},        //BUZZ_POWERON,
  {3, 15, 30},        //BUZZ_ENTERCHECK,
  {1, 10, 50},        //BUZZ_KEY_VALID,
  {2,  8, 15},        //BUZZ_KEY_INVALID,
  {5, 10, 40},        //BUZZ_ALARM,
  {3, 10, 50},        //BUZZ_END,
  {10,10, 30},        //BUZZ_DOOROPEN
};

static BuzzType  xdata currentBuzzType = BUZZ_SILENCE;
static UCHAR xdata buzzCount = 0;
static UCHAR xdata buzzTimesBuf = 0;
static UCHAR xdata buzzOnNumBuf = 0;
static UCHAR xdata buzzOffNumBuf = 0;

//³õÊ¼»¯
void Init_Buzz(void)
{
	Stop_Buzzer();
	// Init_Buzzer();
	// SetPin(BUZC,ON);
}

//Ö´ÐÐ
void Buzz_Control(void)
{
	static UCHAR buzzindex = 0;
	
	if(Buzz_Timer10ms != F_Base10ms)
	{
		Buzz_Timer10ms = F_Base10ms;
		if(++buzzindex >=2)
		{
			buzzindex = 0;
			if (BUZZ_SILENCE != currentBuzzType)
			{
				buzzTimesBuf = buzzDatas[currentBuzzType].buzzTimes;
				buzzOnNumBuf = buzzDatas[currentBuzzType].buzzOnNum;
				buzzOffNumBuf = buzzDatas[currentBuzzType].buzzOffNum;
				currentBuzzType = BUZZ_SILENCE;
			}

			//if ((buzzTimesBuf > 0)&&(!Signal_SoundIsSetted))
			if (buzzTimesBuf > 0)
			{
				buzzCount ++;

				if (buzzCount < buzzOnNumBuf)
				{
					Start_Buzzer();
					// SetPin(BUZC,ON);
					// P01 = 1;
					F_IsBuzzing = 1;
				}
				else if (buzzCount < buzzOffNumBuf)
				{
					Stop_Buzzer();
					// SetPin(BUZC,OFF);
					// P01 = 0;
					F_IsBuzzing = 0;
				}
				else
				{
					buzzTimesBuf --;
					buzzCount = 0;
				}
			}
			else
			{
				F_IsBuzzing = 0;
				Stop_Buzzer();
				// SetPin(BUZC,OFF);
				// P01 = 0;
				F_IsBuzzing = 0;
			}
		}
	}
}

//ÉèÖÃ
void Buzz_SetType(BuzzType type)
{
	// currentBuzzType = type;
	Stop_Buzzer();
	// SetPin(BUZC,OFF);
	// P01 = 0;
	buzzTimesBuf = 0;
	buzzCount = 0;
	currentBuzzType = type;
}

#endif
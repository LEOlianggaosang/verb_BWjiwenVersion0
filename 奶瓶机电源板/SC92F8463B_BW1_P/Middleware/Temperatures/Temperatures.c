/**
 *******************************************************************************
 * Copyright (c) 20250117
 * 
 * @file    Temperatures.c
 * @author  lianggaosang@qq.com
 * @brief   温度控制
 * 
 *******************************************************************************
 */

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "Temperatures.h"
#include "AdDrv.h"
#include "TicketHandling\TicketHandling.h"
/*
********************************************************************************
**  Global Variables Define
********************************************************************************
*/
ByteFlag U_AdErrFlag = {0};
UCHAR_XDATA Temperature_Value = 25;     ///< 当前温度值
UCHAR_XDATA Temperature_AdValue = 0;    ///< 当前采样的温度传感器的AD值
/*
********************************************************************************
**  Private Datas
********************************************************************************
*/
static UCHAR_XDATA ADC_Temperature[18];

//温度表.可用当前的AD值为该表的索引取得当前的温度值(数组下标=(AD/16 - 10))
#if (R100K_25C == NTC_Type)
static const UCHAR code  temperatures[] =
{
	110,110,109,109,108,108,107,106,106,105,	//  83d- 92d
	105,104,104,103,102,102,101,101,100,100,	//  93d- 102d
	99,99,98,98,97,96,96,95,95,94,				//  103d-112d
	94,93,93,92,92,91,91,90,90,89,				//  113d-122d
	89,88,88,87,87,86,86,85,85,85,				//  123d-132d
	84,84,83,83,82,82,81,81,80,80,				//  133d-142d
	79,79,78,78,77,77,76,76,75,75,				//  143d-152d
	74,74,73,73,72,72,71,71,70,70,				//  153d-162d
	69,69,68,68,67,67,66,66,65,65,				// 	163d-172d
	64,64,63,63,62,62,61,61,60,60,				// 	173d-182d
	59,59,58,58,57,57,56,55,55,54,				//  183d-192d
	54,53,53,52,51,51,50,50,49,48,				//  193d-202d
	48,47,46,46,45,45,44,43,42,42,				//  203d-212d
	41,40,39,39,38,37,36,36,35,34,				//  213d-222d
	33,32,31,30,29,28,27,25,24,23,				//  223d-232d
	22,21,20,19,18,17,15,14,12,10,				//  233d-242d
	8,6,4,2,0,0,0,0,0,0,						//  243d-252d

};
#elif (R10K_25C == NTC_Type)
static const UCHAR code  temperatures[] =
{
	120,118,115,112,110,108,106,104,102,100,	//  14d- 23d
	99,98,96,94,92,91,89,88,86,85,				//  24d- 33d
	84,83,81,79,78,77,76,75,74,73,				//  34d- 43d
	72,71,70,69,68,68,67,66,65,64,				//  44d- 53d
	64,64,63,62,61,60,59,59,58,57,				//  54d- 63d
	57,56,55,54,54,53,53,52,52,51,				//  64d- 73d
	50,50,49,49,48,48,47,47,46,46,				//  74d- 83d
	45,44,44,43,43,42,42,41,41,40,				//  84d- 93d
	40,39,39,38,38,38,37,37,36,36,				//  94d-103d
	35,35,34,34,33,33,32,32,32,31,				// 104d-113d
	31,30,30,29,29,29,28,28,27,27,				// 114d-123d
	26,26,26,25,25,25,24,24,24,23,				// 124d-133d
	23,22,22,21,21,20,20,20,19,19,				// 134d-143d
	18,18,18,17,17,16,16,16,15,15,				// 144d-153d
	14,14,14,13,13,12,12,11,11,11,				// 154d-163d
	10,10,9,9,8,8,8,7,7,6,						// 164d-173d
	6,6,5,5,4,4,4,3,3,2,						// 174d-183d
	2,1,1,0,0,0,0,0,							// 184d-191d
};
#endif

void Init_Temperatures(void)
{
  Temperature_Value = 25;
  Temperature_AdValue = 0;
}

/**
 * @brief 获得当前的温度值
 * 
 * 在主系统循环中调用该函数获取当前的温度值并保存在Temperature_Value中.
 * @param 无
 * @exception 温度传感器故障
 * @return 设置全局变量 Temperature_Value,Temperature_AdValue
 */
void Temperature_Read(void)
{
		static UCHAR sampleCount = 0;
		
		if(Temp_Timer10ms != F_Base10ms)
		{
		Temp_Timer10ms = F_Base10ms;
		#if NEWTYPE1
        singleSample(AIN3_NTC,&ADC_Temperature[sampleCount]);
		#else
		singleSample(AIN9_NTC,&ADC_Temperature[sampleCount]);
		#endif
        sampleCount ++;

        if (sampleCount >= 18)
        {
            sampleCount = 0;
            Temperature_AdValue = ADC_AverageValue(ADC_Temperature);
						F_ErrRe	  = 0;
						F_ReShort = 0;
						F_ReOpen  = 0;

						if((Temperature_AdValue <= TEMPERATURE_MIN_AD) || (Temperature_AdValue >= TEMPERATURE_MAX_AD))
						{//C_AD_MIN//C_AD_MAX
							Temperature_Value = 0;
							
							F_ErrRe	  = 1;
							
							if (Temperature_AdValue <=  TEMPERATURE_MIN_AD)
							{
								F_ReShort = 1;
							}
							else
							{
								F_ReOpen  = 1;
							}
						}
						else									//5<AdResult<252
						{
							if (Temperature_AdValue < TEMPERATURE_TEMP_MAX_AD)
							{
								Temperature_Value = TEMPERATURE_TEMP_MAX;
							}
							else if(Temperature_AdValue > TEMPERATURE_TEMP_MIN_AD)
							{
								Temperature_Value = TEMPERATURE_TEMP_MIN;
							}
							else
							{
								#ifdef SC92F8463B_ENABLED
								Temperature_Value = temperatures[Temperature_AdValue - TEMPERATURE_TAB_MIN];
								#endif
							}
						}
        }
		}
}

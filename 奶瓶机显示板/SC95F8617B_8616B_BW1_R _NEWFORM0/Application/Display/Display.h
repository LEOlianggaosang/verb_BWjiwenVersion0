/**
*******************************************************************************
 * Copyright (c) 2025.5.17
 * 
* @file    Display.h
* @author  lianggaosang@qq.com
* @brief   8616b奶瓶机显示板
* 
*******************************************************************************
*/

#ifndef DISPLAY_H_
#define DISPLAY_H_
#include "product_config.h"

//NIGHT_LIGHT*************************************************************
typedef enum
{
    RGB_OFF = 0,//0/0/0
    RGB_RED = 1,//100/0/0
    RGB_GREEN = 2,//0/100/0
    RGB_BLUE = 3,//0/0/100
    RGB_YELLOW = 4,//100/100/0
    RGB_CYAN = 5,//0/100/100
    RGB_PURPLE = 6,//100/0/100
    RGB_ORANGE = 7,//100/50/0
    RGB_PINK = 8,//100/0/50
    RGB_SPRING = 9,//50/100/0
    RGB_SKY = 10,//0/100/50
    RGB_VIOLET = 11,//50/0/100
    RGB_INDIGO = 12,//0/50/100
    RGB_WARM = 13,//100/50/50
    RGB_COLD = 14,//50/50/100
    RGB_WHITE = 0x0f,//100/100/100
    NLCOLOR_END
}NL_ColorType;
typedef enum
{
    ON_RGB = 0,//常亮
    FLESH1_RGB = 0x10,//1Hz闪烁
    FLESH2_RGB = 0x20,//2Hz闪烁
    FLESH3_RGB = 0x30,//3Hz闪烁
    FLASH4_RGB = 0x40,//4Hz闪烁
    FLASH5_RGB = 0x50,//5Hz闪烁
    BREATH_RGB = 0x60,//呼吸
    NLACTION_END
}NL_ActionType;
extern UCHAR_XDATA 		NightLight_ColorType;
extern UCHAR_XDATA 		NightLight_ActionType;

// void Init_Display(void);
void Display_Control(void);

#endif
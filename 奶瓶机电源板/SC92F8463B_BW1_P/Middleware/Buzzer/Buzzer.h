/**
 *******************************************************************************
 * Copyright (c) 20250606
 * 
 * @file    Buzzer.h
 * @author  lianggaosang@qq.com
 * @brief   
 * 
 *******************************************************************************
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "product_config.h"

typedef enum
{
  BUZZ_POWERON = 0,     
  BUZZ_ENTERCHECK = 1,  
  BUZZ_KEY_VALID = 2,   
  BUZZ_KEY_INVALID = 3,   
  BUZZ_ALARM = 4,      
  BUZZ_END = 5,     
  BUZZ_DOOROPEN = 6,
  BUZZ_SILENCE = 7
}BuzzType;

#define BUZZ_NONE 0xFF

/**
 * @brief 蜂鸣器驱动函数
 * 
 * 在系统循环中调用该函数实现对蜂鸣器的实时控制
 * @param   无
 * @return  无 
 */
void Buzz_Control(void);

/**
 * @brief 蜂鸣器控制
 * 
 * 设置蜂鸣器的蜂鸣类型,系统下一个循环将按照设置的蜂鸣器蜂鸣类型驱动蜂鸣器按照蜂鸣类型
 * 定义的方式蜂鸣一次.
 * @param  type:蜂鸣类型
 * @return 无
 */

void Buzz_SetType(BuzzType type);

void Init_Buzz(void);

#endif

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
#ifndef _LEDRAM_H_
#define _LEDRAM_H_
/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
#ifndef NULL
#define NULL    0
#endif
//DDRCOM
#define DDRCOM_DDRON	0x80	//显示驱动扫描开关
#define DDRCOM_DMOD		0x40	//LED模式
#define DDRCOM_DUTY_8DIV		0x00	//分频选择 00:1/8 01:1/6 10:1/5 11:1/4
#define DDRCOM_DUTY_6DIV		0x10
#define DDRCOM_DUTY_5DIV		0x20
#define DDRCOM_DUTY_4DIV		0x30
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
typedef enum 
{
    PVO0 = 0,
    PVO1 = 1,
    PVO2 = 2,
    PVO3 = 3,
    PVO_NULL
}ePvo;

#define PVO_PIN_0  ((unsigned char)0x01)
#define PVO_PIN_1  ((unsigned char)0x02)
#define PVO_PIN_2  ((unsigned char)0x04)
#define PVO_PIN_3  ((unsigned char)0x08)
#define PVO_PIN_4  ((unsigned char)0x10)
#define PVO_PIN_5  ((unsigned char)0x20)
#define PVO_PIN_6  ((unsigned char)0x40)
#define PVO_PIN_7  ((unsigned char)0x80)


typedef struct 
{
    /* data */
    ePvo port;
    unsigned char pin;
}SegRam_InitTypeDef;
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
extern unsigned char xdata LCDRAM[28];
void SegRam_Init(SegRam_InitTypeDef *SegRam);
void SegRam_Clear(void);

#endif //_LEDRAM_H_

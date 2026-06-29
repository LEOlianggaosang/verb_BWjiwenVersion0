/**
 *******************************************************************************
 * Copyright (c) 20250423
 *  
 * @file    PWM.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _PWM_H_
#define _PWM_H_


/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
/*PWMFCG*/
#define CLOCK_SOURCE 	0x00
#define CLOCK_SOURCE_DIV_2	0x40
#define CLOCK_SOURCE_DIV_8	0x80
#define CLOCK_SOURCE_DIV_32	0xC0
#define PWM_INV5	0x20
#define PWM_INV4	0x10
#define PWM_INV3	0x08
#define PWM_INV2	0x04
#define PWM_INV1	0x02
#define PWM_INV0	0x01
/*PWMCON*/
#define PWM_CLOCK_EN	0x80
#define PWM_INT_EN		0x40
#define PWM5_IO_EN		0x20
#define PWM4_IO_EN		0x10
#define PWM3_IO_EN		0x08
#define PWM2_IO_EN		0x04
#define PWM1_IO_EN		0x02
#define PWM0_IO_EN		0x01

/*
*******************************************************************************
**  Macro define//PWM0N/00~07
*******************************************************************************
*/

/*IE1*/
#define IE1_EPWM			0x02
/*IP1*/
#define IP1_IPPWM			0x02
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
extern void PWM_Init( void );
extern void PWM_Start( void );
extern void PWM_Stop( void );

#endif 

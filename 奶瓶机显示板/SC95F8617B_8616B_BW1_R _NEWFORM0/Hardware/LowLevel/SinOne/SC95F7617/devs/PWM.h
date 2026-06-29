/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
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
**	Register bit define//PWM40-53
*******************************************************************************
*/
/*PWMMOD*/
#define PWMMOD_PWMMD_SUPP	0x08
#define PWMMOD_PWMMD_SOLO	0x00
#define PWMMOD_PWMMD_MIDD	0x04
#define PWMMOD_PWMMD_SIDE	0x00
/*PWMFCG*/
#define PWMFCG_ENPWM				0x80
#define PWMFCG_PWMIF				0x40
#define PWMFCG_ENPCK_32M		0x00
#define PWMFCG_ENPCK_16M		0x10
#define PWMFCG_ENPCK_8M			0x20
#define PWMFCG_ENPCK_4M			0x30
/*PWMCON*/
/*1040-104f*/
#define ENPxy								0x8000
#define INVxy								0x4000
/*
*******************************************************************************
**	Register bit define//PWM2/3/4
*******************************************************************************
*/
/*TXINX*/
#define PIONT_TIMER2_TO_PWM2	0x02
#define PIONT_TIMER3_TO_PWM3	0x03
#define PIONT_TIMER4_TO_PWM4	0x04
/*TXCON*/
#define TXCON_WMX_WORK	0x04
/*TXMOD*/
#define TXMOD_ENPWMX1	0x20
#define TXMOD_ENPWMX0	0x10
#define TXMOD_ENINVPWMX1	0x08
#define TXMOD_ENINVPWMX0	0x04
/*RCAPXH*/
/*RCAPXL*/
/*PDTX0H*/
/*PDTX0L*/
/*PDTX1H*/
/*PDTX1L*/
/*
*******************************************************************************
**  Macro define//PWM0N/00~07
*******************************************************************************
*/
/*PWMCON0*/
#define PWMCON0_ENPWM				0x80
#define PWMCON0_PWMIF				0x40
#define PWMCON0_ENPCK_32M		0x00
#define PWMCON0_ENPCK_16M		0x10
#define PWMCON0_ENPCK_8M		0x20
#define PWMCON0_ENPCK_4M		0x30
#define PWMCON0_PWMMD_SUPP	0x10
//#define PWMCON0_PWMMD_SOLO	0x00
#define PWMCON0_PWMMD_SIDE	0x00
#define PWMCON0_PWMMD_MIDD	0x01
/*PWMFCG*/
#define PWMCFG_PWMX_INVX			0x40
/*PWMCON1*/
#define PWMCON1_ENPWM00		0x01
#define PWMCON1_ENPWM01		0x02
#define PWMCON1_ENPWM02		0x04
#define PWMCON1_ENPWM03		0x08
#define PWMCON1_ENPWM04		0x10
#define PWMCON1_ENPWM05		0x20
#define PWMCON1_ENPWM06		0x40
#define PWMCON1_ENPWM07		0x80
/*PWMPDL*/
/*PWMPDH*/
/*IE1*/
#define IE1_EPWM			0x02
/*IP1*/
#define IP1_IPPWM			0x02

/*PWMFLT*/

/*PWMDFR*/
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
extern void PWM_Init( void );
extern void PWM_Start( void );
extern void PWM_Stop( void );

#endif 

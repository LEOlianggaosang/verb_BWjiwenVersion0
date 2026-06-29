/**
 *******************************************************************************
 * Copyright (c) 2024.9.11
 *  
 * @file    ExternalInterrupt.h
 * @author  lianggaosang@qq.com
 * @brief
 *
 *******************************************************************************
 */
#ifndef _EXTERNAL_INTERRUPT_H_
#define _EXTERNAL_INTERRUPT_H_

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void INTP_Init( void );
typedef void (* intc_callback)(void);
extern intc_callback intc_func;
extern void Intc_Set_Callback(intc_callback func);

#endif

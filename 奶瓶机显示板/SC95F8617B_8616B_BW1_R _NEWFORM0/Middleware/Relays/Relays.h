/**
 *******************************************************************************
 * Copyright (c) 2022
 *
 * @file    Relays.h
 * @author  Chen Jianjun (cjj5424@163.com)
 * @brief   继电器控制
 *
 *******************************************************************************
 */
#ifndef _RELAYS_H_
#define _RELAYS_H_

#include "GpioDrv.h"
#include "user_define.h"

/**
 * @name 继电器使能标志位
 * 控制继电器的通断
 */
///@{
#define  RELAY_HEAT_ENABLE    Relay_Enables.f_bits.no0    ///<加热器使能
#define  RELAY_WP_ENABLE      Relay_Enables.f_bits.no1    ///<洗涤使能
#define  RELAY_DR_ENABLE      Relay_Enables.f_bits.no2    ///<排水使能
#define  RELAY_IV_ENABLE      Relay_Enables.f_bits.no3    ///<进水使能
#define  RELAY_PTC_ENABLE     Relay_Enables.f_bits.no4    ///<PTC 使能
#define  RELAY_SV_ENABLE      Relay_Enables.f_bits.no5    ///<软水器使能
#define  RELAY_DV_ENABLE      Relay_Enables.f_bits.no6    ///<分配器使能
#define  RELAY_HALF_ENABLE    Relay_Enables.f_bits.no7    ///<半载阀使能
///@}

#define PORT_PTC      P54           //Todo: PTC?
#define PORT_WP       P03           //washing pump
#define PORT_DR       P04           //drain pump
#define PORT_IV       P51           //inlet value
#define PORT_SV       P52           //soften
#define PORT_DV       P53           //distribute
#define PORT_HALF     P50           //half relay

//继电器使能
extern ByteFlag Relay_Enables;

/**
 * @brief 继电器驱动
 * 除加热器,加热器有专门的方波驱动函数
 * @param 无
 * @return 无
 */
void Relay_Drive(void);

void Relay_Drive_4ms_do(void);//故障修改2.16  继电器闭合和断开延时

void Init_Relays(void);
#endif
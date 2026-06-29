
#ifdef SC95F8617_ENABLED
#include "..\SC95F861x_C.H"
unsigned int xdata PWMRD_40  _at_  0x1040;
unsigned int xdata PWMRD_41  _at_  0x1042;
unsigned int xdata PWMRD_42  _at_  0x1044;
unsigned int xdata PWMRD_43  _at_  0x1046;
unsigned int xdata PWMRD_50  _at_  0x1048;
unsigned int xdata PWMRD_51  _at_  0x104A;
unsigned int xdata PWMRD_52  _at_  0x104C;
unsigned int xdata PWMRD_53  _at_  0x104E;
#endif
#ifdef SC95F8616B_ENABLED
#include "..\SC95F861xB_C.H"
unsigned int xdata PWMREG[14] _at_ 0x2034;	
#endif

#include "intrins.h"
#include "user_define.h"
#include "PWM.H"

#define PWM_T	0x0FA0//(16M//4KHZ)
#define PWM_ON_50	0x07D0//(16M//4KHZ)

#define PWM_32M_T	0x1F40//(32M//4KHZ)
#define PWM_32M_ON_50	0x0FA0//(32M//4KHZ)

void PWM_Init(void);
void PWM_Start(void);
void PWM_Stop(void);
/*****************************************************
*函数名称：void PWM_Init(void)
*函数功能：PWM初始化
*入口参数：void
*出口参数：void
*****************************************************/
void PWM_Init(void)
{
#ifdef SC95F8617_ENABLED
	PWMMOD = 0x00;           //Independent Mode and edge alignment mode
	PWMCON = LOW_8BITS(PWM_T);//The period shared by PWM sets the low 8 bits
	PWMCFG = PWMFCG_ENPWM|PWMFCG_ENPCK_16M|HIGH_8BITS(PWM_T);//bit7:switch control  bit5-4：Clock Source Selector  bit3-0: The period of the PWM is set to the upper four bits
	PWMRD_52 = PWM_ON_50;
	
	IE1 &= ~IE1_EPWM;
	IP1 &= ~IP1_IPPWM;
//*****************************************************
//	//PWM waveform: set the period to 50us and duty cycle to 50% 
//  PWMMOD = 0x00;           //Independent Mode and edge alignment mode
//	PWMCON = 0x3F;           //The period shared by PWM sets the low 8 bits: 50us
//  PWMCFG = 0x86;           //bit7:switch control  bit5-4：Clock Source Selector  bit3-0: The period of the PWM is set to the upper four bits
//	PWMRD_41 = 0x8000 | 0x320;  //Enable PWM41 waveform output.Set duty cycle
//  IE1 |= 0x02;        //Enable PWM interrupt
//	//PWM waveform: set the period to 50us and duty cycle to 50% 
//  PWMMOD = 0x0C;           //Complementary Model and center alignment mode 
//	PWMCON = 0x3F;           //The period shared by PWM sets the low 8 bits: 50us
//  PWMCFG = 0x86;           //bit7:switch control  bit5-4：Clock Source Selector  bit3-0: The period of the PWM is set to the upper four bits
//	PWMRD_40 = 0x8000 | 0x320;     //Enable PWM40 waveform output.Set duty cycle.
//  PWMRD_41 = 0xC000 | 0x320;     //Enable PWM41 waveform output.Set duty cycle.Set PWM41 waveform output reverse
//  PWMDFR = 0x88;                 //rising edge dead time:4*PWMDFR[3:0]/fHRC      PWM falling edge dead time:4*PWMDFR[7:4]/fHRC
//  IE1 |= 0x02;        //Enable PWM interrupt
#endif
//*****************************************************
#ifdef SC95F8616B_ENABLED
	//pwm30//timer3//p24
  TXINX = 0x03;     //TimerX寄存器组指向TIM3
  THX = 0X00;     //计数器高8位清零
  TLX =  0x00;    //计数器低8位清零
  TXMOD |= 0x10;      //使能PWM30波形输出,不使能PWM31波形输出，不反向
  RCAPXH = HIGH_8BITS(PWM_32M_T);      //配置周期寄存器高8位
  RCAPXL = LOW_8BITS(PWM_32M_T);      //配置周期寄存器低8位
  PWMREG[2] = PWM_32M_ON_50;      //配置PWM30占空比
//  TXCON |= 0x04;        //使能PWM3
  IE1 &= ~0x40;         //关闭PWM3中断
//*****************************************************
//	PWMCON0 = PWMCON0_ENPCK_16M|PWMCON0_PWMMD_SIDE;    //7:开关 6:中断  5-4：时钟源选择  3-0：工作模式
//	PWMCFG = 0x00;																		//PWM01不反向
//	PWMCON1 |= 0x02;      														//PWM01输出
//  PWMPDL = LOW_8BITS(PWM_T);      									//周期配置低8位
//  PWMPDH = HIGH_8BITS(PWM_T);      									//周期配置高8位
//	PWMREG[7] = PWM_ON_50;      													//PWM01占空比
//	IE1 &= ~IE1_EPWM;
//	IP1 &= ~IP1_IPPWM;
//*****************************************************
//	  //设置了周期为100us，占空比为50%的PWM0波形
//  //pwm02，PWM03独立输出
//  PWMCON0 = 0x00;     //分频系数设置为1分频，独立模式，边沿对齐
//  PWMCFG |= 0x04;     //PWM02不反向，PWM03反向
//  PWMCON1 |= 0x0C;      //PWM02，PMW03输出
//  PWMPDL = 0x80;      //周期配置低8位
//  PWMPDH = 0x0C;      //周期配置高8位
//  PWMREG[8] = 0x640;      //PWM02占空比
//  PWMREG[9] = 0x640;      //PWM03占空比	
//  PWMCON0 |= 0x80;     //使能PWM0
//  IE1 |= 0x02;        //开启中断标志位
//  //设置了周期为500us，占空比为50%的PWM2波形
//  TXINX = 0x02;     //TimerX寄存器组指向TIM2
//  THX = 0X00;     //计数器高8位清零
//  TLX =  0x00;    //计数器低8位清零
//  TXMOD |= 0x30;      //使能PWM20，PWM21波形输出
//  TXMOD |= 0x08;      //PWM21输出反向
//  RCAPXH = 0x3E;      //配置周期寄存器高8位
//  RCAPXL = 0x80;      //配置周期寄存器低8位
//  PWMREG[0] = 0x1F40;      //配置PWM20占空比
//  PWMREG[1] = 0x1F40;      //配置PWM21占空比
//  TXCON |= 0x04;        //使能PWM2
//  ET2 = 0;        //关闭PWM2中断
//  //设置了周期为1000us，占空比为50%的PWM3波形
//  TXINX = 0x03;     //TimerX寄存器组指向TIM3
//  THX = 0X00;     //计数器高8位清零
//  TLX =  0x00;    //计数器低8位清零
//  TXMOD |= 0x30;      //使能PWM30，PWM31波形输出
//  TXMOD |= 0x08;      //PWM31输出反向
//  RCAPXH = 0x7D;      //配置周期寄存器高8位
//  RCAPXL = 0x00;      //配置周期寄存器低8位
//  PWMREG[2] = 0x3E80;      //配置PWM30占空比
//  PWMREG[3] = 0x3E80;      //配置PWM31占空比
//  TXCON |= 0x04;        //使能PWM3
//  IE1 &= ~0x40;         //关闭PWM3中断
//  //设置了周期为2ms，占空比为50%的PWM4波形
//  TXINX = 0x04;     //TimerX寄存器组指向TIM4
//  THX = 0X00;     //计数器高8位清零
//  TLX =  0x00;    //计数器低8位清零
//  TXMOD |= 0x30;      //使能PWM40，PWM41波形输出
//  TXMOD |= 0x80;      //PWM41输出反向
//  RCAPXH = 0xFA;      //配置周期寄存器高8位
//  RCAPXL = 0x00;      //配置周期寄存器低8位
//  PWMREG[4] = 0x7D00;      //配置PWM40占空比
//  PWMREG[5] = 0x7D00;      //配置PWM41占空比
//  TXCON |= 0x04;        //使能PWM4
//  IE1 &= ~0x40;         //关闭PWM4中断
#endif
}
/*****************************************************
*函数名称：void PWM_Start(void)
*函数功能：PWM启动
*入口参数：void
*出口参数：void
*****************************************************/
void PWM_Start(void)
{
#ifdef SC95F8617_ENABLED
//    PWMCFG |= PWMFCG_ENPWM;           //7:开关  
		PWMRD_52 |= ENPxy;
#endif
#ifdef SC95F8616B_ENABLED
//		PWMCON0 |= PWMCON0_ENPWM;      
		static unsigned char temp = 0;
		temp = TXINX;
	  TXINX = 0x03;//pwm30
		TXCON |= TXCON_WMX_WORK;
		TXINX	= temp;
#endif
}
/*****************************************************
*函数名称：void PWM_Stop(void)
*函数功能：PWM停止
*入口参数：void
*出口参数：void
*****************************************************/
void PWM_Stop(void)
{
	
#ifdef SC95F8617_ENABLED
//    PWMCFG &= ~(PWMFCG_ENPWM);           //7:开关
		PWMRD_52 &= ~(ENPxy);
#endif
#ifdef SC95F8616B_ENABLED
//		PWMCON0 &= ~(PWMCON0_ENPWM);
		static unsigned char temp = 0;
		temp = TXINX;
	  TXINX = 0x03;//pwm30
		TXCON &= ~(TXCON_WMX_WORK);
		TXINX	= temp;
#endif
}
///*****************************************************
//*函数名称：void PWM_Init(void)
//*函数功能：PWM0故障检测初始化
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void PWM_FLT_Init()
//{
//  PWMFLT = 0xB3;       //开启中断检测，立即模式，故障检测高电平有效，滤波时间为16us
//}

///*****************************************************
//*函数名称：void PWM_Interrup() interrupt 8
//*函数功能：PWM0中断服务函数
//*入口参数：void
//*出口参数：void
//*****************************************************/
//void PWM0_Interrup() interrupt 8
//{
//  if(PWMCON0 & 0x40)
//  {
//    PWMCON0 &= ~0x40;  //清除中断标志位
//    P00 = ~P00;
//  }
//}
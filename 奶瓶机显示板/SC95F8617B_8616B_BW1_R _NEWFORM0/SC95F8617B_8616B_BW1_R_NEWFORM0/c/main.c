#include "H/Function_Init.H"

/**************************************************************
说明：
1、Options for Target‘Target1’：BL51 Locate->Code Range:0x100，烧录选项请选择DISRST，复位脚作为普通IO使用；
2、改变TEST的定义，可以分别测试对应的功能；
3、注意：先在Function.H里面选择测试型号
4、版本：V1.1
***************************************************************/
#define Test 5    //BTM:0 EXTI:1 Timer:2 LCD_LED:3 PWM:4 Uart0:5 USCI0:6 USCI1:7 USCI2:8 ADC:9 IAP:10 Multiplier_Divider:11 CMP:12 CRC:13

void main(void)
{
	IO_Init();
  
//	WDTCON |= 0x10;		    //清看门狗
	switch(Test)
	{
		case 0: BTM_Test();				//BTM 低频定时器
		break;
		case 1: EXTI_Test();			//EXTI 外部中断
		break;
		case 2: Timer_Test();			//定时器
		break;
		case 3: LCD_LED_Test();		//LED 
		break;
		case 4: PWM_Test();				//PWM
		break;
		case 5: Uart_Test();			//串口
		break;
		case 6: USCI0_Test();			//三选一通用串行接口
		break;
		case 7: USCI1_Test();
		break;
		case 8: USCIX_Test();
		break;
		case 9: ADC_Test();			//ADC
		break;
		case 10: IAP_Test();
		break;
		case 11: Multiplier_Divider_Test(); //硬件乘除法
		break;
		case 12: CMP_Test();			//模拟比较器
		break;
		case 13: CRC_Test();			//硬件CRC计算
		break;
		default:
		break;
	}
}


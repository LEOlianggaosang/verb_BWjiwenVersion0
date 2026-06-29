#include "H/Function_Init.H"
#include "CRC_Lib/CRC_Option_EW.h"

char Array[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
unsigned long int temp = 0x00;  //最终结果
unsigned long CRC_Result;

void CRC_Software(char array[]);

/*****************************************************
*函数名称：void CRC_Test(void)
*函数功能：CRC测试
*入口参数：void
*出口参数：void
*****************************************************/
void CRC_Test(void)
{
    //硬件APPROM区域校验
    CRC_Result = CRC_CodeAllOption();
    //软件自定义输入校验
    CRC_Software(Array);
	
		while(1);
}


/*****************************************************
*函数名称：void CRC_Software(char array[])
*函数功能：CRC软件校验
*入口参数：void
*出口参数：void
*****************************************************/
void CRC_Software(char array[])
{
    int i = 0;
	
    CRC_ResetDROption(); //CRCDR寄存器复位
	
	  for(i=0;i<16;i++)
	  {
	    CRC_CalcOption(array[i]); //对指定的CRC数据进行计算
	  }
		
    temp = CRC_GetOption();     //最终运算结果

}
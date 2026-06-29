#include "H/Function_Init.H"

//选择三合一模式：
#define  Uart1  0
#define  TWI    1
#define  SPI    2

#define  SSI_Mode  Uart1
#define SPI_Mode 1 //0:主机工作模式   1：从机工作模式

void Uart1_Init(uint Freq,unsigned long int baud);
void TWI_Init(void);
void SPI_Init(void);

bit Uart1SendFlag = 0;    //Uart发送中断标志位
bit Uart1ReceiveFlag = 0; //Uart接收中断标志位
bit SPIFlag = 0;          //SPI数据传输完成标志位
bit TWIFlag = 0;          //中断标志位
uint8_t TxXferCount1 = 0;  //SPI发送数据数目
uint8_t RxXferCount1 = 0;  //SPI接受数据数目
uint8_t Uart1_RxData[5];
uint8_t SPI1_Master_SendData[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
volatile uint8_t SPI1_Slaver_ReceiveData[8];
/*****************************************************
*函数名称：void SSI_Test(void)
*函数功能：SSI测试
*入口参数：void
*出口参数：void
*****************************************************/
void SSI_Test(void)
{
#if (SSI_Mode == Uart1)
	int num1,num2;
	Uart1_Init(12,9600);
	while(1)
	{
		  for(num1=0;num1<5;num1++)
			{
				while(!Uart1ReceiveFlag);
				Uart1ReceiveFlag = 0;
				Uart1_RxData[num1] = SSDAT ;
			}
			for(num2=0;num2<5;num2++)
			{
				SSDAT  = Uart1_RxData[num2];
				while(!Uart1SendFlag);
				Uart1SendFlag = 0;
			}
	}
#endif
	
#if (SSI_Mode == TWI)
	TWI_Init();
	while(1)
	{
	}
#endif

#if (SSI_Mode == SPI)
		SPI_Init();
	while(1)
	{
#if (SPI_Mode == 0)  //主机
				TxXferCount1 = 0;
				while(TxXferCount1 <  8)//判断是否接收所有数据
				{
				 
					SSDAT = SPI1_Master_SendData[TxXferCount1];
					while(!SPIFlag);
		      SPIFlag = 0;	
					TxXferCount1 ++;	//发送数据量计数
				}
				{  int time = 1000;
            while(time--);
        }
#endif
#if (SPI_Mode == 1)  //从机
			while(RxXferCount1 <8)
				{
					/* 等待SPI中断标志位置起 */
					while(!SPIFlag);
	      	SPIFlag = 0;	
					SPI1_Slaver_ReceiveData[RxXferCount1] = SSDAT;			//读取数据
					RxXferCount1++;	//接收数据量计数加1       
				}
				RxXferCount1 = 0;
				{  int time = 100;
           while(time--);
        }

#endif
	
	}
#endif	
}
/*****************************************************
*函数名称：void Uart1_Init(uint Freq,unsigned long int baud)
*函数功能：Uart1中断初始化
*入口参数：Freq-主频，baud-波特率
*出口参数：void
*****************************************************/
void Uart1_Init(uint Freq,unsigned long int baud)
{
	P2CON &= 0xFC;   //TX/RX设置为输入带上拉
	P2PH  |= 0x03;
	
	OTCON |= 0xC0;    //串行接口SSI选择Uart1通信
	SSCON0 = 0x50;   //设置通信方式为模式一，允许接收
	SSCON1 = Freq*1000000/baud;   //波特率低位控制
	SSCON2 = (Freq*1000000/baud)>>8;   //波特率高位控制
	IE1 |= 0x01;      //开启SSI中断
    EA = 1;	
}

/*****************************************************
*函数名称：void TWI_Init(void)
*函数功能：TWI初始化
*入口参数：void
*出口参数：void
*****************************************************/
void TWI_Init(void)
{
	OTCON |= 0x80;  //选择TWI模式
	SSCON0 = 0x80;  // ---- x---  0为不允许接收，1为允许接收
	SSCON1 = 0x01;  //xxxx xxxy  x为地址寄存器，y为0禁止/1允许通用地址响应
	IE1 |= 0x01;
	EA = 1;
}

/*****************************************************
*函数名称：void SPI_Init(void)
*函数功能：SPI初始化
*入口参数：void
*出口参数：void
*****************************************************/
void SPI_Init(void)
{
	OTCON |= 0X40;  //选择SPI模式
#if (SPI_Mode == 0)	
 {  SSCON0 = 0x2F; }   //设置SPI为主设备，SCK空闲时间为低电平，SCK周期第二沿采集数据，时钟速率为Fsys/512  
#elif (SPI_Mode == 1)	
 {  SSCON0 = 0x0F;   }   //设置SPI为从设备，SCK空闲时间为低电平，SCK周期第二沿采集数据，时钟速率为Fsys/512  
#endif 
  SSCON1 = 0x00;   //不允许发送中断
	SSCON0 |= 0x80; //开启SPI
	IE1 |= 0x01;
	EA = 1;
}


/*****************************************************
*函数名称：void TWI/SPI/UART1_Int() interrupt 7
*函数功能：SSI中断函数
*入口参数：void
*出口参数：void
*****************************************************/
#if (SSI_Mode == Uart1)
void Uart1_Int() interrupt 7   //Uart1中断函数
{
	if(SSCON0&0x02)    //发送标志位判断
	{
		SSCON0 &= 0xFD;
		Uart1SendFlag = 1;
	}
	if((SSCON0&0x01))  //接收标志位判断
	{
		SSCON0 &= 0xFE;
		Uart1ReceiveFlag = 1;
	}	
}
#endif

#if (SSI_Mode == TWI)
void TWI_Int() interrupt 7     //TWI中断函数
{
	if(SSCON0&0x40)
	{
		SSCON0 &= 0xbf;  //中断清零
		TWIFlag = 1;
	}	
}
#endif 

#if (SSI_Mode == SPI)
void SpiInt(void) interrupt 7    //SPI中断函数
{	  
	if(SSCON1&0X08)    //发送缓存器空标志判断
	{
		SSCON1 &= ~0X08;
	}
	if(SSCON1&0X80)    //数据传输标志位判断
	{
		SSCON1 &= ~0X80;
		SPIFlag = 1;
	}
}
#endif 
#include "H/Function_Init.H"

//选择三合一模块：
#define  USCI2   2
#define  USCI3   3
#define  USCI4   4
#define  USCI5   5

//选择三合一模式：
#define  UartX   0
#define  TWIX    1
#define  SPIX    2

#define  USCIX_Select USCI3
#define  USCIX_Mode  SPIX
#define TWIX_Mode 0//0:主机工作模式   1：从机工作模式
#define SPIX_Mode 0 //0:主机工作模式   1：从机工作模式
void UARTX_Init(uint Freq, unsigned long int baud);
void TWIX_Init(void);
void SPIX_Init(void);

bit UartXSendFlag = 0;    //UartX发送中断标志位
bit UartXReceiveFlag = 0; //UartX接收中断标志位
bit SPIXFlag = 0;         //SPIX数据传输完成标志位
bit TWIXFlag = 0;         //TWIX中断标志位

uint8_t TxXferCountX = 0;  //SPI/TWI发送数据数目
uint8_t RxXferCountX = 0;  //SPI/TWI接受数据数目

volatile uint8_t UartX_RxData[5];
uint8_t SPIX_Master_SendData[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
volatile uint8_t SPIX_Master_ReceiveData[8];
uint8_t SPIX_Slaver_SendData[8] = {0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
volatile uint8_t SPIX_Slaver_ReceiveData[8];

uint8_t TWIX_Master_SendData[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
volatile uint8_t TWIX_Master_ReceiveData[8];
uint8_t TWIX_Slaver_SendData[8]={0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
volatile uint8_t TWIX_Slaver_ReceiveData[8];

/*****************************************************
*函数名称：void USCIX_Test(void)
*函数功能：USCIX测试
*入口参数：void
*出口参数：void
*****************************************************/
void USCIX_Test(void)
{
  USXINX = USCIX_Select;       //USCIX寄存器指向对应的USCI

//判断三合一模式
#if (USCIX_Mode == UartX)
  {
		int num1,num2;
    UARTX_Init(32, 9600);      //初始化串口，输入主频和波特率
    while(1)
    {
      for(num1=0;num1<5;num1++)
		{
			while(!UartXReceiveFlag);
			UartXReceiveFlag = 0;
			UartX_RxData[num1] = USXCON3 ;
		}
		for(num2=0;num2<5;num2++)
		{
			USXCON3  = UartX_RxData[num2];
	  	while(!UartXSendFlag);
      UartXSendFlag = 0;
		}     //清除发送标志位
    }
  }
#elif (USCIX_Mode == TWIX)
  {
    TWIX_Init();
    while(1)
    
	#if (TWIX_Mode == 0)  //主机接收数据
			{
				USXCON1 |= 0x20;    //产生起始条件	
				while(TWIXFlag == 0);
				TWIXFlag = 0; 
				USXCON3 = 0x02|0X01;	    //发送地址及写命令
				while(TWIXFlag == 0);
				TWIXFlag = 0; 

		/* 数据接收过程 */
				do
				{
						if(RxXferCountX ==7)
					{
							USXCON0 &= 0XF7;    	
					}
				
					 while(TWIXFlag == 0);
					 TWIXFlag = 0; 
					 TWIX_Master_ReceiveData[RxXferCountX] = USXCON3;             //TWI接收数据
					 RxXferCountX++;	
				}
				while(RxXferCountX < 8);
			
			 RxXferCountX=0;
				/* 无论是否发送完成，都需要发送结束信号，防止主机占用总线 */
			 USXCON0 |= 0X08; //AA使能位,回主机UAC
			 USXCON1 |= 0x10;
			 Delay(500);
			}
	#endif
	#if (TWIX_Mode == 1)  //从机  
		 {  
			  TWIXFlag = 0; 
			 while((0x07 & USXCON0)!=0x00);//判断状态是否回到空闲状态
			 
			  while((0x07 & USXCON0)!=0x03);//判断状态是否发送状态
			  while(TWIXFlag == 0);
			 TWIXFlag = 0; 
			TxXferCountXTWIXFlag=0;
			 while(TxXferCountX < 8)
			 {

				USXCON3 = TWIX_Slaver_SendData[TxXferCountX];             //TWI发送数据
				while(TWIXFlag == 0);
				TWIXFlag = 0; 
				TxXferCountX++;

			 }
				USXCON3 = TWIX_Slaver_SendData[0];
			 
			 while((0x07 & USXCON0)!=0x00);//判断状态是否回到空闲状态

				TxXferCountX=0;
				Delay(100);
			 }
	#endif
	
   }  
#elif (USCIX_Mode == SPIX)
  {
    SPIX_Init();
    while(1)
    {
     #if (SPIX_Mode == 0)  //主机
	   TxXferCountX = 0;
    while(TxXferCountX <  8)//判断是否接收所有数据
    {
     
      USXCON2 = SPIX_Master_SendData[TxXferCountX];
      

      while(SPIXFlag == 0);	//等待发送完成
		 
      SPIXFlag = 0;		
      SPIX_Master_ReceiveData[TxXferCountX]=USXCON2;
      TxXferCountX ++;	//发送数据量计数
    
		}
		Delay(1000);;
		

     #elif (SPIX_Mode == 1) //从机
 
 
	   while(RxXferCountX <8)
    {
			 USXCON2=SPIX_Slaver_SendData[RxXferCountX];
      /* 等待SPI中断标志位置起 */
      
			while(SPIXFlag == 0);	//等待发送完成
		   
      SPIXFlag = 0;		
      SPIX_Slaver_ReceiveData[RxXferCountX] = USXCON2;			//读取16位数据,并且地址自增
      RxXferCountX++;	//接收数据量计数加1
      
      }
		 Delay(100);
	  RxXferCountX = 0;
		
     #endif
    
    }
  }
#endif

}


/*****************************************************
*函数名称：void UARTX_Init(uint Freq,unsigned long int baud)
*函数功能：UartX中断初始化
*入口参数：Freq-主频，baud-波特率
*出口参数：void
*****************************************************/
void UARTX_Init(uint Freq, unsigned long int baud)
{
  TMCON |= 0xC0;    //串行接口USCIX选择Uart通信
#if (USCIX_Select == USCI2)

  P4CON &= ~0x30;
  P4PH |= 0x30;
  IE2 |= 0x02;      //开启中断
#elif (USCIX_Select == USCI3)
  P2CON &= ~0xC0;
  P2PH |= 0xC0;
  IE2 |= 0x04;      //开启中断
#elif (USCIX_Select == USCI4)
  P4CON &= ~0xC0;
  P4PH |= 0xC0;
  IE2 |= 0x08;     //开启中断
#elif (USCIX_Select == USCI5)
  P0CON &= ~0x0C;
  P0PH |= 0x0C;
  IE2 |= 0x10;     //开启中断
#endif

  USXCON0 = 0x50;   //设置通信方式为模式一，允许接收
  USXCON1 = Freq * 1000000 / baud; //波特率低位控制
  USXCON2 = (Freq * 1000000 / baud) >> 8; //波特率高位控制

  EA = 1;
}

/*****************************************************
*函数名称：void TWIX_Init(void)
*函数功能：TWIX初始化
*入口参数：void
*出口参数：void
*****************************************************/
void TWIX_Init(void)
{
  TMCON |= 0x80;    //串行接口USCIX选择TWI通信
#if (USCIX_Select == USCI2)
  P4CON &= ~0x18;
  P4PH |= 0x18;
  IE2 |= 0x02;      //开启中断
#elif (USCIX_Select == USCI3)
  P2CON &= ~0x60;
  P2PH |= 0x60;
  IE2 |= 0x04;      //开启中断
#elif (USCIX_Select == USCI4)
  P5CON &= ~0x20;
  P5PH |= 0x20;
  P4CON &= ~0x70;
  P4PH |= 0x70;
  IE2 |= 0x08;     //开启中断
#elif (USCIX_Select == USCI5)
  P0CON &= ~0x06;
  P0PH |= 0x06;
  IE2 |= 0x10;     //开启中断
#endif
	#if (TWIX_Mode == 0)	
 { USXCON3 = TWIX_Slaver_SendData[0];   }   //从机预先准备好数据
 #endif
  TMCON |= 0x80;   //选择TWIX模式
  USXCON0 = 0x88;  //主模式， 使能应答标志位
  USXCON1 = 0x40;  //---- xxxx  x为时钟速率,开启延展
  USXCON2 = 0x02;  //从机地址
  IE2 |= 1 << (USCIX_Select - 1);    //开启中断
  EA = 1;
}

/*****************************************************
*函数名称：void SPIX_Init(void)
*函数功能：SPIX初始化
*入口参数：void
*出口参数：void
*****************************************************/
void SPIX_Init(void)
{
  TMCON |= 0x40;    //串行接口USCIX选择SPI通信
#if (USCIX_Select == USCI2)
  P4CON &= ~0x38;
  P4PH |= 0x38;
  IE2 |= 0x02;      //开启中断
#elif (USCIX_Select == USCI3)
  P2CON &= ~0xE0;
  P2PH |= 0xE0;
  IE2 |= 0x04;      //开启中断
#elif (USCIX_Select == USCI4)
  P5CON &= ~0x20;
  P5PH |= 0x20;
  P4CON &= ~0xC0;
  P4PH |= 0xC0;
  IE2 |= 0x08;     //开启中断
#elif (USCIX_Select == USCI5)
  P0CON &= ~0x0E;
  P0PH |= 0x0E;
  IE2 |= 0x10;     //开启中断
#endif
  TMCON |= 0X40;    //选择SPIX模式
#if (SPIX_Mode == 0)	
 {  USXCON0 = 0x23;   }   //设置SPIX为主设备，SCK空闲时间为低电平，SCK周期第一沿采集数据，时钟速率为Fsy/8
#elif (SPIX_Mode == 1)	
 {  USXCON0 = 0x03; }   //设置SPIX为从设备，SCK空闲时间为低电平，SCK周期第一沿采集数据，时钟速率为Fsy/8
#endif 
  USXCON1 = 0x00;   //MSB优先发送，8位传输
  USXCON0 |= 0x80;  //开启SPIX
  IE2 |= 1 << (USCIX_Select - 1);    //开启中断
  EA = 1;
}

#if (USCIX_Select == USCI2)
/*****************************************************
*函数名称：void TWI2/SPI2/UART2_Int() interrupt 7
*函数功能：USCI2中断函数
*入口参数：void
*出口参数：void
*****************************************************/
#if (USCIX_Mode == UartX)
void UART2_Int() interrupt 16   //UartX中断函数
{
  if(USXCON0 & 0x02)  //发送标志位判断
  {
    USXCON0 &= 0xFE;
    UartXSendFlag = 1;
  }
  if((USXCON0 & 0x01)) //接收标志位判断
  {
    USXCON0 &= 0xFD;
    UartXReceiveFlag = 1;
  }
}
#elif (USCIX_Mode == TWIX)
void TWI2_Int() interrupt 16     //TWIX中断函数
{
  if(USXCON0 & 0x40)
  {
    USXCON0 &= 0xbf;  //中断清零
    TWIXFlag = 1;
  }
}
#elif (USCIX_Mode == SPIX)
void SPI2Int(void) interrupt 16    //SPIX中断函数
{
  if(USXCON1 & 0X08)  //发送缓存器空标志判断
  {
    USXCON1 &= ~0X08;
  }
  if(USXCON1 & 0X80)  //数据传输标志位判断
  {
    USXCON1 &= ~0X80;
    SPIXFlag = 1;
  }
}
#endif
#elif (USCIX_Select == USCI3)
/*****************************************************
*函数名称：void TWI3/SPI3/UART3_Int() interrupt 7
*函数功能：USCI2中断函数
*入口参数：void
*出口参数：void
*****************************************************/
#if (USCIX_Mode == UartX)
void UART3_Int() interrupt 17   //UartX中断函数
{
  if(USXCON0 & 0x02)  //发送标志位判断
  {
    USXCON0 &= 0xFE;
    UartXSendFlag = 1;
  }
  if((USXCON0 & 0x01)) //接收标志位判断
  {
    USXCON0 &= 0xFD;
    UartXReceiveFlag = 1;
  }
}
#elif (USCIX_Mode == TWIX)
void TWI3_Int() interrupt 17     //TWIX中断函数
{
  if(USXCON0 & 0x40)
  {
    USXCON0 &= 0xbf;  //中断清零
    TWIXFlag = 1;
  }
}
#elif (USCIX_Mode == SPIX)
void SPI3_Int(void) interrupt 17    //SPIX中断函数
{
  if(USXCON1 & 0X08)  //发送缓存器空标志判断
  {
    USXCON1 &= ~0X08;
  }
  if(USXCON1 & 0X80)  //数据传输标志位判断
  {
    USXCON1 &= ~0X80;
    SPIXFlag = 1;
  }
}
#endif
#elif (USCIX_Select == USCI4)
/*****************************************************
*函数名称：void TWI4/SPI4/UART4_Int() interrupt 7
*函数功能：USCI2中断函数
*入口参数：void
*出口参数：void
*****************************************************/
#if (USCIX_Mode == UartX)
void UART4_Int() interrupt 18   //UartX中断函数
{
  if(USXCON0 & 0x02)  //发送标志位判断
  {
    USXCON0 &= 0xFE;
    UartXSendFlag = 1;
  }
  if((USXCON0 & 0x01)) //接收标志位判断
  {
    USXCON0 &= 0xFD;
    UartXReceiveFlag = 1;
  }
}
#elif (USCIX_Mode == TWIX)
void TWI4_Int() interrupt 18     //TWIX中断函数
{
  if(USXCON0 & 0x40)
  {
    USXCON0 &= 0xbf;  //中断清零
    TWIXFlag = 1;
  }
}
#elif (USCIX_Mode == SPIX)
void SPI4_Int(void) interrupt 18   //SPIX中断函数
{
  if(USXCON1 & 0X08)  //发送缓存器空标志判断
  {
    USXCON1 &= ~0X08;
  }
  if(USXCON1 & 0X80)  //数据传输标志位判断
  {
    USXCON1 &= ~0X80;
    SPIXFlag = 1;
  }
}
#endif

#elif (USCIX_Select == USCI5)
#if (USCIX_Mode == UartX)
void UART5_Int() interrupt 19   //UartX中断函数
{
  if(USXCON0 & 0x02)  //发送标志位判断
  {
    USXCON0 &= 0xFE;
    UartXSendFlag = 1;
  }
  if((USXCON0 & 0x01)) //接收标志位判断
  {
    USXCON0 &= 0xFD;
    UartXReceiveFlag = 1;
  }
}
#elif (USCIX_Mode == TWIX)
void TWI5_Int() interrupt 19     //TWIX中断函数
{
  if(USXCON0 & 0x40)
  {
    USXCON0 &= 0xbf;  //中断清零
    TWIXFlag = 1;
  }
}
#elif (USCIX_Mode == SPIX)
void SPI5_Int(void) interrupt 19   //SPIX中断函数
{
  if(USXCON1 & 0X08)  //发送缓存器空标志判断
  {
    USXCON1 &= ~0X08;
  }
  if(USXCON1 & 0X80)  //数据传输标志位判断
  {
    USXCON1 &= ~0X80;
    SPIXFlag = 1;
  }
}
#endif

#endif

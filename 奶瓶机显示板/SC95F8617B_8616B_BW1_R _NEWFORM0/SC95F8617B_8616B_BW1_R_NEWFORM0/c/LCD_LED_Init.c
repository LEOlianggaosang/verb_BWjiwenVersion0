#include "H/Function_Init.H"

unsigned char xdata LCDRAM[28]  _at_  0x2000;
void LCD_Init(void);
void LED_Init(void);
void PxVO_Init(void);
	
/*****************************************************
*function: void LCD_LED_Test(void)
*brief: Test LCD/LED
*param: void
*retval: void
*****************************************************/
void LCD_LED_Test(void)
{
	LCD_Init();
//	LED_Init();
	while(1)
	{
	}
}

/*****************************************************
*function: void LCD_Init(void)
*brief: LCD initialization
*param: void
*retval: void
*****************************************************/
void LCD_Init(void)
{
	unsigned int i;
	DDRCON = 0x8F;    //-xyy zzzz    x:LCD/LED mode y:Duty    z:LCD voltage regulation
	PxVO_Init();
	OTCON |= 0x04;    //---- xxyz    x:LCD divider resistance   y:Multiplex pin selection    z:LCD bias voltage
	for(i=0; i<8; i++)
	{
		LCDRAM[i] = 0xff;
	}
}

/*****************************************************
*function: void LED_Init(void)
*brief: LED initialization
*param: void
*retval: void
*****************************************************/
void LED_Init(void)
{
	unsigned int i;
	DDRCON = 0xC0;    //-xyy zzzz  x:LCD/LED mode    y:Duty 1/8:00 1/6:01 1/5:10 1/4:11    z:LCD voltage regulation
	PxVO_Init();
	OTCON |= 0x00;    //---- xxyz  x:LCD divider resistance   y:Multiplex pin selection   z:LCD bias voltage
	for(i=0; i<8; i++)
	{
		LCDRAM[i] = 0xff;
	}
}

/*****************************************************
*function: void PxVO_Init(void)
*brief: Display Driver Output initialization
*param: void
*retval: void
*****************************************************/
void PxVO_Init(void)
{
	P0VO = 0xFF;
	P1VO = 0xFF;
	P2VO = 0xFF;
	P3VO = 0xFF;
}
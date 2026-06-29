/*--------------------------------------------------------------------------
*file:  SC95F861x_C.H
*brief:  C Header file for SC95F861x microcontroller.
*author:  Shenzhen SinOne Microelectronics Co., Ltd.
*version:  V1.0    
*date:  2021.12.09
*attention:  Copyright (c) 2021 Shenzhen SinOne Microelectronics Co., Ltd.
            All rights reserved
--------------------------------------------------------------------------*/
#ifndef _SC95F861x_H_
#define _SC95F861x_H_

/* ------------------- Byte_registers-------------------- */
///*CPU*/
sfr   ACC	  = 0xE0;		//Accumulator
sfr   B     = 0xF0;	  //B register 		
sfr   PSW	  = 0xD0;		//Program status word register	
sfr   DPS	  = 0x86;		//DPTR selection register	
sfr   DPH1  = 0x85;		//DPTR1 data pointer high	
sfr   DPL1  = 0x84;		//DPTR1 data pointer low	
sfr   DPH	  = 0x83;		//DPTR data pointer high
sfr   DPL	  = 0x82;		//DPTR data pointer low	
sfr   SP	  = 0x81;		//Stack pointer
		

/*system*/
sfr   PCON	= 0x87;		//Power management control register

/*interrupt*/
sfr   IP2   = 0XBA;   //Interrupt priority control register 2
sfr   IP1   = 0XB9;   //Interrupt priority control register 1
sfr   IP	  = 0xB8;		//Interrupt priority control register
sfr   IE	  = 0xA8;		//Interrupt enable register
sfr   IE1   = 0XA9;  	//Interrupt enable register 1
sfr   IE2   = 0XAA;  	//Interrupt enable register 2

/*PORT*/
sfr   P5PH	  = 0xDA;	//P5 port pull-up resistor control register	
sfr	  P5CON	  = 0xD9;	//P5 port input/output control register
sfr   P5	    = 0xD8;	//P5 port data register
sfr   P4PH	  = 0xC2;	//P4 port pull-up resistor control register	
sfr	  P4CON	  = 0xC1;	//P4 port input/output control register
sfr   P4	    = 0xC0;	//P4 port data register
sfr   P3PH	  = 0xB2;	//P3 port pull-up resistor control register
sfr	  P3CON	  = 0xB1;	//P3 port input/output control register
sfr   P3	    = 0xB0;	//P3 port data register
sfr   P2PH	  = 0xA2;	//P2 port pull-up resistor control register
sfr	  P2CON	  = 0xA1;	//P2 port input/output control register
sfr   P2	    = 0xA0;	//P2 port data register
sfr   P1PH    = 0x92;	//P1 port pull-up resistor control register
sfr	  P1CON	  = 0x91;	//P1 port input/output control register
sfr   P1	    = 0x90;	//P1 port data register
sfr	  P0PH	  = 0x9B;	//P0 port pull-up resistor control register
sfr	  P0CON	  = 0x9A;	//P0 port input/output control register
sfr   P0	    = 0x80;	//P0 port data register
sfr   IOHCON0 = 0x96;	//IOH setting register 0
sfr   IOHCON1 = 0x97;	//IOH setting register 1

/*TIMER*/
sfr   TMCON	  = 0x8E; //Timer frequency control register
sfr   TH1	    = 0x8D; //Timer 1 high 8 bits
sfr   TH0	    = 0x8C;	//Timer 0 high 8 bits
sfr   TL1	    = 0x8B;	//Timer 1 low 8 bits
sfr   TL0	    = 0x8A;	//Timer 1 low 8 bits
sfr   TMOD	  = 0x89;	//Timer operating mode register
sfr   TCON	  = 0x88;	//Timer control register
sfr   TXCON   = 0xC8; //Timer 2/3/4 control register
sfr   TXMOD   = 0xC9; //Timer 2/3/4 operating mode register
sfr   RCAPXL  = 0xCA; //Timer 2/3/4 reload low 8 bits
sfr   RCAPXH  = 0xCB; //Timer 2/3/4 reload high 8 bits
sfr   TLX     = 0xCC; //Timer 2/3/4 low 8 bits
sfr   THX     = 0xCD; //Timer 2/3/4 high 8 bits
sfr   TXINX   = 0xCE; //Timer control register pointer

/*ADC*/
sfr	  ADCCFG0 = 0xAB;	//ADC setting register 0
sfr	  ADCCFG1 = 0xAC;	//ADC setting register 1
sfr	  ADCCFG2 = 0xB5;	//ADC setting register 2
sfr   ADCCON  = 0XAD; //ADC control register
sfr   ADCVL	  = 0xAE;	//ADC Conversion value register (low bit) 
sfr   ADCVH	  = 0xAF;	//ADC Conversion value register (High bit) 

/*PWM*/
sfr   PWMMOD  = 0xD7;	//PWM mode setting register
sfr   PWMFLT  = 0xD6;	//PWM fault detection setting register
sfr   PWMDFR  = 0xD5;	//PWM dead time setting register
sfr   PWMCFG  = 0xD4;	//PWM setting register
sfr   PWMCON  = 0xD3;	//PWM control register

///*WatchDog*/
sfr   BTMCON  = 0XFB; //Low frequency timer control register
sfr   WDTCON  = 0xCF;	//WDT control register


/*LCD*/
sfr   OTCON   = 0X8F;	//Output control register
sfr   P0VO    = 0X9C; //P0 port display driver output registe
sfr   P1VO    = 0X94; //P1 port display driver output registe
sfr   P2VO    = 0XA3; //P2 port display driver output registe
sfr   P3VO    = 0XB3; //P3 port display driver output registe

sfr   DDRCON  = 0X93; //Display drive control register


/*INT*/
sfr   INT0F   = 0XB4; //INT0 falling edge interrupt control register
sfr   INT0R   = 0XBB; //INT0 rising edge interrupt control register
sfr   INT1F   = 0XBC; //INT1 falling edge interrupt control register
sfr   INT1R   = 0XBD; //INT1 rising edge interrupt control register
sfr   INT2F   = 0XBE; //INT2 falling edge interrupt control register
sfr   INT2R   = 0XBF; //INT2 rising edge interrupt control register

/*IAP */
sfr   IAPCTL  = 0xF6;	//IAP control register
sfr   IAPDAT  = 0xF5;	//IAP data register
sfr   IAPADE  = 0xF4; //IAP write to extended address register
sfr   IAPADH  = 0xF3;	//IAP write address high register
sfr   IAPADL  = 0xF2;	//IAP write address low register
sfr   IAPKEY  = 0xF1;	//Data protection register

/*UART*/
sfr   SCON    = 0X98; //Serial control register
sfr   SBUF    = 0X99; //Serial data buffer register

/*USCI0*/
sfr   US0CON0 = 0X95; //USCI0 control register 0
sfr   US0CON1 = 0X9D; //USCI0 control register 1
sfr   US0CON2 = 0X9E; //USCI0 control register 2
sfr   US0CON3 = 0X9F; //USCI0 control register 3

/*USCI1*/
sfr   US1CON0 = 0XA4; //USCI1 control register 0
sfr   US1CON1 = 0XA5; //USCI1 control register 1
sfr   US1CON2 = 0XA6; //USCI1 control register 2
sfr   US1CON3 = 0XA7; //USCI1 control register 3

/*USCI2*/
sfr   US2CON0 = 0XC4; //USCI2 control register 0
sfr   US2CON1 = 0XC5; //USCI2 control register 1
sfr   US2CON2 = 0XC6; //USCI2 control register 2
sfr   US2CON3 = 0XC7; //USCI2 control register 3

sfr   OPINX   = 0XFE; 
sfr   OPREG   = 0XFF;
sfr   EXADH   = 0XF7;

/*模拟比较器*/
sfr   CMPCFG  = 0XB6;	//Analog comparator setting register
sfr   CMPCON  = 0XB7;	//Analog Comparator Control Register

/*乘除法器*/
sfr   EXA0    = 0xE9; //Extended Accumulator 0
sfr   EXA1    = 0xEA; //Extended Accumulator 1
sfr   EXA2    = 0xEB; //Extended Accumulator 2
sfr   EXA3    = 0xEC; //Extended Accumulator 3
sfr   EXBL    = 0xED; //Extended B register L
sfr   EXBH    = 0xEE; //Extended B register H
sfr   OPERCON = 0xEF; //Arithmetic control register

/* CRC校验 */
sfr   CRCINX  = 0xFC;
sfr   CRCREG  = 0xFD;

/* ------------------- Bit_registers-------------------- */
/*PSW*/
sbit  CY	    = PSW^7; /*Flag:		 1: When there is a carry in the highest bit of addition, or a borrow in the highest bit of subtraction
                                   0: When there is no carry in the highest bit of addition, or there is no borrow in the highest bit of subtraction*/
sbit  AC	    = PSW^6; /*Carry auxiliary flag:	1: When the addition operation has a carry in bit3, or the subtraction operation has a borrow in bit3
                                                0: No borrowing, carry*/
sbit  F0	    = PSW^5; //User flag
sbit  RS1	    = PSW^4; //Operating register group selection bits
sbit  RS0	    = PSW^3; //Operating register group selection bits
sbit  OV	    = PSW^2; //Overflow flag
sbit  F1	    = PSW^1; //F1 sign
sbit  P	      = PSW^0; //Parity flag:   1: The number of 1s in ACC is odd      0: The number of 1s in ACC is even (including 0)

/*TXCON*/
sbit  TFX     = TXCON^7;
sbit  EXFX    = TXCON^6;
sbit  RCLKX   = TXCON^5;
sbit  TCLKX   = TXCON^4;
sbit  EXENX   = TXCON^3;
sbit  TRX	    = TXCON^2;
sbit  TX      = TXCON^1;
sbit  CP      = TXCON^0;

/*IP*/
sbit  IPADC	  = IP^6;	//ADC interrupt priority selection:           0: ADC interrupt priority is low     1: ADC interrupt priority is high
sbit  IPT2	  = IP^5;	//Timer2 interrupt priority selection:        0: Timer2 interrupt priority is low  1: Timer2 interrupt priority is high
sbit  IPUART  = IP^4;	//UART interrupt priority selection:          0: UART interrupt priority is low    1: UART interrupt priority is high
sbit  IPT1	  = IP^3;	//Timer1 interrupt priority selection:        0: Timer1 interrupt priority is low  1: Timer1 interrupt priority is high
sbit  IPINT1  = IP^2;	//INT1 counter interrupt priority selection:  0: INT1 interrupt priority is low    1: INT1 interrupt priority is high
sbit  IPT0	  = IP^1;	//Timer0 interrupt priority selection:        0: Timer0 interrupt priority is low  1: Timer0 interrupt priority is high
sbit  IPINT0  = IP^0; //INT0 counter interrupt priority selection:  0: INT0 interrupt priority is low    1: INT0 interrupt priority is high

/*IE*/
sbit  EA	    = IE^7;	//Interrupt enable total control:       0: Close all interrupts      1: Enable all interrupts
sbit  EADC    = IE^6;	//ADC interrupt enable control:         0: Disable ADC interrupt     1: Allow the ADC to generate an interrupt when the conversion is complete
sbit  ET2     = IE^5;	//Timer2 interrupt enable control:      0: Disable Timer2 interrupt  1: Enable Timer2 interrupt
sbit  EUART   = IE^4;	//UART interrupt enable control:        0: Disable UART interrupt    1: Allow UART interrupt
sbit  ET1     = IE^3;	//Timer1 interrupt enable control:      0: Disable Timer             1 interrupt1: Enable Timer1 interrupt
sbit  EINT1   = IE^2;	//External interrupt 1 enable control:  0: close INT1 interrupt      1: Enable INT1 interrupt
sbit  ET0	    = IE^1;	//Timer0 interrupt enable control:      0: Disable TIMER0 interrupt  1: Enable TIMER0 interrupt
sbit  EINT0   = IE^0;	//External interrupt 0 enable control:  0: close INT0 interrupt      1: Enable INT0 interrupt


/*TCON*/
sbit  TF1	  = TCON^7;	//T1 overflow interrupt request flag. T1 generates an overflow. When an interrupt occurs, the hardware sets TF1 to "1" and applies for an interrupt. When the CPU responds, the hardware clears "0".
sbit  TR1	  = TCON^6;	//Operation control bit of timer T1:	0:T1 counting is prohibited		1:T1 is allowed to start counting
sbit  TF0	  = TCON^5;	//T0 overflow interrupt request flag. T0 overflows. When an interrupt occurs, the hardware sets TF0 to "1" and applies for an interrupt. When the CPU responds, the hardware clears "0".
sbit  TR0	  = TCON^4;	//Operation control bit of timer T0:	0:T0 counting is prohibited		1:T0 is allowed to start counting

/*SCON*/
sbit  SM0	  = SCON^7;
sbit  SM1	  = SCON^6;
sbit  SM2	  = SCON^5;
sbit  REN	  = SCON^4;
sbit  TB8	  = SCON^3;
sbit  RB8	  = SCON^2;
sbit  TI	  = SCON^1;
sbit  RI	  = SCON^0;

/******************* P0 ******************
*SC95F8617 chip packaging did not lead to the pin: None
*SC95F8616 chip packaging did not lead to the pin: None
*SC95F8615 chip packaging did not lead to the pin: P00/P01/P02/P03
*SC95F8613 chip packaging did not lead to the pin: P00/P01/P02/P03
*SC95F8612 chip packaging did not lead to the pin: P00/P01/P02/P03
******************************************/
sbit 	P07	= P0^7;
sbit 	P06	= P0^6;
sbit 	P05	= P0^5;
sbit 	P04	= P0^4;
sbit 	P03	= P0^3;
sbit 	P02	= P0^2;
sbit 	P01	= P0^1;
sbit 	P00	= P0^0;

/******************* P1 ******************
*SC95F8617 chip packaging did not lead to the pin: None
*SC95F8616 chip packaging did not lead to the pin: None
*SC95F8615 chip packaging did not lead to the pin: P14/P15/P16/P17
*SC95F8613 chip packaging did not lead to the pin: P14/P15/P16/P17
*SC95F8612 chip packaging did not lead to the pin: P14/P15/P16/P17
******************************************/
sbit 	P17	= P1^7;
sbit 	P16	= P1^6;
sbit 	P15	= P1^5;
sbit 	P14	= P1^4;
sbit 	P13	= P1^3;
sbit 	P12	= P1^2;
sbit 	P11	= P1^1;
sbit 	P10	= P1^0;

/******************* P2 ******************
*SC95F8617 chip packaging did not lead to the pin: None
*SC95F8616 chip packaging did not lead to the pin: None
*SC95F8615 chip packaging did not lead to the pin: None
*SC95F8613 chip packaging did not lead to the pin: None
*SC95F8612 chip packaging did not lead to the pin: P24/P25/P26/P27
******************************************/
sbit 	P27	= P2^7;
sbit 	P26	= P2^6;
sbit 	P25	= P2^5;
sbit 	P24	= P2^4;
sbit 	P23	= P2^3;
sbit 	P22	= P2^2;
sbit 	P21	= P2^1;
sbit 	P20	= P2^0;

/******************* P3 ******************
*SC95F8617 chip packaging did not lead to the pin: None
*SC95F8616 chip packaging did not lead to the pin: None
*SC95F8615 chip packaging did not lead to the pin: P34/P35/P36/P37
*SC95F8613 chip packaging did not lead to the pin: P34/P35/P36/P37
*SC95F8612 chip packaging did not lead to the pin: P3
******************************************/
sbit 	P37	= P3^7;
sbit 	P36	= P3^6;
sbit 	P35	= P3^5;
sbit 	P34	= P3^4;
sbit 	P33	= P3^3;
sbit 	P32	= P3^2;
sbit 	P31	= P3^1;
sbit 	P30	= P3^0;

/******************* P4 ******************
*SC95F8617 chip packaging did not lead to the pin: None
*SC95F8616 chip packaging did not lead to the pin: P46/P47
*SC95F8615 chip packaging did not lead to the pin: P46/P47
*SC95F8613 chip packaging did not lead to the pin: P46/P47
*SC95F8612 chip packaging did not lead to the pin: P46/P47
******************************************/
sbit 	P47	= P4^7;
sbit 	P46	= P4^6;
sbit 	P45	= P4^5;
sbit 	P44	= P4^4;
sbit 	P43	= P4^3;
sbit 	P42	= P4^2;
sbit 	P41	= P4^1;
sbit 	P40	= P4^0;

/******************* P5 ******************
*SC95F8617 chip packaging did not lead to the pin: None
*SC95F8616 chip packaging did not lead to the pin: P54/P55
*SC95F8615 chip packaging did not lead to the pin: P54/P55
*SC95F8613 chip packaging did not lead to the pin: P5
*SC95F8612 chip packaging did not lead to the pin: P5
******************************************/
sbit 	P55	= P5^5;
sbit 	P54	= P5^4;
sbit 	P53	= P5^3;
sbit 	P52	= P5^2;
sbit 	P51	= P5^1;
sbit 	P50	= P5^0;

/****************************************************************************
*attention: If chip packaging did not lead to the pin, it needs to be set to strong push-pull output mode
*IC: After initializing the I/O port,Call the corresponding function that does not elicit a pin.
*If you choose SC95F8617 chip, the function is not called.
*****************************************************************************/                                    
#define  SC95F8616_NIO_Init()   {P4CON|=0xC0,P5CON|=0x30;}                                                 //SC95F8616 IO pin configuration that is not elicited
#define  SC95F8615_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P3CON|=0xF0,P4CON|=0xC0,P5CON|=0x30;}             //SC95F8615 IO pin configuration that is not elicited
#define  SC95F8613_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P3CON|=0xF0,P4CON|=0xC0,P5CON|=0x3F;}             //SC95F8613 IO pin configuration that is not elicited
#define  SC95F8612_NIO_Init()   {P0CON|=0x0F,P1CON|=0xF0,P2CON|=0xF0,P3CON|=0xFF,P4CON|=0xC0,P5CON|=0x3F;} //SC95F8612 IO pin configuration that is not elicited
#endif
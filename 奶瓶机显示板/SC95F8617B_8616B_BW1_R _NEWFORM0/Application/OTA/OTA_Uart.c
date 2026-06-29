/***********************************************************************************************************************
* File Name    : OTA_Uart.c
* Version      : 
* Device(s)    : R5F100LE
* Tool-Chain   : CA78K0R
* Description  : 
* Creation Date: 2021/7/5
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "SerialDrv.h"    
#include "product_config.h"

#define _OTA_UART_C
#include "OTA_Uart.h"

#if CONFIG_OTA==1
extern volatile uint32_t Timer_MonotonicClock;
extern void OtaRecInit(void);
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: 
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void OtaInit(void)
{
	fw_checksum = 0;
	fw_addr_offset = 0;
	fw_buf_cnt = 0;
	file_len = 0;
	file_checksum = 0;
}

/***********************************************************************************************************************
* Function Name: OtaSendData
* Description  : This function is INTST0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void OtaSendData(uint8_t* buf,uint8_t len)
{
/*    if (0U < len)
    {
        txd_num = len;
        txd_cnt = 0;
        p_txd_fuf = buf;
        TXD2 = p_txd_fuf[txd_cnt++];
    }
*/
	 Uart_SendData(SERIAL_BLDC_OR_DEBUG, buf, len);
}

/***********************************************************************************************************************
* Function Name: OtaDecode
* Description  : This function is INTST0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void OtaDecode(void)
{
  static uint32_t timer_counter = 0;	
	fsl_u08 ret;
	uint16_t od_i,checksum;
	fsl_write_t write_cfg;
	pfdl_status_t fdl_ret;
	uint8_t FDL_buf[UPDATA_MSG_SIZE];
	
	if(REC_OK==GetReceivedStatus()){
		if(0x99==rxd_buf[1]){
			if(0x00==rxd_buf[2]){		/* 升级请求 */
				if(0x01==rxd_buf[3]){	
					if(0x9A==rxd_buf[4]){		/* 升级请求 */
						ret = Boot_FSL_Erase(35,27);
						
						if(FSL_OK==ret){
							OtaInit();
							
							txd_buf[0] = 0xA5;
							txd_buf[1] = 0x99;
							txd_buf[2] = 0x00;
							txd_buf[3] = 0x06;
							txd_buf[4] = 0x9F;
							txd_buf[5] = 0x5A;
							OtaSendData(txd_buf,6);
						}
					}
				}
			}
			else if(0x06==rxd_buf[2]){	/* 固件文件信息 */
				checksum = (uint16_t)rxd_buf[10];
				if(checksum==(uint8_t)(Get16BitCusum((__far uint8_t *)(&rxd_buf[1]),9))){				
					file_len = ((uint32_t)rxd_buf[4]<<24) + ((uint32_t)rxd_buf[5]<<16) + ((uint32_t)rxd_buf[6]<<8) + (uint32_t)rxd_buf[7];
					file_checksum =  ((uint16_t)rxd_buf[8]<<8) + (uint16_t)rxd_buf[9];
					
					txd_buf[0] = 0xA5;
					txd_buf[1] = 0x99;
					txd_buf[2] = 0x00;
					txd_buf[3] = 0x06;
					txd_buf[4] = 0x9F;
					txd_buf[5] = 0x5A;
					OtaSendData(txd_buf,6);
				}
				else{
					OtaInit();
				}
			}
		}
		else if(0x88==rxd_buf[1]){		/* 接收数据 */
			od_i = ((uint16_t)rxd_buf[2]) + 4;
			checksum = rxd_buf[od_i];
			od_i--;
			if(checksum==(uint8_t)(Get16BitCusum((__far uint8_t *)(&rxd_buf[1]),od_i))){	
				for(od_i=0;od_i<=rxd_buf[2];od_i++)
				{
					fw_write_buf[fw_buf_cnt++] = rxd_buf[3+od_i];
					fw_checksum += rxd_buf[3+od_i];
					
					if(file_len>=(fw_addr_offset+0x100UL)){		/* 判断剩余末写数据长度是否大于一次最大写入长度 */
						if(0x100<=fw_buf_cnt){		
							/* 写入缓存满256字节，进行一次写入 */
							ret = Boot_FSL_Write((FW_START_ADDR + fw_addr_offset),fw_write_buf,64);
							
							if(FSL_OK!=ret){
								/* 写入失败 */
								OtaInit();
							}
							
							fw_addr_offset += fw_buf_cnt;
							fw_buf_cnt = 0;
						}
					}
					else{
						if(file_len==(fw_addr_offset+fw_buf_cnt)){
							od_i = (uint8_t)(fw_buf_cnt%4);
							
							if(0!=od_i){		
								od_i = 4 - od_i;										
								while(0 < od_i){
									fw_write_buf[fw_buf_cnt++] = 0xFF;
									od_i--;
								}
							}
							
							ret = Boot_FSL_Write((FW_START_ADDR + fw_addr_offset),fw_write_buf,(fw_buf_cnt/4));
							
							if(FSL_OK!=ret){
								/* 写入失败 */
								OtaInit();
							}
							
							fw_addr_offset += fw_buf_cnt;
							fw_buf_cnt = 0;
							break;
						}
					}
				}
				
				txd_buf[0] = 0xA5;
				txd_buf[1] = 0x88;
				txd_buf[2] = 0x00;
				txd_buf[3] = 0x08;
				txd_buf[4] = 0x90;
				txd_buf[5] = 0x5A;
				OtaSendData(txd_buf,6);
			}
			else{
				OtaInit();
			}
		}
		else if(0x77==rxd_buf[1]){		/* 数据接收结束 */
			if(fw_checksum==file_checksum){			
				DI();
				Boot_FDL_Open();
				fdl_ret = Boot_FDL_Erase(0);
				if(PFDL_OK == fdl_ret){
					
					FDL_buf[0] = 0xAA;
					FDL_buf[1] = 0x01;
					FDL_buf[2] = (uint8_t)(file_len>>24);
					FDL_buf[3] = (uint8_t)(file_len>>16);
					FDL_buf[4] = (uint8_t)(file_len>> 8);
					FDL_buf[5] = (uint8_t)(file_len);
					FDL_buf[6] = (uint8_t)(file_checksum>> 8);     
					FDL_buf[7] = (uint8_t)(file_checksum);         
					FDL_buf[8] = (uint8_t)(Get16BitCusum((__far uint8_t *)(&FDL_buf[0]),8));
					FDL_buf[9] = 0x55;
					
					fdl_ret = Boot_FDL_Write(UPDATA_MSG_ADDR,FDL_buf,UPDATA_MSG_SIZE);
				}
				Boot_FDL_Close();			
				EI();
				
				txd_buf[0] = 0xA5;
				txd_buf[1] = 0x77;
				txd_buf[2] = 0x00;
				txd_buf[3] = 0x06;
				txd_buf[4] = 0x7D;
				txd_buf[5] = 0x5A;
				OtaSendData(txd_buf,6);
				
				if(PFDL_OK==fdl_ret){
					while(1);		/* 下载完成，重启进入BOOT进行APP区更新 */
				}
				else{
					OtaInit();
				}
			}
		}
		
		OtaRecInit();
		//Uart_ReceiveData(SERIAL_BLDC_OR_DEBUG, rxd_buf, sizeof(rxd_buf));
	}
	else
	{
		/*if (Timer_MonotonicClock - timer_counter >= OneSecondCount)
		{
			timer_counter = Timer_MonotonicClock;
				txd_buf[0] = 0xA5;
				txd_buf[1] = 0x88;
				txd_buf[2] = 0xA5;
				txd_buf[3] = 0x88;
				txd_buf[4] = 0x90;
				txd_buf[5] = 0x5A;
				OtaSendData(txd_buf,6);			
		}*/
	}
}

/***********************************************************************************************************************
* Function Name: GetCusum
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint16_t Get16BitCusum(__far uint8_t *buf,uint16_t num)
{
	uint16_t cusum,cnt;
	for(cusum=0,cnt=0;cnt<num;cnt++)
	{
		cusum += buf[cnt];
	}
	
	return(cusum);
}

#endif

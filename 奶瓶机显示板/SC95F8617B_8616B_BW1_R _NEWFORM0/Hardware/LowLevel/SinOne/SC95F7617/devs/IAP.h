#ifndef __IAP_H_INCLUDED
#define __IAP_H_INCLUDED

/*----------------------------------------------------------------------------------------------*/
/* function prototypes                                                                          */
/*----------------------------------------------------------------------------------------------*/

/*==============================================================================================*/
/* constant definitions                                                                         */
/*==============================================================================================*/


/*----------------------------------------------------------------------------------------------*/
/* switch variable for conditional compiling                                                    */
/* (comment out if backup not required, but please be careful                                   */
/* and take necessary countermeasures in your application)                                      */
/*----------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------*/
/* user function prototypes                                                                    */
/*----------------------------------------------------------------------------------------------*/
#define BLOCK_MAX_LENGTH    33
#ifdef SC95F8617_ENABLED
#define IAP_FLASH_START_ADDR	0XFC00
#define IAP_AREA_VALUE	0X00
#endif
#ifdef SC95F8616B_ENABLED
#define IAP_APROM 0x00
#define IAP_UniqueID 0x01
#define IAP_EEPROM 0x02
#define IAP_LDROM 0x03
#define IAP_FLASH_START_ADDR	0X0000
#define IAP_AREA_VALUE	IAP_EEPROM
#endif
extern void IAP_eepromSaveData(unsigned char *WByte, unsigned char NumByte);
extern void IAP_eepromRestoreData(unsigned char *dataPtr, unsigned char NumByte);
extern unsigned char IAPRead(unsigned long Add, unsigned char Iapade);
#endif

#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "EEPROM.h"
#include "define.h"

/**
  * @brief EEPROM write function.
  * @param[in] The data you want to write to EEPROM.
  * It can be 0x00~0xff.
  * @param[in] Specifies EEPROM address.
  * It can be 0x00~0x3f.
  * @retval None
  */
void EEPROM_Write_Byte(u8 Data,u8 adr)
{
	u8 TempEMI;
	
	TempEMI = _emi;
	
	/*config EEPROM init*/
	_dmbp0 = 1;			
	
	_mp1 = 0x40;
	
	/*config EEPROM address*/
	_eea = adr;	
	/*Write data*/
	_eed = Data;
	
	_emi = 0;		//disable global interrupt	
	/*config EEPROM Write mode*/
	_iar1 |= 0x08;
	_iar1 |= 0x04;
	_emi = TempEMI;		//enable global interrupt			
	/* waitting for EEPROM write finishing */
	while(_iar1 & 0x04);
	_iar1 = 0;
	_dmbp0 = 0;		
	return;
}
	

/**
  * @brief EEPROM read function.
  * @param[in] Specifies EEPROM address that you want to read.
  * It can be 0x00~0x3f.
  * @retval EEPROM data.
  */
u8 EEPROM_Read_Byte(u8 adr)
{
	/* config EEPROM init */
	u8 EP_Read_Data;
	_dmbp0 = 1;
	_mp1 = 0x40;
	
	/*config EEPROM address*/
	_eea = adr;
	
	/*config EEPROM Read mode*/
	_iar1 |= 0x02;
	_iar1 |= 0x01;
	
	/* waitting for EEPROM Read finishing */
	while(_iar1 & 0x01);
	_iar1 = 0;
	_dmbp0 = 0;
		
	EP_Read_Data = _eed;		//Read data
	return EP_Read_Data;			
}

void EEPROM_Init()
{ 
	u8 i =0;
	if(EEPROM_Read_Byte(2) ==255)
	{
		for(i=0;i<33;i++)
		{
		  EEPROM_Write_Byte(0,i);
		}
	}	
}

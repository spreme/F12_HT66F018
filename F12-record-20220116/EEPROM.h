#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "define.h"

void EEPROM_Write_Byte(u8 Data,u8 adr);				//EEPROM Write mode,No interrupt

u8 EEPROM_Read_Byte(u8 adr);							//EEPROM Read mode

void EEPROM_Init();

#endif
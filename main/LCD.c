//====================================================//
//													  //
//         本程序为定制液晶的使用方式，仅供参考		  //
//   	  		  									  //
//					     			  				  //
//====================================================//

#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "EEPROM.h"
#include "define.h"
#include "LCD.h"
#include "tm1628.h"



//LCD显示时间表
void rtc_lcd()
{		
	Write_DATA(WeiL_tab[7],Num_tab_7[rtc_date.hour/10]);
	Write_DATA(WeiL_tab[6],Num_tab_7[rtc_date.hour%10]);
	Write_DATA(WeiL_tab[5],Num_tab_7[rtc_date.minute/10]);
	Write_DATA(WeiL_tab[4],Num_tab_7[rtc_date.minute%10]);
	Write_DATA(WeiL_tab[3],0x00);
	Write_DATA(WeiL_tab[2],0x00);
	Write_DATA(WeiL_tab[1],0x00);
}





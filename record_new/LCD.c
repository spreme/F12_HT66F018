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


u8 col_staus = 1;				//时间点闪烁

//LCD显示时间表
void rtc_lcd()
{		
	Write_DATA(WeiL_tab[7],Num_tab_7[rtc_date.hour/10]);
/*     if(col_staus)*/
/*    {*/
        if(rtc_date.second %2 ==0)   //时间点跳动
        {
            Write_DATA(WeiL_tab[6],Num_tab_7[rtc_date.hour%10]);
        }
        else
        {
            Write_DATA(WeiL_tab[6],Num_tab_8[rtc_date.hour%10]);	
        }
/*    }*/
/*	Write_DATA(WeiL_tab[6],Num_tab_7[rtc_date.hour%10]);*/
	Write_DATA(WeiL_tab[5],Num_tab_7[rtc_date.minute/10]);
	Write_DATA(WeiL_tab[4],Num_tab_7[rtc_date.minute%10]);
	Write_DATA(WeiL_tab[3],0x00);
	Write_DATA(WeiL_tab[2],0x00);
	Write_DATA(WeiL_tab[1],0x00);
}





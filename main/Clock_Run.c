#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "EEPROM.h"
#include "define.h"

//volatile int lcd_timeout =0;		//计时


struct rtc_time rtc_date;

void rtc_init(void)
{
	rtc_date.hour = 0;
	rtc_date.minute = 0;
	rtc_date.second = 0;
}

inline void Clock_Run()
{
	
	rtc_date.second++;
	if(rtc_date.second >59)
	{ 
		rtc_date.minute++;
		rtc_date.second=0;
				
		if(rtc_date.minute >59)
		{ 
		  	rtc_date.hour++;	    
			rtc_date.minute=0;     
			if(rtc_date.hour >23)
			{	  	      
				rtc_date.hour=0;	          
			}
		
		}	
	}
}


void time_save()			//保存时间
{
	EEPROM_Write_Byte(rtc_date.hour,31);
	EEPROM_Write_Byte(rtc_date.minute,32);	

}


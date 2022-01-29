#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "Feed.h"
#include "LCD.h"
#include "Motor.h"

struct feed_record feed_plans[FEED_MAX_NUM];


u8 feed_going = 0; //执行喂食标志位			=1执行喂食（调用feed_run）


//执行喂食：按键手动  定时
u8 feed_run(struct feed_record * info)
{
	u8 weight = 0;
	
	u8 ret = 0; 				//异常


	if(info->quantity == 0)
	{
		return 0;
	}
	weight = info->quantity;

	//启动电机
	info->quantity = motor(weight, &ret);
	return ret; //异常
}


//检测是否有喂食计划
inline void feed_scan(struct feed_record * feed)
{
	struct feed_record feed_info;
	u8 i;

	for(i = 1; i < FEED_MAX_NUM + 1; i++)
	{
		//扇区大小512，但每个扇区只能使用前120字节保存喂食记录，所以需要计算出每个条目保存在eeprom的地址
		feed_info.hour = EEPROM_Read_Byte(1 + 4 * i);
		feed_info.minute = EEPROM_Read_Byte(2 + 4 * i);
		feed_info.quantity = EEPROM_Read_Byte(3 + 4 * i);

		if((feed_info.hour == rtc_date.hour) && (feed_info.minute == rtc_date.minute))
		{
//			feed_run(feed);
			
			rtc_lcd();
			feed->hour = feed_info.hour;
			feed->minute = feed_info.minute;
			feed->quantity = feed_info.quantity;
			feed->music = 1;

			feed_going = 1;
			break;
		}
	}
}

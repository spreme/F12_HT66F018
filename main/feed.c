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


u8 feed_going = 0; //ִ��ιʳ��־λ			=1ִ��ιʳ������feed_run��


//ִ��ιʳ�������ֶ�  ��ʱ
u8 feed_run(struct feed_record * info)
{
	u8 weight = 0;
	
	u8 ret = 0; 				//�쳣


	if(info->quantity == 0)
	{
		return 0;
	}
	weight = info->quantity;

	//�������
	info->quantity = motor(weight, &ret);
	return ret; //�쳣
}


//����Ƿ���ιʳ�ƻ�
inline void feed_scan(struct feed_record * feed)
{
	struct feed_record feed_info;
	u8 i;

	for(i = 1; i < FEED_MAX_NUM + 1; i++)
	{
		//������С512����ÿ������ֻ��ʹ��ǰ120�ֽڱ���ιʳ��¼��������Ҫ�����ÿ����Ŀ������eeprom�ĵ�ַ
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

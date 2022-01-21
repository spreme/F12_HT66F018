#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"

u8 key_flag = 0;

u8 key_scan(void)
{
	u16 g_nConversionValue;
	u8 key_value;
	
	ADC_ENABLE();	
	g_nConversionValue=ADC_GetChannelValue(ADC_CH0);
	
	if(g_nConversionValue>=ADC_0)
	{
		key_value=KEY_NONE;
		key_flag=0;
		return key_value;
	}
	else if(key_flag==0)
	{
		if(g_nConversionValue>=ADC_KEY_PLAY)
		{
			key_value=KEY_PLAY;
			key_flag=1;	
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_RECORD)
		{
			key_value=KEY_RECORD;
			key_flag=1;
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_FEED)
		{
			key_value=KEY_FEED;
			key_flag=1;	
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_TIME)
		{
			key_value=KEY_TIME;
			key_flag=1;
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_SET)
		{
			key_value=KEY_SET;
			key_flag=1;	
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_DOWN)
		{
			key_value=KEY_DOWN;
			key_flag=1;
			return key_value;		
		}
		else if(g_nConversionValue>=ADC_KEY_UP)
		{
			key_value=KEY_UP;
			key_flag=1;
			return key_value;			
		}	
	}

	return 0;	
}


u8 get_key_state(void)
{
	u8 key_value,key_status=0;
	
	ADC_ENABLE();	
	key_value=ADC_GetChannelValue(ADC_CH0);
	
	if(key_value>=ADC_KEY_NO)
	{
		key_status=KEY_NO;
		key_flag=0;
	}
	else if(key_flag==0)
	{
		if(key_value>=ADC_KEY_PLAY)
		{
			key_status=key_status | KEY_PLAY_E;
			key_flag=1;	
		}
		
		else if(key_value>=ADC_KEY_RECORD)
		{
			key_status=key_status | KEY_RECORD_E;
			key_flag=1;
		}
		
		else if(key_value>=ADC_KEY_FEED)
		{
			key_status=key_status | KEY_FEED_E;
			key_flag=1;	
		}
		
		else if(key_value>=ADC_KEY_TIME)
		{
			key_status=key_status | KEY_TIME_E;
			key_flag=1;
		}
		
		else if(key_value>=ADC_KEY_SET)
		{
			key_status=key_status | KEY_SET_E;
			key_flag=1;	
		}
		
		else if(key_value>=ADC_KEY_DOWN)
		{
			key_status=key_status | KEY_DOWN_E;
			key_flag=1;
		}
		
		else if(key_value>=ADC_KEY_UP)
		{
			key_status=key_status | KEY_UP_E;
			key_flag=1;
		}	
	}
	return key_status;
}


u8 key_func(void)
{
	u8 key_flag_1=0;

//	u16 up_key_tick=0;
//	u16 down_key_tick=0;
//	u16 set_key_tick=0;
//	u16 time_key_tick=0;
//	u16 feed_key_tick=0;
	u16 record_key_tick=0;
	u16 play_key_tick=0;

	u8 cur_key;
	
	cur_key=get_key_state();
	
	play_key_tick++;
	if(cur_key==KEY_PLAY_E)
	{
		if(play_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_PLAY_L;
			return key_flag_1;
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(play_key_tick<=KEY_SHORT_TIME&&play_key_tick!=0)
		{
			key_flag_1=KEY_PLAY_S;
			return key_flag_1;
		}		
		else if(play_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_PLAY_L_UP;
			return key_flag_1;
		}
		play_key_tick=0;
	}
	
	record_key_tick++;
	if(cur_key==KEY_RECORD_E)
	{
		if(record_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_RECORD_L;
			return key_flag_1;
			
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(record_key_tick<=KEY_SHORT_TIME&&record_key_tick!=0)
		{
			key_flag_1=KEY_RECORD_S;
			return key_flag_1;

		}		
		else if(record_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_RECORD_L_UP;
			return key_flag_1;

		}
		record_key_tick=0;
	}
	
//	feed_key_tick++;
//	if(cur_key==KEY_FEED_E)
//	{
//		if(feed_key_tick==KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_FEED_L;
//		}
//	}
//	else if(cur_key==KEY_NO)
//	{
//		if(feed_key_tick<=KEY_SHORT_TIME&&feed_key_tick!=0)
//		{
//			key_flag_1=KEY_FEED_S;
//		}		
//		else if(feed_key_tick>KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_FEED_L_UP;
//		}
//		feed_key_tick=0;
//	}
//
//	time_key_tick++;
//	if(cur_key==KEY_TIME_E)
//	{
//		if(time_key_tick==KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_TIME_L;
//		}
//	}
//	else if(cur_key==KEY_NO)
//	{
//		if(time_key_tick<=KEY_SHORT_TIME&&time_key_tick!=0)
//		{
//			key_flag_1=KEY_TIME_S;
//		}		
//		else if(time_key_tick>KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_TIME_L_UP;
//		}
//		time_key_tick=0;
//	}
//
//	set_key_tick++;
//	if(cur_key==KEY_SET_E)
//	{
//		if(set_key_tick==KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_SET_L;
//		}
//	}
//	else if(cur_key==KEY_NO)
//	{
//		if(set_key_tick<=KEY_SHORT_TIME&&set_key_tick!=0)
//		{
//			key_flag_1=KEY_SET_S;
//		}		
//		else if(set_key_tick>KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_SET_L_UP;
//		}
//		set_key_tick=0;
//	}
//
//	down_key_tick++;
//	if(cur_key==KEY_DOWN_E)
//	{
//		if(down_key_tick==KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_DOWN_L;
//		}
//	}
//	else if(cur_key==KEY_NO)
//	{
//		if(down_key_tick<=KEY_SHORT_TIME&&down_key_tick!=0)
//		{
//			key_flag_1=KEY_DOWN_S;
//		}		
//		else if(down_key_tick>KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_DOWN_L_UP;
//		}
//		down_key_tick=0;
//	}
//	
//	up_key_tick++;
//	if(cur_key==KEY_UP_E)
//	{
//		if(up_key_tick==KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_UP_L;
//		}
//	}
//	else if(cur_key==KEY_NO)
//	{
//		if(up_key_tick<=KEY_SHORT_TIME&&up_key_tick!=0)
//		{
//			key_flag_1=KEY_UP_S;
//		}		
//		else if(up_key_tick>KEY_LONG_TIME_SET)
//		{
//			key_flag_1=KEY_UP_L_UP;
//		}
//		up_key_tick=0;
//	}

	return 0;
}


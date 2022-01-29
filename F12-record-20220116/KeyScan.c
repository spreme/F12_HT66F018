#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"


u8 key_scan(void)
{
	u16 g_nConversionValue;
	u8 key_value;
	u8 key_flag_e = 0;

	ADC_ENABLE();	
	g_nConversionValue=ADC_GetChannelValue(ADC_CH0);
	
	if(g_nConversionValue>=ADC_0)
	{
		key_value=KEY_NONE;
		key_flag_e=0;
		return key_value;
	}
	else if(key_flag_e==0)
	{
		if(g_nConversionValue>=ADC_KEY_PLAY)
		{
			key_value=KEY_PLAY;
			key_flag_e=1;	
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_RECORD)
		{
			key_value=KEY_RECORD;
			key_flag_e=1;
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_FEED)
		{
			key_value=KEY_FEED;
			key_flag_e=1;	
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_TIME)
		{
			key_value=KEY_TIME;
			key_flag_e=1;
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_SET)
		{
			key_value=KEY_SET;
			key_flag_e=1;	
			return key_value;			
		}
		else if(g_nConversionValue>=ADC_KEY_DOWN)
		{
			key_value=KEY_DOWN;
			key_flag_e=1;
			return key_value;		
		}
		else if(g_nConversionValue>=ADC_KEY_UP)
		{
			key_value=KEY_UP;
			key_flag_e=1;
			return key_value;			
		}	
	}

	return 0;	
}





u8 get_key_state(void)
{
	u8 key_value,key_status=0;
	u8 key_flag_1=0;
	ADC_ENABLE();	
	key_value=ADC_GetChannelValue(ADC_CH0);
	
	if(key_value>=ADC_KEY_NO)
	{
		key_status=KEY_NO;
		key_flag_1=0;
	}
	else if(key_flag_1==0)
	{
		if(key_value>=ADC_KEY_PLAY)
		{
			key_status=key_status | KEY_PLAY_E;
			key_flag_1=1;	
		}
		
		else if(key_value>=ADC_KEY_RECORD)
		{
			key_status=key_status | KEY_RECORD_E;
			key_flag_1=1;
		}
		
		else if(key_value>=ADC_KEY_FEED)
		{
			key_status=key_status | KEY_FEED_E;
			key_flag_1=1;	
		}
		
		else if(key_value>=ADC_KEY_TIME)
		{
			key_status=key_status | KEY_TIME_E;
			key_flag_1=1;
		}
		
		else if(key_value>=ADC_KEY_SET)
		{
			key_status=key_status | KEY_SET_E;
			key_flag_1=1;	
		}
		
		else if(key_value>=ADC_KEY_DOWN)
		{
			key_status=key_status | KEY_DOWN_E;
			key_flag_1=1;
		}
		
		else if(key_value>=ADC_KEY_UP)
		{
			key_status=key_status | KEY_UP_E;
			key_flag_1=1;
		}	
	}
	return key_status;
}




u8 key_scan_flag=0;
u8 key_flag=0;

void key_func(void)
{
	u16 set_key_tick=0;	
	u16 up_key_tick=0;
	u16 down_key_tick=0;
	u16 time_key_tick=0;
	u16 feed_key_tick=0;
	u16 record_key_tick=0;
	u16 play_key_tick=0;
	
	u8 keep_dowm_flag;
	
	keep_dowm_flag=get_key_state();
	
	if(key_scan_flag == 0)
	{
		
		if(keep_dowm_flag == KEY_NONE)
		{
			if(set_key_tick <= KEY_SHORT_TIME && set_key_tick != 0)
			{
				key_flag = KEY_SET;
			}
			else if(set_key_tick > KEY_LONG_TIME_SET)
			{
				key_flag = KEY_SET_L_UP;
			}
			set_key_tick = 0;
		}
		else if(keep_dowm_flag == KEY_SET_E || key_flag == KEY_SET_L)
		{
			set_key_tick++;
			if(set_key_tick == KEY_LONG_TIME_SET)
			{
				key_flag = KEY_SET_L;
//				set_key_tick = 0;
			}
		}

		if(keep_dowm_flag == KEY_NONE)
		{
			if(up_key_tick <= KEY_SHORT_TIME && up_key_tick != 0)				
			{
				key_flag = KEY_UP;
				
			}
			else if(up_key_tick > KEY_LONG_TIME)
			{
				key_flag = KEY_UP_L_UP;
				
			}
			up_key_tick = 0;		
		}
		else if(keep_dowm_flag == KEY_UP_E || key_flag == KEY_UP_L)
		{
			up_key_tick++;
			if(up_key_tick == KEY_LONG_TIME)
			{
				key_flag = KEY_UP_L;
//				up_key_tick = 0;
			}
		}
		
		if(keep_dowm_flag == KEY_NONE)
		{
			if(down_key_tick <= KEY_SHORT_TIME && down_key_tick != 0)				
			{
				key_flag = KEY_DOWN;
				
			}
			else if(down_key_tick > KEY_LONG_TIME)
			{
				key_flag = KEY_DOWN_L_UP;

			}
			down_key_tick = 0;		
		}
		else if(keep_dowm_flag == KEY_DOWN_E || key_flag == KEY_DOWN_L)
		{
			down_key_tick++;
			if(down_key_tick == KEY_LONG_TIME)
			{
				key_flag = KEY_DOWN_L;
//				down_key_tick = 0;
			}
		}

		if(keep_dowm_flag == KEY_NONE)
		{
			if(record_key_tick <= KEY_SHORT_TIME && record_key_tick != 0)				
			{
				key_flag = KEY_RECORD;
			}
			else if(record_key_tick > KEY_LONG_TIME_SET)
			{
				key_flag = KEY_RECORD_L_UP;
			}
			record_key_tick = 0;
		}
		else if(keep_dowm_flag == KEY_RECORD_E || key_flag == KEY_RECORD_L)
		{
			record_key_tick++;
			if(record_key_tick == KEY_LONG_TIME_SET)
			{
				key_flag = KEY_RECORD_L;
			}
		}

			
		if(keep_dowm_flag == KEY_NONE)
		{
			if(play_key_tick <= KEY_SHORT_TIME && play_key_tick != 0)				
			{
				key_flag = KEY_PLAY;
			}
			else if(play_key_tick > KEY_LONG_TIME_SET)
			{
				key_flag = KEY_PLAY_L_UP;
			}
			play_key_tick = 0;
		}
		else if(keep_dowm_flag == KEY_PLAY_E || key_flag == KEY_PLAY_L)
		{
			play_key_tick++;
			if(play_key_tick == KEY_LONG_TIME_SET)
			{
				key_flag = KEY_PLAY_L;
//				play_key_tick = 0;
			}
		}
		
		
		if(keep_dowm_flag == KEY_NONE)
		{
			if(feed_key_tick <= KEY_SHORT_TIME && feed_key_tick != 0)				
			{
				key_flag = KEY_FEED;
			}
			else if(feed_key_tick > KEY_LONG_TIME)
			{
				key_flag = KEY_FEED_L_UP;
			}
			feed_key_tick = 0;
		}
		else if(keep_dowm_flag == KEY_FEED_E || key_flag == KEY_FEED_L)
		{
			feed_key_tick++;
			if(feed_key_tick == KEY_LONG_TIME)
			{
				key_flag = KEY_FEED_L;
//				feed_key_tick = 0;
			}
		}
	
		if(keep_dowm_flag == KEY_NONE)
		{
			if(time_key_tick <= KEY_SHORT_TIME && time_key_tick != 0)				
			{
				key_flag = KEY_TIME;
			}
			else if(time_key_tick > KEY_LONG_TIME_SET)
			{
				key_flag = KEY_TIME_L_UP;
			}
			time_key_tick = 0;
		}
		else if(keep_dowm_flag == KEY_TIME_E || key_flag == KEY_TIME_L)
		{
			time_key_tick++;
			if(time_key_tick == KEY_LONG_TIME_SET)
			{
				key_flag = KEY_TIME_L;				
//				time_key_tick = 0;
			}
		}		
		
	}

}





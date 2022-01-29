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
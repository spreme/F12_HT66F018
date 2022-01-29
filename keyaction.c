u8 KeyRead(void)//读取键的状态
{
    u16 keyAdcValue = 0;
    keyAdcValue = ADC_GetChannelValue(ADC_CH0);

	if(keyAdcValue >= ADC_0)
	{
		return KEY_NONE;
	}
	else if(keyAdcValue >= ADC_KEY_PLAY)
	{
		return KEY_PLAY;			
	}
	else if(keyAdcValue >= ADC_KEY_RECORD)
	{
		return KEY_RECORD;			
	}
	else if(keyAdcValue >= ADC_KEY_FEED)
	{
		return KEY_FEED;			
	}
	else if(keyAdcValue >= ADC_KEY_TIME)
	{
		return KEY_TIME;			
	}
	else if(keyAdcValue >= ADC_KEY_SET)
	{
		return KEY_SET;			
	}
	else if(keyAdcValue >= ADC_KEY_DOWN)
	{
		return KEY_DOWN;		
	}
	else if(keyAdcValue >= ADC_KEY_UP)
	{
		return KEY_UP;			
	}	
}

void KeyScan(void)
{
    static unsigned char LastKeypad, KeyNum, ShortKey = 0, LongKey = 0;
    static unsigned char KeyValue = KEY_NONE;
    unsigned char KeyStatus = 0;
    KeyStatus = KeyRead();
    if(LastKeypad == KEY_NONE && KeyStatus != LastKeypad)
	{                //按键刚被按下
        KeyNum = 0;
        ShortKey = 0;
        LongKey = 0;
        KeyValue = KEY_NONE;
    }
    else if(KeyStatus == LastKeypad && KeyStatus != KEY_NONE)
	{                //按键正被按着
        KeyNum++;
        if(KeyNum == KEY_LONG_TIME_SET)
		{
            ShortKey = 0;
            LongKey = 1;
            KeyValue = LastKeypad;
        }
    }
    else if(KeyStatus == KEY_NONE && KeyStatus != LastKeypad)
	{                //按键被放开
        if(KeyNum < KEY_LONG_TIME_SET && KeyNum > KEY_SHORT_TIME)
		{
            KeyNum = 0;
            ShortKey = 1;
            LongKey = 0;
            KeyValue=  LastKeypad;
        }
    }
    else
	{
        KeyNum = 0;
        ShortKey = 0;
        LongKey = 0;
        KeyValue = KEY_NONE;
    }
    LastKeypad = KeyStatus;
     
}


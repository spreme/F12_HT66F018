#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "voltage.h"

u8 voltage_low=0;

void battery_detect(void)
{
	if(DC_DET==0)	
	{
		u16 voltage;
		
		ADC_ENABLE();	
		voltage=ADC_GetChannelValue(ADC_CH1);
		if(voltage<2800)
		{
			voltage_low=1;
		}
		else
		{
			voltage_low=0;
		}
	}
	
}

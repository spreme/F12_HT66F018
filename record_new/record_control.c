#include "record_control.h"


volatile unsigned char user_delay_flag = 0;
volatile unsigned int user_delay_time = 0;


//100us
void use_delay_us(unsigned int us_s)
{
	user_delay_time = 0;
	user_delay_flag = 1;
	while(us_s >= user_delay_time)
	{
		;	
	}
	user_delay_flag = 0;
	user_delay_time = 0;
}

void set_voice(unsigned char date_v)
{
	unsigned char i;
	
	//Í·Âë
	_pb3 = 0;
	use_delay_us(40);					//* 100us
	_pb3 = 1;
	use_delay_us(40);
	_pb3 = 0;
	use_delay_us(5);

	for(i = 0; i < 8; i++)
	{
		if(date_v & 0x01)
		{
			//1
			_pb3 = 1;
			use_delay_us(20);
			_pb3 = 0;
			use_delay_us(5);
		}
		else
		{
			//0
			_pb3 = 1;
			use_delay_us(10);
			_pb3 = 0;
			use_delay_us(5);
		}
		date_v >>= 1;
	}

	_pb3 = 1;
	use_delay_us(40);
}


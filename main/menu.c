#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "LCD.h"
#include "Menu.h"
#include "tm1628.h"
#include "Feed.h"
#include "record_control.h"

u8 set_val_flag = 0;
u8 set_time_flag = 0;
u8 set_meal_flag = 0;

char set_val(char dat,char min,char max,u8 addr)
{
	u8 val = dat;
	u8 status;
	u8 key_value_2 = 0;
	uint timeout = 700;
	u8 blink_time = 0;
	
	while(timeout)
	{
		GCC_CLRWDT();
				
		key_value_2 = key_scan();
		switch(key_value_2)
		{
			case KEY_DOWN:
			{
				UART_SoftWareSendByte(6);
				
				if(val > min)
					val--;
				else if(val == min)
					val = max;	
					
				timeout = 500;				
			}
			break;
								
			case KEY_UP:
			{
				UART_SoftWareSendByte(7);	
								
				val++;
				if (val > max)
					val = min;
					
				timeout = 500;	
			}
			break;
			
			case KEY_TIME:
			{
				UART_SoftWareSendByte(37);	
				if(set_time_flag)
				{
					set_val_flag = 2;
					goto back;
				}
			}
			break;

			case KEY_SET:
			{
				UART_SoftWareSendByte(38);	
				if(set_meal_flag)
				{
					set_val_flag = 2;
					goto back;
				}
			}
			break;			
		}

		blink_time++;
		if(blink_time >= 200)
		{
			blink_time = 0;
		}
		if(blink_time == 100)
		{
			switch(addr)
			{
				case 1:
				{
					Write_DATA(WeiL_tab[1],Num_tab_7[val]);					
				}
				break;
				
				case 2:
				{
					Write_DATA(WeiL_tab[3],Num_tab_7[val/10]);
					Write_DATA(WeiL_tab[2],Num_tab_7[val%10]);					
				}
				break;
				
				case 3:
				{
					Write_DATA(WeiL_tab[7],Num_tab_7[val/10]);
					Write_DATA(WeiL_tab[6],Num_tab_7[val%10]);					
				}
				break;

				case 4:
				{
					Write_DATA(WeiL_tab[5],Num_tab_7[val/10]);
					Write_DATA(WeiL_tab[4],Num_tab_7[val%10]);					
				}
				break;
				
				default:
				break;
				
			}
		}
		else if(blink_time == 0)
		{
			switch(addr)
			{
				case 1:
				{
					Write_DATA(WeiL_tab[1],0x00);					
				}
				break;
				
				case 2:
				{
					Write_DATA(WeiL_tab[3],0x00);
					Write_DATA(WeiL_tab[2],0x00);					
				}
				break;
				
				case 3:
				{
					Write_DATA(WeiL_tab[7],0x00);
					Write_DATA(WeiL_tab[6],0x00);					
				}
				break;

				case 4:
				{
					Write_DATA(WeiL_tab[5],0x00);
					Write_DATA(WeiL_tab[4],0x00);					
				}
				break;
				
				default:
				break;
			}			
		}
				
		use_delay_us(100);			//100*100us
		timeout--;
	}
	
back:
	status = val;
	switch(addr)
	{
		case 1:
		{
			Write_DATA(WeiL_tab[1],Num_tab_7[val]);					
		}
		break;
		
		case 2:
		{
			Write_DATA(WeiL_tab[3],Num_tab_7[val/10]);
			Write_DATA(WeiL_tab[2],Num_tab_7[val%10]);					
		}
		break;
		
		case 3:
		{
			Write_DATA(WeiL_tab[7],Num_tab_7[val/10]);
			Write_DATA(WeiL_tab[6],Num_tab_7[val%10]);					
		}
		break;

		case 4:
		{
			Write_DATA(WeiL_tab[5],Num_tab_7[val/10]);
			Write_DATA(WeiL_tab[4],Num_tab_7[val%10]);					
		}
		break;
		
		default:
		break;	
	}
				
	return status;
}



char set_time(void)
{
	char set_time_value_flag=1;
	struct rtc_time time_set;
	
	set_time_flag = 1;
	
	Write_DATA(WeiL_tab[7],Num_tab_7[rtc_date.hour/10]);
	Write_DATA(WeiL_tab[6],Num_tab_7[rtc_date.hour%10]);
	Write_DATA(WeiL_tab[5],Num_tab_7[rtc_date.minute/10]);
	Write_DATA(WeiL_tab[4],Num_tab_7[rtc_date.minute%10]);
			
	while(1)
	{
		GCC_CLRWDT();
				
		switch(set_time_value_flag)
		{
			case 1:
			{
				time_set.hour = set_val(rtc_date.hour,0,23,3);
				
				UART_SoftWareSendByte(21);			
			}
			break;
			
			case 2:
			{
				time_set.minute = set_val(rtc_date.minute,0,59,4);
				
				UART_SoftWareSendByte(22);
			}
			break;
			
			default:
				set_time_value_flag = 3;	
				break;
		}		
		if(set_val_flag == 1)
		{
			if(set_time_value_flag > 0)
				set_time_value_flag--;
			set_val_flag = 0;
		}
		else if(set_val_flag >= 2)
		{
			set_time_value_flag++;
			set_val_flag = 0;
		}
		
		if(set_time_value_flag >= 3)
		{
			rtc_date.second = 0;				
			rtc_date.hour = time_set.hour;
			rtc_date.minute = time_set.minute;
			time_save();
			
			UART_SoftWareSendByte(42);	
			
			set_time_flag = 0;		
			return 0;
		}
	}

	set_time_flag = 0;			
	return 0;
}


char set_meal(void)
{
	int ret;
	u8 num = 1;
	char set_meal_value_flag=1;
	
	set_meal_flag = 1;

	get_meal(num);
	while(1)
	{
		switch(set_meal_value_flag)
		{
			case 1:
			{
				ret = num;
				num = set_val(ret,1,6,1);
				
				get_meal(num);
				UART_SoftWareSendByte(16);			
			}
			break;
			
			case 2:
			{
				ret = feed_plans[num - 1].quantity;
				feed_plans[num - 1].quantity = set_val(ret,1,40,2);
				
				UART_SoftWareSendByte(17);
			}
			break;
			
			case 3:
			{
				ret = feed_plans[num - 1].hour;
				feed_plans[num - 1].hour = set_val(ret,0,23,3);
				
				UART_SoftWareSendByte(18);
			}
			break;
	
			case 4:
			{
				ret = feed_plans[num - 1].minute;
				feed_plans[num - 1].minute = set_val(ret,0,59,4);
				
				UART_SoftWareSendByte(19);
			}
			break;
			
			default:
				set_meal_value_flag = 5;
				break;
		}
		if(set_val_flag == 1)
		{
			if(set_meal_value_flag > 0)
				set_meal_value_flag--;
			set_val_flag = 0;
		}
		else if(set_val_flag >= 2)
		{
			set_meal_value_flag++;
			set_val_flag = 0;
		}

		if(set_meal_value_flag >= 5)
		{
			EEPROM_Write_Byte(feed_plans[num - 1].hour,1 + 4 * num);
			EEPROM_Write_Byte(feed_plans[num - 1].minute,2 + 4 * num);	
			EEPROM_Write_Byte(feed_plans[num - 1].quantity,3 + 4 * num);
			
			set_meal_flag = 0;			
			return 0;
		}
	}
					
	return 0;
	
}


void get_meal(u8 num)
{
	feed_plans[num - 1].hour = EEPROM_Read_Byte(1 + 4 * num);
	feed_plans[num - 1].minute = EEPROM_Read_Byte(2 + 4 * num);
	feed_plans[num - 1].quantity = EEPROM_Read_Byte(3 + 4 * num);

	Write_DATA(WeiL_tab[1],Num_tab_7[num]);	
	Write_DATA(WeiL_tab[7],Num_tab_7[feed_plans[num - 1].hour/10]);
	Write_DATA(WeiL_tab[6],Num_tab_7[feed_plans[num - 1].hour%10]);
	Write_DATA(WeiL_tab[5],Num_tab_7[feed_plans[num - 1].minute/10]);
	Write_DATA(WeiL_tab[4],Num_tab_7[feed_plans[num - 1].minute%10]);
	Write_DATA(WeiL_tab[3],Num_tab_7[feed_plans[num - 1].quantity/10]);
	Write_DATA(WeiL_tab[2],Num_tab_7[feed_plans[num - 1].quantity%10]);
	
}



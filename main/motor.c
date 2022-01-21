#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "motor.h"
#include "record_control.h"

u8 feed_error=0;			//喂食错误标志位：		1（电机超时）2（）3（红外错误）
u8 task_run_led=0;
u8 task_run_motor=0;				//喂食中标志位1（喂食中） 0（空闲）


u8 motor_run(void)
{
	u16 timeout = 600;			//用于判断电机超时
	u16 i = 0;
	u8 key_cont = 0;

//	lcd_timeout = 0;

	//启动电机
	Motor_Driver = 1;



	//先让电机转过一定角度，退出到位开关压着的状态，低->高
#if 1
	key_cont = 0;
	i = 600;

	while(i)
	{
		use_delay_us(100);			//100*100us

		if(MOTOR_DET)
		{
			key_cont++;

			if(key_cont > 30)
			{
				break;
			}

//			break;	（我）	
		}

		if(i < 20) //超时处理
		{
			timeout = 0;
			break;
		}

		i--;

	}

#else
	use_delay_us(10000);			//10000*100us
#endif

	//等待电机中断(下降沿触发)到来，中断到来后判断中断引脚电平是否为低(并有延时去抖)
	//低表示限位开关还被电机的旋转机构压着，这时电机停止转动
//	lcd_timeout = 0;

	while(timeout)
	{
		GCC_CLRWDT();
		
		if(MOTOR_DET == 0)
		{

			key_cont = 0;
			i = 20;
			use_delay_us(100);			//100*100us		//延时去抖

			while(i)
			{
				use_delay_us(100);			//100*100us		//延时去抖

				if(MOTOR_DET == 0)
				{
					key_cont++;
				}

				i--;
			}

			if(key_cont > 6)
			{
				key_cont = 0;
				use_delay_us(100);			//100*100us	//让出食机构可以准确到位
				break;
			}

		}
		use_delay_us(100);			//100*100us		//（我）
		timeout--;

	}

	return timeout;
}



u8 motor(u8 count, u8 * err_type)
{
	u8 errs = 0;
	u8 feed_cont = count;		//用于判断电机转动次数，每转动一次，喂食一份（大概10g）
	u16 timeout = MOTO_TIMEOUT; //用于判断电机超时

	u8 time_ir_out = 50;		//堵粮超时，连续堵粮5s

	/*	u8 errs_flag = 0;
	  u8 errs = 0;*/
	  
	task_run_led = 0;
	led_flag = 0;

	task_run_motor = 1;

	*err_type = 0;				//清空错误码

	while(feed_cont > 0)
	{
		GCC_CLRWDT();			//喂狗
//		lcd_timeout = 0;

		if(IR_DET == 0)
			timeout = motor_run();
		else
		{
			feed_cont++;
			timeout = 5;	
		}

		//电机超时，电机没转或到位开关探测错误(到位开关没中断)
		if(timeout == 0)
		{
			*err_type = ERROR_MOTOR_TIMEOUT;
			task_run_led = 1;
			led_flag = 4;
			goto err;
		}
				
		use_delay_us(100);			//100*100us	
		
		feed_cont--;
				
		if(IR_DET)
		{
			time_ir_out = 50;
			while(time_ir_out)
			{
				Motor_Driver = 0;
				time_ir_out--;
				use_delay_us(1000);			//100*100us		//延时去抖
				
				if(IR_DET == 0)
					break;
				else
				{
					if(time_ir_out == 0)
					{
						*err_type = ERROR_IR;
						feed_error = ERROR_IR;
						led_flag = 1;
						goto err;
					}
				}
			}
		}
		
		if(*err_type)
		{
			if(feed_cont != 0)
			{
				errs++;
				
				if(errs < 2)
				{
					*err_type = 0;
				}
				else
				{
					goto err;
				}
			}
		}
		
		//成功喂食一份
		
		*err_type = 0;
		errs = 0;
		feed_error = 0;
				
	}


err:	
	Motor_Driver = 0;
	task_run_motor = 0;
//	lcd_timeout = 0;

	return (feed_cont);
}

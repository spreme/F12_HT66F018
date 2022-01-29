#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "Feed.h"
#include "Led.h"
#include "Motor.h"
#include "voltage.h"

void error_task(void)
{
	static u8 error_ir_time = 0;
	static u8 led_blink = 0;

	if(feed_error)
	{
		task_run_led = 1;
		led_flag = 4;
	}
	else
	{
		task_run_led = 0;
		led_flag = 0;
	}

	//判断红外对管是否一直被阻挡（gpio引脚电平0或1）
	if(IR_DET == 1)			//堵粮
	{
		error_ir_time++;
		if(error_ir_time >= 150)	//1.5s确定堵粮,亮灯
		{				
			feed_error |= ERROR_IR;
			error_ir_time = 0;
		}
	}
	else
	{
		error_ir_time = 0;
		feed_error &= ~ERROR_IR;
	}

	if((led_flag == 4) && (task_run_led == 1))	
/*	if(feed_error) 		//堵粮或电机超时，红灯慢闪*/
	{
		LED_G = 0;
		
		led_blink++;
		if(led_blink >= 50)
		{
			LED_R = ~LED_R;
			led_blink = 0;
		}
		
	}		
	else if((led_flag == 0) && (task_run_led == 0)) //绿灯常亮
	{
		LED_G = 1;
		LED_R = 0;
		
	}
	
}

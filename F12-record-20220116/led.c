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

	//�жϺ���Թ��Ƿ�һֱ���赲��gpio���ŵ�ƽ0��1��
	if(IR_DET == 1)			//����
	{
		error_ir_time++;
		if(error_ir_time >= 150)	//1.5sȷ������,����
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
/*	if(feed_error) 		//����������ʱ���������*/
	{
		LED_G = 0;
		
		led_blink++;
		if(led_blink >= 50)
		{
			LED_R = ~LED_R;
			led_blink = 0;
		}
		
	}		
	else if((led_flag == 0) && (task_run_led == 0)) //�̵Ƴ���
	{
		LED_G = 1;
		LED_R = 0;
		
	}
	
}

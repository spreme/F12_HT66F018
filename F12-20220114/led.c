#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "Feed.h"
#include "Led.h"
#include "Motor.h"

void error_task(void)
{
	if(feed_error)
	{
		task_run_led = 1;
		led_flag = 3;
	}
	else
	{
		task_run_led = 0;
		led_flag = 0;
	}

	//判断红外对管是否一直被阻挡（gpio引脚电平0或1）
		if (IR_DET) {
			feed_error |= ERROR_IR;
		} else {
			feed_error &= ~ERROR_IR;
		}
}

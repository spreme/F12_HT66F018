#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "EEPROM.h"
#include "define.h"
#include "tm1628.h"
#include "KeyScan.h"
#include "LCD.h"
#include "Menu.h"
#include "Feed.h"
#include "record_control.h"
#include "motor.h"
#include "voltage.h"

u8 led_flag = 0;					//灯状态标志位        0：绿灯常亮	1：绿灯慢闪          2：绿灯灭 3：红灯常亮 4：红灯慢闪 5：红灯灭 6:全灭
u8 record_flag = 0;				//录音标志位
u8 feed_detect_again = 0;		//再次喂食标志
u8 time_save_flag = 0;
char meal_flag=0;

struct feed_record feed;


void main()
{
	char key_value_1=0;				
	u8 rtc_oldmin=99;				
		
	GCC_DELAY(100);  //延时待系统稳定	   
	Init_clock();   //初始化时钟
//======================端口初始化==============================//	   
    GPIOA_INIT(GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5,GPIO_Mode_OUT,DISABLE,RESET);
    GPIOB_INIT(GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6,GPIO_Mode_OUT,RESET);
    GPIOC_INIT(GPIO_Pin_0,GPIO_Mode_OUT,RESET);

    GPIOC_INIT(GPIO_Pin_1|GPIO_Pin_2,GPIO_Mode_INT,RESET);

    init_TM1628();
    
    rtc_init();
    
    EEPROM_Init();
    
    rtc_date.hour=EEPROM_Read_Byte(31);
    rtc_date.minute=EEPROM_Read_Byte(32);
	
/* Debug mode can be enabled by uncommenting "DEBUG" Macro in HT8_MCU_IP_SEL.h */
	SIMULATION_UART_INIT();

	/* Init ADC peripheral,specify ADC clock、reference Volta and 
	data alignment type in HT8_ADC.h */
	ADC_Init();	
	
	use_delay_us(1000);			//1000*100us	//wait system stable
	
    _emi = 1;   //开总中断
	//system loop
	while(1)
	{
		GCC_CLRWDT();
							
		key_value_1 = key_scan();	
		
		switch(key_value_1)
		{
			case KEY_TIME:
			{
				if(meal_flag==0)
				{
					set_time();
				}
			}
			break;
			
			case KEY_SET:
			{
				set_meal();	
			}
			break;
			
			case KEY_FEED:
			{
				feed.hour=0;
				feed.minute=0;
				feed.quantity=1;
				feed.music=1;
				
				feed_going=1;
			}
			break;
			
			case KEY_RECORD:
			{
				if(record_flag != 1)
				{
					record_flag = 1;
					set_voice(0xfe);
					
					UART_SoftWareSendByte(0xff);
				}
				else
				{
					record_flag = 0;
					set_voice(0xff);
					
					UART_SoftWareSendByte(0xaa);
				}
			}
			break;

			case KEY_PLAY:
			{
				set_voice(0xfb);
				
				UART_SoftWareSendByte(0xbb);

			}
			break;
			
			case KEY_UP:
			{
				use_delay_us(1000);			//1000*100us
				meal_flag++;
				if(meal_flag>6)
					meal_flag=0;
			}
			break;
			
			case KEY_DOWN:
			{
				use_delay_us(1000);			//1000*100us
				meal_flag--;
				if(meal_flag<0)
					meal_flag=6;
			}
			break;
		}		
		
		if(meal_flag>0)
		{
			get_meal(meal_flag);
		}
		else
		{
			rtc_lcd();
		}

		if(record_flag == 2)			//超时结束录音
		{
			record_flag = 0;
			set_voice(0xff);
			
			UART_SoftWareSendByte(0x55);
		}
		
		
		
		if(time_save_flag)				//
		{
			time_save_flag = 0;
			time_save();	
		}
		
		if(lcd_timeout==meal_time) //30s
		{
			meal_flag=0;
		}

		if(rtc_oldmin != rtc_date.minute)						//喂食检测：一分钟置1一次
		{
			rtc_oldmin = rtc_date.minute;

			feed_scan(&feed);					//扫描eeprom判断是否需要执行定时喂食
		}
		else if(feed_detect_again)					//再次喂食检测
		{
			if((feed_error & ERROR_IR) == 0)		//不是红外错误，出粮口正常
			{
				feed_going = 1;			//饲料所需
			}
		}
		
		if(feed_going)
		{
/*			set_voice(0xfb);*/
			feed_error = feed_run(&feed);
			time_save();
			if(feed_error & ERROR_IR)			//喂食红外错误
			{
				feed_detect_again = 1;			//红外错误：确保喂食错误，再次喂食检测
			}
			else
			{
				feed_detect_again = 0;
			}
			
			feed_going = 0;
		}
		else
		{
			battery_detect();	
		}


	//判断红外对管是否一直被阻挡（gpio引脚电平0或1）
		if (IR_DET) {
			led_flag=3;
			feed_error |= ERROR_IR;
		} 
		else {
			led_flag=0;
			feed_error &= ~ERROR_IR;
		}



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

		if(feed_error)
/*		if(feed_error & ERROR_IR)		*/
/*		if(led_flag==3&&task_run_led)*/
		{
			LED_G = 0;
			LED_R = 1;
			
		}		
		else if(led_flag==0)
		{
			LED_G = 1;
			LED_R = 0;
			
		}
	 

//		GCC_DELAY(4000);		//delay 2ms
		
	}
	



}


/**
  * @brief external Interruption 0 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x04))) INT0_ISR(void)
{
	/* user define */
	
	
	
	
}

/**
  * @brief compare Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x08))) COMP_ISR(void)
{
	/* user define */
	
	
	
}

/**
  * @brief timer0 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x0C))) Timer0_ISR(void)
{
	/* user define */
	static u16 record_time = 0;
	static u16 task_feed_again = 0;
	static u16 led_blink1 = 0;
	static u16 led_blink2 = 0;
	static u16 t1sflag = 0;

	_t0af=0;


	t1sflag++;
	if(t1sflag==115)
	{
		t1sflag=0;
		rtc_date.second++;	
		if(rtc_date.second >59)
		{ 
			rtc_date.minute++;
			rtc_date.second=0;			
			time_save_flag=1;							
			if(rtc_date.minute >59)
			{
							
			  	rtc_date.hour++;	    
				rtc_date.minute=0; 
				    
				if(rtc_date.hour >23)
				{	  	      
					rtc_date.hour=0;
				}
			}	
		}
		
	}
	
	
	lcd_timeout++;
	if(lcd_timeout>=sleep_time)//40s
	{
		lcd_timeout=0;
	}
	
	if(feed_error)	
/*	if(feed_error & ERROR_IR)*/
	{
/*		if((led_flag & 1))			//堵粮*/
		{
			led_blink1++;
			if(led_blink1 >= 50)
			{
				F8_Y_LED = ~F8_Y_LED;
				led_blink1 = 0;
			}
		}
	}
	else
		F8_Y_LED = 0;
	
	
	if(voltage_low)
	{
/*		if((led_flag & 2))		//低电量*/
		{
			led_blink2++;
			if(led_blink2 >= 50)
			{
				F8_R_LED = ~F8_R_LED;
				led_blink2 = 0;
			}
		}
	}
	else
		F8_R_LED = 0;

//	if(led_flag==4&&task_run_led)
//	{
//		led_blink1++;
//		if(led_blink1 >= 50)
//		{
//			LED_G = 0;
//			LED_R = ~LED_R;
//			led_blink1 = 0;
//		}
//	}		

	
	if(record_flag)
	{
		record_time++;
		if(record_time >= 1000)
		{
			record_time = 0;
			record_flag = 2;
			
		}
	}
	else
	{
		record_time = 0;
		
	}
	
	if(feed_detect_again)
	{
		task_feed_again++;

		if(task_feed_again > FEED_AGAIN_PERIOD)
		{
			feed_detect_again = 0;
			task_feed_again = 0;
		}
	}
		
	_emi=1;
}

/**
  * @brief timer1 or tomer 2 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x10))) Timer1_2_ISR(void)
{
	/* user define */
	
    _t1af=0;       //t0中断请求标志清零
    
	if(user_delay_flag > 0)
	{
		user_delay_time++;
		if(user_delay_time >= 65534)
			user_delay_time = 65534;			
	}	
	   
    _emi=1;        //开总中断	
	
	
	
}

/**
  * @brief LVD or EEPROM Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x14))) LVD_EEPROM_ISR(void)
{
	/* user define */
	
	
	
}

/**
  * @brief ADC Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x18))) ADC_ISR(void)
{
	/* user define */
	
	
	
}


/**
  * @brief timebase0 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x1C))) TB0_ISR(void)
{
	/* user define */
	
//	_tb0f=0;
//	
//
//	_emi=1;
	
}


/**
  * @brief timebase1 Interruption routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x20))) TB1_ISR(void)
{
	/* user define */
	
	
	
}


/**
  * @brief external Interruption 1 routine.
  * @par Parameters:
  * None
  * @retval
  * None
  */
void __attribute((interrupt(0x24))) INT1_ISR(void)
{
	/* user define */
	
	
	
}
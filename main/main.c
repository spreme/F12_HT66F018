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

u8 led_flag = 0;					//��״̬��־λ        0���̵Ƴ���	1���̵�����          2���̵��� 3����Ƴ��� 4��������� 5������� 6:ȫ��
u8 record_flag = 0;				//¼����־λ
u8 feed_detect_again = 0;		//�ٴ�ιʳ��־
u8 col_staus = 1;				//ʱ�����˸
	char meal_flag=0;
	struct feed_record feed;


void main()
{
	char key_value_1=0;				
	u8 rtc_oldmin=99;				
		
	GCC_DELAY(100);  //��ʱ��ϵͳ�ȶ�	   
	Init_clock();   //��ʼ��ʱ��
//======================�˿ڳ�ʼ��==============================//	   
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

	/* Init ADC peripheral,specify ADC clock��reference Volta and 
	data alignment type in HT8_ADC.h */
	ADC_Init();	
	
	use_delay_us(1000);			//1000*100us	//wait system stable
	
    _emi = 1;   //�����ж�
	UART_SoftWareSendByte(100);
	//system loop
	while(1)
	{
		GCC_CLRWDT();
							
		key_value_1 = key_scan();	
		
		switch(key_value_1)
		{
			case KEY_TIME:
			{
				UART_SoftWareSendByte(11);
				set_time();
			}
			break;
			
			case KEY_SET:
			{
				UART_SoftWareSendByte(1);
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
				UART_SoftWareSendByte(2);
			}
			break;
			
			case KEY_RECORD:
			{
				UART_SoftWareSendByte(3);
				if(record_flag != 1)
				{
					record_flag = 1;
					set_voice(0xfe);
				}
				else
				{
					record_flag = 0;
					set_voice(0xff);
				}
			}
			break;

			case KEY_PLAY:
			{
				UART_SoftWareSendByte(4);
				set_voice(0xfb);
			}
			break;
			
			case KEY_UP:
			{
				UART_SoftWareSendByte(5);
				use_delay_us(1000);			//1000*100us
				meal_flag++;
				if(meal_flag>6)
					meal_flag=0;
			}
			break;
			
			case KEY_DOWN:
			{
				UART_SoftWareSendByte(10);
				use_delay_us(1000);			//1000*100us
				meal_flag--;
				if(meal_flag<0)
					meal_flag=6;
			}
			break;
		}		
		
		if(meal_flag>0)
		{
			UART_SoftWareSendByte(12);
			get_meal(meal_flag);
		}
		else
		{
			UART_SoftWareSendByte(13);
			rtc_lcd();
		}

		if(record_flag == 2)			//��ʱ����¼��
		{
			UART_SoftWareSendByte(14);
			record_flag = 0;
			set_voice(0xff);
		}
		
		if(rtc_oldmin != rtc_date.minute)						//ιʳ��⣺һ������1һ��
		{
			UART_SoftWareSendByte(15);
			rtc_oldmin = rtc_date.minute;
			
			feed_scan(&feed);					//ɨ��eeprom�ж��Ƿ���Ҫִ�ж�ʱιʳ
		}
		else if(feed_detect_again)					//�ٴ�ιʳ���
		{
			if((feed_error & ERROR_IR) == 0)		//���Ǻ�����󣬳���������
			{
				feed_going = 1;			//��������
			}
		}
		
		if(feed_going)
		{
			feed_error = feed_run(&feed);	
		
			if(feed_error & ERROR_IR)			//ιʳ�������
			{
				feed_detect_again = 1;			//�������ȷ��ιʳ�����ٴ�ιʳ���
			}
			else
			{
				feed_detect_again = 0;
			}
			
			feed_going = 0;
		}


        if(col_staus)
        {
            if(rtc_date.second %2 ==0)   //ʱ�������
            {
                Write_DATA(WeiL_tab[6],Num_tab_7[rtc_date.hour%10]);
            }
            else
            {
                Write_DATA(WeiL_tab[6],Num_tab_8[rtc_date.hour%10]);	
            }
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
	
	_t0af=0;
	
	if((led_flag & 1))			//����
	{
		led_blink1++;
		if(led_blink1 >= 50)
		{
			LED_G = ~LED_G;
			led_blink1 = 0;
		}
	}
	else
		LED_G = 0;
		
	if((led_flag & 2))		//�͵���
	{
		led_blink2++;
		if(led_blink2 >= 50)
		{
			LED_R = ~LED_R;
			led_blink2 = 0;
		}
	}
	else
		LED_R = 0;
	
	if(record_flag)
	{
		record_time++;
		if(record_time >= 1000)
		{
			record_time = 0;
			record_flag = 2;	
		}
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
	
    _t1af=0;       //t0�ж������־����
    
	if(user_delay_flag > 0)
	{
		user_delay_time++;
		if(user_delay_time >= 65534)
			user_delay_time = 65534;			
	}	
	   
    _emi=1;        //�����ж�	
	
	
	
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
	
	_tb0f=0;
	
	rtc_date.second++;	
	if(rtc_date.second >59)
	{ 
		rtc_date.minute++;
		rtc_date.second=0;
				
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

	_emi=1;	
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
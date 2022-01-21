/**
  ******************************************************************************
  * @file ADC\main.c
  * @brief This file contains the main function for the ADC Conversion example.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2019-05-07
  ******************************************************************************
  * MCU 				: HT66F018
  * Operating Voltage 	: 5.0v
  * System Clock 		: 8MHz
  ******************************************************************************
  * @attention
  *
  * Firmware Disclaimer Information
  *
  * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
  *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
  *    other intellectual property laws.
  *
  * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
  *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
  *    other than HOLTEK and the customer.
  *
  * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
  *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
  *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
  *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
  *
  * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
  ************************************************************************************************************/

#include "HT8_MCU_IP_SEL.h"
#include "init.h"

#define uchar unsigned char

#ifdef	DEBUG
/* Debug mode can be enabled by uncommenting "DEBUG" Macro in HT8_MCU_IP_SEL.h */
	#include "HT8_Simulation_UART.h"
#endif

#define STB 			_pa3		 
#define DIO				_pb6     
#define CLK				_pb5
	 
#define DC_DET			_pb2  

const static uchar Num_tab_7[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//共阴

//TM1628A低8段位码【SEG1-SEG8】
const static uchar WeiL_tab[]={0xce,0xcc,0xca,0xc8,0xc6,0xc4,0xc2,0xc0};

//TM1628A低8段位码【SEG9-SEG10】
const static uchar WeiH_tab[]={0xcf,0xcd,0xcb,0xc9,0xc7,0xc5,0xc3,0xc1};

void send_8bit(uchar dat)	 
{
	uchar i;
	for(i=0;i<8;i++)
	{
		CLK = 0;
		
		if(dat&0x01) 
			DIO = 1;
		else         
			DIO = 0;
			
		dat>>=1;	 
		CLK = 1;
	}
}

void send_command(uchar com)  
{
	STB = 0;						  
	send_8bit(com);	
	STB = 1;						  
		          
}

void Write_DATA(uchar add,uchar DATA)                
{
	send_command(0x44);	
	STB = 0;
	send_8bit(add);
	send_8bit(DATA);
	STB = 1;
}

void init_TM1628(void)
{
	uchar i;
	send_command(0x03);
	send_command(0x8f);
	send_command(0x40);
	
	STB = 0;
	send_8bit(0xc0);
	
	for(i=0;i<16;i++)
	{
		send_8bit(0x00);
	}
	STB = 1;
}

void Delay_ms(unsigned int ms)
{
	while(ms--)
	{
		GCC_DELAY(2000);//编译器自带延时指定个周期，在主频8Mhz下，一个指令周期为0.5us	
/*		GCC_CLRWDT();*/
	}
}
		
//===========================PA端口初始化函数=========================================//
void GPIOA_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 wakeup,u8 GPIO_BitVal)  //u8 为无符号字符型
{
	if ((u8)GPIO_Mode == (u8)0x01)   //pa为输入型时
	{
	 	_pac|=GPIO_Pin;             //当pa引脚GPIO_Pin为输入，则置位pac ，同时设置上拉电阻
	 	_papu|=GPIO_Pin;
	}
	else
	{
		_pac&=(u8)(~GPIO_Pin);      //将pa设置为输出型 
		_papu&=(u8)(~GPIO_Pin);	
	}
	 
	if (GPIO_BitVal != RESET)       //重置
	{
	  	 _pa|=GPIO_Pin;
	}
	else
	{
	 	 _pa&=(u8)(~GPIO_Pin);   

	}	 	
}
//===========================PB端口初始化函数=========================================//
void GPIOB_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 GPIO_BitVal)
{
	 
	if ((u8)GPIO_Mode == (u8)0x01)
	{
	 	_pbc|=GPIO_Pin;
	 	_pbpu|=GPIO_Pin;
	}
	else
	{
		_pbc&=(u8)(~GPIO_Pin);
		_pbpu&=(u8)(~GPIO_Pin);	
	}
	 
	if (GPIO_BitVal != RESET)
	{
	  	 _pb|=GPIO_Pin;
	}
	else
	{
	 	 _pb&=(u8)(~GPIO_Pin);
	}	 	
}
//===========================PC端口初始化函数=========================================//
void GPIOC_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 GPIO_BitVal)
{
	 
	if ((u8)GPIO_Mode == (u8)0x01)
	{
		_pcc|=GPIO_Pin;
		_pcpu|=GPIO_Pin;
	}
	else
	{
		_pcc&=(u8)(~GPIO_Pin);
		_pcpu&=(u8)(~GPIO_Pin);	
	}
	 
	if (GPIO_BitVal != RESET)
	{
	  	 _pc|=GPIO_Pin;
	}
	else
	{
	 	 _pc&=(u8)(~GPIO_Pin);
	}	 	
}

	
//===========================数据存储区使能配置=========================================//
void clr_ram_en(unsigned char t)
{
	_dmbp0 = t;
	_mp1 = 0x80;
	while(_mp1!=0)
	{
		_iar1 = 0;
		_mp1++;
	}
}	
//===========================时钟初始化函数=========================================//
void Init_clock(void)
{
  	_smod=0x01;            //选择gao速时钟为系统时钟 内部8Mhz
  	while(!_hto);          //等待高速震荡器就位
  	_wdtc=0x57;            //使能看门狗
  	_acerl=0x00;		   //取消A/D输入
  	_tmpc=0x00;            //取消相关引脚用作TM 输入/ 输出，相关引脚保持原来功能
  	_cpc=0x08;             //比较器输出仅内部使用
  	_integ=0x00;			//所有外部中断边沿控制除能
  	_int0e=0;				//INTO中断除能
  	_emi = 0;   			//关闭总中断

/***********TM0************/
  	_tm0c0=0x00;			//选择系统时钟fsys作为t0时钟fint=2MHZ	
  	_tm0c1=0xc1;			//定时模式，a匹配
  	_tm0al=0x20;			//定时初值  0x4e20=20000
  	_tm0ah=0x4e;            //20000/2MHZ=10ms
  	_t0af=0;				//清t中断标志位
  	_t0on=1;				//启动定时
  	_mf0e=1;				//开多功能中断
  	_t0ae=1;	    		//开t0中断
/***********时基0************/	  
  	//_tbc=0b10000111;       //时基定时器配置使能 fTBC时钟源 LXT快速启振
  	//_tb0f=0;               //时基0中断请求标志清零
  	//_tb0e=1;               //时基0中断控制位使能
  	
  	_emi=1;		  			//开总中断
  	
  	GCC_CLRWDT();	       //清除看门狗
	clr_ram_en(0);         //数据存储区选择BANK0
	clr_ram_en(1);         //数据存储区选择BANK1

}



//键值
enum KEY_STATE_E
{
	KEY_UP_E = 0x01,
	KEY_DOWN_E = 0x02,
	KEY_SET_E = 0x04,
	KEY_TIME_E = 0x08,
	KEY_FEED_E = 0x10,
	KEY_RECORD_E = 0x20,
	KEY_PLAY_E = 0x40,
};

enum KEY_TYPE_E{
	KEY_NO			= 0,		//无按键
	
    KEY_UP_S,			//
    KEY_DOWN_S,			//
    KEY_SET_S,					//按键短按
	KEY_TIME_S,
    KEY_FEED_S,			//	
    KEY_RECORD_S,		//
    KEY_PLAY_S,			//
	
	
    KEY_UP_L,			//
    KEY_DOWN_L,			//
    KEY_SET_L,					//按键长按触发
	KEY_TIME_L,
    KEY_FEED_L,			//	
    KEY_RECORD_L,		//
    KEY_PLAY_L,			//
	
    KEY_UP_L_UP,			//
    KEY_DOWN_L_UP,			//
    KEY_SET_L_UP,				//按键长按松开
	KEY_TIME_L_UP,
    KEY_FEED_L_UP,			//	
    KEY_RECORD_L_UP,		//
    KEY_PLAY_L_UP,			//	
};


#define ADC_KEY_NO   	(4000)		//VCC
 
#define ADC_KEY_UP   	(2600)     //20K
#define ADC_KEY_DOWN  	(3000)     //33K
#define ADC_KEY_SET   	(3300)     //47K
#define ADC_KEY_TIME   	(3450)     //56K
#define ADC_KEY_FEED   	(3500)     //62K
#define ADC_KEY_RECORD  (3600)     //75K
#define ADC_KEY_PLAY   	(3700)     //100K


#define KEY_SHORT_TIME			100			//按键短按时间	1s

#define KEY_LONG_TIME			150			//按键长按时间	1.5s

#define KEY_LONG_TIME_SET		300			//按键长按时间	3s


u8 key_flag=0;

u8 get_key_state(void)
{
	u8 key_value,key_status=0;
	
	ADC_ENABLE();	
	key_value=ADC_GetChannelValue(ADC_CH0);
	
	if(key_value>=ADC_KEY_NO)
	{
		key_status=KEY_NO;
		key_flag=0;
	}
	else if(key_flag==0)
	{
		if(key_value>=ADC_KEY_PLAY)
		{
			key_status=key_status | KEY_PLAY_E;
			key_flag=1;	
		}
		
		else if(key_value>=ADC_KEY_RECORD)
		{
			key_status=key_status | KEY_RECORD_E;
			key_flag=1;
		}
		
		else if(key_value>=ADC_KEY_FEED)
		{
			key_status=key_status | KEY_FEED_E;
			key_flag=1;	
		}
		
		else if(key_value>=ADC_KEY_TIME)
		{
			key_status=key_status | KEY_TIME_E;
			key_flag=1;
		}
		
		else if(key_value>=ADC_KEY_SET)
		{
			key_status=key_status | KEY_SET_E;
			key_flag=1;	
		}
		
		else if(key_value>=ADC_KEY_DOWN)
		{
			key_status=key_status | KEY_DOWN_E;
			key_flag=1;
		}
		
		else if(key_value>=ADC_KEY_UP)
		{
			key_status=key_status | KEY_UP_E;
			key_flag=1;
		}	
	}
	return key_status;
}

u16 up_key_tick=0;
u16 down_key_tick=0;
u16 set_key_tick=0;
u16 time_key_tick=0;
u16 feed_key_tick=0;
u16 record_key_tick=0;
u16 play_key_tick=0;

u8 key_flag_1=0;

void key_func(void)
{
	u8 cur_key;
	
	cur_key=get_key_state();
	
	play_key_tick++;
	if(cur_key==KEY_PLAY_E)
	{
		if(play_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_PLAY_L;
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(play_key_tick<=KEY_SHORT_TIME&&play_key_tick!=0)
		{
			key_flag_1=KEY_PLAY_S;
		}		
		else if(play_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_PLAY_L_UP;
		}
		play_key_tick=0;
	}
	
	record_key_tick++;
	if(cur_key==KEY_RECORD_E)
	{
		if(record_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_RECORD_L;
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(record_key_tick<=KEY_SHORT_TIME&&record_key_tick!=0)
		{
			key_flag_1=KEY_RECORD_S;
		}		
		else if(record_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_RECORD_L_UP;
		}
		record_key_tick=0;
	}
	
	feed_key_tick++;
	if(cur_key==KEY_FEED_E)
	{
		if(feed_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_FEED_L;
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(feed_key_tick<=KEY_SHORT_TIME&&feed_key_tick!=0)
		{
			key_flag_1=KEY_FEED_S;
		}		
		else if(feed_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_FEED_L_UP;
		}
		feed_key_tick=0;
	}

	time_key_tick++;
	if(cur_key==KEY_TIME_E)
	{
		if(time_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_TIME_L;
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(time_key_tick<=KEY_SHORT_TIME&&time_key_tick!=0)
		{
			key_flag_1=KEY_TIME_S;
		}		
		else if(time_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_TIME_L_UP;
		}
		time_key_tick=0;
	}

	set_key_tick++;
	if(cur_key==KEY_SET_E)
	{
		if(set_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_SET_L;
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(set_key_tick<=KEY_SHORT_TIME&&set_key_tick!=0)
		{
			key_flag_1=KEY_SET_S;
		}		
		else if(set_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_SET_L_UP;
		}
		set_key_tick=0;
	}

	down_key_tick++;
	if(cur_key==KEY_DOWN_E)
	{
		if(down_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_DOWN_L;
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(down_key_tick<=KEY_SHORT_TIME&&down_key_tick!=0)
		{
			key_flag_1=KEY_DOWN_S;
		}		
		else if(down_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_DOWN_L_UP;
		}
		down_key_tick=0;
	}
	
	up_key_tick++;
	if(cur_key==KEY_UP_E)
	{
		if(up_key_tick==KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_UP_L;
		}
	}
	else if(cur_key==KEY_NO)
	{
		if(up_key_tick<=KEY_SHORT_TIME&&up_key_tick!=0)
		{
			key_flag_1=KEY_UP_S;
		}		
		else if(up_key_tick>KEY_LONG_TIME_SET)
		{
			key_flag_1=KEY_UP_L_UP;
		}
		up_key_tick=0;
	}

}


//===========================定时器0中断入口=========================================//
DEFINE_ISR(isr_TM0, 0x0c)   //定时器0中断函数  191us
{
    _t0af=0;       //t0中断请求标志清零	    

	tms++;
	if(tms>=20)
	{
		tms=0;
		t10msflag=1;	
	}			
	
	key_func();
    
    _emi=1;        //开总中断	
}


/**
  * @brief A/D Conversion main entry point.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
void main()
{
	u16 g_nConversionValue=0;		//AD conversion value
				
	u16 voltage=0;
		
	GCC_DELAY(100);  //延时待系统稳定	   
	Init_clock();   //初始化时钟
//======================端口初始化==============================//	   
    GPIOA_INIT(GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5,GPIO_Mode_OUT,DISABLE,RESET);
    GPIOB_INIT(GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6,GPIO_Mode_OUT,RESET);
    GPIOC_INIT(GPIO_Pin_0,GPIO_Mode_OUT,RESET);

    GPIOC_INIT(GPIO_Pin_1|GPIO_Pin_2,GPIO_Mode_INT,RESET);

	init_TM1628();
	
#ifdef	DEBUG
/* Debug mode can be enabled by uncommenting "DEBUG" Macro in HT8_MCU_IP_SEL.h */
	SIMULATION_UART_INIT();
#endif

	/* Init ADC peripheral,specify ADC clock、reference Volta and 
	data alignment type in HT8_ADC.h */
	ADC_Init();	
	
	/* ADC channel select */
/*	ADC_SelectChannel(ADC_CH0);*/
	
	/* enable ADC IP */
	ADC_ENABLE();
	
	GCC_DELAY(2000);	//wait system stable
	
	//system loop
	while(1)
	{
		GCC_CLRWDT();
		
		/* get AD converter value */
		if(t10msflag)
		{
			t10msflag=0;
			g_nConversionValue = ADC_GetChannelValue(ADC_CH0);
			
/*			voltage=ADC_GetChannelValue(ADC_CH1);*/
								
		}
		
//		if(DC_DET==0)	
//		{						
//			ADC_ENABLE();	
//			voltage=ADC_GetChannelValue(ADC_CH1);
//			
//		}

		Write_DATA(WeiL_tab[7],Num_tab_7[g_nConversionValue/1000]);
		Write_DATA(WeiL_tab[6],Num_tab_7[g_nConversionValue/100%10]);
		Write_DATA(WeiL_tab[5],Num_tab_7[g_nConversionValue/10%10]);
		Write_DATA(WeiL_tab[4],Num_tab_7[g_nConversionValue%10]);
		Write_DATA(WeiL_tab[3],0x3f);
		Write_DATA(WeiL_tab[2],0x66);
		Write_DATA(WeiL_tab[1],0x06);

//		Write_DATA(WeiL_tab[7],Num_tab_7[voltage/1000]);
//		Write_DATA(WeiL_tab[6],Num_tab_7[voltage/100%10]);
//		Write_DATA(WeiL_tab[5],Num_tab_7[voltage/10%10]);
//		Write_DATA(WeiL_tab[4],Num_tab_7[voltage%10]);
//		Write_DATA(WeiL_tab[3],0x3f);
//		Write_DATA(WeiL_tab[2],0x66);
//		Write_DATA(WeiL_tab[1],0x06);
		
		
			
		if(voltage<2750)
			_pc0=1;	
		else
			_pc0=0;
				
/*		_emi = 1;   //开总中断*/

		GCC_DELAY(4000);		//delay 2ms
	
	
				
		
	#ifdef DEBUG	
	/* send conversion data to PC for debug, Debug mode can be enabled
	   by uncommenting "DEBUG" Macro in HT8_MCU_IP_SEL.h */	
		UART_SoftWareSendByte(0xaa);						//send head code to PC
		GCC_DELAY(100);
		UART_SoftWareSendByte(g_nConversionValue>>8);		//send AD conversion value high byte to PC
		GCC_DELAY(100);
		UART_SoftWareSendByte(g_nConversionValue&0xff);		//send AD conversion value low byte to PC
	#endif

		
	}
	
	
}



/******************* (C) COPYRIGHT 2019 Holtek Semiconductor Inc *****END OF FILE****/
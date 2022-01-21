//====================================================//
//先初始化完成IO口，IO口配置请务必根据项目要求进行配置//
//		   根据项目要求再配置并初始化其他模块		   //
//		   注意主函数调用初始化函数的先后顺序		  //
//					程序必须做好注释				  //
//====================================================//
#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "EEPROM.h"
#include "define.h"


void WDT_Init()
{
#ifdef	WDT_OF_TIME_2_8
	_ws2=0;_ws1=0;_ws0=0;
	
#elif	WDT_OF_TIME_2_10
	_ws2=0;_ws1=0;_ws0=1;
	
#elif	WDT_OF_TIME_2_12
	_ws2=0;_ws1=1;_ws0=0;
	
#elif	WDT_OF_TIME_2_14
	_ws2=0;_ws1=1;_ws0=1;
	
#elif	WDT_OF_TIME_2_15
	_ws2=1;_ws1=0;_ws0=0;
	
#elif	WDT_OF_TIME_2_16
	_ws2=1;_ws1=0;_ws0=1;
	
#elif	WDT_OF_TIME_2_17
	_ws2=1;_ws1=1;_ws0=0;
	
#elif	WDT_OF_TIME_2_18
	_ws2=1;_ws1=1;_ws0=1;
#endif
}



void TimeBase_Init(void)
{
/***************** TimeBase clock select *****************/
	#ifdef	TB_CLOCK_FTBC
		{
			/* select TimeBase clock ftbc */
			_tbck = 0; 
		}		
	#elif	TB_CLOCK_FSYS_DIV4
		{
			/* select TimeBase clock fsys/4 */
			_tbck = 1; 
		}
	#endif	
/*************** end of TimeBase clock select ******************/	

						
/******** TimeBase0 time-out period select**********/
	#ifdef	TB0_Period_2_8		
		{
			/* select TimeBase0 time-out period 2^8(256)	*/
			_tb02 = 0;	_tb01 = 0;	_tb00 = 0;
		}	
	#elif	TB0_Period_2_9		
		{
			/* select TimeBase0 time-out period 2^9(512)	*/
			_tb02 = 0;	_tb01 = 0;	_tb00 = 1;
		}
	#elif	TB0_Period_2_10		
		{
			/* select TimeBase0 time-out period 2^10(1024) */
			_tb02 = 0;	_tb01 = 1;	_tb00 = 0;
		}
	#elif	TB0_Period_2_11		
		{
			/* select TimeBase0 time-out period 2^11(2048)	*/
			_tb02 = 0;	_tb01 = 1;	_tb00 = 1;
		}
	#elif	TB0_Period_2_12		
		{
			/* select TimeBase0 time-out period 2^12(4096)	*/
			_tb02 = 1;	_tb01 = 0;	_tb00 = 0;
		}	
	#elif	TB0_Period_2_13		
		{
			/* select TimeBase0 time-out period 2^13(8192)	*/
			_tb02 = 1;	_tb01 = 0;	_tb00 = 1;
		}
	#elif	TB0_Period_2_14		
		{
			/* select TimeBase0 time-out period 2^14(16384)	*/
			_tb02 = 1;	_tb01 = 1;	_tb00 = 0;
		}
	#elif	TB0_Period_2_15		
		{
			/* select TimeBase0 time-out period 2^15(32768)	*/
			_tb02 = 1;	_tb01 = 1;	_tb00 = 1;
		}
	#endif
/***** end of TimeBase0 time-out period select ******/


/******** TimeBase1 time-out period select**********/
	#ifdef	TB1_Period_2_12	
		{
			/* select TimeBase1 time-out period 2^12(4096)	*/
			_tb11 = 0;	_tb10 = 0;
		}	
	#elif	TB1_Period_2_13		
		{
			/* select TimeBase1 time-out period 2^13(8192)	*/
			_tb11 = 0;	_tb10 = 1;
		}
	#elif	TB1_Period_2_14		
		{
			/* select TimeBase1 time-out period 2^14(16384)	*/
			_tb11 = 1;	_tb10 = 0;
		}
	#elif	TB1_Period_2_15		
		{
			/* select TimeBase1 time-out period 2^15(32768)	*/
			_tb11 = 1;	_tb10 = 1;
		}
	#endif
/***** end of TimeBase1 time-out period select ******/


}







/**
  * @brief Initializes the ADC peripheral according to the specified parameters
  * @retval None
  */
void ADC_Init(void)
{
/***************** ADC clock select *****************/
	#ifdef	ADC_CLOCK_FSYS
		{
			/* select ADC clock fsys */
			_adck2 = 0; _adck1 = 0; _adck0 = 0;
		}		
	#elif	ADC_CLOCK_FSYS_DIV2
		{
			/* select ADC clock fsys/2 */
			_adck2 = 0; _adck1 = 0; _adck0 = 1;
		}
	#elif	ADC_CLOCK_FSYS_DIV4
		{
			/* select ADC clock fsys/4 */
			_adck2 = 0; _adck1 = 1; _adck0 = 0;
		}
	#elif	ADC_CLOCK_FSYS_DIV8
		{
			/* select ADC clock fsys/8 */
			_adck2 = 0; _adck1 = 1; _adck0 = 1;
		}
	#elif	ADC_CLOCK_FSYS_DIV16
		{
			/* select ADC clock fsys16 */
			_adck2 = 1; _adck1 = 0; _adck0 = 0;
		}
	#elif	ADC_CLOCK_FSYS_DIV32
		{
			/* select ADC clock fsys/32 */
			_adck2 = 1; _adck1 = 0; _adck0 = 1;
		}
	#elif	ADC_CLOCK_FSYS_DIV64
		{
			/* select ADC clock fsys/64 */
			_adck2 = 1; _adck1 = 1; _adck0 = 0;
		}
	#endif	
/*************** end of ADC clock select ******************/	

						
/******** setting AD convert data alignment type **********/
	#ifdef	ADC_VALUE_ALIGN_RIGHT		
		{
			/* select AD convert data alignment right	*/
			_adrfs = 1;
		}	
	#else		
		{
			/* select 	AD convert data alignment left */	
			_adrfs = 0;
		}	
	#endif
/***** end of setting AD convert data alignment type ******/


/********** setting AD convert reference voltage *********/		
	#ifdef	ADC_REF_VOLTAGE_VDD
		{
			_vrefs = 0;
		}	
	#else
		{
			_vrefs = 1;
		}		
	#endif
/********* end of setting AD convert reference voltage *********/
}



/**
  * @brief select ADC channel.
  * @param[in] ADC_Channel: specifies the ADC channel.
  * can have one of the values of @ref ADC_Channel_TypeDef.
  * @retval  none.
  */
void ADC_SelectChannel(u8 ADC_Channel)
{
	_acs4 = 0;
	if((ADC_Channel >= 0)&&(ADC_Channel < 8))
	{
		/* clear ADC channel */
		_adcr0 &= 0b11111000;
		
		/* selection external ADC channel */
		_adcr0 |= ADC_Channel;
		
		/* select IO in AD input */
		_acerl = 0x01;
		_acerl <<= 	ADC_Channel;
	}
	else
	{
		/* selection internal ADC channel */
		ADC_VBG_ENABLE();	
		_acs4 = 1;		
	}	
}/* end of ADC_SelectChannel(u8 ADC_Channel) */


/**
  * @brief Get one sample of measured signal.
  * @param[in] None.
  * @retval ConversionValue:  value of the measured signal.
  */
u16 ADC_GetValue(void)
{
	u16 Value;
	
	/* start AD converter */
	ADC_START();
	
	/* waitting AD conversion finish */
	while(1 == _eocb);	
	
/* AD conversion data alignment right */
	#ifdef	ADC_VALUE_ALIGN_RIGHT		
		{
			/* get the AD conversion value */
			Value = (_adrh <<8) | _adrl;
		}	
	
/* AD conversion data alignment left */
	#else	
		{
			/* get the AD conversion value */
			Value = (_adrh <<4) | (_adrl >>4);
		}	
	#endif
	return Value;
}



/**
  * @brief Get one sample of measured signal.
  * @param[in] ADC_Channel: specifies the ADC channel.
  * can have one of the values of @ref ADC_Channel_TypeDef.
  * @retval ConversionValue:  value of the measured signal.
  * @par Required preconditions:
  * ADC conversion finished.
  */
u16 ADC_GetChannelValue(u8 ADC_Channel)
{
	u16 AD_ConverterValue;
	
	_acs4 = 0;
	if((ADC_Channel >= 0)&&(ADC_Channel < 8))
	{
		/* clear ADC channel */
		_adcr0 &= 0b11111000;
		
		/* selection external ADC channel */
		_adcr0 |= ADC_Channel;
		
		/* select IO in AD input */
		_acerl = 0x01;
		_acerl <<= 	ADC_Channel;
	}
	else
	{
		/* selection internal ADC channel */
		ADC_VBG_ENABLE();	
		_acs4 = 1;		
	}
	
	/* start AD convert */
	ADC_START();
		
	/* waitting AD conversion finish */	
	while(1 == _eocb);	
	
	/* AD conversion data alignment right */
	#ifdef	ADC_VALUE_ALIGN_RIGHT		
		{
			/* get the AD conversion value */
			AD_ConverterValue = (_adrh <<8) | _adrl;
		}	
			
	/* AD conversion data alignment left */
	#else	
		{
			/* get the AD conversion value */
			AD_ConverterValue = (_adrh <<4) | (_adrl >>4);
		}	
	#endif
	
		return AD_ConverterValue;
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
	
/***********TM1************/
	_tm1c0=0x10;			//选择系统时钟fsys作为t1时钟fint=8MHZ	
	_tm1c1=0xc1;			//定时模式，a匹配
	_tm1al=0x20;			//定时初值  0x320=800
	_tm1ah=0x03;            //800/8MHZ=100us
	_t1af=0;				//清t中断标志位
	_t1on=1;				//启动定时
	_mf1e=1;				//开多功能中断
	_t1ae=1;	    		//开t1中断

/***********时基0************/	  
//	_tbc=0x87;      		//时基定时器配置使能 fTBC时钟源 LXT快速启振
//	_tb0f=0;               //时基0中断请求标志清零
//	_tb0e=1;               //时基0中断控制位使能
	
	_emi=1;		  			//开总中断
	
	GCC_CLRWDT();	       //清除看门狗
	clr_ram_en(0);         //数据存储区选择BANK0
	clr_ram_en(1);         //数据存储区选择BANK1

}



//void UART_SoftWareSendByte(u8 TxData)
//{
//	u8 i;
//	TXD = 0;					//start bit
//	GCC_DELAY(BAUDRATE);
//	
//	for(i=0;i<8;i++)			//send 8-bit data
//	{		
//		if(TxData & 0x01)
//		{
//			TXD = 1;
//		}
//		else 
//		{
//			TXD = 0;
//		}
//		GCC_DELAY(BAUDRATE);
//		TxData >>= 1;
//	}
//	TXD = 1;					//stop bit
//	GCC_DELAY(BAUDRATE);
//}
//====================================================//
//�ȳ�ʼ�����IO�ڣ�IO����������ظ�����ĿҪ���������//
//		   ������ĿҪ�������ò���ʼ������ģ��		   //
//		   ע�����������ó�ʼ���������Ⱥ�˳��		  //
//					�����������ע��				  //
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
		GCC_DELAY(2000);//�������Դ���ʱָ�������ڣ�����Ƶ8Mhz�£�һ��ָ������Ϊ0.5us	
/*		GCC_CLRWDT();*/
	}
}



//===========================PA�˿ڳ�ʼ������=========================================//
void GPIOA_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 wakeup,u8 GPIO_BitVal)  //u8 Ϊ�޷����ַ���
{
	if ((u8)GPIO_Mode == (u8)0x01)   //paΪ������ʱ
	{
		_pac|=GPIO_Pin;             //��pa����GPIO_PinΪ���룬����λpac ��ͬʱ������������
		_papu|=GPIO_Pin;
	}
	else
	{
		_pac&=(u8)(~GPIO_Pin);      //��pa����Ϊ����� 
		_papu&=(u8)(~GPIO_Pin);	
	}
	 
	if (GPIO_BitVal != RESET)       //����
	{
		_pa|=GPIO_Pin;
	}
	else
	{
		_pa&=(u8)(~GPIO_Pin);   

	}	 	
}
//===========================PB�˿ڳ�ʼ������=========================================//
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
//===========================PC�˿ڳ�ʼ������=========================================//
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



	
//===========================���ݴ洢��ʹ������=========================================//
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



//===========================ʱ�ӳ�ʼ������=========================================//
void Init_clock(void)
{
	_smod=0x01;            //ѡ��gao��ʱ��Ϊϵͳʱ�� �ڲ�8Mhz
	while(!_hto);          //�ȴ�����������λ
	_wdtc=0x57;            //ʹ�ܿ��Ź�
	_acerl=0x00;		   //ȡ��A/D����
	_tmpc=0x00;            //ȡ�������������TM ����/ �����������ű���ԭ������
	_cpc=0x08;             //�Ƚ���������ڲ�ʹ��
	_integ=0x00;			//�����ⲿ�жϱ��ؿ��Ƴ���
	_int0e=0;				//INTO�жϳ���
	_emi = 0;   			//�ر����ж�

/***********TM0************/
	_tm0c0=0x00;			//ѡ��ϵͳʱ��fsys��Ϊt0ʱ��fint=2MHZ	
	_tm0c1=0xc1;			//��ʱģʽ��aƥ��
	_tm0al=0x20;			//��ʱ��ֵ  0x4e20=20000
	_tm0ah=0x4e;            //20000/2MHZ=10ms
	_t0af=0;				//��t�жϱ�־λ
	_t0on=1;				//������ʱ
	_mf0e=1;				//���๦���ж�
	_t0ae=1;	    		//��t0�ж�
	
/***********TM1************/
	_tm1c0=0x10;			//ѡ��ϵͳʱ��fsys��Ϊt1ʱ��fint=8MHZ	
	_tm1c1=0xc1;			//��ʱģʽ��aƥ��
	_tm1al=0x20;			//��ʱ��ֵ  0x320=800
	_tm1ah=0x03;            //800/8MHZ=100us
	_t1af=0;				//��t�жϱ�־λ
	_t1on=1;				//������ʱ
	_mf1e=1;				//���๦���ж�
	_t1ae=1;	    		//��t1�ж�

/***********ʱ��0************/	  
//	_tbc=0x87;      		//ʱ����ʱ������ʹ�� fTBCʱ��Դ LXT��������
//	_tb0f=0;               //ʱ��0�ж������־����
//	_tb0e=1;               //ʱ��0�жϿ���λʹ��
	
	_emi=1;		  			//�����ж�
	
	GCC_CLRWDT();	       //������Ź�
	clr_ram_en(0);         //���ݴ洢��ѡ��BANK0
	clr_ram_en(1);         //���ݴ洢��ѡ��BANK1

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
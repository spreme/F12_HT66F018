/**
  ******************************************************************************
  * @file HT8_Simulation_UART\main.c
  * @brief This file contains the main function for the simulation UART transmit example.
  * @author Holtek Semiconductor Inc.
  * @version V1.0.0
  * @date 2018-12-20
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
#include "HT8_Simulation_UART.h"
#include "init.h"

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
  	_tm0c0=0x10;			//ѡ��ϵͳʱ��fsys��Ϊt1ʱ��fint=8MHZ	
  	_tm0c1=0xc1;			//��ʱģʽ��aƥ��
  	_tm0al=0x00;			//��ʱ��ֵ  0x300=768
  	_tm0ah=0x03;            //300/8MHZ=96us
  	_t0af=0;				//��t�жϱ�־λ
  	_t0on=1;				//������ʱ
  	_mf0e=1;				//���๦���ж�
  	_t0ae=1;	    		//��t0�ж�
/***********ʱ��0************/	  
  	//_tbc=0b10000111;       //ʱ����ʱ������ʹ�� fTBCʱ��Դ LXT��������
  	//_tb0f=0;               //ʱ��0�ж������־����
  	//_tb0e=1;               //ʱ��0�жϿ���λʹ��
  	
  	_emi=1;		  			//�����ж�
  	
  	GCC_CLRWDT();	       //������Ź�
	clr_ram_en(0);         //���ݴ洢��ѡ��BANK0
	clr_ram_en(1);         //���ݴ洢��ѡ��BANK1

}


//===========================��ʱ��0�ж����=========================================//
DEFINE_ISR(isr_TM0, 0x0c)   //��ʱ��0�жϺ���  191us
{
    _t0af=0;       //t0�ж������־����
    
    
    
    _emi=1;        //�����ж�	
}


vu8 g_nUART_TX_Data = 0;	//UART TX data

/**
  * @brief simulation UART transmit main entry point.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
  
void main()
{
	GCC_DELAY(100);  //��ʱ��ϵͳ�ȶ�	   
	Init_clock();   //��ʼ��ʱ��
	//======================�˿ڳ�ʼ��==============================//	   
	GPIOA_INIT(GPIO_Pin_All,GPIO_Mode_OUT,DISABLE,RESET);
	GPIOB_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	GPIOC_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	
	SIMULATION_UART_INIT();		//simulation uart initialization,set baud rate 9600(Fsys=8MHz)
	GCC_DELAY(2000);			//wait system stable
	//system loop
	while(1)
	{
		
//		UART_SoftWareSendByte(g_nUART_TX_Data);	//send data to PC by UART
//		g_nUART_TX_Data++;						//transmit data+1,it will be transmit next loop

		UART_SoftWareSendByte(0xaa);		
		Send_String("hello,world!");
		GCC_CLRWDT();
		GCC_DELAY(1000);
		GCC_CLRWDT();
	}
}

/******************* (C) COPYRIGHT 2018 Holtek Semiconductor Inc *****END OF FILE****/
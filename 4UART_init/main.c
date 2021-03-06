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
  	_tm0c0=0x10;			//选择系统时钟fsys作为t1时钟fint=8MHZ	
  	_tm0c1=0xc1;			//定时模式，a匹配
  	_tm0al=0x00;			//定时初值  0x300=768
  	_tm0ah=0x03;            //300/8MHZ=96us
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


//===========================定时器0中断入口=========================================//
DEFINE_ISR(isr_TM0, 0x0c)   //定时器0中断函数  191us
{
    _t0af=0;       //t0中断请求标志清零
    
    
    
    _emi=1;        //开总中断	
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
	GCC_DELAY(100);  //延时待系统稳定	   
	Init_clock();   //初始化时钟
	//======================端口初始化==============================//	   
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
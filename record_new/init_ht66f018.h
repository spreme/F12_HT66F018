#ifndef __INIT_HT66F018_H__
#define __INIT_HT66F018_H__

#include "define.h"

void WDT_Init();


void TimeBase_Init(void);


/** ADC initialization function£¬you can select 
  * ADC clock,ADC reference voltage and AD converter
  * data format in ADC.h **/
void ADC_Init(void);

/** ADC channel select function£¬you can select 
  * the channel that you want to use **/
void ADC_SelectChannel(u8 ADC_Channel);

/** ADC converter function£¬ when you have already
  * select one channel£¬you can get the AD converter
  * value by this function **/
u16 ADC_GetValue(void);

/** ADC channel select and get AD converter data
  * function **/
u16 ADC_GetChannelValue(u8 ADC_Channel);


void Delay_ms(unsigned int ms);

void GPIOA_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 wakeup,u8 GPIO_BitVal);  //u8 ÎªÎÞ·ûºÅ×Ö·ûÐÍ

void GPIOB_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 GPIO_BitVal);

void GPIOC_INIT(u8 GPIO_Pin,u8 GPIO_Mode,u8 GPIO_BitVal);

void clr_ram_en(unsigned char t);

void Init_clock(void);

//void UART_SoftWareSendByte(u8 TxData);


#endif
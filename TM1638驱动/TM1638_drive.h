/*********************************************************************
 *
 *                           TM1638_drive.h
 *
 *********************************************************************
 * ��    ��: TM1638��������ͷ�ļ�
 * ����ƽ̨: KEIL C51
 * ��    ˾: 			
 * ��    ַ: 
 * ����			����			ע��
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ���ƴ������		18/10/26		ԭʼ�ļ�
 
 ********************************************************************/

#ifndef TM1638_DRIVE_H
#define TM1638_DRIVE_H

#include<stc15series.h>

#define K1S1   1
#define K1S2   2
#define K1S3   3
#define K1S4   4
#define K1S5   5
#define K1S6   6
#define K1S7   7
#define K1S8   8
#define K2S1   9
#define K2S2   10
#define K2S3   11
#define K2S4   12
#define K2S5   13
#define K2S6   14
#define K2S7   15
#define K2S8   16
#define K3S1   17
#define K3S2   18
#define K3S3   19
#define K3S4   20
#define K3S5   21
#define K3S6   22
#define K3S7   23
#define K3S8   24

#define SEG9      0
#define SEG10     1
#define SEG9SEG10 2

//TM1638ģ�����Ŷ���
sbit	DIO=P1^0;
sbit	CLK=P1^1;
sbit	STB=P1^2;

 //��������ܶ���
extern unsigned char code Num_tab[16];

//TM1638��8��λ��  ��SEG1-SEG8��
extern unsigned char code WeiL_tab[8];

//TM1638��2��λ��  ��SEG9-SEG10��
extern unsigned char code WeiH_tab[8];

void TM1638_W_DATA(unsigned char DATA);
void TM1638_W_CMD(unsigned char cmd);
void Write_DATA(unsigned char add,unsigned char DATA);
void init_TM1638(void);
unsigned char Read_Onekey(void);
void WriteSEG9_LED(unsigned char sta);
void WriteSEG10_LED(unsigned char sta);
void Write_LED(unsigned char sta9,unsigned char sta10);



#endif 
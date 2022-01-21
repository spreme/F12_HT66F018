/*********************************************************************
 *
 *                           TM1638_drive.c
 *
 *********************************************************************
 * ��    ��: TM1638����������
 * ����ƽ̨: KEIL C51
 * �Ա���ַ: https://shop472896494.taobao.com			 
 * ����			����			ע��
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ���ƴ������		18/10/26		ԭʼ�ļ�
 *
 ********************************************************************/

#include <TM1638_drive.h>

 //��������ܶ���
unsigned char code Num_tab[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                           0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

//TM1638��8��λ��  ��SEG1-SEG8��
unsigned char code WeiL_tab[]={0xce,0xcc,0xca,0xc8,0xc6,0xc4,0xc2,0xc0};

//TM1638��2��λ��  ��SEG9-SEG10��
unsigned char code WeiH_tab[]={0xcf,0xcd,0xcb,0xc9,0xc7,0xc5,0xc3,0xc1};

void TM1638_W_DATA(unsigned char	DATA)			//д���ݺ���
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		CLK=0;
		if(DATA&0X01)
			DIO=1;
		else
			DIO=0;
		DATA>>=1;
		CLK=1;
	}
}

void TM1638_W_CMD(unsigned char cmd)		//д�����
{
	STB=0;
	TM1638_W_DATA(cmd);
	STB=1;
}

void Write_DATA(unsigned char add,unsigned char DATA)		//ָ����ַд������
{
	TM1638_W_CMD(0x44);
	STB=0;
	TM1638_W_DATA(add);
	TM1638_W_DATA(DATA);
	STB=1;
}

unsigned char TM1638_Read(void)					//�����ݺ���
{
	unsigned char i;
	unsigned char temp=0;
	DIO=1;	//����Ϊ����
	for(i=0;i<8;i++)
	{
		temp>>=1;
		
		CLK=0;
		CLK=1;							   //CLK�����ض����ݲ���Ч

		if(DIO)
			temp|=0x80;
	}
	return temp;
}

unsigned char Read_Onekey(void)	           //��һ�°���ֵ����֧����ϼ�
{
	unsigned char key_val[4],i,key=0;
	
	STB=0;
	
	TM1638_W_DATA(0x42);		           //����ɨ��������  ע�⣺����Ҫ�ȶ���4�ֽڼ�ֵ���ܽ�STB��1���������ֵ��Ч
	
	for(i=0;i<4;i++)		
		key_val[i]=TM1638_Read();
	
	STB=1;					           //4���ֽ����ݺϳ�һ���ֽ�


	if(key_val[0]!=0)        //������KS1��KS2
	{
		switch(key_val[0])
		{
			case 1:
				key=K3S1;
			break;
			
			case 2:
				key=K2S1;
			break;
			
			case 4:
				key=K1S1;
			break;

			case 16:
				key=K3S2;
			break;
			
			case 32:
				key=K2S2;
			break;
			
			case 64:
				key=K1S2;
			break;
		}
	}
	else if(key_val[1]!=0)        //������KS3��KS4
	{
		switch(key_val[1])
		{
			case 1:
				key=K3S3;
			break;
			
			case 2:
				key=K2S3;
			break;
			
			case 4:
				key=K1S3;
			break;

			case 16:
				key=K3S4;
			break;
			
			case 32:
				key=K2S4;
			break;
			
			case 64:
				key=K1S4;
			break;
		}
	}
	else if(key_val[2]!=0)        //������KS5��KS6
	{
		switch(key_val[2])
		{
			case 1:
				key=K3S5;
			break;
			
			case 2:
				key=K2S5;
			break;
			
			case 4:
				key=K1S5;
			break;

			case 16:
				key=K3S6;
			break;
			
			case 32:
				key=K2S6;
			break;
			
			case 64:
				key=K1S6;
			break;
		}
	}
	else if(key_val[3]!=0)        //������KS7��KS8
	{
		switch(key_val[3])
		{
			case 1:
				key=K3S7;
			break;
			
			case 2:
				key=K2S7;
			break;
			
			case 4:
				key=K1S7;
			break;

			case 16:
				key=K3S8;
			break;
			
			case 32:
				key=K2S8;
			break;
			
			case 64:
				key=K1S8;
			break;
		}
	}
	
	return key;

}

void WriteSEG9_LED(unsigned char sta)					//����ȫ��LED������LED_flag��ʾ����LED״̬
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(sta&(1<<i))
			Write_DATA(WeiH_tab[i],1);
		else
			Write_DATA(WeiH_tab[i],0);
	}
}

void WriteSEG10_LED(unsigned char sta)					//����ȫ��LED������LED_flag��ʾ����LED״̬
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(sta&(1<<i))
			Write_DATA(WeiH_tab[i],2);
		else
			Write_DATA(WeiH_tab[i],0);
	}
}

void Write_LED(unsigned char sta9,unsigned char sta10)					//����ȫ��LED������LED_flag��ʾ����LED״̬
{
	// 0b 1 0 0 0 0 0 0 0
	// 0b 0 1 1 0 0 0 0 0 

	Write_DATA(WeiH_tab[7],((sta10&0x80)>>6)|((sta9&0x80)>>7));
	Write_DATA(WeiH_tab[6],((sta10&0x40)>>5)|((sta9&0x40)>>6));
	Write_DATA(WeiH_tab[5],((sta10&0x20)>>4)|((sta9&0x20)>>5));
	Write_DATA(WeiH_tab[4],((sta10&0x10)>>3)|((sta9&0x10)>>4));
	Write_DATA(WeiH_tab[3],((sta10&0x08)>>2)|((sta9&0x08)>>3));
	Write_DATA(WeiH_tab[2],((sta10&0x04)>>1)|((sta9&0x04)>>2));
	Write_DATA(WeiH_tab[1],(sta10&0x02)|((sta9&0x02)>>1));
	Write_DATA(WeiH_tab[0],((sta10&0x01)<<1)|(sta9&0x01));

}

//TM1638��ʼ������
void init_TM1638(void)
{
	unsigned char i;
	TM1638_W_CMD(0x89);       //���� (0x88-0x8f)8�����ȿɵ�
	TM1638_W_CMD(0x40);       //���õ�ַ�Զ���1
	STB=0;		           //
	TM1638_W_DATA(0xc0);    //������ʼ��ַ

	for(i=0;i<16;i++)	   //����16���ֽڵ�����
		TM1638_W_DATA(0x00);
	STB=1;
}


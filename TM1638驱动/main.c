/*********************************************************************
 
 * �Ա���ַ: https://shop472896494.taobao.com			 
 * ��    �ߣ����ƴ������

 ********************************************************************/
#include <stc15series.h>
#include <TM1638_drive.h>
#include <delay.h>

void sys_init()
{
	unsigned char i;
	
	init_TM1638();	                           //��ʼ��TM1638

	for(i=0;i<8;i++)
		Write_DATA(WeiL_tab[i],Num_tab[8]);	               //��ʼ���Ĵ���

	Write_LED(0xff,0xff);	

	delayms(5000);
	
	Write_LED(0,0);

	for(i=0;i<8;i++)
		Write_DATA(WeiL_tab[i],0x00);	               //��ʼ���Ĵ���

	Write_DATA(WeiL_tab[6],Num_tab[0]);
	Write_DATA(WeiL_tab[7],Num_tab[0]);	

}

void main()
{
	
	unsigned char key=0;
	
	sys_init();

	while(1)
	{
		key=Read_Onekey();
		
		if(key>=1&&key<=64)
		{	
			Write_DATA(WeiL_tab[6],Num_tab[key/10]);
			Write_DATA(WeiL_tab[7],Num_tab[key%10]);	 

			if(key==1)
			{
				Write_LED(0x60,0x80);
			}
			else if(key==2)
			{
				Write_LED(0xda,0x40);		 
			}
			else if(key==3)
			{
				Write_LED(0xf2,0x20);		   
			}
			else if(key==9)
			{
				Write_LED(0x66,0x10);		  
			}
			else if(key==10)
			{
				Write_LED(0xb6,0x08);		  
			}
			else if(key==11)
			{
				Write_LED(0xbe,0x04);		  
			}
			else if(key==17)
			{
				Write_LED(0xe0,0x02);		 
			}
			else if(key==18)
			{
				Write_LED(0xfe,0x01);			
			}

			while(Read_Onekey()==key);		       //�ȴ������ͷ�
		}
		
	}
}
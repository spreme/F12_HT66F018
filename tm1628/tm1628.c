#include "HT66F018.h"
#include "init.h"

#define uchar unsigned char
#define u16 unsigned int


struct rtc_time {
	volatile uchar hour;
	volatile uchar minute;
	volatile uchar second;
};
struct rtc_time rtc_date;


#define STB _pa3		 
#define DIO	_pb6     
#define CLK	_pb5	 

const static uchar Num_tab_7[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//����
const static uchar Num_tab_8[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};//��������С���㣩

//TM1628A��8��λ�롾SEG1-SEG8��
const static uchar WeiL_tab[]={0xce,0xcc,0xca,0xc8,0xc6,0xc4,0xc2,0xc0};

//TM1628A��8��λ�롾SEG9-SEG10��
const static uchar WeiH_tab[]={0xcf,0xcd,0xcb,0xc9,0xc7,0xc5,0xc3,0xc1};

u8 col_staus=1;

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
  	_tm0al=0xf8;			//��ʱ��ֵ  0x5f8=1528
  	_tm0ah=0x05;            //1528/8MHZ=191us
  	_t0af=0;				//��t�жϱ�־λ
  	_t0on=1;				//������ʱ
  	_mf0e=1;				//���๦���ж�
  	_t0ae=1;	    		//��t0�ж�
/***********TM1************/
  	_tm0c0=0x10;			//ѡ��ϵͳʱ��fsys��Ϊt1ʱ��fint=8MHZ	
  	_tm0c1=0xc1;			//��ʱģʽ��aƥ��
  	_tm0al=0xf8;			//��ʱ��ֵ  0x5f8=1528
  	_tm0ah=0x05;            //1528/2MHZ=191us
  	_t0af=0;				//��t�жϱ�־λ
  	_t0on=1;				//������ʱ
  	_mf0e=1;				//���๦���ж�
  	_t0ae=1;	    		//��t0�ж�

/***********ʱ��0************/	  
  	_tbc=0x87;       //ʱ����ʱ������ʹ�� fTBCʱ��Դ LXT��������
  	_tb0f=0;               //ʱ��0�ж������־����
  	_tb0e=1;               //ʱ��0�жϿ���λʹ��
  	
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

DEFINE_ISR(isr_TB0, 0x1c)   //ʱ��0�жϺ���  1s
{
    _tb0f=0;       //tb0�ж������־����
    
	rtc_date.second++;
	if(rtc_date.second >59)
	{ 
		rtc_date.minute++;
		rtc_date.second=0;
//		feed_detect = 1;	//��ʱιʳʱ���⣬ÿ���Ӽ��һ��
//		time_save_flag = 1;
		
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
    
   
    _emi=1;        //�����ж�	
}

void main()
{	
	   GCC_DELAY(100);  //��ʱ��ϵͳ�ȶ�	   
	   Init_clock();   //��ʼ��ʱ��
//======================�˿ڳ�ʼ��==============================//	   
	   GPIOA_INIT(GPIO_Pin_All,GPIO_Mode_OUT,DISABLE,RESET);
	   GPIOB_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	   GPIOC_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);

	   init_TM1628();

		rtc_date.hour = 20;
		rtc_date.minute = 10;
		rtc_date.second = 0;
		
	    _emi = 1;   //�����ж�
	
	while(1)
	{

		Write_DATA(WeiL_tab[7],Num_tab_7[rtc_date.hour/10]);
		
            if(rtc_date.second %2 ==0)   //ʱ�������
            {
                Write_DATA(WeiL_tab[6],Num_tab_7[rtc_date.hour%10]);
            }
            else
            {
                Write_DATA(WeiL_tab[6],Num_tab_8[rtc_date.hour%10]);	
            }
		
//		Write_DATA(WeiL_tab[6],Num_tab_7[rtc_date.hour%10]);
				
		Write_DATA(WeiL_tab[5],Num_tab_7[rtc_date.minute/10]);
		Write_DATA(WeiL_tab[4],Num_tab_7[rtc_date.minute%10]);
		Write_DATA(WeiL_tab[3],0x00);
		Write_DATA(WeiL_tab[2],0x00);
		Write_DATA(WeiL_tab[1],0x00);
		

		GCC_CLRWDT();          //ι��

/*		
        if(col_staus)
        {
			;
        }
*/
		
	}
	
}
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

const static uchar Num_tab_7[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//共阴
const static uchar Num_tab_8[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};//共阴（带小数点）

//TM1628A低8段位码【SEG1-SEG8】
const static uchar WeiL_tab[]={0xce,0xcc,0xca,0xc8,0xc6,0xc4,0xc2,0xc0};

//TM1628A低8段位码【SEG9-SEG10】
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
  	_tm0al=0xf8;			//定时初值  0x5f8=1528
  	_tm0ah=0x05;            //1528/8MHZ=191us
  	_t0af=0;				//清t中断标志位
  	_t0on=1;				//启动定时
  	_mf0e=1;				//开多功能中断
  	_t0ae=1;	    		//开t0中断
/***********TM1************/
  	_tm0c0=0x10;			//选择系统时钟fsys作为t1时钟fint=8MHZ	
  	_tm0c1=0xc1;			//定时模式，a匹配
  	_tm0al=0xf8;			//定时初值  0x5f8=1528
  	_tm0ah=0x05;            //1528/2MHZ=191us
  	_t0af=0;				//清t中断标志位
  	_t0on=1;				//启动定时
  	_mf0e=1;				//开多功能中断
  	_t0ae=1;	    		//开t0中断

/***********时基0************/	  
  	_tbc=0x87;       //时基定时器配置使能 fTBC时钟源 LXT快速启振
  	_tb0f=0;               //时基0中断请求标志清零
  	_tb0e=1;               //时基0中断控制位使能
  	
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

DEFINE_ISR(isr_TB0, 0x1c)   //时基0中断函数  1s
{
    _tb0f=0;       //tb0中断请求标志清零
    
	rtc_date.second++;
	if(rtc_date.second >59)
	{ 
		rtc_date.minute++;
		rtc_date.second=0;
//		feed_detect = 1;	//定时喂食时间检测，每分钟检测一次
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
    
   
    _emi=1;        //开总中断	
}

void main()
{	
	   GCC_DELAY(100);  //延时待系统稳定	   
	   Init_clock();   //初始化时钟
//======================端口初始化==============================//	   
	   GPIOA_INIT(GPIO_Pin_All,GPIO_Mode_OUT,DISABLE,RESET);
	   GPIOB_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);
	   GPIOC_INIT(GPIO_Pin_All,GPIO_Mode_OUT,RESET);

	   init_TM1628();

		rtc_date.hour = 20;
		rtc_date.minute = 10;
		rtc_date.second = 0;
		
	    _emi = 1;   //开总中断
	
	while(1)
	{

		Write_DATA(WeiL_tab[7],Num_tab_7[rtc_date.hour/10]);
		
            if(rtc_date.second %2 ==0)   //时间点跳动
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
		

		GCC_CLRWDT();          //喂狗

/*		
        if(col_staus)
        {
			;
        }
*/
		
	}
	
}
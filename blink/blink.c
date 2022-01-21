#include "HT66F018.h"

unsigned int count = 0;
unsigned int count1 = 0;

void __attribute((interrupt(0x0C))) timer0(void)
{
	_t0af = 0;	
	
	count++;
	if(count >= 500)
	{
		_pc0 = 1;
		count = 0;	
	}
		
	_emi = 1;
}


void __attribute((interrupt(0x10))) timer1(void)
{
	_t1af = 0;
//	_t2af = 0;
    
    count1++;
    if(count1 >= 2)	
    {   
    	_pb4 = 1;
		count1 = 0;	
    }

    /* 一旦中断子程序被响应，系统将自动清除EMI位，所有其它的中断将被屏蔽 */
    _emi = 1;   //手动打开总中断
}

/*tb0，1s*/
void __attribute((interrupt(0x1c))) tb0(void)
{
	_tb0f = 0;

		
    /* 一旦中断子程序被响应，系统将自动清除EMI位，所有其它的中断将被屏蔽 */
    _emi = 1;   //手动打开总中断
}

/*tb1，1s*/
void __attribute((interrupt(0x20))) tb1(void)
{
	_tb1f = 0;

	
    /* 一旦中断子程序被响应，系统将自动清除EMI位，所有其它的中断将被屏蔽 */
    _emi = 1;   //手动打开总中断
}

/* int0 */
void __attribute((interrupt(0x04))) Int0(void)
{
    //不需要清除中断标志位

	
    _emi = 1;   //手动打开总中断
}


/* int1 */
void __attribute((interrupt(0x24))) Int1(void)
{
    //不需要清除中断标志位

    	
    _emi = 1;   //手动打开总中断
}


void main()
{
	_pcc0 = 0;
	_pbc4 = 0;
	
	_pc0 = 0;
	_pb4 = 0;	

	
    _cpc = 0x08;    //关比较器
    _tmpc = 0;  //禁止TMn输入/输出引脚

	_tbc = 0x37;
	
	_tm0c0 = 0x00; //TM0时钟为系统时钟4分频（Fsys=8M),则TM0时钟为2M,并关闭定时器
    _tm0c1 = 0xC1;  //定时/计数器模式模式，比较器A匹配（即16位比较）
    _tm0al = 0xD0;  //定时器T0赋初值，定时1ms
    _tm0ah = 0x07;

    _tm1c0 = 0x00;  //TM1时钟为系统时钟4分频（Fsys=8M),则TM1时钟为2M,并关闭定时器
    _tm1c1 = 0xC1;  //1100 0001 定时器模式，比较器A匹配
    _tm1al = 0xc8;
    _tm1ah = 0x00;  //定时器T1赋初值，定时100us	

    _tm2c0 = 0x30; //TM2时钟为系统时钟64分频（Fsys=8M),则TM2时钟为125kHz,并关闭定时器
    _tm2c1 = 0xC1;  //定时/计数器模式模式，比较器A匹配（即16位比较）
    _tm2al = 0x24;  //定时器T2赋初值，定时0.5s
    _tm2ah = 0xf4;



    _integ = 0x0f;      //外部INT0中断和INT1双沿控制
    _intc0 = 0x08;      //使能外部中断0，使能多功能中断0（其中包括TM0定时）
    _intc1 = 0x09;      //使能多功能中断1（即使能TM1中断），以及允许时基0中断	
    _intc2 = 0x01;      //允许时基1中断

    _mfi0 = 0x02;       //TM0比较匹配A中断使能
    
    _mfi1 = 0x02;       //TM1比较匹配A中断使能   
//    _mfi1 = 0x08;       //TM2比较匹配A中断使能   

    _mfi2 = 0x00;
   
   
    _t0on = 1;  //启动定时器0
    
    _t1on = 1;
//    _t2on = 1;
  
  	_tbon = 1;	//启动时基中断
    
    _int0e = 1; //使能外部中断0	
    _int1e = 1; //使能外部中断1

  	  
    _emi = 1;   //开总中断
    
    while(1)
    {
    	;
    }

}
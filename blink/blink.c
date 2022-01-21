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

    /* һ���ж��ӳ�����Ӧ��ϵͳ���Զ����EMIλ�������������жϽ������� */
    _emi = 1;   //�ֶ������ж�
}

/*tb0��1s*/
void __attribute((interrupt(0x1c))) tb0(void)
{
	_tb0f = 0;

		
    /* һ���ж��ӳ�����Ӧ��ϵͳ���Զ����EMIλ�������������жϽ������� */
    _emi = 1;   //�ֶ������ж�
}

/*tb1��1s*/
void __attribute((interrupt(0x20))) tb1(void)
{
	_tb1f = 0;

	
    /* һ���ж��ӳ�����Ӧ��ϵͳ���Զ����EMIλ�������������жϽ������� */
    _emi = 1;   //�ֶ������ж�
}

/* int0 */
void __attribute((interrupt(0x04))) Int0(void)
{
    //����Ҫ����жϱ�־λ

	
    _emi = 1;   //�ֶ������ж�
}


/* int1 */
void __attribute((interrupt(0x24))) Int1(void)
{
    //����Ҫ����жϱ�־λ

    	
    _emi = 1;   //�ֶ������ж�
}


void main()
{
	_pcc0 = 0;
	_pbc4 = 0;
	
	_pc0 = 0;
	_pb4 = 0;	

	
    _cpc = 0x08;    //�رȽ���
    _tmpc = 0;  //��ֹTMn����/�������

	_tbc = 0x37;
	
	_tm0c0 = 0x00; //TM0ʱ��Ϊϵͳʱ��4��Ƶ��Fsys=8M),��TM0ʱ��Ϊ2M,���رն�ʱ��
    _tm0c1 = 0xC1;  //��ʱ/������ģʽģʽ���Ƚ���Aƥ�䣨��16λ�Ƚϣ�
    _tm0al = 0xD0;  //��ʱ��T0����ֵ����ʱ1ms
    _tm0ah = 0x07;

    _tm1c0 = 0x00;  //TM1ʱ��Ϊϵͳʱ��4��Ƶ��Fsys=8M),��TM1ʱ��Ϊ2M,���رն�ʱ��
    _tm1c1 = 0xC1;  //1100 0001 ��ʱ��ģʽ���Ƚ���Aƥ��
    _tm1al = 0xc8;
    _tm1ah = 0x00;  //��ʱ��T1����ֵ����ʱ100us	

    _tm2c0 = 0x30; //TM2ʱ��Ϊϵͳʱ��64��Ƶ��Fsys=8M),��TM2ʱ��Ϊ125kHz,���رն�ʱ��
    _tm2c1 = 0xC1;  //��ʱ/������ģʽģʽ���Ƚ���Aƥ�䣨��16λ�Ƚϣ�
    _tm2al = 0x24;  //��ʱ��T2����ֵ����ʱ0.5s
    _tm2ah = 0xf4;



    _integ = 0x0f;      //�ⲿINT0�жϺ�INT1˫�ؿ���
    _intc0 = 0x08;      //ʹ���ⲿ�ж�0��ʹ�ܶ๦���ж�0�����а���TM0��ʱ��
    _intc1 = 0x09;      //ʹ�ܶ๦���ж�1����ʹ��TM1�жϣ����Լ�����ʱ��0�ж�	
    _intc2 = 0x01;      //����ʱ��1�ж�

    _mfi0 = 0x02;       //TM0�Ƚ�ƥ��A�ж�ʹ��
    
    _mfi1 = 0x02;       //TM1�Ƚ�ƥ��A�ж�ʹ��   
//    _mfi1 = 0x08;       //TM2�Ƚ�ƥ��A�ж�ʹ��   

    _mfi2 = 0x00;
   
   
    _t0on = 1;  //������ʱ��0
    
    _t1on = 1;
//    _t2on = 1;
  
  	_tbon = 1;	//����ʱ���ж�
    
    _int0e = 1; //ʹ���ⲿ�ж�0	
    _int1e = 1; //ʹ���ⲿ�ж�1

  	  
    _emi = 1;   //�����ж�
    
    while(1)
    {
    	;
    }

}
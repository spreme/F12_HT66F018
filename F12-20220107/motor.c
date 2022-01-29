#include "HT66F018.h"
#include "init_ht66f018.h"
#include "Clock_Run.h"
#include "KeyScan.h"
#include "EEPROM.h"
#include "define.h"
#include "motor.h"
#include "record_control.h"

u8 feed_error=0;			//ιʳ�����־λ��		1�������ʱ��2����3���������
u8 task_run_led=0;
u8 task_run_motor=0;				//ιʳ�б�־λ1��ιʳ�У� 0�����У�


u8 motor_run(void)
{
	u16 timeout = 600;			//�����жϵ����ʱ
	u16 i = 0;
	u8 key_cont = 0;

//	lcd_timeout = 0;

	//�������
	Motor_Driver = 1;



	//���õ��ת��һ���Ƕȣ��˳���λ����ѹ�ŵ�״̬����->��
#if 1
	key_cont = 0;
	i = 600;

	while(i)
	{
		use_delay_us(100);			//100*100us

		if(MOTOR_DET)
		{
			key_cont++;

			if(key_cont > 30)
			{
				break;
			}

//			break;	���ң�	
		}

		if(i < 20) //��ʱ����
		{
			timeout = 0;
			break;
		}

		i--;

	}

#else
	use_delay_us(10000);			//10000*100us
#endif

	//�ȴ�����ж�(�½��ش���)�������жϵ������ж��ж����ŵ�ƽ�Ƿ�Ϊ��(������ʱȥ��)
	//�ͱ�ʾ��λ���ػ����������ת����ѹ�ţ���ʱ���ֹͣת��
//	lcd_timeout = 0;

	while(timeout)
	{
		GCC_CLRWDT();
		
		if(MOTOR_DET == 0)
		{

			key_cont = 0;
			i = 20;
			use_delay_us(100);			//100*100us		//��ʱȥ��

			while(i)
			{
				use_delay_us(100);			//100*100us		//��ʱȥ��

				if(MOTOR_DET == 0)
				{
					key_cont++;
				}

				i--;
			}

			if(key_cont > 6)
			{
				key_cont = 0;
				use_delay_us(100);			//100*100us	//�ó�ʳ��������׼ȷ��λ
				break;
			}

		}
		use_delay_us(100);			//100*100us		//���ң�
		timeout--;

	}

	return timeout;
}



u8 motor(u8 count, u8 * err_type)
{
	u8 errs = 0;
	u8 feed_cont = count;		//�����жϵ��ת��������ÿת��һ�Σ�ιʳһ�ݣ����10g��
	u16 timeout = MOTO_TIMEOUT; //�����жϵ����ʱ

	u8 time_ir_out = 50;		//������ʱ����������5s

	/*	u8 errs_flag = 0;
	  u8 errs = 0;*/
	  
	task_run_led = 0;
	led_flag = 0;

	task_run_motor = 1;

	*err_type = 0;				//��մ�����

	while(feed_cont > 0)
	{
		GCC_CLRWDT();			//ι��
//		lcd_timeout = 0;

		if(IR_DET == 0)
			timeout = motor_run();
		else
		{
			feed_cont++;
			timeout = 5;	
		}

		//�����ʱ�����ûת��λ����̽�����(��λ����û�ж�)
		if(timeout == 0)
		{
			*err_type = ERROR_MOTOR_TIMEOUT;
			task_run_led = 1;
			led_flag = 4;
			goto err;
		}
				
		use_delay_us(100);			//100*100us	
		
		feed_cont--;
				
		if(IR_DET)
		{
			time_ir_out = 50;
			while(time_ir_out)
			{
				Motor_Driver = 0;
				time_ir_out--;
				use_delay_us(1000);			//100*100us		//��ʱȥ��
				
				if(IR_DET == 0)
					break;
				else
				{
					if(time_ir_out == 0)
					{
						*err_type = ERROR_IR;
						feed_error = ERROR_IR;
						led_flag = 1;
						goto err;
					}
				}
			}
		}
		
		if(*err_type)
		{
			if(feed_cont != 0)
			{
				errs++;
				
				if(errs < 2)
				{
					*err_type = 0;
				}
				else
				{
					goto err;
				}
			}
		}
		
		//�ɹ�ιʳһ��
		
		*err_type = 0;
		errs = 0;
		feed_error = 0;
				
	}


err:	
	Motor_Driver = 0;
	task_run_motor = 0;
//	lcd_timeout = 0;

	return (feed_cont);
}

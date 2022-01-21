#ifndef	__MOTOR_H
#define	__MOTOR_H


#define MOTO_TIMEOUT                600  //6s

//������
#define ERROR_MOTOR_TIMEOUT			0x01	//��ʱ
#define ERROR_EMPTY					0x02	//ιʳ������
#define ERROR_IR					0x03	//���ⱻ��
#define ERROR_EMPTY_NIR				0x04	//ʳ���
#define ERROR_FULL_IR				0x05	//ʳ������ס����
#define ERROR_EMPTY_IR				0x06	//ʳ��գ����ⱻ������ס

extern u8 err_type;
extern u8 feed_error;			//ιʳ�����־λ��		1�������ʱ��2����3���������
extern u8 task_run_led;

u8 motor(u8 count,u8 *err_type);

void motor_init(void);

#endif
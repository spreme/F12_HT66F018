#ifndef	__MOTOR_H
#define	__MOTOR_H


#define MOTO_TIMEOUT                600  //6s

//错误码
#define ERROR_MOTOR_TIMEOUT			0x01	//超时
#define ERROR_EMPTY					0x02	//喂食份数空
#define ERROR_IR					0x03	//红外被挡
#define ERROR_EMPTY_NIR				0x04	//食物空
#define ERROR_FULL_IR				0x05	//食物满挡住红外
#define ERROR_EMPTY_IR				0x06	//食物空，红外被不明挡住

extern u8 err_type;
extern u8 feed_error;			//喂食错误标志位：		1（电机超时）2（）3（红外错误）
extern u8 task_run_led;

u8 motor(u8 count,u8 *err_type);

void motor_init(void);

#endif
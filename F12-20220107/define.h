#ifndef __DEFINE_H__
#define __DEFINE_H__

#include "HT66F018.h"

/*#define	DEBUG	1	//only for debug*/



#define	WDT_ENABLE()			_we4=0;_we3=1;_we2=0;_we1=1;_we0=0
#define	WDT_DISABLE()			_wdtc = 0b10101000




#define	INT0_ISR_ENABLE()			_int0e = 1
#define	INT0_ISR_DISABLE()			_int0e = 0
#define	INT1_ISR_ENABLE()			_int1e = 1
#define	INT1_ISR_DISABLE()			_int1e = 0

#define	INT0_SET_FLAG()				_int0f = 1
#define	INT0_CLEAR_FLAG()			_int0f = 0
#define	INT1_SET_FLAG()				_int1f = 1
#define	INT1_CLEAR_FLAG()			_int1f = 0


/* interrupt control */
#define	EMI_ENABLE()			(_emi = 1)
#define	EMI_DISABLE()			(_emi = 0)

#define	MF0E_ENABLE()			(_mf0e = 1)
#define	MF0E_DISABLE()			(_mf0e = 0)
#define	MF0F_CLEAR_FLAG()		(_mf0f = 0)

#define	MF1E_ENABLE()			(_mf1e = 1)
#define	MF1E_DISABLE()			(_mf1e = 0)
#define	MF1F_CLEAR_FLAG()		(_mf1f = 0)

#define	MF2E_ENABLE()			(_mf2e = 1)
#define	MF2E_DISABLE()			(_mf2e = 0)
#define	MF2F_CLEAR_FLAG()		(_mf2f = 0)


#define		TB_ENABLE()					_tbon = 1
#define		TB_DISABLE()				_tbon = 0

#define		TB0_ISR_ENABLE()			_tb0e = 1
#define		TB0_ISR_DISABLE()			_tb0e = 0
#define		TB0_SET_FLAG()				_tb0f = 1
#define		TB0_CLEAR_FLAG()			_tb0f = 0
#define		TB0_FLAG()					_tb0f

#define		TB1_ISR_ENABLE()			_tb1e = 1
#define		TB1_ISR_DISABLE()			_tb1e = 0
#define		TB1_SET_FLAG()				_tb1f = 1
#define		TB1_CLEAR_FLAG()			_tb1f = 0
#define		TB1_FLAG()					_tb1f


/*
PAn/PBn/PCn：输入 / 输出口数据位
0：数据 0
1：数据 1
*/
#define Motor_Driver	_pa1
#define F8_R_LED		_pc0    
#define F8_Y_LED		_pb4	 
#define IRDA			_pb3		 
#define LED_G			_pa4     
#define LED_R			_pa5	 

#define STB				_pa3		 
#define DIO				_pb6     
#define CLK				_pb5	 

#define IR_DET			_pc1 
#define MOTOR_DET		_pc2 
#define ADC_KEY			_pb0 
#define BAT_DET			_pb1 
#define DC_DET			_pb2  


#define 	TXD		    _pa6			//TX pin mapping on PC0	
#define 	TXC		    _pac6			//TX pin input/output control
#define 	TXPU	    _papu6			//TX pin pull-high control

#define 	RXD		    _pa7			//TX pin mapping on PC0	
#define 	RXC		    _pac7			//TX pin input/output control
#define 	RXPU	    _papu7			//TX pin pull-high control

#define		SIMULATION_UART_INIT()	TXD=1,TXC=0,TXPU=1	

/**** select simulation uart baud for 8MHz system clock ****/	
//	#define BAUDRATE	404		// baud rate 4800,395~413
	#define BAUDRATE	193		// baud rate 9600,191~195
//	#define BAUDRATE	96		// baud rate 19200,93~99
//	#define BAUDRATE	43		// baud rate 38400,41~45
/***********************************************************/



#define ADC_0   (4000)		//VCC
#define ADC_KEY_UP   (2600)     //20K
#define ADC_KEY_DOWN   (3000)     //33K
#define ADC_KEY_SET   (3300)     //47K
#define ADC_KEY_TIME   (3450)     //56K
#define ADC_KEY_FEED   (3500)     //62K
#define ADC_KEY_RECORD   (3600)     //75K
#define ADC_KEY_PLAY   (3700)     //100K




//键值
enum KEY_TYPE_E
{
	KEY_NONE = 0,

	KEY_UP,
	KEY_DOWN,
	KEY_SET,
	KEY_TIME,
	KEY_FEED,
	KEY_RECORD,
	KEY_PLAY,

	KEY_UP_L,
	KEY_DOWN_L,
	KEY_SET_L,
	KEY_TIME_L,
	KEY_FEED_L,
	KEY_RECORD_L,
	KEY_PLAY_L	
};


typedef signed long  					s32;
typedef signed short 					s16;
typedef signed char  					s8;

typedef signed long  const 				sc32;  /* Read Only */
typedef signed short const 				sc16;  /* Read Only */
typedef signed char  const 				sc8;   /* Read Only */

typedef volatile signed long  			vs32;
typedef volatile signed short 			vs16;
typedef volatile signed char  			vs8;

typedef volatile signed long  const 	vsc32;  /* Read Only */
typedef volatile signed short const 	vsc16;  /* Read Only */
typedef volatile signed char  const 	vsc8;   /* Read Only */

typedef unsigned long  					u32;
typedef unsigned short 					u16;
typedef unsigned char  					u8;

typedef unsigned char  					uchar;
typedef unsigned int  					uint;

typedef unsigned long  const 			uc32;  /* Read Only */
typedef unsigned short const 			uc16;  /* Read Only */
typedef unsigned char  const 			uc8;   /* Read Only */

typedef volatile unsigned long  		vu32;
typedef volatile unsigned short 		vu16;
typedef volatile unsigned char  		vu8;

typedef volatile unsigned long  const 	vuc32;  /* Read Only */
typedef volatile unsigned short const 	vuc16;  /* Read Only */
typedef volatile unsigned char  const 	vuc8;   /* Read Only */

typedef enum
{
  FALSE = 0,
  TRUE = !FALSE
}bool;

typedef enum 
{
  RESET = 0,
  SET = !RESET
}FlagStatus, ITStatus, BitStatus;

typedef enum 
{
  DISABLE = 0,
  ENABLE = !DISABLE
}FunctionalState;

typedef enum 
{
  ERROR = 0,
  SUCCESS = !ERROR
}ErrorStatus;



#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */





#define		ADC_ENABLE()			_adoff = 0
#define		ADC_DISABLE()			_adoff = 1

#define		ADC_ISR_ENABLE()		_ade = 1
#define		ADC_ISR_DISABLE()		_ade = 0
#define		ADC_CLEAR_ISR_FLAG()	_adf = 0
#define		ADC_SET_ISR_FLAG()		_adf = 1

#define		ADC_VBG_ENABLE()		(_vbgen = 1)
#define		ADC_VBG_DISABLE()		(_vbgen = 0)

#define		ADC_START()				{_start = 0; _start = 1; _start = 0;}


/* attention：ADC clock is 0.1 to 2MHz,such as FSYS=8MHz，
 * ADC clock from FSYS/64 ~ FSYS/8 is OK.
 */
/******************* select ADC clock **********************/
//	#define		ADC_CLOCK_FSYS				(1)
//	#define		ADC_CLOCK_FSYS_DIV2			(1)
//	#define		ADC_CLOCK_FSYS_DIV4			(1)
	#define		ADC_CLOCK_FSYS_DIV8			(1)
//	#define		ADC_CLOCK_FSYS_DIV16		(1)
//	#define		ADC_CLOCK_FSYS_DIV32		(1)
//	#define		ADC_CLOCK_FSYS_DIV64		(1)
/* end of select ADC clock */


/*************** select ADC reference voltage **************/ 
	#define		ADC_REF_VOLTAGE_VDD			(1)
//	#define		ADC_REF_VOLTAGE_VREF		(1)
/* end of select ADC reference voltage */


/***************** select ADC data format ******************/
//	#define		ADC_VALUE_ALIGN_LEFT		(1)
	#define		ADC_VALUE_ALIGN_RIGHT		(1)
//end of select ADC data format



/**
  * @brief ADC analog channel selection list
  */
typedef enum 
{
	ADC_CH0  = (u8)0x00, /**< Analog channel 0 */
	ADC_CH1  = (u8)0x01, /**< Analog channel 1 */
	ADC_CH2  = (u8)0x02, /**< Analog channel 2 */
	ADC_CH3  = (u8)0x03, /**< Analog channel 3 */
	ADC_CH4  = (u8)0x04, /**< Analog channel 4 */
	ADC_CH5  = (u8)0x05, /**< Analog channel 5 */
	ADC_CH6  = (u8)0x06, /**< Analog channel 6 */
	ADC_CH7  = (u8)0x07, /**< Analog channel 7 */
	ADC_CH_INTERNAL_VBG		 = (u8)0x20, 
} ADC_Channel_TypeDef;


/* READ ADC VALUE function */

#ifdef	ADC_VALUE_ALIGN_LEFT
	
	#define	ADC_READ_VALUE()	(_adrh << 4) | (_adrl >> 4)
	
#else 

	#define	ADC_READ_VALUE()	(_adrh << 8) | _adrl

#endif



typedef enum
{
  GPIO_Pin_0    = ((u8)0x01),   /*!< Pin 0 selected */
  GPIO_Pin_1    = ((u8)0x02),   /*!< Pin 1 selected */
  GPIO_Pin_2    = ((u8)0x04),   /*!< Pin 2 selected */
  GPIO_Pin_3    = ((u8)0x08),   /*!< Pin 3 selected */
  GPIO_Pin_4    = ((u8)0x10),   /*!< Pin 4 selected */
  GPIO_Pin_5    = ((u8)0x20),   /*!< Pin 5 selected */
  GPIO_Pin_6    = ((u8)0x40),   /*!< Pin 6 selected */
  GPIO_Pin_7    = ((u8)0x80),   /*!< Pin 7 selected */
  GPIO_Pin_LNib = ((u8)0x0F),   /*!< Low nibble pins selected */
  GPIO_Pin_HNib = ((u8)0xF0),   /*!< High nibble pins selected */
  GPIO_Pin_All  = ((u8)0xFF)    /*!< All pins selected */
}GPIO_Pin_TypeDef;

typedef enum
{
  GPIO_Mode_INT      = (u8)0x01,   
  GPIO_Mode_OUT      = (u8)0x00,  

}GPIO_Mode_TypeDef;


#define   ENABLE     0X01             //1:使能
#define   DISABLE    0X00             //0:除能

#define   SET        0X01                //1：SET
#define   RESET      0X00                //0：RESET


const static uchar Num_tab_7[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//共阴
const static uchar Num_tab_8[10]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};//共阴

//TM1628A低8段位码【SEG1-SEG8】
const static uchar WeiL_tab[8]={0xce,0xcc,0xca,0xc8,0xc6,0xc4,0xc2,0xc0};

//TM1628A低8段位码【SEG9-SEG10】
const static uchar WeiH_tab[8]={0xcf,0xcd,0xcb,0xc9,0xc7,0xc5,0xc3,0xc1};

#define FEED_AGAIN_PERIOD 		30000		//300s  喂食错误之后5分钟再试一次

extern u8 led_flag;					//灯状态标志位        0：绿灯常亮	1：绿灯慢闪          2：绿灯灭 3：红灯常亮 4：红灯慢闪 5：红灯灭 6:全灭

#endif

/***********************************************************************/
/*  File Name   :Pin_Define.h                                          */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/

//cyw add 2014 11 04
#define Hanging_display 0
#define Hanging_none 1
#define ProductID Hanging_display


#if(ProductID==Hanging_none)//�������ĳ�ʼ��
/******************������data�Ĵ���************************************/
/* ADF7012 register interface */
#define ADF7021_SCLK            PB_ODR_ODR3     // Output   ʱ����
#define ADF7021_SDATA           PB_ODR_ODR2     // Output   ������
#define ADF7021_SLE             PB_ODR_ODR1     // Output   Ƭѡ
#define ADF7021_POWER           PB_ODR_ODR6     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE              PB_ODR_ODR0     // Output   ADF7012ʹ�ܽ�
#define ADF7021_MUXOUT          PB_IDR_IDR7    // Input   ADF7012��ؼ�� <2.35


/* Other ADF7021 connections */
#define ADF7021_DATA_tx         PB_ODR_ODR5     // Output   ����DATA��
#define ADF7021_DATA_CLK        PB_IDR_IDR4     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN		PA_IDR_IDR2   	// ����  OPEN��
#define	PIN_KEY_STOP		PA_IDR_IDR3     // ����  STOP��
#define	PIN_KEY_CLOSE		PD_IDR_IDR0     // ����  CLOSE��
#define PIN_KEY_VENT            PC_IDR_IDR1     // ����  ������
//#define	PIN_KEY_CLOSE		PD_IDR_IDR4     // ����  CLOSE��
//#define	PIN_KEY_LOGIN		PB_IDR_IDR7     // ����  LOGIN��
#define	PIN_KEY_LOGIN		PC_IDR_IDR6     // ����  LOGIN��
#define	PIN_UART_TX		PC_ODR_ODR5     // Output  uart TX

//#define PIN_LED                 PD_ODR_ODR0     // Output   LED��
#define PIN_LED                 PC_ODR_ODR4     // Output   LED��
#define PIN_TX_LED              PC_ODR_ODR4     // Output   LED��

//#define PIN_BEEP                PB_ODR_ODR5     // Output   ������
#define PIN_BEEP                PA_ODR_ODR0     // Output   ������
//#define PIN_POWER_CONTROL       PC_ODR_ODR1     // Output   ��Դ����
#define PIN_POWER_CONTROL       PB_ODR_ODR0     // Output   ��Դ����
#define PIN_POWER_AD            PB_IDR_IDR7     // ����     ��Դ���AD��

#define PIN_test_mode           PC_IDR_IDR0     // ����     test��

/************************�����Ƿ���Ĵ���*****************************/
/* ADF7012 register interface */
#define ADF7021_SCLK_direc      PB_DDR_DDR3     // Output   ʱ����
#define ADF7021_SDATA_direc     PB_DDR_DDR2     // Output   ������
#define ADF7021_SLE_direc       PB_DDR_DDR1     // Output   Ƭѡ
#define ADF7021_POWER_direc     PB_DDR_DDR6     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE_direc        PB_DDR_DDR0     // Output   ADF7012ʹ�ܽ�
#define ADF7021_MUXOUT_direc    PB_DDR_DDR7     // Input   ADF7012��ؼ�� <2.35

/* Other ADF7021 connections */
#define ADF7021_DATA_tx_direc   PB_DDR_DDR5     // Output   ����DATA��
#define ADF7021_DATA_CLK_direc  PB_DDR_DDR4     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN_direc	PA_DDR_DDR2   	// ����  OPEN��
#define	PIN_KEY_STOP_direc	PA_DDR_DDR3     // ����  STOP��
#define	PIN_KEY_CLOSE_direc	PD_DDR_DDR0     // ����  CLOSE��
#define PIN_KEY_VENT_direc      PC_DDR_DDR1     // ����  ������
//#define	PIN_KEY_CLOSE_direc	PD_DDR_DDR4     // ����  CLOSE��
//#define	PIN_KEY_LOGIN_direc	PB_DDR_DDR7     // ����  LOGIN��
#define	PIN_KEY_LOGIN_direc	PC_DDR_DDR6     // ����  LOGIN��
#define	PIN_UART_TX_direc	PC_DDR_DDR5     // Output  uart TX

//#define PIN_LED_direc          PD_DDR_DDR0     // Output   LED��
#define PIN_LED_direc           PC_DDR_DDR4     // Output   LED��

#define PIN_BEEP_direc          PA_DDR_DDR0     // Output   ������
//#define PIN_BEEP_direc          PB_DDR_DDR5     // Output   ������
//#define PIN_POWER_CONTROL_direc PC_DDR_DDR1     // Output   ��Դ����
#define PIN_POWER_CONTROL_direc PB_DDR_DDR0     // Output   ��Դ����
#define PIN_POWER_AD_direc      PB_DDR_DDR7     // ����     ��Դ���AD��

#define PIN_test_mode_direc     PC_DDR_DDR0     // ����     test��

/************************�����ǿ��ƼĴ���*****************************/
/* ADF7012 register interface */
#define ADF7021_SCLK_CR1        PB_CR1_C13     // Output   ʱ����
#define ADF7021_SDATA_CR1       PB_CR1_C12     // Output   ������
#define ADF7021_SLE_CR1         PB_CR1_C11     // Output   Ƭѡ
#define ADF7021_POWER_CR1       PB_CR1_C16     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE_CR1          PB_CR1_C10     // Output   ADF7012ʹ�ܽ�
#define ADF7021_MUXOUT_CR1      PB_CR1_C17    // Input   ADF7012��ؼ�� <2.35

/* Other ADF7021 connections */
#define ADF7021_DATA_tx_CR1     PB_CR1_C15     // Output   ����DATA��
#define ADF7021_DATA_CLK_CR1    PB_CR1_C14     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN_CR1	PA_CR1_C12   	// ����  OPEN��
#define	PIN_KEY_STOP_CR1	PA_CR1_C13     // ����  STOP��
#define	PIN_KEY_CLOSE_CR1	PD_CR1_C10     // ����  CLOSE��
#define PIN_KEY_VENT_CR1        PC_CR1_C11     // ����  ������
//#define	PIN_KEY_CLOSE_CR1	PD_CR1_C14     // ����  CLOSE��
//#define	PIN_KEY_LOGIN_CR1	PB_CR1_C17     // ����  LOGIN��
#define	PIN_KEY_LOGIN_CR1	PC_CR1_C16     // ����  LOGIN��
#define	PIN_UART_TX_CR1		PC_CR1_C15     // Output  uart TX

//#define PIN_LED_CR1           PD_CR1_C10     // Output   LED��
#define PIN_LED_CR1             PC_CR1_C14     // Output   LED��

#define PIN_BEEP_CR1            PA_CR1_C10     // Output   ������
//#define PIN_BEEP_CR1           PB_CR1_C15     // Output   ������
//#define PIN_POWER_CONTROL_CR1   PC_CR1_C11     // Output   ��Դ����
#define PIN_POWER_CONTROL_CR1   PB_CR1_C10     // Output   ��Դ����
#define PIN_POWER_AD_CR1        PB_CR1_C17     // ����     ��Դ���AD��

#define PIN_test_mode_CR1       PC_CR1_C10     // ����     test��


#define ADF7021_DATA_CLK_CR2    PB_CR2_C24     // ����   ����ͬ��ʱ����
#endif

#if(ProductID==Hanging_display)//�����ĳ�ʼ��
/* ADF7012 register interface */
#define ADF7021_SCLK            PD_ODR_ODR3     // Output   ʱ����
#define ADF7021_SDATA           PD_ODR_ODR2     // Output   ������
//#define ADF7021_SLE             PC_ODR_ODR3     // Output   Ƭѡ
//#define ADF7021_POWER           PC_ODR_ODR2     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE              PB_ODR_ODR0     // Output   ADF7012ʹ�ܽ�
#define ADF7021_MUXOUT          PB_IDR_IDR3    // Input   ADF7012��ؼ�� <2.35
#define ADF7021_SLE             PE_ODR_ODR7     // Output   Ƭѡ
#define ADF7021_POWER           PE_ODR_ODR6     // Output   ADF7012��Դʹ�ܽ�

/* Other ADF7021 connections */
#define ADF7021_DATA_tx         PB_ODR_ODR5     // Output   ����DATA��
#define ADF7021_DATA_CLK        PB_IDR_IDR4     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN		PA_IDR_IDR2   	// ����  OPEN��
#define	PIN_KEY_STOP		PA_IDR_IDR3     // ����  STOP��
#define	PIN_KEY_CLOSE		PA_IDR_IDR4     // ����  CLOSE��
#define PIN_KEY_VENT            PA_IDR_IDR5     // ����  ������
//#define	PIN_KEY_CLOSE		PD_IDR_IDR4     // ����  CLOSE��
//#define	PIN_KEY_LOGIN		PB_IDR_IDR7     // ����  LOGIN��
//#define	PIN_KEY_LOGIN		PC_IDR_IDR6     // ����  LOGIN��
#define	PIN_UART_TX		PC_ODR_ODR3     // Output  uart TX

#define PIN_KEY_DECIDE    PE_IDR_IDR4
#define PIN_KEY_CLOSETIME  PE_IDR_IDR5

//#define PIN_KEY_NOWTIME  PD_IDR_IDR0
#define PIN_KEY_NOWTIME  PA_IDR_IDR0//2015.3.13����

#define	PIN_KEY_LOGIN	PD_IDR_IDR6
//#define PIN_KEY_NOWTIME  PA_IDR_IDR6
//#define	PIN_KEY_LOGIN	PA_IDR_IDR5
#define PIN_KEY_OPENTIME  PD_IDR_IDR1
#define PIN_KEY_DEC      PE_IDR_IDR3// PE_IDR_IDR2
#define PIN_KEY_ADD      PE_IDR_IDR2// PE_IDR_IDR3


//#define PIN_LED                 PD_ODR_ODR0     // Output   LED��
#define PIN_LED                 PD_ODR_ODR7     // Output   LED��
#define PIN_TX_LED              PD_ODR_ODR7     // Output   LED��

//#define PIN_BEEP                PB_ODR_ODR5     // Output   ������
//#define PIN_BEEP                PA_ODR_ODR0     // Output   ������
#define PIN_BEEP                PD_ODR_ODR0     // Output   ������//2015.3.13����
//#define PIN_POWER_CONTROL       PC_ODR_ODR1     // Output   ��Դ����
#define PIN_POWER_CONTROL       PC_ODR_ODR6     // Output   ��Դ����
#define PIN_POWER_AD            PC_IDR_IDR4     // ����     ��Դ���AD��

#define PIN_test_mode           PA_IDR_IDR6     // ����     test��

#define PIN_LCD_SEL             PB_ODR_ODR2 
#define PIN_LCD_RST             PB_ODR_ODR1
#define PIN_LCD_LIGHT           PB_ODR_ODR7
#define PIN_FONT_SEL            PE_ODR_ODR0
#define PIN_LCD_RS             PB_ODR_ODR0
#define PIN_FONT_DATAIN        PE_IDR_IDR1

#define PIN_PCF8563_SDAOUT        PC_ODR_ODR0   //����Ĵ���
#define PIN_PCF8563_SDAIN        PC_IDR_IDR0
#define PIN_PCF8563_SCL          PC_ODR_ODR1



/************************�����Ƿ���Ĵ���*****************************/
/* ADF7012 register interface */
#define ADF7021_SCLK_direc      PD_DDR_DDR3     // Output   ʱ����
#define ADF7021_SDATA_direc     PD_DDR_DDR2     // Output   ������
//#define ADF7021_SLE_direc       PC_DDR_DDR3     // Output   Ƭѡ
//#define ADF7021_POWER_direc     PC_DDR_DDR2     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE_direc        PB_DDR_DDR0     // Output   ADF7012ʹ�ܽ�
#define ADF7021_MUXOUT_direc    PB_DDR_DDR3     // Input   ADF7012��ؼ�� <2.35
#define ADF7021_SLE_direc       PE_DDR_DDR7     // Output   Ƭѡ
#define ADF7021_POWER_direc     PE_DDR_DDR6     // Output   ADF7012��Դʹ�ܽ�


/* Other ADF7021 connections */
#define ADF7021_DATA_tx_direc   PB_DDR_DDR5     // Output   ����DATA��
#define ADF7021_DATA_CLK_direc  PB_DDR_DDR4     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN_direc	PA_DDR_DDR2   	// ����  OPEN��
#define	PIN_KEY_STOP_direc	PA_DDR_DDR3     // ����  STOP��
#define	PIN_KEY_CLOSE_direc	PA_DDR_DDR4     // ����  CLOSE��
#define PIN_KEY_VENT_direc      PA_DDR_DDR5     // ����  ������
//#define	PIN_KEY_CLOSE_direc	PD_DDR_DDR4     // ����  CLOSE��
//#define	PIN_KEY_LOGIN_direc	PB_DDR_DDR7     // ����  LOGIN��
#define PIN_KEY_DECIDE_direc    PE_DDR_DDR4
#define PIN_KEY_CLOSETIME_direc  PE_DDR_DDR5
//#define PIN_KEY_NOWTIME_direc  PD_DDR_DDR0
#define PIN_KEY_NOWTIME_direc  PA_DDR_DDR0//2015.3.13����

#define	PIN_KEY_LOGIN_direc	PD_DDR_DDR6
//#define PIN_KEY_NOWTIME_direc  PA_DDR_DDR6
//#define	PIN_KEY_LOGIN_direc	PA_DDR_DDR5
#define PIN_KEY_OPENTIME_direc  PD_DDR_DDR1
#define PIN_KEY_DEC_direc      PE_DDR_DDR3 // PE_DDR_DDR2
#define PIN_KEY_ADD_direc      PE_DDR_DDR2//  PE_DDR_DDR3

//#define	PIN_KEY_LOGIN_direc	PC_DDR_DDR6     // ����  LOGIN��
#define	PIN_UART_TX_direc	PC_DDR_DDR3     // Output  uart TX

//#define PIN_LED_direc          PD_DDR_DDR0     // Output   LED��
#define PIN_LED_direc           PD_DDR_DDR7     // Output   LED��

//#define PIN_BEEP_direc          PA_DDR_DDR0     // Output   ������
//#define PIN_BEEP_direc          PB_DDR_DDR5     // Output   ������
#define PIN_BEEP_direc          PD_DDR_DDR0//2015.3.13����

//#define PIN_POWER_CONTROL_direc PC_DDR_DDR1     // Output   ��Դ����
#define PIN_POWER_CONTROL_direc PC_DDR_DDR6     // Output   ��Դ����
#define PIN_POWER_AD_direc      PC_DDR_DDR4     // ����     ��Դ���AD��

#define PIN_test_mode_direc     PA_DDR_DDR6     // ����     test��

#define PIN_LCD_SEL_direc             PB_DDR_DDR2 
#define PIN_LCD_RST_direc             PB_DDR_DDR1
#define PIN_LCD_LIGHT_direc           PB_DDR_DDR7
#define PIN_FONT_SEL_direc            PE_DDR_DDR0
#define PIN_LCD_RS_direc             PB_DDR_DDR0 
#define PIN_FONT_DATAIN_direc        PE_DDR_DDR1

#define PIN_PCF8563_SDA_direc        PC_DDR_DDR0
#define PIN_PCF8563_SCL_direc        PC_DDR_DDR1

/************************�����ǿ��ƼĴ���*****************************/
/* ADF7012 register interface */
#define ADF7021_SCLK_CR1        PD_CR1_C13     // Output   ʱ����
#define ADF7021_SDATA_CR1       PD_CR1_C12     // Output   ������
//#define ADF7021_SLE_CR1         PC_CR1_C13     // Output   Ƭѡ
//#define ADF7021_POWER_CR1       PC_CR1_C12     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE_CR1          PB_CR1_C10     // Output   ADF7012ʹ�ܽ�
#define ADF7021_MUXOUT_CR1      PB_CR1_C13    // Input   ADF7012��ؼ�� <2.35
#define ADF7021_SLE_CR1         PE_CR1_C17     // Output   Ƭѡ
#define ADF7021_POWER_CR1       PE_CR1_C16     // Output   ADF7012��Դʹ�ܽ�

/* Other ADF7021 connections */
#define ADF7021_DATA_tx_CR1     PB_CR1_C15     // Output   ����DATA��
#define ADF7021_DATA_CLK_CR1    PB_CR1_C14     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN_CR1	PA_CR1_C12   	// ����  OPEN��
#define	PIN_KEY_STOP_CR1	PA_CR1_C13     // ����  STOP��
#define	PIN_KEY_CLOSE_CR1	PA_CR1_C14     // ����  CLOSE��
#define PIN_KEY_VENT_CR1        PA_CR1_C15     // ����  ������
//#define	PIN_KEY_CLOSE_CR1	PD_CR1_C14     // ����  CLOSE��
//#define	PIN_KEY_LOGIN_CR1	PB_CR1_C17     // ����  LOGIN��
//#define	PIN_KEY_LOGIN_CR1	PC_CR1_C16     // ����  LOGIN��

#define PIN_KEY_DECIDE_CR1    PE_CR1_C14
#define PIN_KEY_CLOSETIME_CR1  PE_CR1_C15
//#define PIN_KEY_NOWTIME_CR1  PD_CR1_C10
//2015.3.13����
#define PIN_KEY_NOWTIME_CR1  PA_CR1_C10

#define	PIN_KEY_LOGIN_CR1	PD_CR1_C16
//#define PIN_KEY_NOWTIME_CR1  PA_CR1_C16
//#define	PIN_KEY_LOGIN_CR1	PA_CR1_C15
#define PIN_KEY_OPENTIME_CR1  PD_CR1_C11
#define PIN_KEY_DEC_CR1       PE_CR1_C13//PE_CR1_C12
#define PIN_KEY_ADD_CR1       PE_CR1_C12//PE_CR1_C13

#define	PIN_UART_TX_CR1		PC_CR1_C13     // Output  uart TX

//#define PIN_LED_CR1           PD_CR1_C10     // Output   LED��
#define PIN_LED_CR1             PD_CR1_C17     // Output   LED��

//#define PIN_BEEP_CR1            PA_CR1_C10     // Output   ������
//2015.3.13����
#define PIN_BEEP_CR1            PD_CR1_C10     // Output   ������

//#define PIN_BEEP_CR1           PB_CR1_C15     // Output   ������
//#define PIN_POWER_CONTROL_CR1   PC_CR1_C11     // Output   ��Դ����
#define PIN_POWER_CONTROL_CR1   PC_CR1_C16     // Output   ��Դ����
#define PIN_POWER_AD_CR1        PC_CR1_C14     // ����     ��Դ���AD��

#define PIN_test_mode_CR1       PA_CR1_C16     // ����     test��


#define ADF7021_DATA_CLK_CR2    PB_CR2_C24     // ����   ����ͬ��ʱ����

#define PIN_LCD_SEL_CR1             PB_CR1_C12 
#define PIN_LCD_RST_CR1             PB_CR1_C11
#define PIN_LCD_LIGHT_CR1           PB_CR1_C17
#define PIN_FONT_SEL_CR1            PE_CR1_C10
#define PIN_LCD_RS_CR1              PB_CR1_C10
#define PIN_FONT_DATAIN_CR1         PE_CR1_C11

#define PIN_PCF8563_SDA_CR1        PC_CR1_C10
#define PIN_PCF8563_SCL_CR1        PC_CR1_C11


/**********/
#define POWER_ON   PIN_POWER_CONTROL=1
#define  POWER_OFF  PIN_POWER_CONTROL=0

#define LED_ON  if( Second_send_STR.flag_second_send != 3){PIN_LED=0;PIN_TX_LED=0;}
#define LED_OFF PIN_LED=1;PIN_TX_LED=1;

#define ADF7012_POWERON ADF7021_POWER = 1
#define ADF7012_POWEROFF ADF7021_POWER = 0

//#define BACKLIGHT_ON() FLAG_BACKLIGHT_5S = 7
#define TIME_10S()     {FLAG_BACKLIGHT_5S = 14;TB_POWER =150;}//��������� �����������ͨģʽ ���ص�Դʱ���
#define TIME_1S()     {FLAG_BACKLIGHT_1S = 2;TB_POWER =150;}
#define TIME_60S()     {FLAG_BACKLIGHT_60S = 84;TB_POWER =150;}

#endif
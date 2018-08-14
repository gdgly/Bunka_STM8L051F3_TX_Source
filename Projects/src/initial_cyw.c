/***********************************************************************/
/*  FILE        :initial_cyw.c                                             */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
//#include "stm8s.h"
//#include  <iostm8s003f3.h>
#include  <iostm8l151c6.h>				// CPU�ͺ� 
#include "initial.h"		// ��ʼ��  Ԥ����
#include "Pin_define.h"		// �ܽŶ���
#include "initial_cyw.h"		// ��ʼ��  Ԥ����
#include "ram_cyw.h"		// RAM����


#if(ProductID==Hanging_display)//
/****************�˿�����˵��***************************
CR1�Ĵ���  ��� Output��1=���졢0=OC��
           ���� Input��1=������0=������
***************end************************************/
void VHF_GPIO_INIT_cyw(void)   // CPU�˿�����
{
 /* ADF7012 register interface */  
  ADF7021_SCLK_direc = Output;   //PB2
  ADF7021_SCLK_CR1 = 1;	
  ADF7021_SCLK=0;
  
  ADF7021_SDATA_direc = Output;// PB2
  ADF7021_SDATA_CR1 = 1;
  ADF7021_SDATA=0;
  
  ADF7021_SLE_direc = Output; //PB1
  ADF7021_SLE_CR1 = 1;  
  ADF7021_SLE=0;
  
  ADF7021_POWER_direc = Output;//PB6
  ADF7021_POWER_CR1 = 1; 
  //ADF7021_POWER=1;
  ADF7012_POWEROFF;
  //ADF7021_CE_direc = Output;
  //ADF7021_CE_CR1 = 1; 
  //ADF7021_CE=0;
  
  ADF7021_MUXOUT_direc=Input;//PB7
  ADF7021_MUXOUT_CR1=0;    //ADF7012Ҫ���������
  
/* Other ADF7021 connections */
  ADF7021_DATA_tx_direc = Output; // Output   ����DATA��//PB5
  ADF7021_DATA_tx_CR1 = 1;
  ADF7021_DATA_tx=0;
  
  ADF7021_DATA_CLK_direc= Input;//PB4
  ADF7021_DATA_CLK_CR1= 1;

  PIN_KEY_OPEN_direc = Input; 	// ����  OPEN��
  PIN_KEY_OPEN_CR1 = 1;
  
  PIN_KEY_STOP_direc = Input;    // ����  STOP��
  PIN_KEY_STOP_CR1 = 1;
  
  PIN_KEY_CLOSE_direc = Input;   // ����  CLOSE��
  PIN_KEY_CLOSE_CR1 = 1;
  
  PIN_KEY_VENT_direc = Input;   // ����  ������
  PIN_KEY_VENT_CR1 = 1;
  
 PIN_KEY_LOGIN_direc = Input;   // ����  LOGIN��
  PIN_KEY_LOGIN_CR1 = 1;
  
  PIN_KEY_DECIDE_direc = Input;   // ����  LOGIN��
  PIN_KEY_DECIDE_CR1 = 1;
  
  PIN_KEY_CLOSETIME_direc = Input;   // ����  LOGIN��
  PIN_KEY_CLOSETIME_CR1 = 1;
  
  PIN_KEY_NOWTIME_direc = Input;   // ����  LOGIN��
  PIN_KEY_NOWTIME_CR1 = 1;
  
  PIN_KEY_OPENTIME_direc = Input;   // ����  LOGIN��
  PIN_KEY_OPENTIME_CR1 = 1;

  PIN_KEY_DEC_direc = Input;   // ����  LOGIN��
  PIN_KEY_DEC_CR1 = 1;
  
  PIN_KEY_ADD_direc = Input;   // ����  LOGIN��
  PIN_KEY_ADD_CR1 = 1;
  
  PIN_LED_direc = Output;     // Output   LED��
  PIN_LED_CR1 = 1;
  LED_OFF;
  
  
  PIN_BEEP_direc = Output;    // Output   ������
  PIN_BEEP_CR1 = 1;
  PIN_BEEP=0;
  
  PIN_POWER_CONTROL_direc = Output;    // Output   ��Դ����
  PIN_POWER_CONTROL_CR1 = 1;
  POWER_OFF;
  
  PIN_test_mode_direc=Input;    // ����     test��
  PIN_test_mode_CR1=1;
  
  PIN_POWER_AD_direc = Input;     // ����     ��Դ���AD�� 
  PIN_POWER_AD_CR1 =1;//ʱ�ӱ���
  
  PIN_LCD_SEL_direc = Output;
  PIN_LCD_SEL_CR1   = 1;// ����
  PIN_LCD_SEL       = 1;// Һ��LCD��ѡ��
  
  
  PIN_LCD_LIGHT_direc = Output;
  PIN_LCD_LIGHT_CR1   = 1;
  
  PIN_LCD_RST_direc = Output;
  PIN_LCD_RST_CR1  = 1;
  
  
  
  PIN_LCD_LIGHT_direc = Output;
  PIN_LCD_LIGHT_CR1 = 1;
  
  
  PIN_FONT_SEL_direc = Output;
  PIN_FONT_SEL_CR1  = 1;
  PIN_FONT_SEL      = 1;//font ��ѡ��
  
  PIN_LCD_RS_direc = Output;
  PIN_LCD_RS_CR1   = 1;
  
  
  PIN_FONT_DATAIN_direc = Input;
  PIN_FONT_DATAIN_CR1 = 1;//����
  
  
  PIN_PCF8563_SDA_direc = Output;
  PIN_PCF8563_SDA_CR1 = 0;
  PIN_PCF8563_SDAOUT = 1;//ZHIGAO
  
  PIN_PCF8563_SCL_direc = Output;
  PIN_PCF8563_SCL_CR1 = 0;
  PIN_PCF8563_SCL = 1;//ZHIGAO
  
}

void WDT_init_cyw(void)
{
  IWDG_KR=0x55;//ʹ��IWDG_PR IWDG_RLR�Ĵ���
  IWDG_PR=6;//��Ƶ
  IWDG_RLR=0xFF;//����װ�� �����ֵ��ʼDOWN
  IWDG_KR=0xCC;//ʹ�ܿ��Ź�
}

void Power_On_Init_cyw(void)
{
   TB_POWER = 20;
}

void Delaycyw(unsigned char timer)
{
unsigned char x;   

for(x=0;x<timer;x++)
{
  Delayus(255);
}

}

#endif
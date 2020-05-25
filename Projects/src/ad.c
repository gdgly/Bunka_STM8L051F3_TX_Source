/***********************************************************************/
/*  FILE        :ad.c                                                */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include <stdio.h>
#include <pic.h>
#include "Pin_define.h"		// �ܽŶ���
#include "initial.h"		// ��ʼ��  Ԥ����
#include "ram.h"		// RAM����
#include "uart.h"		// uart
#include "eeprom.h"		// eeprom
#include "adf7012.h"		// RF IC
#include "ad.h"		       //  A/D


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void START_AD_SAMPLER(void){	// ����ADת�����ж�ģʽ��

}
				// ADC�жϷ������
void ADC2_EOC_INT(void){
//	ADC1_SR_EOC = 0;	 // ��ADC�ж�
//        AD_DATA_BUFF[1] = ADC1_DRH;
//        AD_DATA_BUFF[0] = ADC1_DRL;
	RAM_BAT_SUM += AD_DATA_BUFF[1]*256+AD_DATA_BUFF[0];
        RAM_BAT_CNT++;
        if(RAM_BAT_CNT>=20){
		RAM_BAT_CNT = 0;
		RAM_BAT_AVG = RAM_BAT_SUM/20;
                BAT_Voltage_value=5013504/RAM_BAT_AVG;
		RAM_BAT_SUM = 0;		// clean sum
	}  
        START_AD_SAMPLER();
}
//BAT_out=0   ������ѹ  >=2.4V
//       =1   Ƿѹ      2.2v~2.4v  bi.bi.bi....
//       =2   ����������ѹ����Ϊ��������Ƶ��ƫ�ƹ���  <2.2v   ʲô��������
void AD_control(void){
      if(TIME_power_on_AD)
      {
          if(BAT_Voltage_value>2400)BAT_out=0;
          else if((BAT_Voltage_value<=2400)&&(BAT_Voltage_value>2200))BAT_out=1;
          else BAT_out=2; 
      }
}


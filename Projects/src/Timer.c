/***********************************************************************/
/*  FILE        :Timer.c                                               */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include <stdio.h>
#include <pic.h>
#include "Pin_define.h"		// �ܽŶ���
#include "initial.h"		// ��ʼ��  Ԥ����
#include "ram.h"		// RAM����

////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Timer 1 start
//void TIM1_init(void){						// 0.8333ms��ʱ��
//	TIM1_PSCRH = 0x00;				// 10Mϵͳʱ�Ӿ�Ԥ��Ƶf=fck/(PSCR+1)
//	TIM1_PSCRL =0x00; 		     // PSCR=0x1F3F��f=3.6864M/(0x1200)=800Hz����������1.25ms
//	TIM1_ARRH = 0x20;					// �Զ����ؼĴ���ARR=5
//	TIM1_ARRL = 0x8c;		//78.125*(3+1)=312.5us		// ÿ2.5ms����һ���ж�
//	TIM1_IER = 0x01;						// ��������ж�
//	TIM1_CR1 = 0x01;					// ������ʹ�ܣ���ʼ����
//}
//
//void TIM1_OVR_UIF(void){        
//	TIM1_SR1 = 0;						// ����жϱ��
//}


void TIM3_init(void){			// 2015.3.11����

}
void Tone_OFF(void){		// �ر�Tone   2015.3.11����

        PIN_BEEP=0;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Timer 4 start   1ms
void TIM4_Init(void){				
 TMR2=0X00;          //��ʱ������ֵ
 PR2=0X64;
 TMR2IF=0;                  //��ʱ���жϱ�־��0
 //INTCON=0XC0;//GIE=1; PEIE=1;      //�����ж�,�������ж�
 TMR2IE=1;              //����ʱ���ж�
 T2CON=0B01001101;            //TMR2ON=1; ���Ƶ��1:16
}

void TIM4_UPD_OVF(void){
        FG_1ms = 1;
}


/***********************************************************************/
/*  FILE        :Uart.c                                                */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include  <iostm8l151g6.h>				// CPU�ͺ� 
#include "Pin_define.h"		// �ܽŶ���
#include "initial.h"		// ��ʼ��  Ԥ����
#include "ram.h"		// RAM����


#define	TXD1_enable	(USART1_CR2 = 0x08)		// ������	
#define RXD1_enable	(USART1_CR2 = 0x24)		// ������ռ����ж�	
//********************************************
void UART1_INIT(void){						// 
	USART1_CR1 = 0;							// 1����ʼλ,8������λ 
	USART1_CR3 = 0;							// 1��ֹͣλ 
	USART1_CR4 = 0;
	USART1_CR5 = 0x08;						// ��˫��ģʽ
	USART1_BRR2 = 0x03;						// ���ò�����9600
	USART1_BRR1 = 0x68;						// 3.6864M/9600 = 0x180
	                                                                //16.00M/9600 = 0x683
	//USART1_CR2 = 0x08;	// ������
        USART1_CR2 = 0x24;    // ������ռ����ж�
	
        //USART1_CR2 = 0x2C;    //������ .   ������ռ����ж�
} 


//--------------------------------------------
void Send_char(unsigned char ch){			// �����ַ�
	TXD1_enable;							// ������	
	while(!USART1_SR_TXE);
	USART1_DR = ch;							// ����
	while(!USART1_SR_TC);					// �ȴ���ɷ���
	RXD1_enable;							// ������ռ����ж�	
}
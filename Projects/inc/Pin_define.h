/***********************************************************************/
/*  File Name   :Pin_Define.h                                          */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8S003     Crystal: 4M HSI                          */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
#include <stdio.h>
#include <pic.h>
/******************������data�Ĵ���************************************/
/* ADF7012 register interface */
#define ADF7021_SCLK            RB6     // Output   ʱ����
#define ADF7021_SDATA           RC7     // Output   ������
#define ADF7021_SLE             RC6     // Output   Ƭѡ
#define ADF7021_POWER           RC2     // Output   ADF7012��Դʹ�ܽ�
//#define ADF7021_CE              PB_ODR_ODR0     // Output   ADF7012ʹ�ܽ�
#define ADF7021_MUXOUT          RC1    // Input   ADF7012��ؼ�� <2.35


/* Other ADF7021 connections */
#define ADF7021_DATA_tx         RC0     // Output   ����DATA��
#define ADF7021_DATA_CLK        RA2     // ����   ����ͬ��ʱ����

#define	PIN_KEY_OPEN		RB4   	// ����  OPEN��
#define	PIN_KEY_STOP		RC4     // ����  STOP��
#define	PIN_KEY_CLOSE		RA4     // ����  CLOSE��    //2015.3.11����
#define PIN_KEY_VENT            RA3     // ����  ������
//#define	PIN_KEY_CLOSE		PD_IDR_IDR4     // ����  CLOSE��
//#define	PIN_KEY_LOGIN		PB_IDR_IDR7     // ����  LOGIN��
#define	PIN_KEY_LOGIN		RC5     // ����  LOGIN��
#define	PIN_UART_TX		RC4     // Output  uart TX

//#define PIN_LED                 PD_ODR_ODR0     // Output   LED��
#define PIN_LED                 RB5     // Output   LED��
#define PIN_TX_LED              RB5     // Output   LED��

//#define PIN_BEEP                PB_ODR_ODR5     // Output   ������
#define PIN_BEEP                RA5     // Output   ������     //2015.3.11����
//#define PIN_POWER_CONTROL       PC_ODR_ODR1     // Output   ��Դ����
#define PIN_POWER_CONTROL       RB7     // Output   ��Դ����
#define PIN_POWER_AD            RC1     // ����     ��Դ���AD��

#define PIN_test_mode           RC3     // ����     test��


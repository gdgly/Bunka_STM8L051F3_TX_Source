#include  <iostm8l151c6.h>				// CPU�ͺ� 
#include "initial.h"		// ��ʼ��  Ԥ����
#include "Pin_define.h"		// �ܽŶ���
#include "ram.h"		// RAM����
#include "ram_cyw.h"		// RAM����
#include "Timer.h"		// ��ʱ��
#include "adf7012.h"		// RF IC
#include "EXIT_FUN.h"		// �ⲿEXIT�ж�
#include "key_and_Other.h"	// ����
#include "eeprom.h"		// eeprom
#include "uart.h"		// uart
#include "lcd_cyw.h"
#include "font_cyw.h"

//�ֿ������������ ����ʽ û��֪����ʾ����





#if(ProductID==Hanging_display)//



 
#define  FONT_READ     0X03000000
#define  FONT_FASTREAD 0X0B000000
#define Long_15_16  32
#define Font_Word_Long  Long_15_16
#define Long_8_16  16
#define Font_Ascii_Long   Long_8_16




void FONT_SendData(unsigned char dat)	//����	
{
	unsigned char Tp_i = 0;
        
        
	ADF7021_SCLK = 0;
     	
        for(Tp_i=0;Tp_i<8;Tp_i++)
        {
            ADF7021_SCLK = 0;
      //  OSTimeDlyHMSM(0,0,0,1);
            if((dat&0x80)==0x80)
            {
               ADF7021_SDATA = 1;
            }
            else
            {
                ADF7021_SDATA = 0;
            }  
         	
            ADF7021_SCLK = 1;
        
            dat = dat << 1;
        }
	//LCD_CS_UNSELECT;
       
	ADF7021_SCLK = 0;
}


void FONT_ReadData(unsigned char x_sub)
{
  unsigned char Tp_i = 0;
   
   Read_Buf_temp[x_sub] = 0;
   
   for(Tp_i=0;Tp_i<8;Tp_i++)
        {
         
          ADF7021_SCLK = 0;
         
          Read_Buf_temp[x_sub] = Read_Buf_temp[x_sub]<<1;
          Read_Buf_temp[x_sub] = Read_Buf_temp[x_sub]|PIN_FONT_DATAIN;
          
          ADF7021_SCLK =1;
            
        }
}


void Read_Font(unsigned long x_addr,unsigned char x_long)
{
      
     
     unsigned char Tp_i=0;
     
     
     PIN_FONT_SEL = 0;
     PIN_LCD_SEL  = 1;
     
     
     FONT_SendData((unsigned char)(x_addr>>24));
     FONT_SendData((unsigned char)((x_addr>>16)&0XFF));
      FONT_SendData((unsigned char)((x_addr>>8)&0XFF));
       FONT_SendData((unsigned char)((x_addr)&0XFF));
       
       if((x_addr&0xff000000)==FONT_FASTREAD)
            FONT_SendData(0X55);//Dummy Byte
     
       for(Tp_i = 0 ;Tp_i<x_long; Tp_i++)
     {
          FONT_ReadData(Tp_i);
     }
       
     
     PIN_FONT_SEL = 1;
    
     return;
}



unsigned char* GetDisplayAscii(unsigned char* AsciiBuf)
{

     UINT32 address=0;
     
     
     
     if((AsciiBuf[0] >=0x20) && (AsciiBuf[0] <=0x7F))
     {
          address =(AsciiBuf[0] - 0x20)*16+255968;
     }
     if(address > 0xffffff)
     {
         address = 0;//��ַԽ�����
     }
     address = address|FONT_FASTREAD;//�ϳ�32bit��
     
     Read_Font(address,Font_Ascii_Long);
     return Read_Buf_temp;   
}



unsigned char* GetDisplayWord(unsigned char* WordBuf)
{
     
     unsigned long Tp_address=0;
     
     //WordBuf[0]=16;
     //WordBuf[1]=64;
     //ClearWDT(); // Service the WDT
     
     
     if(WordBuf[0] >=1 && WordBuf[0] <= 15 && WordBuf[1] >=1 && WordBuf[1] <= 94)
     Tp_address =( (WordBuf[0] - 1) * 94 + (WordBuf[1] - 1))*32;
     else if(WordBuf[0] >=16 && WordBuf[0] <= 47 && WordBuf[1] >=1 && WordBuf[1] <= 94)
     Tp_address =( (WordBuf[0] - 16) * 94 + (WordBuf[1] - 1))*32+43584;
     else if(WordBuf[0] >=48 && WordBuf[0] <=84 && WordBuf[1] >=1 && WordBuf[1] <= 94)
     Tp_address = ((WordBuf[0] - 48) * 94 + (WordBuf[1] - 1))*32+ 138463;
     else if(WordBuf[0] ==85 && WordBuf[1] >=0x01 && WordBuf[1] <= 94)
     Tp_address = ((WordBuf[0] - 85) * 94 + (WordBuf[1] - 1))*32+ 246944;
     else if(WordBuf[0] >=88 && WordBuf[0] <=89 && WordBuf[1] >=1 && WordBuf[1] <= 94)
     Tp_address = ((WordBuf[0] - 88) * 94 + (WordBuf[1] - 1))*32+ 249952;
     
//     if((WordBuf[0] >=1) && (WordBuf[0] <= 15) && (WordBuf[1] >=1) && (WordBuf[1] <= 94))
//     {
//     Tp_address =( (WordBuf[0] - 1)*94 + (WordBuf[1] - 1))*32;
//     }
//     else 
//     {  
//       if((WordBuf[0] >=16) && (WordBuf[0] <= 47) && (WordBuf[1] >=1) && (WordBuf[1] <= 94))
//       {  
//       Tp_address =( (WordBuf[0] - 16)*94 + (WordBuf[1] - 1))*32+43584;
//       }
//       else 
//       {
//         if((WordBuf[0] >=48) && (WordBuf[0] <=84) && (WordBuf[1] >=1 )&& (WordBuf[1] <= 94))
//         {
//         Tp_address = ((WordBuf[0] - 48)*94 + (WordBuf[1] - 1))*32+ 138463;
//         }
//         else 
//         {
//           if((WordBuf[0] ==85) && (WordBuf[1] >=0x01) && (WordBuf[1] <= 94))
//           {
//           Tp_address = ((WordBuf[0] - 85)*94 + (WordBuf[1] - 1))*32+ 246944;
//           }
//           else 
//           {
//             if((WordBuf[0] >=88) && (WordBuf[0] <=89) && (WordBuf[1] >=1) && (WordBuf[1] <= 94))
//             {
//                Tp_address = ((WordBuf[0] - 88)*94 + (WordBuf[1] - 1))*32+ 249952;
//             }
//           }
//         }
//       }
//     }
//     
     if(Tp_address > 0xffffff)
     {
         Tp_address = 0;//��ַԽ�����
     }
     Tp_address = Tp_address|FONT_FASTREAD;//�ϳ�32bit��
     Read_Font(Tp_address,Font_Word_Long);
     return Read_Buf_temp;
}
#endif
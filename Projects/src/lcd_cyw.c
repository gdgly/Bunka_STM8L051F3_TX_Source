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
#include "pcf8563_cyw.h"
#include "eeprom_cyw.h"
#include "ad.h"

#if(ProductID==Hanging_display)//
//ҳ��ַ����
#define     PAGE_ADDR_SET   0xb0

//�е�ַ����
#define     SEG_ADDR_H  0x10
#define     SEG_ADDR_L  0x00


void send_command(int data)
{
   char i;
   PIN_LCD_SEL  = 0;//ѡ��
   PIN_LCD_RS = 0;
   for(i=0;i<8;i++)
   {
     ADF7021_SCLK = 0;
     if(data&0x80)
       ADF7021_SDATA = 1;
     else
       ADF7021_SDATA = 0;
     ADF7021_SCLK = 1;
     data= data <<1;
   }
}

void send_data(int data)
{
   char i;
   PIN_LCD_SEL  = 0;//ѡ��
   PIN_LCD_RS = 1;
   for(i=0;i<8;i++)
   {
     ADF7021_SCLK = 0;
     if(data&0x80)
       ADF7021_SDATA = 1;
     else
       ADF7021_SDATA = 0;
     ADF7021_SCLK = 1;
     data= data <<1;
   }
}


void delay(int i)
{
   int j,k;
   for(j=0;j<i;j++)
     for(k=0;k<110;k++);
}

void lcd_address(uchar page,uchar column)
{
  
   PIN_LCD_SEL  = 0;//ѡ��
   column  = column -1;
   page    = page   -1;
   send_command(0xb0+page);
   send_command(((column>>4)&0x0f)+0x10);
   send_command(column&0x0f);
}





void display_graphic_8x16(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
    uchar i,j;
    //cs1=0;
    ClearWDT(); // Service the WDT
    PIN_LCD_SEL  = 0;//ѡ��
    for(j=0; j<2; j++)
    {
        lcd_address(page,column+j*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);                 /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
            }
            else
            {
            send_data(~(*dp));
            }
            dp++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//��ѡ��
}




/*��ʾ16x16����ͼ�񡢺��֡���Ƨ�ֻ�16x16���������ͼ��*/
void display_graphic_16x16(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
    uchar i,j;
    //uchar page_address;
    //uchar column_address_L,column_address_H;
    
    ClearWDT(); // Service the WDT
    
   // page_address = 0xb0+page-1;
   // column_address_L =(column&0x0f);
   // column_address_H =((column>>4)&0x0f)+0x10;
    //cs1=0;
    PIN_LCD_SEL  = 0;//ѡ��
    
    for(j=0; j<4; j++)
    {
       // send_command(page_address+j);   /*����ҳ��ַ*/
       // send_command(column_address_H); /*�����е�ַ�ĸ�4λ*/
       // send_command(column_address_L); /*�����е�ַ�ĵ�4λ*/
       lcd_address(page+j/2,column+(j%2)*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);     /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
            }
            else
            {
              send_data(~(*dp)); 
            }
            dp++;
        }
    }
    //cs1=1;
     PIN_LCD_SEL  = 1;//��ѡ��
}

void display_graphic_16x32(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
    uchar i,j;
   // uchar page_address;
  //  uchar column_address_L,column_address_H;
    
    ClearWDT(); // Service the WDT
    
    //page_address = 0xb0+page-1;
    //column_address_L =(column&0x0f);
    //column_address_H =((column>>4)&0x0f)+0x10;
    //cs1=0;
    PIN_LCD_SEL  = 0;//ѡ��
    
    for(j=0; j<8; j++)
    {
       // send_command(page_address+j);   /*����ҳ��ַ*/
       // send_command(column_address_H); /*�����е�ַ�ĸ�4λ*/
       // send_command(column_address_L); /*�����е�ַ�ĵ�4λ*/
      lcd_address(page+j/4,column+(j%4)*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);     /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
            }
            else
            {
              send_data(~(*dp)); 
            }
            dp++;
        }
    }
    //cs1=1;
     PIN_LCD_SEL  = 1;//��ѡ��
}

void display_graphic_24x32(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
    uchar i,j;
   // uchar page_address;
  //  uchar column_address_L,column_address_H;
    
    ClearWDT(); // Service the WDT
    
    //page_address = 0xb0+page-1;
    //column_address_L =(column&0x0f);
    //column_address_H =((column>>4)&0x0f)+0x10;
    //cs1=0;
    PIN_LCD_SEL  = 0;//ѡ��
    
    for(j=0; j<12; j++)
    {
       // send_command(page_address+j);   /*����ҳ��ַ*/
       // send_command(column_address_H); /*�����е�ַ�ĸ�4λ*/
       // send_command(column_address_L); /*�����е�ַ�ĵ�4λ*/
      lcd_address(page+j/4,column+(j%4)*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);     /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
            }
            else
            {
              send_data(~(*dp)); 
            }
            dp++;
        }
    }
    //cs1=1;
     PIN_LCD_SEL  = 1;//��ѡ��
}


//��������Ǵ��ֿ�оƬ�����ȡ���� ��ת�������ݺ���ʾ
void  display_graphic_16x16_FONTIC(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
//    uchar i,j;
//    uchar page_address;
//    uchar column_address_L,column_address_H;
//    
//    ClearWDT(); // Service the WDT
//    
//    page_address = 0xb0+page-1;
//    column_address_L =(column&0x0f);
//    column_address_H =((column>>4)&0x0f)+0x10;
//    //cs1=0;
//    PIN_LCD_SEL  = 0;//ѡ��
//    
//    for(j=0; j<2; j++)
//    {
//        send_command(page_address+j);   /*����ҳ��ַ*/
//        send_command(column_address_H); /*�����е�ַ�ĸ�4λ*/
//        send_command(column_address_L); /*�����е�ַ�ĵ�4λ*/
//        for (i=0; i<16; i++)
//        {
//            if(x_flag == 0)
//            {
//            send_data(*dp);     /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
//            }
//            else
//            {
//              send_data(~(*dp)); 
//            }
//            dp++;
//        }
//    }
//    //cs1=1;
//     PIN_LCD_SEL  = 1;//��ѡ��
    UINT8 DP_NI[32];
    UINT8 i,j;
   // UINT8 page_address;
    //UINT8 column_address_L,column_address_H;
    ClearWDT(); // Service the WDT
    
    for(i=0;i<8;i++)
    {
       for(j=0;j<8;j++)
       {
           if(dp[i]&(1<<j))
           {
             DP_NI[j] = DP_NI[j]|(1<<(i));
           }
           else
           {
             DP_NI[j] = DP_NI[j]&(~(1<<(i)));
           }
       }
    }
    for(i=0;i<8;i++)
    {
       for(j=0;j<8;j++)
       {
           if(dp[8+i]&(1<<j))
           {
             DP_NI[16+j] = DP_NI[16+j]|(1<<(i));
           }
           else
           {
             DP_NI[16+j] = DP_NI[16+j]&(~(1<<(i)));
           }
       }
    }
    for(i=0;i<8;i++)
    {
       for(j=0;j<8;j++)
       {
           if(dp[16+i]&(1<<j))
           {
             DP_NI[8+j] = DP_NI[8+j]|(1<<(i));
           }
           else
           {
             DP_NI[8+j] = DP_NI[8+j]&(~(1<<(i)));
           }
       }
    }
    for(i=0;i<8;i++)
    {
       for(j=0;j<8;j++)
       {
           if(dp[24+i]&(1<<j))
           {
             DP_NI[24+j] = DP_NI[24+j]|(1<<(i));
           }
           else
           {
             DP_NI[24+j] = DP_NI[24+j]&(~(1<<(i)));
           }
       }
    }
    
  //  page_address = 0xb0+page-1;
  //  column_address_L =(column&0x0f);
   // column_address_H =((column>>4)&0x0f)+0x10;
    //cs1=0;
    
    PIN_LCD_SEL  = 0;//ѡ��
    for(j=0; j<4; j++)
    {
        //send_command(page_address+j);   /*����ҳ��ַ*/
        //send_command(column_address_H); /*�����е�ַ�ĸ�4λ*/
        //send_command(column_address_L); /*�����е�ַ�ĵ�4λ*/
       lcd_address(page+j/2,column+(j%2)*8);
        for (i=0; i<8; i++)
        {
             if(x_flag == 0)
             {     
          send_data(DP_NI[j*16+i]);     /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
             }
             else
             {
          send_data(~DP_NI[j*16+i]);         
             }
           // DP_NI++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//��ѡ��
    
}

void display_graphic_8x24(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
   uchar i,j;
    //cs1=0;
    ClearWDT(); // Service the WDT
    
    PIN_LCD_SEL  = 0;//ѡ��
    for(j=0; j<3; j++)
    {
        lcd_address(page,column+j*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);                 /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
            }
            else
            {
            send_data(~(*dp));
            }
            dp++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//��ѡ��
}
void display_graphic_8x32(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
   uchar i,j;
    //cs1=0;
    ClearWDT(); // Service the WDT
    
    PIN_LCD_SEL  = 0;//ѡ��
    for(j=0; j<4; j++)
    {
        lcd_address(page,column+j*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);                 /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
            }
            else
            {
            send_data(~(*dp));
            }
            dp++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//��ѡ��
}
void display_graphic_8x48(uchar column,uchar page,const uchar *dp,uchar x_flag)
{
   uchar i,j;
    //cs1=0;
    ClearWDT(); // Service the WDT
    PIN_LCD_SEL  = 0;//ѡ��
    for(j=0; j<6; j++)
    {
        lcd_address(page,column+j*8);
        for (i=0; i<8; i++)
        {
            if(x_flag == 0)
            {
            send_data(*dp);                 /*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
            }
            else
            {
            send_data(~(*dp));
            }
            dp++;
        }
    }
    //cs1=1;
    PIN_LCD_SEL  = 1;//��ѡ��
}



void display_onetimedata_8_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   uchar Tp_timelsb,Tp_timemsb;//ʱ��ĵ�λ�͸�λ
   Tp_timelsb = data%16;
    Tp_timemsb = data/16;

    if(data<=0x99)//Խ��Ĳ���ʾ
    {
    display_graphic_8x32(hang,lie,&FONT_BUF_8_32[Tp_timemsb*32],x_flag);
    display_graphic_8x32(hang,1+lie,&FONT_BUF_8_32[Tp_timelsb*32],x_flag);//�������
    }
    else//��һ������ ����
    {
    display_graphic_8x32(hang,lie,&FONT_BUF_8_32[code_daE_8_32*32],x_flag);
    display_graphic_8x32(hang,1+lie,&FONT_BUF_8_32[code_xiaor_8_32*32],x_flag);//�������   
    }
    
}

//
//void display_onetimedata_gothic_8_32(uchar hang,uchar lie,uchar data,uchar x_flag)
//{
//   uchar Tp_timelsb,Tp_timemsb;//ʱ��ĵ�λ�͸�λ
//   Tp_timelsb = data%16;
//    Tp_timemsb = data/16;
//
//    if(data<=0x99)//Խ��Ĳ���ʾ
//    {
//    display_graphic_8x32(hang,lie,&FONT_BUF_8_32[(Tp_timemsb+code_num_MSGothic_8_32)*32],x_flag);
//    display_graphic_8x32(hang,1+lie,&FONT_BUF_8_32[(Tp_timelsb+code_num_MSGothic_8_32)*32],x_flag);//�������
//    }
//    else//��һ������ ����
//    {
//    display_graphic_8x32(hang,lie,&FONT_BUF_8_32[code_daE_8_32*32],x_flag);
//    display_graphic_8x32(hang,1+lie,&FONT_BUF_8_32[code_xiaor_8_32*32],x_flag);//�������   
//    }
//    
//}


void display_onetimedata_gothic_8_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
 
  display_onetimedata_8_32(hang,lie,data,x_flag);
    
}

void display_onetimedata_8_16(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   uchar Tp_timelsb,Tp_timemsb;//ʱ��ĵ�λ�͸�λ
   Tp_timelsb = data%16;
    Tp_timemsb = data/16;

    if(data<=0x99)//Խ��Ĳ���ʾ
    {
    display_graphic_8x16(hang,lie,&FONT_BUF_8_16[Tp_timemsb*16],x_flag);
    display_graphic_8x16(hang,1+lie,&FONT_BUF_8_16[Tp_timelsb*16],x_flag);//�������
    }
    else//��һ������ ����
    {
       
    }
    
}

void display_onetimedata_8_24(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   uchar Tp_timelsb,Tp_timemsb;//ʱ��ĵ�λ�͸�λ
   Tp_timelsb = data%16;
    Tp_timemsb = data/16;

    if(data<=0x99)//Խ��Ĳ���ʾ
    {
    display_graphic_8x24(hang,lie,&FONT_BUF_8_24[Tp_timemsb*24],x_flag);
    display_graphic_8x24(hang,1+lie,&FONT_BUF_8_24[Tp_timelsb*24],x_flag);//�������
    }
    else//��һ������ ����
    {
       
    }
    
}


void display_oneword_8_16(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_8x16(hang,lie,&FONT_BUF_8_16[16*data],x_flag);//������
}

void display_oneword_8_24(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_8x24(hang,lie,&FONT_BUF_8_24[24*data],x_flag);//������
}

void display_oneword_8_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_8x32(hang,lie,&FONT_BUF_8_32[32*data],x_flag);//������
}

void display_oneword_16_16(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_16x16(/*4+16**/hang,lie,&FONT_BUF_16_16[num_addr+32*data],x_flag);//������
}

void display_oneword_16_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_16x32(hang,lie,&FONT_BUF_16_32[num_addr+64*data],x_flag);//������
}

void display_oneword_24_32(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   display_graphic_24x32(hang,lie,&FONT_BUF_24_32[num_addr+96*data],x_flag);//������
}

uchar caluate_monthtoreason(uchar x_mon)
{
   uchar Tp_mon;
    Tp_mon = x_mon%16 + (x_mon/16)*10;
    if((Tp_mon >= 3) &&(Tp_mon <= 5))
    {
      return 0;//��
    }
    if((Tp_mon >= 6) &&(Tp_mon <= 8))
    {
      return 1;//��
    }
    if((Tp_mon >= 9) &&(Tp_mon <= 11))
    {
      return 2;//��
    }
    return 3;//��
}

//���data Ϊ��ǰ�·�
void display_reason(uchar hang,uchar lie,uchar data,uchar x_flag)
{
    uchar Tp_reason = 0;
    Tp_reason = caluate_monthtoreason(data);
    switch(Tp_reason)
    {
    case 0:display_oneword_16_16(hang,lie,code_chun_season,x_flag);
      break;
    case 1:display_oneword_16_16(hang,lie,code_xia_season,x_flag);
      break;
    case 2:display_oneword_16_16(hang,lie,code_qiu_season,x_flag);
      break;
    case 3:display_oneword_16_16(hang,lie,code_dong_season,x_flag);
      break;
    default:break;
    }
}

void display_dianci(uchar hang,uchar lie,uchar data,uchar x_flag)
{
  switch(data)
    {
    case 0:display_oneword_16_16(hang,lie,biguashidianliang0,x_flag);
      break;
    case 1:display_oneword_16_16(hang,lie,biguashidianliang1,x_flag);
      break;
    case 2:display_oneword_16_16(hang,lie,biguashidianliang2,x_flag);
      break;
    case 3:display_oneword_16_16(hang,lie,biguashidianliang3,x_flag);
      break;
    default:break;
    }
}

void display_week(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   switch(data)
    {
    case 0:display_oneword_16_16(hang,lie,code_ri,x_flag);
      break;
    case 1:display_oneword_16_16(hang,lie,code_yue,x_flag);
      break;
    case 2:display_oneword_16_16(hang,lie,code_huo_week,x_flag);
      break;
    case 3:display_oneword_16_16(hang,lie,code_shui_week,x_flag);
      break;
    case 4:display_oneword_16_16(hang,lie,code_mu_week,x_flag);
      break;
     case 5:display_oneword_16_16(hang,lie,code_jin_week,x_flag);
      break;
      case 6:display_oneword_16_16(hang,lie,code_tu_week,x_flag);
      break;
    default:break;
    }
   display_oneword_16_16(hang,lie+2,code_yao_week,x_flag);
   display_oneword_16_16(hang,lie+4,code_ri,x_flag);
}


void display_area(uchar hang,uchar lie,uchar data,uchar x_flag)
{
   switch(data)
    {
    case 0://display_oneword_16x16(hang,lie,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie,code_bei,x_flag);
           display_oneword_16_16(hang,lie+2,code_bei+1,x_flag);
           display_oneword_16_16(hang,lie+4,code_bei+2,x_flag);
      break;
    case 1:
           display_oneword_16_16(hang,lie,code_chong,x_flag);//�����ض�
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_shen,x_flag);
           //display_oneword_16x16(hang,lie+6,code_dong,x_flag);
           
      break;
    case 2:display_oneword_16_16(hang,lie,code_jiu,x_flag);
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_zou,x_flag);
           //display_oneword_16x16(hang,lie+6,code_fang,x_flag);
      break;
    case 3:display_oneword_16_16(hang,lie,code_zhong,x_flag);
           display_oneword_16_16(hang,lie+2,code_si,x_flag);
           display_oneword_16_16(hang,lie+4,code_guo,x_flag);
           //display_oneword_16x16(hang,lie+6,code_fang,x_flag);
      break;
    case 4://display_oneword_16_16(hang,lie,code_guan,x_flag);
          display_oneword_16_16(hang,lie,code_jin,x_flag);//20150403 ������Ϊ����
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           //display_oneword_16_16(hang,lie+4,code_xi,x_flag);
         display_oneword_16_16(hang,lie+4,code_ji,x_flag);
      break;
     case 5:display_oneword_16_16(hang,lie,code_zhong,x_flag);
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_bu,x_flag);
           //display_oneword_16x16(hang,lie+6,code_shen,x_flag);
      break;
      case 6:
           display_oneword_16_16(hang,lie,code_guan,x_flag);
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_dong,x_flag);
     break;
      case 7:
           display_oneword_16_16(hang,lie,code_dong,x_flag);
           display_oneword_16_16(hang,lie+2,code_kongbai,x_flag);
           display_oneword_16_16(hang,lie+4,code_bei,x_flag);
      break;
    default:break;
    }
}

//����Ļ
void clear_clear(void)
{
   unsigned char i,j;
   //ClearWDT(); // Service the WDT
   PIN_LCD_SEL  = 0;//ѡ��
   for(i=0;i<9;i++)
   {
      ClearWDT(); // Service the WDT
      lcd_address(1+i,1);
      for(j=0;j<132;j++)
      {
         send_data(0x00);
      }  
   }
   PIN_LCD_SEL  = 1;//��ѡ��
   
}

//���һ��64*32
void Clear_64_32(UINT8 x_hang,UINT8 x_flag)
{
      display_oneword_8_32(x_hang,lie_1,code_kongbai_8_32,x_flag);//Сʱ����
      display_oneword_8_32(x_hang,lie_2,code_kongbai_8_32,x_flag);//Сʱ����
      display_oneword_8_32(x_hang,lie_3,code_kongbai_8_32,x_flag);//Сʱ����
      display_oneword_8_32(x_hang,lie_4,code_kongbai_8_32,x_flag);//Сʱ����
      display_oneword_8_32(x_hang,lie_5,code_kongbai_8_32,x_flag);
      display_oneword_8_32(x_hang,lie_6,code_kongbai_8_32,x_flag);
      display_oneword_8_32(x_hang,lie_7,code_kongbai_8_32,x_flag);
       display_oneword_8_32(x_hang,lie_8,code_kongbai_8_32,x_flag);
}

void menu_linshi(void)/*��ʾ �� �� �� ʱ ��*/
{
    
    
    
    
    
    display_dianci(0,0,3,0);
    
    display_onetimedata_8_32(1,0,0x20,0);
    display_onetimedata_8_32(1,2,now_year,0);
    display_oneword_16_16(1,4,code_nian,0);
      
    display_reason(1,6,now_mon,0);
    
    display_onetimedata_8_32(2,0,now_mon,0);
    display_oneword_16_16(2,2,code_yue,0);
    display_onetimedata_8_32(2,4,now_day,0);
    display_oneword_16_16(2,6,code_ri,0);
    
    display_onetimedata_8_32(3,2,now_hour,0);
    display_oneword_16_16(3,4,code_maohao,0);
    display_onetimedata_8_32(3,6,now_min,0);
    
    display_week(4,2,now_week,0);
    
    display_area(5,0,DISP_DIQU,0);
    //Tp_timelsb = now_year%16;
   // Tp_timemsb = now_year/16;
    //display_graphic_8x16(1,5,&FONT_BUF[2*16]);
    //display_graphic_8x16(2,5,&FONT_BUF[0*16]);
    //display_graphic_8x16(3,5,&FONT_BUF[Tp_timemsb*16]);
    //display_graphic_8x16(4,5,&FONT_BUF[Tp_timelsb*16]);//�������
    //display_graphic_16x16(5,4,&FONT_BUF[num_addr+32*code_nian]);//������
    
    
//    Tp_timelsb = now_mon%16;
//    Tp_timemsb = now_mon/16;
//    display_graphic_8x16(1,21,&FONT_BUF[Tp_timemsb*16]);
//    display_graphic_8x16(2,21,&FONT_BUF[Tp_timelsb*16]);//�µ�����
//    display_graphic_16x16(3,20,&FONT_BUF[num_addr+32*code_yue]);//������
//    Tp_timelsb = now_day%16;
//    Tp_timemsb = now_day/16;
//    display_graphic_8x16(5,21,&FONT_BUF[Tp_timemsb*16]);
//    display_graphic_8x16(6,21,&FONT_BUF[Tp_timelsb*16]);//�յ�����
//    display_graphic_16x16(7,20,&FONT_BUF[num_addr+32*code_ri]);//������
//    
//    Tp_timelsb = now_hour%16;
//    Tp_timemsb = now_hour/16;
//    display_graphic_8x16(1,37,&FONT_BUF[Tp_timemsb*16]);
//    display_graphic_8x16(2,37,&FONT_BUF[Tp_timelsb*16]);
//    display_graphic_16x16(3,36,&FONT_BUF[num_addr+32*code_maohao]);
//    Tp_timelsb = now_min%16;
//    Tp_timemsb = now_min/16;
//    display_graphic_8x16(5,37,&FONT_BUF[Tp_timemsb*16]);
//    display_graphic_8x16(6,37,&FONT_BUF[Tp_timelsb*16]);
//    
} 

void display_timeroff(UINT8 x_hang,UINT8 x_data1,UINT8 x_data2,UINT8 x_flag)//x_flag 0-ʱ������ 1-ʱ�ַ��� 2-ʱ������ 3-ʱ���ַ� 
{
   if((x_data1 == 0xff) || (x_data2 == 0xff))
   {
    
     switch(x_flag)
     {
      case 0:
      case 1: 
            display_oneword_8_32(x_hang,lie_1,code_kongbai_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_2,code_kongbai_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_3,code_kongbai_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_4,code_kongbai_8_32,x_flag);
            
            display_oneword_8_32(x_hang,lie_5,0,x_flag);
            display_oneword_8_32(x_hang,lie_6,code_shuangff_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_7,code_shuangff_8_32,x_flag);
            display_oneword_8_32(x_hang,lie_8,code_kongbai_8_32,x_flag);
           break;
     case 2:  
            display_oneword_8_32(x_hang,lie_1,code_kongbai_8_32,1);
            display_oneword_8_32(x_hang,lie_2,code_kongbai_8_32,1);
            display_oneword_8_32(x_hang,lie_3,code_kongbai_8_32,1);
             display_oneword_8_32(x_hang,lie_4,code_kongbai_8_32,1);
             display_oneword_8_32(x_hang,lie_5,0,0);
            // display_oneword_8_32(x_hang,lie_5,0,0);
            //display_oneword_8_32(x_hang,lie_5,code_maohao_8_32,0);
            //display_oneword_16_32(x_hang,lie_4,code_O_16_32,0);
            display_oneword_8_32(x_hang,lie_6,code_shuangff_8_32,0);
            display_oneword_8_32(x_hang,lie_7,code_shuangff_8_32,0);
             display_oneword_8_32(x_hang,lie_8,code_kongbai_8_32,0);
          break;
     case 3: 
             display_oneword_8_32(x_hang,lie_1,code_kongbai_8_32,0);
            display_oneword_8_32(x_hang,lie_2,code_kongbai_8_32,0);
            display_oneword_8_32(x_hang,lie_3,code_kongbai_8_32,0);
            display_oneword_8_32(x_hang,lie_4,code_kongbai_8_32,0);
            display_oneword_8_32(x_hang,lie_5,0,0);
            //display_oneword_8_32(x_hang,lie_5,code_maohao_8_32,0);
            //display_oneword_8_32(x_hang,lie_5,0,1);
            display_oneword_8_32(x_hang,lie_6,code_shuangff_8_32,1);
            display_oneword_8_32(x_hang,lie_7,code_shuangff_8_32,1);
            display_oneword_8_32(x_hang,lie_8,code_kongbai_8_32,1);
          break;
     default :break;
     }
     
   }
   else //��һ������
   {
      display_graphic_8x32(x_hang,2,&FONT_BUF_8_32[code_daE_8_32*32],0);
    display_graphic_8x32(x_hang,3,&FONT_BUF_8_32[code_xiaor_8_32*32],0);//�������   
   }
}

void display_nowtime(void)
{
   if(FLAG_MODE==NOWTIMESET_mode)
   {

  //   display_oneword_8_32(nowtimeset_hang_3,lie_1,code_kongbai_8_32,0);//
   //  display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
    //  display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
    //  display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
     // display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      // display_oneword_8_32(nowtimeset_hang_3,lie_8,code_kongbai_8_32,0);//
   }
   else
   {
     display_onetimedata_8_32(Normal_hang_1,lie_2,now_hour,0);
    display_oneword_8_32(Normal_hang_1,lie_4,code_kongbai_8_32,0);
    display_oneword_8_32(Normal_hang_1,lie_5,code_maohao_8_32,0);
    display_onetimedata_8_32(Normal_hang_1,lie_6,now_min,0);
   }
}

void menu_normal(void)   //������ʾ�� ��ʾ����ʱ�� ��ʱ�� ��ʱ��
{

  //UINT8 CHAR[]={41,1}; 
    clear_clear();
  
    display_onetimedata_8_32(Normal_hang_1,lie_2,now_hour,0);
    display_oneword_8_32(Normal_hang_1,lie_4,code_kongbai_8_32,0);
    display_oneword_8_32(Normal_hang_1,lie_5,code_maohao_8_32,0);
    display_onetimedata_8_32(Normal_hang_1,lie_6,now_min,0);
    
    if(TIMER_MODE_OPEN==Timer_Mode_SET)
    {
    display_onetimedata_8_32(Normal_hang_2,lie_2,open_hour,0);
    display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,0);
    display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,0);
    display_onetimedata_8_32(Normal_hang_2,lie_6,open_min,0);
    display_oneword_8_32(Normal_hang_2,lie_8,code_kongbai_8_32,0);
    }
    if(TIMER_MODE_OPEN==Timer_Mode_OFF)
    {
    display_timeroff(Normal_hang_2,open_hour,open_min,0);
    }
    if(TIMER_MODE_OPEN==Timer_Mode_AUTO)
    {
    display_oneword_24_32(Normal_hang_2,lie_1,code_zidong_24_32,0);//Сʱ����
    display_onetimedata_8_24(Normal_hang_2_1_0824,lie_4,auto_open_hour,0);
    display_oneword_8_24(Normal_hang_2_1_0824,lie_6,code_maohao_8_24,0);
    display_onetimedata_8_24(Normal_hang_2_1_0824,lie_7,auto_open_min,0);
    }
    
    if(TIMER_MODE_CLOSE==Timer_Mode_SET)
    {
    display_onetimedata_8_32(Normal_hang_3,lie_2,close_hour,0);
    display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,0);
    display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,0);
    display_onetimedata_8_32(Normal_hang_3,lie_6,close_min,0);
    display_oneword_8_32(Normal_hang_3,lie_8,code_kongbai_8_32,0);
    }
    if(TIMER_MODE_CLOSE==Timer_Mode_OFF)
    {
    display_timeroff(Normal_hang_3,close_hour,close_min,0);
    }
    if(TIMER_MODE_CLOSE==Timer_Mode_AUTO)
    {
     display_oneword_24_32(Normal_hang_3,lie_1,code_zidong_24_32,0);//Сʱ����
    display_onetimedata_8_24(Normal_hang_3_1_0824,lie_4,auto_close_hour,0);
    display_oneword_8_24(Normal_hang_3_1_0824,lie_6,code_maohao_8_24,0);
    display_onetimedata_8_24(Normal_hang_3_1_0824,lie_7,auto_close_min,0); 
    } 
    
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(5,1,Read_Buf_temp,0);
//   CHAR[0]=19;
//   CHAR[1]=4;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(5,3,Read_Buf_temp,0);
//   CHAR[0]=38;
//   CHAR[1]=27;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(5,5,Read_Buf_temp,0);
//   CHAR[0]=47;
//   CHAR[1]=31;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(5,7,Read_Buf_temp,0);
//   CHAR[0]=47;
//   CHAR[1]=30;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(21,1,Read_Buf_temp,0);
//   CHAR[0]=47;
//   CHAR[1]=34;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(21,3,Read_Buf_temp,0);
//   CHAR[0]=47;
//   CHAR[1]=36;
//   GetDisplayWord(CHAR);
//   display_graphic_16x16_FONTIC(21,5,Read_Buf_temp,0);
}

void menu_dispdianci(void)
{
    
    display_oneword_16_16(30,1,code_diancigenhuan,0);
    display_oneword_16_16(30,3,code_diancigenhuan+1,0);
    display_oneword_16_16(30,5,code_diancigenhuan+2,0);
    
    display_oneword_16_16(46,1,code_diancigenhuan+3,0);
    display_oneword_16_16(46,3,code_diancigenhuan+4,0);
    display_oneword_16_16(46,5,code_diancigenhuan+5,0);
    display_oneword_16_16(46,7,code_diancigenhuan+6,0);
     ClearWDT(); // Service the WDT
     
    display_oneword_16_16(62,1,code_diancigenhuan+7,0);
    display_oneword_16_16(62,3,code_diancigenhuan+8,0);
    display_oneword_16_16(62,5,code_diancigenhuan+9,0);
    display_oneword_16_16(62,7,code_diancigenhuan+10,0);
    //display_oneword_16_16(62,7,code_diancigenhuan+11,0);
    //display_oneword_16_16(78,1,code_diancigenhuan+12,0);
   // display_oneword_16_16(78,3,code_diancigenhuan+13,0);
    
}



void menu_setnowtime(void)
{
  // clear_clear();
  
  if(DISP_GUANGBIAO == 0)
   {
       display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
       display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
       display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0); 
       display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
   }
   if(DISP_GUANGBIAO == 1)//�귴
   {
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//Сʱ����
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],1);//Сʱ����
      
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//Сʱ����
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//Сʱ����
       
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
      //display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
   if(DISP_GUANGBIAO == 2)//�·�
   {
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//Сʱ����
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],1);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//Сʱ����
     // display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
      //display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
      //display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
    if(DISP_GUANGBIAO == 3)//�շ�
   {
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//Сʱ����
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//Сʱ����
     // display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],1);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
      //display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
      //display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
    if(DISP_GUANGBIAO == 4)//ʱ��
   {
     display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//Сʱ����
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],1);
      display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,1);//
     // display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
      
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
    if(DISP_GUANGBIAO == 5)//�ַ�
   {
     display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//Сʱ����
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
    //  
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//Сʱ����
     // display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//Сʱ����
     // display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
      display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
      //display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],1);
      display_oneword_8_32(nowtimeset_hang_3,lie_8,code_kongbai_8_32,1);//
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,0);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,0);
      
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],0);
   }
    if(DISP_GUANGBIAO == 6)//������
   {
     display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_2,0X20,0);//Сʱ����
     // display_oneword_8_32(0,4,code_kongbai_8_32,1);
      display_onetimedata_gothic_8_32(nowtimeset_hang_1,lie_4,now_timer[0],0);//Сʱ����
      //display_oneword_16_32(nowtimeset_hang_1,lie_6,code_nian_16_32,0);
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_1,now_timer[1],0);//Сʱ����
     // display_oneword_16_32(nowtimeset_hang_2,lie_3,code_yue_16_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_2,lie_5,now_timer[2],0);//Сʱ����
     // display_oneword_16_32(nowtimeset_hang_2,lie_7,code_ri_16_32,0);  
      
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_2,now_timer[3],0);
    //  display_oneword_8_32(nowtimeset_hang_3,lie_4,code_kongbai_8_32,0);//
    //  display_oneword_8_32(nowtimeset_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_gothic_8_32(nowtimeset_hang_3,lie_6,now_timer[4],0);
       display_oneword_8_32(nowtimeset_hang_3,lie_8,code_kongbai_8_32,0);//
      
      //display_oneword_16_32(nowtimeset_hang_4,lie_2,code_bei_16_32,0);
      //display_oneword_16_32(nowtimeset_hang_4,lie_4,code_hai_16_32,0);//
      //display_oneword_16_32(nowtimeset_hang_4,lie_6,code_dao_16_32,0);
      
      //display_oneword_16x16(nowtimeset_hang_4,lie_2,code_bei,1);
     // display_oneword_16x16(nowtimeset_hang_4,lie_4,code_bei+1,1);
      //display_oneword_16x16(nowtimeset_hang_4,lie_6,code_bei+2,1);
      display_oneword_16_16(nowtimeset_hang_4,lie_1,code_kongbai,1);
      display_area(nowtimeset_hang_4,lie_2,now_timer[5],1);
      display_oneword_16_16(nowtimeset_hang_4,lie_8,code_kongbai,1);
   }
}

void  menu_setopentime(void)
{
   if(DISP_GUANGBIAO == 0)
   {
     
   }
   if(DISP_GUANGBIAO == 1)
   {
       display_oneword_8_32(Normal_hang_2,lie_1,code_kongbai_8_32,0);//Сʱ����
     display_onetimedata_8_32(Normal_hang_2,lie_2,now_timer[1],1);//Сʱ����
      //display_oneword_8_32(1,4,code_kongbai_8_32,1);
      display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,1);//Сʱ����
      display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,0);
      display_onetimedata_8_32(Normal_hang_2,lie_6,now_timer[0],0);
      display_oneword_8_32(Normal_hang_2,lie_8,code_kongbai_8_32,0);
      //display_timeroff(Normal_hang_2,now_timer[1],now_timer[0],2);//����OFF���������õ�
   }
   if(DISP_GUANGBIAO == 2)
   {
     display_oneword_8_32(Normal_hang_2,lie_1,code_kongbai_8_32,0);//Сʱ����
     display_onetimedata_8_32(Normal_hang_2,lie_2,now_timer[1],0);//�ַ���
      display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,0);
      display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,0);
      display_onetimedata_8_32(Normal_hang_2,lie_6,now_timer[0],1);
      display_oneword_8_32(Normal_hang_2,lie_8,code_kongbai_8_32,1);
      //display_timeroff(Normal_hang_2,now_timer[1],now_timer[0],3);//����OFF���������õ�
   }
   
}

void  menu_setclosetime(void)
{
   if(DISP_GUANGBIAO == 0)
   {
     
   }
   if(DISP_GUANGBIAO == 1)
   {
     
     display_oneword_8_32(Normal_hang_3,lie_1,code_kongbai_8_32,0);//Сʱ����
     display_onetimedata_8_32(Normal_hang_3,lie_2,now_timer[1],1);//Сʱ����
    //  display_oneword_8_32(2,4,code_kongbai_8_32,1);
      display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,1);//Сʱ����
      display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_8_32(Normal_hang_3,lie_6,now_timer[0],0);
      display_oneword_8_32(Normal_hang_3,lie_8,code_kongbai_8_32,0);
      //display_timeroff(Normal_hang_3,now_timer[1],now_timer[0],2);//����OFF���������õ�
   }
   if(DISP_GUANGBIAO == 2)
   {
      display_oneword_8_32(Normal_hang_3,lie_1,code_kongbai_8_32,0);//Сʱ����
     display_onetimedata_8_32(Normal_hang_3,lie_2,now_timer[1],0);//�ַ���
      display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,0);
      display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,0);
      display_onetimedata_8_32(Normal_hang_3,lie_6,now_timer[0],1);
      display_oneword_8_32(Normal_hang_3,lie_8,code_kongbai_8_32,1);
     // display_timeroff(Normal_hang_3,now_timer[1],now_timer[0],3);//����OFF���������õ�
   }
   
}
void menu_preinstall(void)
{
  UINT8 install_open_hour[7] = {0x07,0x07,0xff,0x06,0x06,0xff,0xfe};
  UINT8 install_open_min[7] = {0x00,0x00,0xff,0x30,0x30,0xff,0xfe};
  
  UINT8 install_close_hour[7] = {0x17,0xff,0x17,0x17,0xff,0x17,0xfe};
  UINT8 install_close_min[7] = {0x00,0xff,0x00,0x30,0xff,0x30,0xfe};
  
  if(DISP_SANSUO == 6)//�Զ�
  {
          // display_oneword(4,2,code_kongbai,1);
          // display_oneword(4,4,code_zi_auto,1);
          // display_oneword(4,6,code_dong_auto,1);
         //  display_oneword(7,2,code_kongbai,1);
         //  display_oneword(7,4,code_zi_auto,1);
         //  display_oneword(7,6,code_dong_auto,1);
           
         display_oneword_16_32(Normal_hang_2,lie_2,code_zi_auto_16_32,1);  
         display_oneword_16_32(Normal_hang_2,lie_4,code_kongbai_16_32,1);
         display_oneword_16_32(Normal_hang_2,lie_6,code_dong_auto_16_32,1);  
         display_oneword_16_32(Normal_hang_3,lie_2,code_zi_auto_16_32,1);
         display_oneword_16_32(Normal_hang_3,lie_4,code_kongbai_16_32,1);
         display_oneword_16_32(Normal_hang_3,lie_6,code_dong_auto_16_32,1); 
  }
  else//���Զ�
  {
           display_onetimedata_8_32(Normal_hang_2,lie_2,install_open_hour[DISP_SANSUO],1);//ȫ��
           display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,1);
           display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,1);
           display_onetimedata_8_32(Normal_hang_2,lie_6,install_open_min[DISP_SANSUO],1);
           
           //display_timeroff(Normal_hang_2,install_open_hour[DISP_SANSUO],install_open_min[DISP_SANSUO],1);
           
           display_onetimedata_8_32(Normal_hang_3,lie_2,install_close_hour[DISP_SANSUO],1);//ȫ��
           display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,1);
           display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,1);
           display_onetimedata_8_32(Normal_hang_3,lie_6,install_close_min[DISP_SANSUO],1);
          
           //display_timeroff(Normal_hang_3,install_close_hour[DISP_SANSUO],install_close_min[DISP_SANSUO],1);
  }
  
}


void menu_openonoff(void)
{
 // if(FG_LCD_1s==1)
 // {
  //  FG_LCD_1s = 0;
    
   
    
    DISP_SANSUO++;
    
    
    
    
      if(TIMER_MODE_DISP==Timer_Mode_SET)
      {
       
      display_oneword_8_32(Normal_hang_2,lie_1,code_kongbai_8_32,1);
      display_onetimedata_8_32(Normal_hang_2,lie_2,now_timer[1],1);//Сʱ����
      display_oneword_8_32(Normal_hang_2,lie_4,code_kongbai_8_32,1);
      display_oneword_8_32(Normal_hang_2,lie_5,code_maohao_8_32,1);
      display_onetimedata_8_32(Normal_hang_2,lie_6,now_timer[0],1);
      display_oneword_8_32(Normal_hang_2,lie_8,code_kongbai_8_32,1);
      }
      if(TIMER_MODE_DISP==Timer_Mode_OFF)
      {
      display_timeroff(Normal_hang_2,now_timer[1],now_timer[0],1);
      }
      if(TIMER_MODE_DISP==Timer_Mode_AUTO)
      {
        Clear_64_32(Normal_hang_2,1);
        display_oneword_24_32(Normal_hang_2,lie_1,code_zidong_24_32,1);//Сʱ����
        display_onetimedata_8_24(Normal_hang_2_1_0824,lie_4,now_timer[1],1);
        display_oneword_8_24(Normal_hang_2_1_0824,lie_6,code_maohao_8_24,1);
        display_onetimedata_8_24(Normal_hang_2_1_0824,lie_7,now_timer[0],1);
      }
    
//  }
}

void menu_closeonoff(void)
{
  //if(FG_LCD_1s==1)
 // {
   // FG_LCD_1s = 0;
    
   
    
    DISP_SANSUO++;
    
  
    
    
      if(TIMER_MODE_DISP==Timer_Mode_SET)
      {
       display_oneword_8_32(Normal_hang_3,lie_1,code_kongbai_8_32,1);
        display_onetimedata_8_32(Normal_hang_3,lie_2,now_timer[1],1);//Сʱ����
      display_oneword_8_32(Normal_hang_3,lie_4,code_kongbai_8_32,1);
       display_oneword_8_32(Normal_hang_3,lie_5,code_maohao_8_32,1);
      display_onetimedata_8_32(Normal_hang_3,lie_6,now_timer[0],1);
       display_oneword_8_32(Normal_hang_3,lie_8,code_kongbai_8_32,1);
      }
      if(TIMER_MODE_DISP==Timer_Mode_OFF)
      {
      display_timeroff(Normal_hang_3,now_timer[1],now_timer[0],1);
      }
      if(TIMER_MODE_DISP==Timer_Mode_AUTO)
      {
        Clear_64_32(Normal_hang_3,1);
        display_oneword_24_32(Normal_hang_3,lie_1,code_zidong_24_32,1);//Сʱ����
        display_onetimedata_8_24(Normal_hang_3_1_0824,lie_4,now_timer[1],1);
        display_oneword_8_24(Normal_hang_3_1_0824,lie_6,code_maohao_8_24,1);
        display_onetimedata_8_24(Normal_hang_3_1_0824,lie_7,now_timer[0],1);
      }
  //  }
  
}




void DISP_Refresh(void)
{
  ClearWDT(); // Service the WDT
  switch(FLAG_MODE)
  {
  case NORMAL_mode:
  case ADDDEC30_mode:
       menu_normal();break;
  case NOWTIMESET_mode:
       menu_setnowtime();break;
  case OPENTIMESET_mode:
       menu_setopentime();break;
  case CLOSETIMESET_mode:
       menu_setclosetime();break;
  case PREINSTALL_mode:
       menu_preinstall();break;
  case OPENONOFF_mode:
       menu_openonoff();break;
  case CLOSEONOFF_mode:
       menu_closeonoff();break;
  default:break;       
  }
  
  if(FG_LCD_1s== 1)
  {
     FG_LCD_1s =0;
  }
}



void lcd_backlight(void)
{ 
   if((FLAG_MODE!= INIT_mode)&&(FLAG_MODE!= CONTROL_mode))
   {
   
     
      
     //if(FLAG_BACKLIGHT_5S)
   //{
      
   //    PIN_LCD_LIGHT = 1;//������
  // }
  // else
   //{
    //  PIN_LCD_LIGHT = 0;//�ر���
  //}
     
    

     
      if(FLAG_MODE!= NORMAL_mode)
      {
        if((AD_Flag==1)&&(BAT_out!=2))
          {
             PIN_LCD_LIGHT = 1;//������
          }
        switch(FLAG_MODE)
        { 
       
         case OPENTIMESET_mode: 
          case CLOSETIMESET_mode: 
        case OPENONOFF_mode:
          case CLOSEONOFF_mode:
          if(FLAG_BACKLIGHT_5S  == 0)
        {
          FLAG_MODE = NORMAL_mode;
          PIN_LCD_LIGHT = 0;//�ر���
          TB_POWER =150;
          DISP_Refresh();
        }
             break;
        
        case ADDDEC30_mode:  
          if(FLAG_BACKLIGHT_1S  == 0)
        {
          FLAG_MODE = NORMAL_mode;
          PIN_LCD_LIGHT = 0;//�ر���
          TB_POWER =150;
          DISP_Refresh();
        }
          break;
        
         case NOWTIMESET_mode: 
        if(FLAG_BACKLIGHT_60S  == 0)
        {
          FLAG_MODE = NORMAL_mode;
          PIN_LCD_LIGHT = 0;//�ر���
          TB_POWER =150;
          DISP_Refresh();
        }
        break;
        
        default:break;
        }
        
      }
     
   }
   
}

//�����������˳�����ʱ��λ
void key_touch_retime(void)
{
        switch(FLAG_MODE)
        { 
          case NORMAL_mode:
          case OPENTIMESET_mode: 
          case CLOSETIMESET_mode: 
          case OPENONOFF_mode:
          case CLOSEONOFF_mode:
          TIME_10S();
          break;
        
          case ADDDEC30_mode:  
          TIME_1S();
          break;
        
          case NOWTIMESET_mode: 
          TIME_60S();
          break;
        
          default:break;
        }
}




//Һ����ʼ��
void  lcd_init(void)
{
   if(FLAG_INITLCD == 0)
   {
   FLAG_INITLCD = 1;
   PIN_LCD_SEL  = 0;//ѡ��
   PIN_LCD_RST  = 0;//�͵�ƽ��λ
   delay(100);
   PIN_LCD_RST  = 1;//��λ���
   delay(20);
   send_command(0xe2);//�����λ
   delay(5);
   send_command(0x2c);//��ѹ1
   delay(5);
   send_command(0x2e);//��ѹ2
   delay(5);
   send_command(0x2f);//��ѹ3
   delay(5);
   send_command(0x24);//�ֵ��Աȶ�
   send_command(0x81);/*΢���Աȶ�*/
   send_command(0x1a);/*΢���Աȶȵ�ֵ�������÷�Χ0��63*/
   send_command(0xa2);/*1/9ƫѹ�ȣ�bias��*/
   send_command(0xc8);/*��ɨ��˳�򣺴��ϵ���*/
   send_command(0xa1);/*��ɨ��˳�򣺴�����*/
   send_command(0x40);//��ʾ��ʼ������
   send_command(0xaf); /*����ʾ*/
   
   clear_clear();
   //display_dianci(0,0,3,0);//�����ģʽ�޹�
   
   PIN_LCD_LIGHT = 0;//�ر���
   PIN_LCD_SEL  = 1;//��ѡ��
   
   FLAG_POWER = 0;//�����־��ֹҺ������ �������߲��ֵ��µĹػ� '
   
   if(FG_PWRON==0)
     FG_PWRON = 1;
   }
}

void Power_Low(void)
{
   if((BAT_out==2)&&(AD_Flag==1))//Ƿѹ
   {
     PIN_LCD_LIGHT = 0;//�ر���
            POWER_OFF;
            FLAG_POWER = 1;
            while(1);
   }
}


void dianciqianya_lcd(void)
{
   //UINT16 Tp_Count=0;
  // while(AD_Flag == 0)//û���С��һ��
   //{
   //    Tp_Count++;
    //   ADC2_EOC_INT();
     //  AD_control();
     //  if(Tp_Count ==0)
     //  {
     //    break;
     //  }
  // }
  
  
   if((BAT_out!=0)&&(AD_Flag==1))//Ƿѹ
     {
        if(LOW_Flag == 0)
        {
          LOW_Flag = 1;
       POWER_ON;
         TB_POWER = 50;//10second
         lcd_init();
        // PIN_LCD_LIGHT = 1;//kai����
        
          clear_clear();
         
          
          menu_dispdianci();
          
         if(BAT_out == 2)//������߶���������Һ��Ҳ����
         {
            PIN_LCD_LIGHT = 0;//�ر���
            POWER_OFF;
            FLAG_POWER = 1;
            while(1);
         }
          else
          {
              if(FLAG_MODE != CONTROL_mode)//ֻ��������
              {
            PIN_LCD_LIGHT = 1;//������
              }
          }
         
             while(1)
             {
                
                
                COUNT_QIANYA++;
                ClearWDT(); // Service the WDT
                
                 if(FLAG_MODE == CONTROL_mode)
                  {
                    TB_POWER =  0 ;
                    FLAG_POWER=1;//���Թ���
                    break;
                    
                  }
                
                if(COUNT_QIANYA >= 156000)
                {
                 
                  //2015 03 06 �޸� ��ʾ��͵�ѹ��������غ����Ϲص�Դ  ��������´ε͵�ѹ�����������
                  //TB_POWER = 50;//10second
                  if(FLAG_MODE == NORMAL_mode)
                  {
                    TB_POWER = 50;//15second  5sencond ->10sencond 20150526
                  }
                
                  
                  clear_clear();
                  PIN_LCD_LIGHT = 0;//�ر���
                 break;
                 
                }
             }
          
        }
     }
  
}

#endif
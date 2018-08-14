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
#include "key_and_Other_cyw.h"	// ����
#include "eeprom_cyw.h"		// eeprom

#if(ProductID==Hanging_display)//

UINT8 ack = 0;//Ӧ���ź�

//uchar TAB_T[]={ 0x31,0x06,0x10,//��,��,ʱ</P>
//                0x13,0x01,0x07,0x08};//��,����,��,��. 
//
//#define MIN    0x02 //��Ĵ���   
//#define SEC    0x03 //�ּĴ���   
//#define HOUR   0x04 //ʱ�Ĵ���   
//#define DAY    0x05 //�ռĴ���   
//#define WEEK   0x06 //�ܼĴ���   
//#define MONTH 0x07 //�¼Ĵ���   
//#define YEAR   0x08 //��Ĵ���   
//#define read_ADD 0xA3 //д������ַ   
//#define write_ADD 0xA2 //��������ַ   
//#define delayNOP(); delay(1);  
//
//
//unsigned char g8563_Store[4]={0x0}; /*ʱ�佻����,ȫ�ֱ�������*/  
//const unsigned char c8563_Store[4]={0x00,0x59,0x07,0x01}; /*д��ʱ���ֵ������һ 07:59:00*/  
//unsigned char F0;
//unsigned char SystemError;
//
//
////--------------------------------------------------------------------------------------------------   
//// �������ƣ� iic_start()   
//// �������ܣ� ����I2C�����ӳ���   
////--------------------------------------------------------------------------------------------------   
//void iic_start(void)  
//{
//  PIN_PCF8563_SDAOUT = 1;           
//  PIN_PCF8563_SCL = 1;  
//  delayNOP();      // ��ʱ5us    
//  PIN_PCF8563_SDAOUT = 0;  
//  delayNOP();  
//  PIN_PCF8563_SCL = 0;  
//}  
////--------------------------------------------------------------------------------------------------   
//// �������ƣ� iic_stop()   
//// �������ܣ� ֹͣI2C�������ݴ����ӳ���   
////--------------------------------------------------------------------------------------------------   
//void iic_stop(void)  
//{   
//  PIN_PCF8563_SDAOUT = 0;       //ʱ�ӱ��ָߣ������ߴӵ͵���һ�����䣬I2Cͨ��ֹͣ   
//  PIN_PCF8563_SCL = 1;  
//  delayNOP();  
//  PIN_PCF8563_SDAOUT = 1;  
//  delayNOP();  
//  PIN_PCF8563_SCL = 0;  
//}  
////--------------------------------------------------------------------------------------------------   
//// �������ƣ� slave_ACK   
//// �������ܣ� �ӻ�����Ӧ��λ�ӳ���   
////--------------------------------------------------------------------------------------------------   
//void slave_ACK(void)  
//{  
//  PIN_PCF8563_SDAOUT = 0;      
//  PIN_PCF8563_SCL = 1;  
//  delayNOP();     
//  PIN_PCF8563_SDAOUT = 1;  
//  PIN_PCF8563_SCL = 0;  
//}  
////--------------------------------------------------------------------------------------------------   
//// �������ƣ� slave_NOACK   
//// �������ܣ� �ӻ����ͷ�Ӧ��λ�ӳ�����ʹ���ݴ�����̽���   
////--------------------------------------------------------------------------------------------------   
//void slave_NOACK(void)  
//{   
//  PIN_PCF8563_SDAOUT = 1;     
//  PIN_PCF8563_SCL = 1;  
//  delayNOP();  
//  PIN_PCF8563_SDAOUT = 0;  
//  PIN_PCF8563_SCL = 0;  
//}  
////--------------------------------------------------------------------------------------------------   
//// �������ƣ� check_ACK   
//// �������ܣ� ����Ӧ��λ����ӳ�����ʹ���ݴ�����̽���   
////--------------------------------------------------------------------------------------------------   
//void check_ACK(void)  
//{   
//  PIN_PCF8563_SDAOUT = 1;      // ��p1.0���ó����룬��������˿�д1   
//  PIN_PCF8563_SCL = 1;  
//  F0 = 0;  
//  
//  PIN_PCF8563_SDA_direc = Input;
//  if(PIN_PCF8563_SDAIN == 1)    // ��SDA=1������Ӧ����λ��Ӧ���־F0   
//   F0 = 1;  
//  PIN_PCF8563_SDA_direc = Output;
//  
//  PIN_PCF8563_SCL = 0;  
//}  
//  
////--------------------------------------------------------------------------------------------------   
//// �������ƣ� IICSendByte   
//// ��ڲ����� ch   
//// �������ܣ� ����һ���ֽ�   
////--------------------------------------------------------------------------------------------------   
//void IICSendByte(unsigned char ch)  
//{   
//  unsigned char  n=8;     // ��SDA�Ϸ���һλ�����ֽڣ�����λ   
//  while(n--)  
//  {   
//      if((ch&0x80) == 0x80)    // ��Ҫ���͵��������λΪ1����λ1   
//      {  
//       PIN_PCF8563_SDAOUT = 1;    // ����λ1   
//       PIN_PCF8563_SCL = 1;  
//       delayNOP();  
//       PIN_PCF8563_SDAOUT = 0;  
//       PIN_PCF8563_SCL = 0;      
//   }  
//  else  
//   {   
//   PIN_PCF8563_SDAOUT = 0;    // ������λ0   
//   PIN_PCF8563_SCL = 1;  
//   delayNOP();  
//   PIN_PCF8563_SCL = 0;   
//   }  
//  ch = ch<<1;    // ��������һλ   
//}  
//}  
////--------------------------------------------------------------------------------------------------   
//// �������ƣ� IICreceiveByte   
//// ���ؽ��յ�����   
//// �������ܣ� ����һ�ֽ��ӳ���   
////--------------------------------------------------------------------------------------------------   
//unsigned char IICreceiveByte(void)  
//{  
//unsigned char n=8;    // ��SDA���϶�ȡһ�������ֽڣ�����λ   
//unsigned char tdata;  
//while(n--)  
//{  
//   PIN_PCF8563_SDAOUT = 1;  
//   PIN_PCF8563_SCL = 1;  
//   tdata = tdata<<1;    // ����һλ����_crol_(temp,1)   
//   
//   PIN_PCF8563_SDA_direc = Input;
//   if(PIN_PCF8563_SDAIN == 1)  
//    tdata = tdata|0x01;    // �����յ���λΪ1�������ݵ����һλ��1   
//  else   
//    tdata = tdata&0xfe;    // �������ݵ����һλ��0  
//  PIN_PCF8563_SDA_direc = Output;
//   PIN_PCF8563_SCL=0;  
//}  
//return(tdata);  
//}  
//
////--------------------------------------------------------------------------------------------------   
//// �û������ӳ���   
//// �������ƣ� receiveNbyte   
//// ��ڲ����� CFG_add�Ĵ�����ַ��ַ   
//// ���ڲ����� receive_da   
//// �������ܣ� ����ĳ���Ĵ��������ӳ���   
////--------------------------------------------------------------------------------------------------   
//unsigned char receive_CFGbyte(unsigned char CFG_add)  
//{   
//unsigned char receive_da;  
//  iic_start();  
//   IICSendByte(write_ADD); //����д��ַ   
//check_ACK();  
//if(F0 == 1)  
//{  
//   SystemError = 1;  
//   return(0);  
//}  
//IICSendByte(CFG_add); //�Ĵ�����ַ   
//check_ACK();  
//if(F0 == 1)  
//{  
//   SystemError = 1;  
//   return(0);  
//}  
//     iic_start();  
//    IICSendByte(read_ADD); //��������ַ   
//   if(F0 == 1)  
//{  
//   SystemError = 1;  
//   return(0);  
//}  
//    receive_da=IICreceiveByte();  
//   slave_NOACK();       // �յ����һ���ֽں���һ����Ӧ��λ   
//iic_stop();  
//return(receive_da);  
//}  
////--------------------------------------------------------------------------------------------------   
//// �û����ú���   
//// �������ƣ� receive_CFGNbyte   
//// ��ڲ����� CFG_add�Ĵ�����ַ��ַ��n��������λ��* buff�洢����ַ   
//// �������ܣ� ����n���Ĵ��������ӳ���   
////--------------------------------------------------------------------------------------------------   
//void receive_CFGNbyte(unsigned char CFG_add, unsigned char n,unsigned char * buff)  
//{   
//unsigned char receive_da,i=0;  
//iic_start();  
//   IICSendByte(write_ADD); //����д��ַ   
//check_ACK();  
//if(F0 == 1)  
//{  
//   SystemError = 1;  
//   return;  
//}  
//  IICSendByte(CFG_add); //�Ĵ�����ַ   
//  check_ACK();  
//  if(F0 == 1)  
//  {  
//     SystemError = 1;  
//     return;  
//  }  
//     iic_start();  
//     IICSendByte(read_ADD); //��������ַ   
//     if(F0 == 1)  
//  {  
//     SystemError = 1;  
//     return;  
//  }  
//    while(n--)  
//{   
//        receive_da=IICreceiveByte();  
//       buff[i++]=receive_da;  
//       slave_ACK();    // �յ�һ���ֽں���һ��Ӧ��λ   
//    }  
//    slave_NOACK();    // �յ����һ���ֽں���һ����Ӧ��λ   
//    iic_stop();  
//} 
//
////--------------------------------------------------------------------------------------------------   
//// �û������ӳ���   
//// �������ƣ� write_CFGbyte   
//// ��ڲ����� CFG_add�Ĵ�����ַ,CFG_dataҪд��Ĵ�������ֵ   
//// �������ܣ� ����nλ�����ӳ���   
////--------------------------------------------------------------------------------------------------   
//void write_CFGbyte(unsigned char CFG_add,unsigned char CFG_data)  
//{            
////unsigned char idata send_da,i=0;   
//    iic_start();                // ����I2C   
//    IICSendByte(write_ADD);     // ��������д��ַ   
//    check_ACK();                // ���Ӧ��λ   
//      if(F0 == 1)  
//    {   
//       SystemError = 1;  
//       return;    // ����Ӧ���������������ѻ����ô����־λSystemError   
//    }  
//    IICSendByte(CFG_add);       // ���ͼĴ�����ַ   
//    check_ACK();                // ���Ӧ��λ   
//       if(F0 == 1)  
//    {   
//      SystemError = 1;  
//      return;    // ����Ӧ���������������ѻ����ô����־λSystemError   
//    }  
//      IICSendByte(CFG_data);       // ���ͼĴ�������   
//      check_ACK();                // ���Ӧ��λ   
//       if(F0 == 1)  
//   {   
//      SystemError = 1;  
//      return;    // ����Ӧ���������������ѻ����ô����־λSystemError   
//   }  
//   iic_stop();         // ȫ��������ֹͣ   
//}  
////--------------------------------------------------------------------------------------------------   
//// �û����ú���   
//// �������ƣ� P8563_Readtime   
//// �������ܣ� ����ʱ����Ϣ   
////--------------------------------------------------------------------------------------------------   
//void P8563_Readtime()  
//{   
//  unsigned char time[7]={0x0};  
//   receive_CFGNbyte(MIN,0x07,time);  
//   g8563_Store[0]=time[0]&0x7f; /*��*/  
//   g8563_Store[1]=time[1]&0x7f; /*��*/  
//   g8563_Store[2]=time[2]&0x3f; /*Сʱ*/  
//   g8563_Store[3]=time[4]&0x07; /*����*/  
//}  
////--------------------------------------------------------------------------------------------------   
//// �û����ú���   
//// �������ƣ� P8563_settime   
//// �������ܣ� дʱ���޸�ֵ   
////--------------------------------------------------------------------------------------------------   
//void P8563_settime()  
//{  
//     unsigned char i;  
//     for(i=2;i<=4;i++) { write_CFGbyte(i,c8563_Store[i-2]); }  //miao fen shi
//     write_CFGbyte(6,c8563_Store[3]);  //weekday
//}  
//
//
//
//


//void Delayus(unsigned int timer)
//{
//  unsigned int x;            //��ʱT=(timer)us     //SYSCLK=20M
 // for(x=0;x<26*timer;x++);    //�ر�˵�������в���XC32��1���Ż���C�������Ż�����ʱ��������ʱʱ�䱻�ı��ˣ���ע�⡣    ʱ��=0.7us+timer*1.2us

//}

//void Mack(void) //����Ӧ���ź�
//{
// //SDA = 1;
// //ack=ack;
// //ack=ack;
// Delayus(1);
// PIN_PCF8563_SDA_direc = Input;
// //ack=ack;
// //ack=ack;
// Delayus(10);
// Delayus(5); //>4.7us
// PIN_PCF8563_SCL = 1;
// Delayus(4); //>4us
// Delayus(4);
// Delayus(4);
// //SDAIO = 1;
// if(PIN_PCF8563_SDAIN == 1)
//     ack = 0;
// else
//     ack = 1; //��ASK=1Ϊ��Ӧ���ź�
// PIN_PCF8563_SCL = 0;
// //ack=ack;
// //ack=ack;
// Delayus(1);
// PIN_PCF8563_SDA_direc = Output;
// Delayus(10);
//}
//
//
//void send_byte(UINT8 c)
//{
// UINT8 bit_count;
// for(bit_count = 0;bit_count < 8;bit_count++)
//     {
//      if((c << bit_count) & 0x80) PIN_PCF8563_SDAOUT = 1;
//      else  PIN_PCF8563_SDAOUT = 0;
//      //ack=ack;
//      Delayus(5); //>4.7us
//      PIN_PCF8563_SCL = 1;
//      Delayus(4); //>4us
//      PIN_PCF8563_SCL = 0;
//     }
// Mack();//�ȴ���Ӧ
//}
//
//void start_i2c(void)
//{
//    PIN_PCF8563_SDAOUT=1; //������ʼ�����������ź�
//    //ack=ack;
//    //ack=ack;
//    Delayus(1);
//    PIN_PCF8563_SCL=1;
//    Delayus(5);  //>4.7us
//    PIN_PCF8563_SDAOUT=0; //������ʼ�ź�
//    Delayus(4);  //>4us
//    PIN_PCF8563_SCL=0; //ǯסI2C����,׼���������ݻ��������
//    //ack=ack;
//    //ack=ack;
//    Delayus(1);
// }
//
//void stop_i2c(void)
//{
//   PIN_PCF8563_SDAOUT = 0; //���ͽ��������������ź�
//   Delayus(5);  //>4.7us
//   PIN_PCF8563_SCL = 1;
//   Delayus(4);//>4us
//   PIN_PCF8563_SDAOUT = 1;
//   Delayus(5);  //>4.7us
//}
//
//
//UINT8 receive_byte(void)
//{
// UINT8 retc, bit_count;
// retc = 0;
// for(bit_count = 0;bit_count < 8;bit_count++)
//     {
//     // ack=ack;
//       Delayus(1);
//      PIN_PCF8563_SCL = 0;
//      Delayus(5);  //>4.7us
//      //SDA =1;
//      PIN_PCF8563_SCL = 1;
//      Delayus(5); //>4.7us
//      retc = retc << 1;
//      if(PIN_PCF8563_SDAIN == 1)
//          retc = retc + 1;
//     }
// PIN_PCF8563_SCL = 0;
// //ack=ack;
// //ack=ack;
//  Delayus(1);
// return(retc);
//}
//
////==============Write()дN�ֽ�����=================//
//
//void Write_pcf8563(UINT8 *s,UINT8 suba,UINT8 n)  //24LC16B
//
//{
//     UINT8 i;
// 
//    start_i2c(); //��������
//
//    send_byte(0xa2);//����������ַ
//
//    send_byte(suba); //�����ֵ�ַ
//
//    for (i = 0;i < n;i++)
//     
//    {
//      
//       send_byte(*s); //�����ֽ�����
//     
//       s++;
//     
//    }
// 
//    stop_i2c(); //����ֹͣλ
//
//}
//
//void N0ack(char a) //����Ӧ��λ
//{
// PIN_PCF8563_SDA_direc = Output;
// //ack=ack;
// Delayus(10);
// if(a==0)PIN_PCF8563_SDAOUT = 0;
// else  PIN_PCF8563_SDAOUT = 1;
// Delayus(5);  //>4.7us
// PIN_PCF8563_SCL = 1;
// Delayus(4);//>4us
// PIN_PCF8563_SCL = 0;
//}
//
//void Read_pcf8563(UINT8 *s,UINT8 suba,UINT8 n)
//
//{
// UINT8 i;
// 
//   start_i2c(); //��������
//
//   send_byte(0xa2);//����������ַ
//
//   send_byte(suba); //�����ֵ�ַ
//
//   start_i2c(); //������������
//
//   send_byte(0xa3); //���Ͷ������������ַ
//
//   for(i = 0;i < n - 1;i++)
//     
//   {
//      
//     PIN_PCF8563_SDA_direc = Input;
//     
//      Delayus(10);
//     
//     *s = receive_byte(); //�������
//     
//     s++;
//      
//     N0ack(0); //����Ӧ���ź�
//    
//   }
// 
//     PIN_PCF8563_SDA_direc = Input;
//   
//   Delayus(10);
//   
//     *s = receive_byte(); //�������
//
//     N0ack(1); //���ͷ�Ӧ��λ
//
//     stop_i2c(); //����ֹͣλ
//}
//
//
// void Read_Time(void)
// 
// {
//   unsigned char  time_arr[7] = {0};
//   Read_pcf8563(&time_arr[0],0x02,7);
//          
//   g8563_Store[0]= time_arr[0]&0x7F;
//          
//   g8563_Store[1]= time_arr[1]&0x7F;
//          
//   g8563_Store[2]= time_arr[2]&0x3F;
//          
//   g8563_Store[3]= time_arr[3]&0x3F;
//          
//   g8563_Store[4]= time_arr[4]&0x07;
//          
//   g8563_Store[5]=time_arr[5]&0x1F;
//          
//   g8563_Store[6]= time_arr[6];
// }
//
//
// void Set_Time(void)
//
//{
//     
//                             /*�롢  ��  ��ʱ�����ڡ����ڡ��¡��� */
//    unsigned char c8563_Store[7]={0x00,0x59,0x07,0x01,0x01,0x01,0x14}; /*д��ʱ���ֵ������һ 07:59:00*/  
//    UINT8 data_i[2]={0x00,0x00};
//    
//     Write_pcf8563(&data_i[0],0x00,2);
//  //����״̬�Ĵ���        
//     Delayus(10);
//          
//     Write_pcf8563(&c8563_Store[0],0x02,7);
//}


//#define iic_delay Delayus(20)
#define iic_delay Delayus(1)//������ӳ������������IIC ����

 void Start(void) 
 { 
      PIN_PCF8563_SDAOUT=1; 
      PIN_PCF8563_SCL=1; 
      iic_delay;
      PIN_PCF8563_SDAOUT=0; 
      iic_delay;
 } 

void Stop(void) 
 { 
    PIN_PCF8563_SDAOUT=0; 
    PIN_PCF8563_SCL=1; 
    iic_delay;
    PIN_PCF8563_SDAOUT=1; 
    iic_delay;
} 

void Reack(void) 
 { 
    uchar i=0; 
    PIN_PCF8563_SDA_direc = Input;
    iic_delay;
    PIN_PCF8563_SCL=1; //׼�����SDA Delay5us(); 
    while((PIN_PCF8563_SDAIN==1)&&(i<100))
    {
      i++;//SDA=0ΪӦ���ź�,SDA=1Ϊ��Ӧ��</P>
    }
    PIN_PCF8563_SDA_direc = Output;
    iic_delay;
    PIN_PCF8563_SCL=0; //׼����һ�仯����</P>
 } 

void WriteByte(uchar ucByte) 
 { 
    uchar i; 
    PIN_PCF8563_SCL=0; 
    for(i=0;i<8;i++) 
    { 
      if(ucByte&0x80)//��д���λ</P>
      {
        PIN_PCF8563_SDAOUT=1;
      }
      else
      {
         PIN_PCF8563_SDAOUT=0;
      }
      PIN_PCF8563_SCL=1; 
      iic_delay;
      PIN_PCF8563_SCL=0; 
      ucByte<<=1; 
    } 
    PIN_PCF8563_SDAOUT=1; //�ͷ�������</P>
 } 

uchar ReadByte(void) 
 { 
    uchar i,ucByte=0; 
    
     PIN_PCF8563_SDA_direc = Input;
    iic_delay;
    
    PIN_PCF8563_SCL=0; 
    for(i=0;i<8;i++) 
    { 
        ucByte<<=1; 
       if(PIN_PCF8563_SDAIN) 
          ucByte++; 
       PIN_PCF8563_SCL=1; 
       iic_delay;
      PIN_PCF8563_SCL=0; 
    } 
    
     PIN_PCF8563_SDA_direc = Output;
    iic_delay;
    
    return ucByte; 
 } 

void Write8563(uchar ucAddr,uchar ucData) 
 { 
       iic_delay;
      Start(); 
      WriteByte(0xa2); 
      Reack(); 
      WriteByte(ucAddr); 
      Reack(); 
      WriteByte(ucData); 
      Reack(); 
      Stop(); 
} 

uchar Read8563(uchar ucAddr) 
 { 
      uchar ucData; 
       iic_delay;
      Start(); 
      WriteByte(0xa2); //д������ַ</P>
      Reack(); 
      WriteByte(ucAddr); //д�ֽڵ�ַ</P>
      Reack(); 
      Start(); 
      WriteByte(0xa3); //д������ַ,���Ϊ1��ʾ��</P>
      Reack(); 
      ucData=ReadByte(); //д�ֽڵ�ַ</P>
      Stop(); 
      return ucData; //������</P>
} 


void Alarm8563(void)
{
  UINT16 Tp_opentime,Tp_closetime,Tp_nowtime;
  UINT8 Tp_mon=0;//,Tp_Data;
  UINT8 Tp_flag = 0;// 0-�����κ����� 1-����OPEN  2-����CLOSE
  
  ClearWDT(); // Service the WDT
  
  
 
  
  
  
  if((TIMER_MODE_OPEN == Timer_Mode_SET)||(TIMER_MODE_OPEN == Timer_Mode_OFF))
  {
     Tp_opentime = (decimal(open_hour))*60+decimal(open_min);
  }
  if(TIMER_MODE_OPEN == Timer_Mode_AUTO)
  {
    Tp_opentime = (decimal(auto_open_hour))*60+decimal(auto_open_min);
  }
   if((TIMER_MODE_CLOSE == Timer_Mode_SET)||(TIMER_MODE_CLOSE == Timer_Mode_OFF))
  {
    Tp_closetime = (decimal(close_hour))*60+decimal(close_min);
  }
   if(TIMER_MODE_CLOSE == Timer_Mode_AUTO)
   {
     Tp_closetime = (decimal(auto_close_hour))*60+decimal(auto_close_min);
   }
  Tp_nowtime = (decimal(now_hour))*60+decimal(now_min);
  
  
   if((TIMER_MODE_OPEN == Timer_Mode_AUTO)||(TIMER_MODE_CLOSE == Timer_Mode_AUTO))
  {
    //���
    if(decimal(now_day)==calculate_monandday(now_year,now_mon))//���������һ����
    {
       if(((Tp_nowtime >= Tp_opentime)||(Tp_opentime > 1440))&&((Tp_nowtime >= Tp_closetime)||(Tp_closetime>1440)))//���еĶ��������� 
       {
          Tp_mon = decimal(now_mon) + 1; 
          if(Tp_mon >= 13)
            Tp_mon = 1;
          Auto_Timer_refresh(hex(Tp_mon));
          
          if(TIMER_MODE_OPEN == Timer_Mode_AUTO)
           {
                Tp_opentime = (decimal(auto_open_hour))*60+decimal(auto_open_min);
           }
           if(TIMER_MODE_CLOSE == Timer_Mode_AUTO)
           {
                Tp_closetime = (decimal(auto_close_hour))*60+decimal(auto_close_min);
           }
          
       }  
    }
  }
  
  
  ClearWDT(); // Service the WDT
  
  
  if(Tp_opentime!=Tp_closetime)//���������ͬһʱ�� ���������� ���Ҫ���� ��һ���ϵ� Ҫ������
  {
  //˫��û����
   if((Tp_opentime > 1440)&&(Tp_closetime < 1440)) //������
  {
    Tp_flag = 2;//����CLOSEΪ����ı���ʱ��
  }
  if((Tp_closetime > 1440)&&(Tp_opentime < 1440)) //������
  {
    Tp_flag = 1;//����OPENΪ����ı���ʱ��
  }
  if((Tp_closetime < 1440)&&(Tp_opentime < 1440))//���ؼĴ�����û��OFF�Ļ� Ӧ�������뵱ǰʱ������Ķ����ǽ�����ʱ��Ϊ����ʱ��
  {
    if((Tp_nowtime<Tp_opentime)&&(Tp_nowtime<Tp_closetime))//�������ʱ�̶��ǽ���ʱ�� ���ý���
    {
        if(Tp_opentime>Tp_closetime)//Tp_opentime>Tp_closetime>Tp_nowtime
        {
          Tp_flag = 2;//����CLOSEΪ����ı���ʱ��
        }
        else
        {
          Tp_flag = 1;//����OPENΪ����ı���ʱ��
        }
    }
     if((Tp_nowtime>Tp_opentime)&&(Tp_nowtime>Tp_closetime))//�������ʱ�̶��ǵڶ����ʱ�� ����С��
     {
        if(Tp_opentime>Tp_closetime)//Tp_opentime>Tp_closetime>Tp_nowtime
        {
          Tp_flag = 2;//����CLOSEΪ����ı���ʱ��
        }
        else
        {
          Tp_flag = 1;//����OPENΪ����ı���ʱ��
        }
     }
     if((Tp_nowtime>Tp_opentime)&&(Tp_nowtime<Tp_closetime))
     {
       Tp_flag = 2;//����CLOSEΪ����ı���ʱ��
     }
    if((Tp_nowtime<Tp_opentime)&&(Tp_nowtime>Tp_closetime))
     {
       Tp_flag = 1;//����OPENΪ����ı���ʱ��
     }
    if(Tp_nowtime == Tp_opentime)//���������RTC�ձ��꿪�ľ� �ѹ�ʱ�̷Ž�ȥ ǰ���������ò���ʱ���� �������Ǳ��꾯������
     {
        Tp_flag = 2;//����CLOSEΪ����ı���ʱ��
     }
    if(Tp_nowtime == Tp_closetime)//���������RTC�ձ���صľ� �ѿ�ʱ�̷Ž�ȥ ǰ���������ò���ʱ���� �������Ǳ��꾯������
     {
         Tp_flag = 1;//����OPENΪ����ı���ʱ��
     }
  }
  }
  ClearWDT(); // Service the WDT
  
  
 // Write8563(0x00,0x20); //ͣʱ��
  if(Tp_flag == 1)//�������ǿ�ʱ��Ž��Ĵ���
  {
 // Write8563(0x00,0x20); 
  if(TIMER_MODE_OPEN == Timer_Mode_SET)
  {
     Write8563(0x09,open_min); //�ֱ���
     Write8563(0x0A,open_hour); //ʱ����
  }
  if(TIMER_MODE_OPEN == Timer_Mode_AUTO)
  {
     Write8563(0x09,auto_open_min); //�ֱ���
     Write8563(0x0A,auto_open_hour); //ʱ����
  }
  Write8563(0x0B,0X80); //ÿ��1�ձ����ر��ձ���
  Write8563(0x0C,0X80);//�ر��ܱ���
 
  }
  if(Tp_flag == 2)//�������Ǳ�ʱ��Ž��Ĵ���
  {
 // Write8563(0x00,0x20);
   if(TIMER_MODE_CLOSE == Timer_Mode_SET)
   {
     Write8563(0x09,close_min); //�ֱ���
     Write8563(0x0A,close_hour); //ʱ����
   }
   if(TIMER_MODE_CLOSE == Timer_Mode_AUTO)
   {
     Write8563(0x09,auto_close_min); //�ֱ���
     Write8563(0x0A,auto_close_hour); //ʱ����
   }
   Write8563(0x0B,0X80); //ÿ��1�ձ����ر��ձ���
   Write8563(0x0C,0X80);//�ر��ܱ���
 // Write8563(0x00,0x00);
//  Write8563(0x0b,0x00); //�ֱ���
 // Write8563(0x0c,0x00); //ʱ����
  }
  if(Tp_flag == 0)//��ֹ���б��� ����=�� Ҳ���� ���Ҫ��Ҫ ����
  {
     Write8563(0x09,0x80); //�ֱ���
     Write8563(0x0A,0x80); //ʱ����
     Write8563(0x0B,0X80); //ÿ��1�ձ����ر��ձ���
     Write8563(0x0C,0X80);//�ر��ܱ���
  }
  // Write8563(0x00,0x00); //ͣʱ��
  //��������AUTOģʽ
  //Tp_Data= Read8563(1);
   //  if((Tp_Data&0x02)==0)//������ʾPCF8563û�б�����
    //  {  
    //      Rewrite8563();
    //   }
   Auto_Timer_refresh(now_mon);//��ʹʵʱʱ���ǰ����¸��µ���LOAD�� ������ʾ���ǵ��µ�ֱ������24�� �����Ұ� ��������װ��
}


void Init8563(void) 
 { 
      
   /*�롢  ��  ��ʱ�����ڡ����ڡ��¡��� */
   unsigned char c8563_Store[7]={0x00,0x00,0x00,0x24,0x05,0x10,0x14}; /*д��ʱ���ֵ������һ 07:59:00*/  
   
      uchar i,ucAddr=0x02,Tp_data; 
       FLAG_RTC_RTC = 1;//���������
      Tp_data = Read8563(1);
      if((Tp_data&0x02)==0)//������ʾPCF8563û�б�����
      {  
        
       ClearWDT(); // Service the WDT   
      //ClearWDT(); // Service the WDT
     // Write8563(0x00,0x20); 
      Write8563(0x01,0x02); 
     
      for(i=0;i<7;i++) 
      { 
        Write8563(ucAddr,c8563_Store[i]); 
        ucAddr++; 
      }
      
       FLAG_RTC_RTC = 0;
      GetTime();
       FLAG_RTC_RTC = 1;
      ClearWDT(); // Service the WDT   
       Auto_Timer_refresh(now_mon);
       ClearWDT(); // Service the WDT   
      Alarm8563();
     Write8563(0x00,0x00);
     
      }
      
       FLAG_RTC_RTC = 0;
      
      
 } 
 
 
 //���ֶ�����ʱ����
void Rewrite8563(void) 
 { 
      
   /*�롢  ��  ��ʱ�����ڡ����ڡ��¡��� */
   
      uchar i,ucAddr=0x02; 
      
      ClearWDT(); // Service the WDT
     // Write8563(0x00,0x20); 
      FLAG_RTC_RTC = 1;
      //Write8563(0x00,0x20);//ͣʱ��
     // Write8563(0x01,0x02); 
      Write8563(0x01,0x02); 
      for(i=0;i<7;i++) 
      { 
        Write8563(ucAddr,g8563_Store[i]); 
        ucAddr++; 
      } 
      Write8563(0x00,0x00);
      FLAG_RTC_RTC = 0;
 } 
 
 
void GetTime(void) 
 { 
      uchar i,ucAddr=0x02; 
      uchar *pTime=g8563_Store; 
      
      ClearWDT(); // Service the WDT
      
      
      if(FLAG_RTC_RTC ==1)
      {
         return;
      }
      
     
      FLAG_RTC_RTC = 1;
      for(i=0;i<7;i++) 
      { 
          pTime[i]=Read8563(ucAddr); 
          ucAddr++; 
      } 
      pTime[0]&=0x7f; //������Чλ</P>
      pTime[1]&=0x7f; 
      pTime[2]&=0x3f; 
      pTime[3]&=0x3f; 
      pTime[4]&=0x07; 
      pTime[5]&=0x1f; 
     FLAG_RTC_RTC = 0;
      FLAG_CLOCK =1;
} 

void real_time(void)
{
  uchar Tp_data,i;
   unsigned char c8563_Store[7]={0x00,0x00,0x00,0x24,0x05,0x10,0x14}; /*д��ʱ���ֵ������һ 07:59:00*/  
  
    
  
  if((FLAG_MODE!= INIT_mode)&&(FLAG_MODE!= CONTROL_mode))
   {
       if(FG_RTC_1s == 1)
       {
          
         Tp_data = Read8563(1);
        if((Tp_data&0x02)==0)//������ʾPCF8563û�б�����
        {  
          Rewrite8563();
           Write8563(0x01,0x02); 
          return;
        }
         GetTime();
        FG_RTC_1s = 0;
        if(HIS_MIN!=now_min)
        {
          display_nowtime();
           HIS_MIN = now_min;
           Auto_Timer_refresh(now_mon);//ˢ���Զ�������ʱ�� 20150505
        }
       // FLAG_PRESS =0;//so long so clear
         
       }
   }
  if((decimal(now_sec)>=60)||(decimal(now_min)>=60)||(decimal(now_hour)>=24)||(decimal(now_day)>=32)||(decimal(now_mon)>=13)||(decimal(now_year)>=100)\
    ||(decimal(now_day)==0)||(decimal(now_mon)==0))
    
  {
     if(FLAG_CLOCK==1)
     {
    for(i=0;i<7;i++) 
      { 
        g8563_Store[i]=c8563_Store[i]; 
      
      }
     
    Rewrite8563();
     }
  }
  if(DISP_DIQU>=8)
  {
     DISP_DIQU = 0;
     eeprom_diqu_save();
  }
 
}

#endif


#include  <iostm8l151c6.h>				// CPU�ͺ� 
#include "initial.h"		// ��ʼ��  Ԥ����
#include "Pin_define.h"		// �ܽŶ���
#include "Timer.h"
#include "ram.h"		// RAM����
#include "ram_cyw.h"		// RAM����
#include "adf7012.h"		// RF IC
#include "EXIT_FUN.h"		// �ⲿEXIT�ж�
#include "eeprom.h"		// eeprom
#include "uart.h"		// uart
#include "lcd_cyw.h"
#include "font_cyw.h"
#include "pcf8563_cyw.h"
#include "key_and_Other_cyw.h"		// ����
#include "key_and_Other.h"		// ����
#include "eeprom_cyw.h"		// eeprom
#include "initial_cyw.h"		// ��ʼ��  Ԥ����
#include "ad.h"		        // AD

#if(ProductID==Hanging_display)//


void Refresh_second_send_time(UINT8 x_type)
{
  static UINT8  Tp_last_bit;
  Second_send_STR.times_second_send = time1ms_count;
  Second_send_STR.flag_second_send = 1;
  Second_send_STR.Type_second_send = x_type;
  Tp_last_bit = ID_data.IDL%10;
  Second_send_STR.Interval_second_send = 2300 + (UINT16)Tp_last_bit*200;
  //PIN_LCD_LIGHT = 1;//������
  FLAG_POWER =0;
  TB_POWER = 100;//10S
  PIN_POWER_CONTROL = 1;
}


//�����л���ʱ����
void Auto_Timer_refresh(UINT8 x_mon)
{
   UINT8 Tp_mon;
   Tp_mon = decimal(x_mon);
   
   if((Tp_mon<13)&&(DISP_DIQU<8))
   auto_open_min =  Area_time[DISP_DIQU][Tp_mon-1][1];
   auto_open_hour =  Area_time[DISP_DIQU][Tp_mon-1][0];
   auto_close_min =  Area_time[DISP_DIQU][Tp_mon-1][3];
   auto_close_hour =  Area_time[DISP_DIQU][Tp_mon-1][2];
}

void openclose_output(void)
{
    //��ʱ��������
  
    if((PIN_POWER_AD == 0)&&(AD_Flag==1))
    {
        ClearWDT(); // Service the WDT
      
        
        
        
        if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == INIT_mode)||(FLAG_MODE == CONTROL_mode))//���õ�ʱ���ܲ�������źţ�
        {
          
            GetTime();//��ȡʱ��
          
         
          if((FLAG_MODE == INIT_mode)||(FLAG_MODE == CONTROL_mode)) //���������̬��RTC�͵�ƽ���ѵ� �������ɰ������ѵ�NORMAL̬��Ҫ��ȡEEPROM����Ĳ���
          {
            
            eeprom_kaiguan_load();
            eeprom_kaiguanmode_load();
            eeprom_diqu_load();
            Auto_Timer_refresh(now_mon);
           
          }  
          //}
          if(FLAG_MODE == NORMAL_mode)//����ǰ������ѵ�NORMAL״̬ͬʱRTC�������� ������ʾ�µ�ǰʱ��
          {
             DISP_Refresh();
          }
          
           ClearWDT(); // Service the WDT
          
         
          
          
          if((now_min==open_min)&&(now_hour==open_hour)&&(TIMER_MODE_OPEN == Timer_Mode_SET))
          {
             if(BAT_out == 0)//��ѹ����
            {
            Control_code=0x08;     //open
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
           _ReqBuzzer(103,103,0);//������
           Refresh_second_send_time(Control_code);
            }
             if(BAT_out == 1)//��ѹ�쳣
            {
            Control_code=0x08;     //open
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
           _ReqBuzzer(40,60,2);//������
            Refresh_second_send_time(Control_code);
            }
          }
           if((now_min==close_min)&&(now_hour==close_hour)&&(TIMER_MODE_CLOSE == Timer_Mode_SET))
          {
             if(BAT_out == 0)//��ѹ����
            {
            Control_code=0x02;     //CLOSE
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
             _ReqBuzzer(103,103,2);//������
              Refresh_second_send_time(Control_code);
            }
             if(BAT_out == 1)//��ѹ����
            {
            Control_code=0x02;     //CLOSE
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
             _ReqBuzzer(40,60,2);//������
              Refresh_second_send_time(Control_code);
            }
          }
          
          if((now_min==auto_open_min)&&(now_hour==auto_open_hour)&&(TIMER_MODE_OPEN == Timer_Mode_AUTO))
          {
            
             if(BAT_out == 0)//��ѹ����
            {
            Control_code=0x08;     //open
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
            _ReqBuzzer(103,103,0);//������
             Refresh_second_send_time(Control_code);
            }
              if(BAT_out == 1)//��ѹ����
            {
            Control_code=0x08;     //open
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
            _ReqBuzzer(40,60,2);//������
             Refresh_second_send_time(Control_code);
            }
          }
                                                                       
            if((now_min==auto_close_min)&&(now_hour==auto_close_hour)&&(TIMER_MODE_CLOSE == Timer_Mode_AUTO))
          {
             if(BAT_out == 0)//��ѹ����
            {
            Control_code=0x02;     //CLOSE
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
             _ReqBuzzer(103,103,2);//������
              Refresh_second_send_time(Control_code);
            }
             if(BAT_out == 1)//��ѹ����
            {
            Control_code=0x02;     //CLOSE
            dd_set_ADF7021_Power_on();
            dd_set_TX_mode();	
            SendTxData();
           // LED_ON;
             _ReqBuzzer(40,60,2);//������
              Refresh_second_send_time(Control_code);
            }
          }
                                                                       
          if((FLAG_MODE == INIT_mode)||(FLAG_MODE == CONTROL_mode))//�������ʱ�䲻�Ǳ���ʱ�䶼Ҫ�ر� ���ϵͳ�Ǳ�RTC���ѵ�
          {
            FLAG_MODE = CONTROL_mode;//���õ�Դ�ر�
            TB_POWER =60;// 20;//��������0.02S���POWER_OFF
            POWER_ON;
            FLAG_POWER = 0;//�����־��ֹҺ������ �������߲��ֵ��µĹػ� '
            if(FG_PWRON==0)
                FG_PWRON = 1;
          }
        
      
        }
        
        
        
          dianciqianya_lcd();
            Write8563(0x01,0x02); //�ֶ����ƽ
          Alarm8563();//���ñ���
        
    }
    
     if( Second_send_STR.flag_second_send == 1)
     {
            //if(get_timego(Second_send_STR.times_second_send)>=  Second_send_STR.Interval_second_send)
          if(FLAG_APP_TX ==0)
            {
            Second_send_STR.flag_second_send = 2;
            Second_send_STR.times_second_send = time1ms_count;
           
            
            }
    }
    
    if( Second_send_STR.flag_second_send == 2)//��һ�η�����ɺ󣬵ȴ�ʱ�䵽
    {
      while(1)//���1 2��֮���ֹ����
      {
      if(get_timego(Second_send_STR.times_second_send)>=  Second_send_STR.Interval_second_send)
      {
        Second_send_STR.flag_second_send =3;
         Control_code= Second_send_STR.Type_second_send;     
         dd_set_ADF7021_Power_on();
         dd_set_TX_mode();	
         SendTxData();
         break; 
       //  FLAG_POWER = 1;
        //LED_ON;
      }
      }
    }
    
    if(Second_send_STR.flag_second_send == 3)//��ֹ��TIMER���ѵĵڶ����Ժ� һֱ����û��LED���
    {
      if(FLAG_APP_TX ==0)
      {
        Second_send_STR.flag_second_send =4;
      }
      TB_POWER = 20; //CYW9��6�ոĵ� ����˵����Ҫֹͣ2S
    }
    
    if(Second_send_STR.flag_second_send == 4)
    {
      while(1)
      {
        power_control();
        ClearWDT();
        if(TB_POWER==0)
        {
          POWER_OFF;
          while(1);
        }
      }
    }
    
    
}


void BEEP_ON_SHORT(void)
{
  //FLAG_beep_CYW = 1;
  //BEEP_COUNT=500;
  
  //TIM3_init();//TEST
   DISP_Refresh();//ˢ����ʾ
}

void BEEP_ON_LONG(void)
{
  //FLAG_beep_CYW = 1;
 // BEEP_COUNT=2000;
 
  DISP_Refresh();//ˢ����ʾ
}

void BEEP_OFF(void)
{
//  if(BEEP_COUNT)
 //  {
 //     BEEP_COUNT--;
 //  }
 //  if(BEEP_COUNT == 0)
 //  {
  //   FLAG_beep_CYW = 0;
 //  }
    //if((FG_LCD_1s == 1)&&((FLAG_MODE ==OPENONOFF_mode)||(FLAG_MODE ==CLOSEONOFF_mode)))//ֻ�����»�����
   // {
      
     //  DISP_Refresh();//ˢ����ʾ
    //}
}


void OPEN_TIMER_ONOFF(void)
{
  if(FLAG_MODE == NORMAL_mode)
  {
    TIME_10S();
    FLAG_MODE = OPENONOFF_mode;
    Auto_Timer_refresh(now_mon);
    if(TIMER_MODE_OPEN == Timer_Mode_SET)
    {
    now_timer[0] = open_min;
    now_timer[1] = open_hour;//nowtime����Ĵ�����ʵ���ǻ���һ��
    }
    if(TIMER_MODE_OPEN == Timer_Mode_OFF)
    {
      now_timer[0] = 0xff;
      now_timer[1] = 0xff;
    }
    if(TIMER_MODE_OPEN == Timer_Mode_AUTO)
    {
      now_timer[0] =  auto_open_min;
      now_timer[1] = auto_open_hour;
    }
    DISP_SANSUO = 0;//��һ����˸�ܽ���������ֵ
    TIMER_MODE_DISP =TIMER_MODE_OPEN;
    
  }
}

void CLOSE_TIMER_ONOFF(void)
{
  if(FLAG_MODE == NORMAL_mode)
  {
    TIME_10S();
    FLAG_MODE = CLOSEONOFF_mode;
    Auto_Timer_refresh(now_mon);
    if(TIMER_MODE_CLOSE == Timer_Mode_SET)
    {
    now_timer[0] = close_min;
    now_timer[1] = close_hour;//nowtime����Ĵ�����ʵ���ǻ���һ��
    }
    if(TIMER_MODE_CLOSE == Timer_Mode_OFF)
    {
      now_timer[0] = 0xff;
       now_timer[1] = 0xff;
    }
    if(TIMER_MODE_CLOSE == Timer_Mode_AUTO)
    {
      now_timer[0] = auto_close_min;
      now_timer[1] = auto_close_hour;
    }
    
      DISP_SANSUO = 0;//��һ����˸�ܽ���������ֵ
      TIMER_MODE_DISP =TIMER_MODE_CLOSE;
      
  }
}


void Clear_Key_Function_Count(void)
{
          KEY_CLOSETIME_COUNT = 0;
          KEY_OPENTIME_COUNT = 0;
          KEY_NOWTIME_COUNT = 0;
          KEY_ADD_COUNT = 0;
          KEY_DEC_COUNT = 0;
          KEY_DECIDE_COUNT=0;
}

void OPEN_LCD_AND_8563(void)
{
  UINT32 Tp_count=0;
  if((FLAG_MODE == INIT_mode)||(FLAG_MODE == CONTROL_mode))
  {
    if(OPEN_Flag == 0)
    {
         // Delaycyw(178);
      
          OPEN_Flag  =1;//Ҫ��������
          POWER_ON;
          //TB_POWER = 600;//1min
          TB_POWER = 150;//5second ->15second 20150403
          TB_POWER = 150;//5second ->15second 20150403
          TB_POWER = 150;//5second ->15second 20150403
          TB_POWER = 150;//5second ->15second 20150403
          TB_POWER = 150;//5second ->15second 20150403
          //ClearWDT(); // Service the WDT
          ClearWDT(); // Service the WDT
          //Ҫ��Ҫ��ʱ��ϵͳ�ȶ�
          lcd_init();
          ClearWDT(); // Service the WDT
          eeprom_kaiguan_load();
          ClearWDT(); // Service the WDT
          eeprom_diqu_load();
          ClearWDT(); // Service the WDT
          eeprom_kaiguanmode_load();
          ClearWDT(); // Service the WDT
          eeprom_kaiguanlast_load();//��Щ˳�򶼻�����
          ClearWDT(); // Service the WDT
          GetTime();
          ClearWDT(); // Service the WDT
          Auto_Timer_refresh(now_mon);
          ClearWDT(); // Service the WDT
          Init8563();//�ȱ��������Ѿ�OK�� ��װRTC������
          ClearWDT(); // Service the WDT
         
          
          KEY_COUNT = 0;
          FG_KEY_OPEN_CYW = 0;
          FG_KEY_STOP_CYW = 0;
          FG_KEY_CLOSE_CYW = 0;
          FG_KEY_LOGIN_CYW = 0;
          FG_KEY_DECIDE=0;// 
          FG_KEY_CLOSETIME=0;//
          FG_KEY_NOWTIME=0;//
          FG_KEY_OPENTIME=0;//
          FG_KEY_DEC=0;//
          FG_KEY_ADD=0;
          FLAG_MODE = NORMAL_mode;
          Clear_Key_Function_Count();
          
          
          while(AD_Flag==0)
          {
            ADC2_EOC_INT();
            AD_control();
            Tp_count++;
            if(Tp_count >=90000)
            {
              break;
            }
          }//20150526 ��ʱ�򴥷�ʱҺ�����ⲻ��BUG 
         
          dianciqianya_lcd();//���Ƿѹ��ʾ
         if((AD_Flag==1)&&(BAT_out!=2))
         {
          PIN_LCD_LIGHT = 1;//������
         }
         //  if((AD_Flag==1))
         // {
            
         // }
        
         
    }
  }
  else
  {
     
  }
  
}

void SET_PREINSTALL(void)
{
   if(FLAG_MODE == NORMAL_mode)
  {
     //TIME_10S();
   // FLAG_MODE = PREINSTALL_mode;//����Ԥ��ģʽ
    //DISP_SANSUO = 0;//��˸������Ԥ�������Ǻ�
   
  }
}

void SET_CLOSETIME(void)
{
   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == CLOSETIMESET_mode)) //ֻ����ͨģʽ�ܽ� ���߱��������� 
   //if((FLAG_MODE == CLOSEONOFF_mode)) //ֻ����ͨģʽ�ܽ� ���߱��������� 
  {
      if(1)//����ģʽֻ��00��00�����ܽ�
    // if(TIMER_MODE_DISP == Timer_Mode_SET)//����ģʽֻ��00��00�����ܽ�
     {
     if(TIMER_MODE_CLOSE == Timer_Mode_SET)
      //if(TIMER_MODE_CLOSE == Timer_Mode_SET) 
     {
        now_timer[0] = close_min;
        now_timer[1] = close_hour;//nowtime����Ĵ�����ʵ���ǻ���һ��
     }
     //if((TIMER_MODE_CLOSE == Timer_Mode_OFF)||(TIMER_MODE_CLOSE == Timer_Mode_AUTO))
     if((TIMER_MODE_CLOSE == Timer_Mode_OFF)||(TIMER_MODE_CLOSE == Timer_Mode_AUTO))
     {
       now_timer[0] = last_close_min;
       now_timer[1] = last_close_hour;//nowtime����Ĵ�����ʵ���ǻ���һ��
     }
     //TIMER_MODE_CLOSE = Timer_Mode_SET;
     //eeprom_guanmode_save();
      TIME_10S();
      FLAG_MODE = CLOSETIMESET_mode;//����ʱ���趨ģʽ
      DISP_GUANGBIAO = 1;//�����ʾСʱͻ��
   }
   }
   // if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == CLOSETIMESET_mode)) //ֻ����ͨģʽ�ܽ� ���߱��������� 
   if((FLAG_MODE == CLOSEONOFF_mode)) //ֻ����ͨģʽ�ܽ� ���߱��������� 
  {
      //if(TIMER_MODE_CLOSE == Timer_Mode_SET)//����ģʽֻ��00��00�����ܽ�
     if(TIMER_MODE_DISP == Timer_Mode_SET)//����ģʽֻ��00��00�����ܽ�
     {
    
      TIME_10S();
      FLAG_MODE = CLOSETIMESET_mode;//����ʱ���趨ģʽ
      DISP_GUANGBIAO = 1;//�����ʾСʱͻ��
   }
   }
}

void SET_OPENTIME(void)
{
   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == OPENTIMESET_mode)) //ֻ����ͨģʽ�ܽ� ���߱��������� 
   //if((FLAG_MODE == OPENONOFF_mode))
   {
      if(1)//����ģʽֻ��00��00�����ܽ�
    // if(TIMER_MODE_DISP  == Timer_Mode_SET )
      {
      //if(TIMER_MODE_OPEN == Timer_Mode_SET)
      if(TIMER_MODE_OPEN  == Timer_Mode_SET )
     {
        now_timer[0] = open_min;
        now_timer[1] = open_hour;//nowtime����Ĵ�����ʵ���ǻ���һ��
     }
     //if((TIMER_MODE_OPEN == Timer_Mode_OFF)||(TIMER_MODE_OPEN == Timer_Mode_AUTO))
     if((TIMER_MODE_OPEN == Timer_Mode_OFF)||(TIMER_MODE_OPEN == Timer_Mode_AUTO))
     {
       now_timer[0] = last_open_min;
       now_timer[1] = last_open_hour;//nowtime����Ĵ�����ʵ���ǻ���һ��
     }
     
      //TIMER_MODE_OPEN = Timer_Mode_SET;
      //eeprom_kaimode_save();
      TIME_10S();
      FLAG_MODE = OPENTIMESET_mode;//����ʱ���趨ģʽ
      
      DISP_GUANGBIAO = 1;//�����ʾСʱͻ��
     
   }
   }
     // if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == OPENTIMESET_mode)) //ֻ����ͨģʽ�ܽ� ���߱��������� 
   if((FLAG_MODE == OPENONOFF_mode))
   {
     // if(TIMER_MODE_OPEN == Timer_Mode_SET)//����ģʽֻ��00��00�����ܽ�
     if(TIMER_MODE_DISP  == Timer_Mode_SET )
      {
    
     
      //TIMER_MODE_OPEN = Timer_Mode_SET;
      //eeprom_kaimode_save();
      TIME_10S();
      FLAG_MODE = OPENTIMESET_mode;//����ʱ���趨ģʽ
      
      DISP_GUANGBIAO = 1;//�����ʾСʱͻ��
     
   }
   }
}

void SET_NOWTIME(void)//���õ�ǰʱ��
{
   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == NOWTIMESET_mode)) //ֻ����ͨģʽ�ܽ� ���߱��������� 
   {
      TIME_60S();
      FLAG_MODE = NOWTIMESET_mode;//����ʱ���趨ģʽ
      DISP_GUANGBIAO = 0;//�����ʾ��ͻ��
      now_timer[0] = now_year;
      now_timer[1] = now_mon;//nowtime����Ĵ�����ʵ���ǻ���һ��
      now_timer[2] = now_day;
      now_timer[3] = now_hour;
      now_timer[4] = now_min;
      now_timer[5] = DISP_DIQU;
      clear_clear();
      menu_setnowtime();//�����ˢ���� �� �� ��Щ�̶��ĵ�
      DISP_GUANGBIAO = 1;//�����ʾ��ͻ��
      
  }
}
 
void OPEN_TO_NORMAL(void)
{
       DISP_GUANGBIAO = 0;
       FLAG_MODE=NORMAL_mode;
        PIN_LCD_LIGHT = 0;//�ر���
       if(TIMER_MODE_OPEN == Timer_Mode_SET)//�����Զ�ģʽ
       {
        if(((now_timer[0]!=open_min)||(now_timer[1]!=open_hour))&&(now_timer[0]!=0XFF)&&(now_timer[1]!=0XFF))//һ�������ı� ���� �������Ͳ�������
        {
         open_min = now_timer[0];
         open_hour = now_timer[1];
         eeprom_kai_save();
         
        // if((open_min!=0xff)&&(open_hour!=0xff))
        // {
         last_open_timer[1]=open_hour;
        last_open_timer[0]=open_min;
        eeprom_kaiguanlast_save();
       //  }
         
         //Alarm8563();  
        }
       }
        if(TIMER_MODE_OPEN == Timer_Mode_OFF)//�����Զ�ģʽ
       {
        if(((now_timer[0]!=open_min)||(now_timer[1]!=open_hour))&&(now_timer[0]==0XFF)&&(now_timer[1]==0XFF))//һ�������ı� ���� �������Ͳ�������
        {
         open_min = now_timer[0];
         open_hour = now_timer[1];
         eeprom_kai_save();
         
        // if((open_min!=0xff)&&(open_hour!=0xff))
        // {
       //  last_open_timer[1]=open_hour;
        //last_open_timer[0]=open_min;
        //eeprom_kaiguanlast_save();
        // }
         
         //Alarm8563();  
        }
       }
       Alarm8563();  //����ʲôģʽ���¼���RTC�ı����Ǳ����
}
void CLOSE_TO_NORMAL(void)
{
   DISP_GUANGBIAO = 0;
       FLAG_MODE=NORMAL_mode;
        PIN_LCD_LIGHT = 0;//�ر���
       if(TIMER_MODE_CLOSE == Timer_Mode_SET)
       {
       if(((now_timer[0]!=close_min)||(now_timer[1]!=close_hour))&&(now_timer[0]!=0XFF)&&(now_timer[1]!=0XFF))//һ�������ı� ���� �������Ͳ�������
       {
         close_min = now_timer[0];
         close_hour = now_timer[1];
          eeprom_guan_save();
        // if((close_min!=0xff)&&(close_hour!=0xff))
         //{
          last_close_timer[1]=close_hour;
        last_close_timer[0]=close_min;
         eeprom_kaiguanlast_save();
        // }
        
        // Alarm8563();   
       }
       }
       if(TIMER_MODE_CLOSE == Timer_Mode_OFF)
       {
       if(((now_timer[0]!=close_min)||(now_timer[1]!=close_hour))&&(now_timer[0]==0XFF)&&(now_timer[1]==0XFF))//һ�������ı� ���� �������Ͳ�������
       {
         close_min = now_timer[0];
         close_hour = now_timer[1];
          eeprom_guan_save();
        // if((close_min!=0xff)&&(close_hour!=0xff))
         //{
         // last_close_timer[1]=close_hour;
        //last_close_timer[0]=close_min;
         //eeprom_kaiguanlast_save();
        // }
        
        // Alarm8563();   
       }
       }
       Alarm8563(); //����ʲôģʽ���¼���RTC�ı����Ǳ����
}

void PREINTALL_TO_NORMAL(void)
{
  UINT8 install_open_hour[7] = {0x07,0x07,0xff,0x06,0x06,0xff,0xfe};
  UINT8 install_open_min[7] = {0x00,0x00,0xff,0x30,0x30,0xff,0xfe};
  
  UINT8 install_close_hour[7] = {0x17,0xff,0x17,0x17,0xff,0x17,0xfe};
  UINT8 install_close_min[7] = {0x00,0xff,0x00,0x30,0xff,0x30,0xfe};
  
  
  
  if(DISP_SANSUO == 6)//�Զ�
  {
    FLAG_MODE=NORMAL_mode;//?
     PIN_LCD_LIGHT = 0;//�ر���
  }
  else
  {
    FLAG_MODE=NORMAL_mode;
    open_min = install_open_min[DISP_SANSUO];
    open_hour = install_open_hour[DISP_SANSUO];
    if((open_min!=0xff)&&(open_hour!=0xff))
    {
    last_open_timer[1]=open_hour;
    last_open_timer[0]=open_min;
    eeprom_kaiguanlast_save();
    }
    close_min = install_close_min[DISP_SANSUO];
    close_hour = install_close_hour[DISP_SANSUO];
    if((close_min!=0xff)&&(close_hour!=0xff))
    {
    last_close_timer[1]=close_hour;
    last_close_timer[0]=close_min;
    eeprom_kaiguanlast_save();
    }
    eeprom_kai_save();
    eeprom_guan_save();
    Alarm8563();  
  }
  
}


void FUNCTION_DUE(void)
{
  
  if((FLAG_MODE==NOWTIMESET_mode)||(FLAG_MODE==OPENTIMESET_mode)||(FLAG_MODE==CLOSETIMESET_mode))
   {
     if((FLAG_MODE==NOWTIMESET_mode)&&(DISP_GUANGBIAO == 6))
     {
       DISP_GUANGBIAO = 0;
       FLAG_MODE=NORMAL_mode;
        PIN_LCD_LIGHT = 0;//�ر���
       if((now_timer[0]!=now_year)||(now_timer[1]!=now_mon)||(now_timer[2]!=now_day)||(now_timer[3]!=now_hour)||(now_timer[4]!=now_min))//һ�������ı� ���� �������Ͳ������� ��������BUG
       {
         //now_min = now_timer[0];
         //now_hour = now_timer[1];
         now_year   = now_timer[0] ;
         now_mon    = now_timer[1] ;//nowtime����Ĵ�����ʵ���ǻ���һ��
         now_day    = now_timer[2] ;
         now_hour   = now_timer[3] ;
         now_min    = now_timer[4] ;
         now_sec  = 0;//��������ʱ���ʱ����������
         clear_clear();
         Rewrite8563();
       }
       if(DISP_DIQU != now_timer[5])
       {
          DISP_DIQU  = now_timer[5] ;
          eeprom_diqu_save(); 
          
       }
        //clear_clear();
        Auto_Timer_refresh(now_mon);
        Alarm8563();//��ʱ��LOAD�����ڼĴ���ȫ��������֮�����
     }
     if((FLAG_MODE==OPENTIMESET_mode)&&(DISP_GUANGBIAO == 2))
     {
        TIMER_MODE_OPEN = Timer_Mode_SET;
       eeprom_kaimode_save();//���Զ�/OFF/SETģʽ��¼��
       OPEN_TO_NORMAL();
       
     }
     
      if((FLAG_MODE==CLOSETIMESET_mode)&&(DISP_GUANGBIAO == 2))
     {
      
        TIMER_MODE_CLOSE= Timer_Mode_SET;
       eeprom_guanmode_save();//���Զ�/OFF/SETģʽ��¼��
       CLOSE_TO_NORMAL();
       
     }
     
    // if(DISP_GUANGBIAO == 1)
    // {
       DISP_GUANGBIAO++;//��Ϊ��͹��
     //}
     
   }
  
  if(FLAG_MODE==OPENONOFF_mode)
  {
    
   //if((open_min!=0xff)&&(open_hour!=0xff))//�ڱ�����֮ǰ�Ͻ����˰�
    
    //{
     // last_open_timer[0] = open_min;//��¼��һ�εĿ���ʱ��
     // last_open_timer[1] = open_hour;
     // eeprom_kaiguanlast_save();
  // }
    TIMER_MODE_OPEN = TIMER_MODE_DISP;
    eeprom_kaimode_save();//���Զ�/OFF/SETģʽ��¼��
    OPEN_TO_NORMAL();
  }
  if(FLAG_MODE==CLOSEONOFF_mode)
  {
  //  if((close_min!=0xff)&&(close_hour!=0xff))//�ڱ�����֮ǰ�Ͻ����˰�
   
  // {
   //   last_close_timer[0] = close_min;
   //   last_close_timer[1] = close_hour;
   //   eeprom_kaiguanlast_save();
   // }
    TIMER_MODE_CLOSE = TIMER_MODE_DISP;
    eeprom_guanmode_save();//���Զ�/OFF/SETģʽ��¼��
    CLOSE_TO_NORMAL();
  }
  
  if(FLAG_MODE==PREINSTALL_mode)
  {
    PREINTALL_TO_NORMAL();
  }
  
}

UINT8 decimal(UINT8 x_Data)
{
   UINT8 Tp_data;
   Tp_data = x_Data%16 + (x_Data/16)*10;
   return Tp_data;
}

UINT8 hex(UINT8 x_Data)
{
   UINT8 Tp_data;
   Tp_data = x_Data%10 + (x_Data/10)*16;
   return Tp_data;
}

void CURSOR_CHANGE_ADD(void)
{
   if(FLAG_MODE == PREINSTALL_mode)//ֻ��Ԥ��ģʽ��Ч �ڶ�ʱ��ON/OFFģʽDISP_SANSUOΪ�Զ�����
   {
     DISP_SANSUO++;
     if(DISP_SANSUO == 7) DISP_SANSUO=0;
   }
   
}

void CURSOR_CHANGE_DEC(void)
{
   if(FLAG_MODE == PREINSTALL_mode)//ֻ��Ԥ��ģʽ��Ч �ڶ�ʱ��ON/OFFģʽDISP_SANSUOΪ�Զ�����
   {
     if(DISP_SANSUO == 0) DISP_SANSUO=7;
     DISP_SANSUO--;
   }
   
}

void ONOFF_OPEN_ADD(void)
{
  
   if(FLAG_MODE == OPENONOFF_mode)//
   {
      TIMER_MODE_DISP++;
     if(TIMER_MODE_DISP > 2)
        TIMER_MODE_DISP = 0;
     
     if(TIMER_MODE_DISP==Timer_Mode_SET)
     {
      // if((open_hour==0xff)||(open_min ==0xff))//�ǹصĻ�����ʾ��һ�εĿ�ʱ����
      //   {
              now_timer[1] = last_open_timer[1];
              now_timer[0] = last_open_timer[0];
              
       // }
       // else
       //  {
       //       now_timer[1] = open_hour;
       //      now_timer[0] = open_min;//��һ��
       // }
     }
     if(TIMER_MODE_DISP==Timer_Mode_OFF)
     {
       now_timer[1] = 0xff;
       now_timer[0] = 0xff;
      
     }
      if(TIMER_MODE_DISP==Timer_Mode_AUTO)
      {
        now_timer[1] = auto_open_hour;
        now_timer[0] = auto_open_min;
      }
      DISP_SANSUO = 0;
       TB_1s_CYW = BASE_1s;
       FG_LCD_1s =1;//����������ʾЧ���� Ϊ��һ����������������ĸо�
     
   }
  
  
}

void ONOFF_CLOSE_ADD(void)
{
  
     if(FLAG_MODE == CLOSEONOFF_mode)//
   {
     
      TIMER_MODE_DISP++;
     if(TIMER_MODE_DISP > 2)
        TIMER_MODE_DISP = 0;
     
     if(TIMER_MODE_DISP==Timer_Mode_SET)
     {
      // if((close_hour==0xff)||(close_min ==0xff))//�ǹصĻ�����ʾ��һ�εĿ�ʱ����
     // {
      now_timer[1] = last_close_timer[1];
      now_timer[0] = last_close_timer[0];
     // }
     // else
     // {
      //now_timer[1] = close_hour;
     // now_timer[0] = close_min;//��һ��
     // }
     }
     if(TIMER_MODE_DISP==Timer_Mode_OFF)
     {
     
      now_timer[1] = 0xff;
      now_timer[0] = 0xff;
      
     }
     
      if(TIMER_MODE_DISP==Timer_Mode_AUTO)
      {
        now_timer[1] = auto_close_hour;
        now_timer[0] = auto_close_min;
      }
      DISP_SANSUO = 0;
       TB_1s_CYW = BASE_1s;
       FG_LCD_1s =1;//����������ʾЧ���� Ϊ��һ����������������ĸо�
   }
    
}


UINT8 calculate_monandday(UINT8 x_year,UINT8 x_mon)
{
  //���� ���µ�����
  UINT8 Tp_day = 0;
  UINT16 Tp_year=0;
  ClearWDT(); // Service the WDT
  Tp_year = 2000+ decimal(x_year);
  switch(x_mon)
  {    
     case 0x1:    
     case 0x03:    
     case 0x05:   
     case 0x07:    
     case 0x08:    
     case 0x10:    
     case 0x12:Tp_day=31;break;    
     case 0x04:    
     case 0x06:    
     case 0x09:    
     case 0x11:Tp_day=30;break;    
     case 0x02:Tp_day=28+(Tp_year%4==0&&Tp_year%100!=0||Tp_year%400==0);    
     default :break;    
  }
  return  Tp_day;
}


UINT8 DATA_CHANGE_ADD(void)//���ݵ���
{
   UINT8 Tp_jinzhi;
   UINT8 Tp_max[2] = {23,59};
   UINT8 Tp_sub[2] = {1,0};
   UINT8 Tp_max_now[6] = {99,12,31,23,59,7};
   UINT8 Tp_min_now[6] = {0,  1, 1, 0, 0,0};
   
  Tp_max_now[2] = calculate_monandday(now_timer[0],now_timer[1]);
  
   if(FLAG_MODE == NOWTIMESET_mode)
  {
      
      Tp_jinzhi  = decimal(now_timer[DISP_GUANGBIAO-1]);
      Tp_jinzhi  =  Tp_jinzhi+1;
      if(Tp_jinzhi > Tp_max_now[DISP_GUANGBIAO-1] )
      {
         Tp_jinzhi = Tp_min_now[DISP_GUANGBIAO-1] ;
      }
      now_timer[DISP_GUANGBIAO-1] = hex(Tp_jinzhi);
      
      Tp_max_now[2] = calculate_monandday(now_timer[0],now_timer[1]);
      if(now_timer[2] > hex(Tp_max_now[2]))//���ڲ��ܴ�
      {
        now_timer[2] = hex(Tp_max_now[2]);
      }
  }
  
  if((FLAG_MODE == OPENTIMESET_mode)||(FLAG_MODE == CLOSETIMESET_mode))
  {
     if((now_timer[0]==0xff)||(now_timer[1]==0xff))
   {
      return 0;
   }
   
    if((DISP_GUANGBIAO==1)||(DISP_GUANGBIAO==2))//˵��������Сʱ
    {
      Tp_jinzhi = decimal(now_timer[Tp_sub[DISP_GUANGBIAO-1]]);
      Tp_jinzhi = Tp_jinzhi + 1;
      if(Tp_jinzhi > Tp_max[DISP_GUANGBIAO-1])
      {
         Tp_jinzhi = Tp_jinzhi  - Tp_max[DISP_GUANGBIAO-1] -1;
      }
      now_timer[Tp_sub[DISP_GUANGBIAO-1]] = hex(Tp_jinzhi);
    }
  }
  
  
   return 0;
}


UINT8 DATA_CHANGE_ADD30(UINT8 x_flag)
{
   UINT16 Tp_jinzhi;
  if(OPEN_Flag == 0)
  {
    return 0;
  }

   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == ADDDEC30_mode))//����ģʽ��Ч
   {
      FLAG_MODE = ADDDEC30_mode;
    //  TIME_1S();
      if(x_flag == 0)
      {
         if((TIMER_MODE_OPEN==Timer_Mode_AUTO)||(TIMER_MODE_OPEN==Timer_Mode_OFF))
         {
           return 0;
         }
        now_timer[1]=open_hour;
        now_timer[0]=open_min;
      }
      if(x_flag == 1)
      {
        if((TIMER_MODE_CLOSE==Timer_Mode_AUTO)||(TIMER_MODE_CLOSE==Timer_Mode_OFF))
         {
           return 0;
         }
        now_timer[1]=close_hour;
        now_timer[0] =close_min;
      }
       if((now_timer[0]==0xff)||(now_timer[1]==0xff))
      {
         return 0;
      }
      TIME_1S();
      Tp_jinzhi = decimal(now_timer[0]) + decimal(now_timer[1])*60;
      Tp_jinzhi = Tp_jinzhi + 30;
      if(Tp_jinzhi > 1439)
      {
        Tp_jinzhi = Tp_jinzhi  - 1439 - 1;
      }
      now_timer[0] = hex(Tp_jinzhi%60);
      now_timer[1] = hex(Tp_jinzhi/60);
      if((x_flag == 0)&&(TIMER_MODE_OPEN==Timer_Mode_SET))
      {
        open_hour = now_timer[1];
        open_min = now_timer[0];
         eeprom_kai_save();
         
        if((open_min!=0xff)&&(open_hour!=0xff))
        {
        last_open_timer[1]=open_hour;
        last_open_timer[0]=open_min;
        eeprom_kaiguanlast_save();
        }
       
         Alarm8563();  
      }
      if((x_flag == 1)&&(TIMER_MODE_CLOSE==Timer_Mode_SET))
      {
        close_hour = now_timer[1];
        close_min = now_timer[0];
        if((close_min!=0xff)&&(close_hour!=0xff))
        {
        last_close_timer[1]=close_hour;
        last_close_timer[0]=close_min;
        eeprom_kaiguanlast_save();
        }
        eeprom_guan_save();
         Alarm8563();  
      }
   }
    return 1;
}

UINT8 DATA_CHANGE_DEC30(UINT8 x_flag)
{
   UINT16 Tp_jinzhi;
   if(OPEN_Flag == 0)
  {
    return 0;
  }
   if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == ADDDEC30_mode))//����ģʽ��Ч
   {
       FLAG_MODE = ADDDEC30_mode;
     // TIME_1S();
      if(x_flag == 0)
      {
        if((TIMER_MODE_OPEN==Timer_Mode_AUTO)||(TIMER_MODE_OPEN==Timer_Mode_OFF))
         {
           return 0;
         }
        now_timer[1]=open_hour ;
        now_timer[0]=open_min;
      }
      if(x_flag == 1)
      {
         if((TIMER_MODE_CLOSE==Timer_Mode_AUTO)||(TIMER_MODE_CLOSE==Timer_Mode_OFF))
         {
           return 0;
         }
        now_timer[1]=close_hour;
        now_timer[0] =close_min;
      }
       if((now_timer[0]==0xff)||(now_timer[1]==0xff))
      {
         return 0;
      }
      TIME_1S();
      Tp_jinzhi = decimal(now_timer[0]) + decimal(now_timer[1])*60;
      
      if(Tp_jinzhi < 30)
      {
        Tp_jinzhi = 1440 + Tp_jinzhi;
      }
      
      Tp_jinzhi = Tp_jinzhi - 30;
      
      now_timer[0] = hex(Tp_jinzhi%60);
      now_timer[1] = hex(Tp_jinzhi/60);
      if((x_flag == 0)&&(TIMER_MODE_OPEN==Timer_Mode_SET))
      {
        open_hour = now_timer[1];
        open_min = now_timer[0];
        if((open_min!=0xff)&&(open_hour!=0xff))
        {
        last_open_timer[1]=open_hour;
        last_open_timer[0]=open_min;
        eeprom_kaiguanlast_save();
        }
        eeprom_kai_save();
         Alarm8563();  
      }
      if((x_flag == 1)&&(TIMER_MODE_CLOSE==Timer_Mode_SET))
      {
        close_hour = now_timer[1];
        close_min = now_timer[0];
        if((close_min!=0xff)&&(close_hour!=0xff))
        {
         last_close_timer[1]=close_hour;
        last_close_timer[0]=close_min;
        eeprom_kaiguanlast_save();
        }
        eeprom_guan_save();
         Alarm8563();  
      }
   }
    return 1;
}

UINT8 DATA_CHANGE_DEC(void)//���ݵ���
{
   UINT8 Tp_jinzhi;
   UINT8 Tp_max[2] = {24,60};
   UINT8 Tp_sub[2] = {1,0};
   UINT8 Tp_max_now[6] = {99,12,31,23,59,7};
   UINT8 Tp_min_now[6] = {0,  1, 1, 0, 0,0};
   Tp_max_now[2] = calculate_monandday(now_timer[0],now_timer[1]);
   
    if(FLAG_MODE == NOWTIMESET_mode)
  {
      
      Tp_jinzhi  = decimal(now_timer[DISP_GUANGBIAO-1]);
      
      if(Tp_jinzhi <= Tp_min_now[DISP_GUANGBIAO-1] )
      {
         Tp_jinzhi = Tp_max_now[DISP_GUANGBIAO-1] +1 ;
      }
      Tp_jinzhi  =  Tp_jinzhi-1;
      now_timer[DISP_GUANGBIAO-1] = hex(Tp_jinzhi);
      
      
       Tp_max_now[2] = calculate_monandday(now_timer[0],now_timer[1]);
       if(now_timer[2] > hex(Tp_max_now[2]))//���ڲ��ܴ�
      {
        now_timer[2] = hex(Tp_max_now[2]);
      }
  }
  
  
  if((FLAG_MODE == OPENTIMESET_mode)||(FLAG_MODE == CLOSETIMESET_mode))
  {
   if((now_timer[0]==0xff)||(now_timer[1]==0xff))
      {
         return 0;
      }
   
  if((DISP_GUANGBIAO==1)||(DISP_GUANGBIAO==2))//˵��������Сʱ
   {
      Tp_jinzhi = decimal(now_timer[Tp_sub[DISP_GUANGBIAO-1]]);
      if(Tp_jinzhi == 0 )
      {
         Tp_jinzhi = Tp_max[DISP_GUANGBIAO-1];
      }
      Tp_jinzhi = Tp_jinzhi - 1 ;
      now_timer[Tp_sub[DISP_GUANGBIAO-1]] = hex(Tp_jinzhi);
   }
  }
  
   return 0;
}

void SCAN_OPEN(void)
{
  if((PIN_KEY_OPEN==0)&&(FG_KEY_OPEN_CYW==0)){
    FG_KEY_OPEN_CYW=1;
    //����ص�Դ
     if(FLAG_MODE == INIT_mode)
     {
    FLAG_MODE = CONTROL_mode;
    
    TB_POWER = 1000;
   // dianciqianya_lcd();//���Ƿѹ��ʾ
     }
  }
   if((PIN_KEY_OPEN==1)&&(FG_KEY_OPEN_CYW==1)) KEY_COUNT++;
}


void SCAN_CLOSE(void)
{
    if((PIN_KEY_CLOSE==0)&&(FG_KEY_CLOSE_CYW==0)){
    FG_KEY_CLOSE_CYW=1;
    if(FLAG_MODE == INIT_mode)
    {
      FLAG_MODE = CONTROL_mode;//��Һ������ʱ ���߲���������CONTROLģʽ
      TB_POWER = 1000;
     
     // dianciqianya_lcd();//���Ƿѹ��ʾ
    }
    //����ص�Դ
  }
  if((PIN_KEY_CLOSE==1)&&(FG_KEY_CLOSE_CYW==1)) KEY_COUNT++;  
  
}

void SCAN_STOP(void)
{
  if((PIN_KEY_STOP==0)&&(FG_KEY_STOP_CYW==0)){
    FG_KEY_STOP_CYW=1;
    //����ص�Դ
    if(FLAG_MODE == INIT_mode)
    {
    FLAG_MODE = CONTROL_mode;
    TB_POWER = 1000;
    
   // dianciqianya_lcd();//���Ƿѹ��ʾ
    }
  }
  if((PIN_KEY_STOP==1)&&(FG_KEY_STOP_CYW==1)) KEY_COUNT++;
}

void SCAN_LOGIN(void)
{
   if((PIN_KEY_LOGIN==0)&&(FG_KEY_LOGIN_CYW==0)){
    FG_KEY_LOGIN_CYW=1;
    //����ص�Դ
    if(FLAG_MODE == INIT_mode)
    {
    FLAG_MODE = CONTROL_mode;
    TB_POWER = 1000;
  
   // dianciqianya_lcd();//���Ƿѹ��ʾ
    }
  }
  if((PIN_KEY_LOGIN==1)&&(FG_KEY_LOGIN_CYW==1)) KEY_COUNT++;
}

UINT8 FLAG_NOWTIME_LONG=0;
void  SCAN_NOWTIME(void)
{
       //����ʱ���
   if(PIN_KEY_NOWTIME==0)
   {
     Delayus(key_Antishake);
      if(PIN_KEY_NOWTIME==0)
   {
    // TIME_10S();
     key_touch_retime();
    FG_KEY_NOWTIME=1;
    KEY_NOWTIME_COUNT++;
     if((FLAG_NOWTIME_LONG==0)&&(KEY_NOWTIME_COUNT > key_fun))
     {
       if(FLAG_PRESS==0)
       {
         FLAG_PRESS = key_press_long;
       //BACKLIGHT_ON();
       SET_NOWTIME();//���õ�ǰʱ��
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); //�� �����ʱ������ ��������ڲ����ı�֮��
       FLAG_NOWTIME_LONG = 1;
       }
     }
     key_touch_retime();
   }
  }
  if((PIN_KEY_NOWTIME==1)&&(FG_KEY_NOWTIME==1))KEY_COUNT++;
  
   if((PIN_KEY_NOWTIME==1)&&(FG_KEY_NOWTIME==1)&&(KEY_NOWTIME_COUNT!=0)) 
  {   
     
     if(KEY_NOWTIME_COUNT < key_fun)
     {
       //BEEP_ON_SHORT();//�� 
      // BACKLIGHT_ON();
       OPEN_LCD_AND_8563();
       BEEP_ON_SHORT();//�� 
     }
     else
     {
      //BACKLIGHT_ON();
       //BEEP_ON_LONG(); //�� ��������ʱ�̵�����ģʽ
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); 
     }
     KEY_NOWTIME_COUNT = 0;
    // Clear_Key_Function_Count();
     FLAG_NOWTIME_LONG = 0;
  }
}




UINT8 FLAG_DECIDE_LONG=0;

void SCAN_DECIDE(void)
{
   if(PIN_KEY_DECIDE==0)
   {
      Delayus(key_Antishake);
      if(PIN_KEY_DECIDE==0)
   {
     //TIME_10S();
     key_touch_retime();
     FG_KEY_DECIDE=1;
    KEY_DECIDE_COUNT++;
    if((FLAG_DECIDE_LONG==0)&&(KEY_DECIDE_COUNT > key_fun))
     {
       //BACKLIGHT_ON();
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); //��Һ�� ��ʼ��ʱ��
       FLAG_DECIDE_LONG = 1;
     }
  }
  }
  if((PIN_KEY_DECIDE==1)&&(FG_KEY_DECIDE==1))KEY_COUNT++;
  
   if((PIN_KEY_DECIDE==1)&&(FG_KEY_DECIDE==1)&&(KEY_DECIDE_COUNT!=0)) 
  {   
     
     if(KEY_DECIDE_COUNT < key_fun)
     {
       if(FLAG_PRESS==0)
       {
       FLAG_PRESS = key_press_short;
         FUNCTION_DUE();
       
      // BACKLIGHT_ON();
       OPEN_LCD_AND_8563();
       BEEP_ON_SHORT();//��
       }
     }
     else
     {
       //BACKLIGHT_ON();
       //  BEEP_ON_LONG(); //�� ����LCD
       OPEN_LCD_AND_8563();
       BEEP_ON_SHORT();//�� 
     }
     KEY_DECIDE_COUNT = 0;
     //Clear_Key_Function_Count();
     FLAG_DECIDE_LONG = 0;
  }
}


UINT8 FLAG_ADD_ZUHE=0;


void SCAN_ADD(void)
{
   if(PIN_KEY_ADD==0)
   {
    Delayus(key_Antishake);
    if(PIN_KEY_ADD==0)
   {
    // TIME_10S();
     key_touch_retime();
    FG_KEY_ADD=1;
    KEY_ADD_COUNT++;
    if(PIN_KEY_OPENTIME == 0)
    {
      FLAG_ADD_ZUHE = 1;
    }
    if(PIN_KEY_CLOSETIME == 0)
    {
      FLAG_ADD_ZUHE = 2;
    }
    if(KEY_ADD_COUNT>key_fast)
    {
     if(FLAG_PRESS==0)
     {
      FLAG_PRESS=60;
       COUNT_FAST++;
        if(COUNT_FAST >= count_speed) 
        {
          DATA_CHANGE_ADD();
          COUNT_FAST = 0;
          //BACKLIGHT_ON();
          OPEN_LCD_AND_8563();
        }
      BEEP_ON_LONG(); //�� ���
     }
    }
  }
   }
  if((PIN_KEY_ADD==1)&&(FG_KEY_ADD==1))KEY_COUNT++;
  
   if((PIN_KEY_ADD==1)&&(FG_KEY_ADD==1)&&(KEY_ADD_COUNT!=0)) 
  {   
     
     if(KEY_ADD_COUNT < key_fun)
     {
      if(FLAG_PRESS==0)
      {
        FLAG_PRESS = key_press_short;
       if(FLAG_ADD_ZUHE==0)//�̼�
       {
         DATA_CHANGE_ADD();
         CURSOR_CHANGE_ADD();
         //ONOFF_CHANGE_ADDDEC(0);
         
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       if(FLAG_ADD_ZUHE==1)//��ʱ���30
       {
         DATA_CHANGE_ADD30(0);//����ģʽ�¼�30
         
        // BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       if(FLAG_ADD_ZUHE==2)//��ʱ���30
       {
         DATA_CHANGE_ADD30(1);//����ģʽ�¼�30
         
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
      }
     }
     else
     {
      //BACKLIGHT_ON();
       //BEEP_ON_LONG(); //�� ���
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); //�� ���
     }
     KEY_ADD_COUNT = 0;
     //Clear_Key_Function_Count();
     FLAG_ADD_ZUHE = 0;
  }
}


UINT8 FLAG_DEC_ZUHE=0;

void SCAN_DEC(void)
{
   if(PIN_KEY_DEC==0)
   {
     Delayus(key_Antishake);
     if(PIN_KEY_DEC==0)
   {
     //TIME_10S();
     key_touch_retime();
    FG_KEY_DEC=1;
    KEY_DEC_COUNT++;
    if(PIN_KEY_OPENTIME == 0)
    {
      FLAG_DEC_ZUHE = 1;
    }
    if(PIN_KEY_CLOSETIME == 0)
    {
      FLAG_DEC_ZUHE = 2;
    }
    if(KEY_DEC_COUNT>key_fast)
    {
       if(FLAG_PRESS==0)
       {
       FLAG_PRESS = 60;
         COUNT_FAST++;
        if(COUNT_FAST >= count_speed) 
        {
          DATA_CHANGE_DEC();
          COUNT_FAST = 0;
          //BACKLIGHT_ON();
          OPEN_LCD_AND_8563();
        }
      BEEP_ON_LONG(); //�� ���
       }
    }
  }
   }
  if((PIN_KEY_DEC==1)&&(FG_KEY_DEC==1))KEY_COUNT++;
  
   if((PIN_KEY_DEC==1)&&(FG_KEY_DEC==1)&&(KEY_DEC_COUNT!=0)) //�̼��ɿ�ʱ���� ������ʱ��ʹ���
  {   
     
     if(KEY_DEC_COUNT < key_fun)
     {
      if(FLAG_PRESS==0)
       {
         FLAG_PRESS = key_press_short;
       if(FLAG_DEC_ZUHE==0)//�̼�
       {
         DATA_CHANGE_DEC();
         CURSOR_CHANGE_DEC();
         //ONOFF_CHANGE_ADDDEC(1);
         
        // BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       if(FLAG_DEC_ZUHE==1)//��ʱ���30
       {
         DATA_CHANGE_DEC30(0);
        
        // BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
          BEEP_ON_SHORT();//�� 
       }
       if(FLAG_DEC_ZUHE==2)//��ʱ���30
       {
         DATA_CHANGE_DEC30(1);
        
       //  BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
          BEEP_ON_SHORT();//�� 
       }
       }
     }
     else
     {
      //BACKLIGHT_ON();
       //BEEP_ON_LONG(); //�� ���
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); //�� ���
     }
     KEY_DEC_COUNT = 0;
     //Clear_Key_Function_Count();
     FLAG_DEC_ZUHE = 0;
  }
}



UINT8 FLAG_OPENTIME_ZUHE=0;
UINT8 FLAG_OPENTIME_LONG=0;

void SCAN_OPENTIME(void)
{
   if(PIN_KEY_OPENTIME==0)
   {
    Delayus(key_Antishake);
    if(PIN_KEY_OPENTIME==0)
   {
    // TIME_10S();
     key_touch_retime();
    FG_KEY_OPENTIME=1;
    KEY_OPENTIME_COUNT++;
     if(PIN_KEY_CLOSETIME == 0)
    {
      FLAG_OPENTIME_ZUHE = 1;
    }
     if(PIN_KEY_ADD == 0)
    {
      FLAG_OPENTIME_ZUHE = 2;
    }
     if(PIN_KEY_DEC == 0)
    {
      FLAG_OPENTIME_ZUHE = 3;
    }
      if((FLAG_OPENTIME_LONG==0)&&(KEY_OPENTIME_COUNT > key_fun))
     {
        if(FLAG_PRESS==0)
        {
          FLAG_PRESS = key_press_long;
       //BEEP_ON_LONG(); //�� ����kaiʱ������
       FLAG_OPENTIME_LONG = 1;
      if(FLAG_OPENTIME_ZUHE==0)
      {
        SET_OPENTIME();//���ÿ�ʱ��
        OPEN_LCD_AND_8563();
        BEEP_ON_LONG(); //���뿪ʱ������
       // BACKLIGHT_ON();
      }
      if(FLAG_OPENTIME_ZUHE==1)
      {
        //SET_PREINSTALL(); //���뿪��ʱ��Ԥ���趨 �ڶ�������û���ᵽ���
        OPEN_LCD_AND_8563();
        BEEP_ON_LONG(); 
      //  BACKLIGHT_ON();
      }
        }
     }
     key_touch_retime();
    }
  }
  if((PIN_KEY_OPENTIME==1)&&(FG_KEY_OPENTIME==1))KEY_COUNT++;
  
   if((PIN_KEY_OPENTIME==1)&&(FG_KEY_OPENTIME==1)&&(KEY_OPENTIME_COUNT!=0)) 
  {   
     
     if(KEY_OPENTIME_COUNT < key_fun)
     {
       //BEEP_ON_SHORT();//�� 
       if(FLAG_PRESS==0)
       {
        FLAG_PRESS= key_press_short;
        if(FLAG_OPENTIME_ZUHE==0)//���뿪��ʱ���ĹغͿ�
       {
        ONOFF_OPEN_ADD();//on off AUTO�л�
         OPEN_TIMER_ONOFF();//���뿪�ؿ�ʼʱ�䶨ʱ��ģʽ
        
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
          BEEP_ON_SHORT();//�� 
       }
       if(FLAG_OPENTIME_ZUHE==1)//����Ԥ��ֵѡ��
       {
        // BACKLIGHT_ON();
        // BEEP_ON_SHORT();//�� 
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       if(FLAG_OPENTIME_ZUHE==2)//��ʼʱ��+30 ������ADD���Ѿ����� ���ظ�����
       {
       // BACKLIGHT_ON();
         //BEEP_ON_SHORT();//�� 
         DATA_CHANGE_ADD30(0);
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       if(FLAG_OPENTIME_ZUHE==3)//��ʼʱ��-30 ������ADD���Ѿ����� ���ظ�����
       {
        // BACKLIGHT_ON();
         //BEEP_ON_SHORT();//�� 
         DATA_CHANGE_DEC30(0);
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       }
     }
     else
     {
    //  BACKLIGHT_ON();
       //BEEP_ON_LONG(); //�� ����LCD
        OPEN_LCD_AND_8563();
        BEEP_ON_LONG(); //�� ����LCD
     }
     KEY_OPENTIME_COUNT = 0;
     //Clear_Key_Function_Count();
     FLAG_OPENTIME_ZUHE = 0;
     FLAG_OPENTIME_LONG = 0;
  }
}




UINT8 FLAG_CLOSETIME_LONG=0;
UINT8 FLAG_CLOSETIME_ZUHE=0;

void SCAN_CLOSETIME(void)
{
   if(PIN_KEY_CLOSETIME==0)
   {
      Delayus(key_Antishake);
      if(PIN_KEY_CLOSETIME==0)
   {
     //TIME_10S();
     key_touch_retime();
    FG_KEY_CLOSETIME=1;
    KEY_CLOSETIME_COUNT++;
     if(PIN_KEY_OPENTIME == 0)
    {
      FLAG_CLOSETIME_ZUHE = 1;
    }
     if(PIN_KEY_ADD == 0)
    {
      FLAG_CLOSETIME_ZUHE = 2;
    }
     if(PIN_KEY_DEC == 0)
    {
      FLAG_CLOSETIME_ZUHE = 3;
    }
     if((FLAG_CLOSETIME_LONG==0)&&(KEY_CLOSETIME_COUNT > key_fun))
     {
       if(FLAG_PRESS == 0)
       {
        FLAG_PRESS = key_press_long; 
       FLAG_CLOSETIME_LONG = 1;
       if(FLAG_CLOSETIME_ZUHE == 0)
       {
          SET_CLOSETIME();
          OPEN_LCD_AND_8563();
           BEEP_ON_LONG(); //�� �����ʱ������
          // BACKLIGHT_ON();
       }
       if(FLAG_CLOSETIME_ZUHE == 1)//����ʱ��Ԥ�� �����Ѿ������� �հ��� �����ظ�����
       {
        // BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_LONG(); //�� �����ʱ������
       }
       }
     }
     key_touch_retime();
    }
  }
  if((PIN_KEY_CLOSETIME==1)&&(FG_KEY_CLOSETIME==1))KEY_COUNT++;
  
   if((PIN_KEY_CLOSETIME==1)&&(FG_KEY_CLOSETIME==1)&&(KEY_CLOSETIME_COUNT!=0)) //�ɿ���1��
  {   
     
     if(KEY_CLOSETIME_COUNT < key_fun)
     {
       //BEEP_ON_SHORT();//��
       if(FLAG_PRESS==0)
       {
         FLAG_PRESS = key_press_short;
           
        if(FLAG_CLOSETIME_ZUHE==0)//����ض�ʱ���ĹغͿ�
       {
         ONOFF_CLOSE_ADD();//on off AUTO�л�
         CLOSE_TIMER_ONOFF();
         
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       if(FLAG_CLOSETIME_ZUHE==1)//����Ԥ��ֵѡ�� ������OPENTIME���Ѿ����� �����ظ�����
       {
         
         //BEEP_ON_SHORT();//�� 
         //BACKLIGHT_ON();
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       if(FLAG_CLOSETIME_ZUHE==2)//��ʼʱ��+30 ������ADD���Ѿ����� ���ظ�����
       {
        
         //BEEP_ON_SHORT();//�� 
         //BACKLIGHT_ON();
         DATA_CHANGE_ADD30(1);
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       if(FLAG_CLOSETIME_ZUHE==3)//��ʼʱ��-30 ������ADD���Ѿ����� ���ظ�����
       {
         
        // BEEP_ON_SHORT();//�� 
         //BACKLIGHT_ON();
         DATA_CHANGE_DEC30(1);
         OPEN_LCD_AND_8563();
         BEEP_ON_SHORT();//�� 
       }
       }
     }
     else
     {
     //BACKLIGHT_ON();
       // BEEP_ON_LONG(); 
       OPEN_LCD_AND_8563();
       BEEP_ON_LONG(); 
     }
     KEY_CLOSETIME_COUNT = 0;
    // Clear_Key_Function_Count();
    FLAG_CLOSETIME_LONG = 0;
    FLAG_CLOSETIME_ZUHE = 0;
  }
}


void power_control(void)
{
  if((FLAG_MODE == NORMAL_mode)||(FLAG_MODE == CONTROL_mode))//ֻ��NORMAL_mode CONTROL_mode����� bunengping
  //CONTROL MODE �����Ǳ߿��ƹ��� 2015 03 06�޸� 
  {
     if(FG_100ms_CYW)
    {
     FG_100ms_CYW = 0;
    if(TB_POWER)
     TB_POWER -- ;
     
     } 
  }
  if((TB_POWER == 0)/*&&(m_KeyOptSetMode==0)&&(FG_PWRON==1)&&(!_GetRegMode())*//*||(BAT_out==2)*/)//�����ѹ�͵�2.2V���� ���߲��ܶ��� Һ��Ҳ����ʾ ���ⲻ�� ����ֻ��ʾ�������
   {
      // POWER_OFF;
      FLAG_POWER = 1;
   }

 
}


/*ɨ�����*/
UINT8 key_scan(void)
{
   // if((PIN_KEY_OPEN==0)||(PIN_KEY_STOP==0)||(PIN_KEY_CLOSE==0))
   //  return 0; 
  
       ClearWDT();
       SCAN_OPEN();
       ClearWDT();
       SCAN_CLOSE();
       ClearWDT();
       SCAN_STOP();
       ClearWDT();
       SCAN_LOGIN();
       ClearWDT();
       
       SCAN_CLOSETIME();
       ClearWDT();
       SCAN_NOWTIME();
       ClearWDT();
       //SCAN_LOGIN();
       ClearWDT();
       SCAN_OPENTIME();
       ClearWDT();
       SCAN_DEC();
       ClearWDT();
       SCAN_ADD();
       ClearWDT();
       SCAN_DECIDE();
        ClearWDT();
        
       
       if(KEY_COUNT >= key_shortdelay)
      {
        // Tone_OFF();
          KEY_COUNT = 0;
          FG_KEY_OPEN_CYW = 0;
          FG_KEY_STOP_CYW = 0;
          FG_KEY_CLOSE_CYW = 0;
          FG_KEY_LOGIN_CYW = 0;
          FG_KEY_DECIDE=0;// 
          FG_KEY_CLOSETIME=0;//
          FG_KEY_NOWTIME=0;//
          FG_KEY_OPENTIME=0;//
          FG_KEY_DEC=0;//
          FG_KEY_ADD=0;
           Clear_Key_Function_Count();
          //if(FLAG_MODE!=CONTROL_mode)
          //TB_POWER = 600;//1min �м�����
      }
      ClearWDT();
      BEEP_OFF();
      
      //if(FLAG_MODE != CONTROL_mode)//�����������Ӱ��CONTROLģʽ�����߹ض�
     // {
      if((TB_5s==0)&&(TB_5S_CYW == 0))//51;  //5.1��  add 2015 04 21  cyw  Ϊ�˱���5S���ָܻ�ʹ��������Һ��������CPU�ϵ���
      {
         TB_5S_CYW=69;//20170725//TB_51s;//51;  //5.1��
      }
     // }
    
  return 0; 
}
#endif
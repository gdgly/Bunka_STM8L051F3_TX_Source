#define INIT_mode  0
#define NORMAL_mode 1
#define CONTROL_mode 2
#define NOWTIMESET_mode 3
#define OPENTIMESET_mode 4
#define CLOSETIMESET_mode 5
#define OPENONOFF_mode 6
#define CLOSEONOFF_mode 7
#define PREINSTALL_mode 8
#define AOTU_mode 9 
#define ADDDEC30_mode 10

#define Timer_Mode_SET 0
#define Timer_Mode_OFF 1 
#define Timer_Mode_AUTO 2

#define Normal_hang_1  4//������ʾ����µ���1
#define Normal_hang_2  53//������ʾ����µ���2
#define Normal_hang_3  101//������ʾ����µ���3
#define lie_1 1//��һ��
#define lie_2 2//�ڶ���
#define lie_3 3//������
#define lie_4 4//������
#define lie_5 5//������
#define lie_6 6//������
#define lie_7 7//������
#define lie_8 8//������
#define nowtimeset_hang_1  4//��������ʱ����1
#define nowtimeset_hang_2  36//��������ʱ����2
#define nowtimeset_hang_3  68//��������ʱ����3
#define nowtimeset_hang_4  108//��������ʱ����3
#define Normal_hang_2_1_0816  69
#define Normal_hang_3_1_0816  117
#define Normal_hang_2_1_0824  61
#define Normal_hang_3_1_0824  109

void menu_linshi(void);
void lcd_init(void); 
void delay(int i);

void menu_normal(void);
void menu_second(void);
void DISP_Refresh(void);
void lcd_backlight(void);
uchar caluate_monthtoreason(uchar x_mon);
void clear_clear(void);
void menu_setnowtime(void);
void dianciqianya_lcd(void);
void display_nowtime(void);
void key_touch_retime(void);
void Power_Low(void);

void lcd_checker(unsigned char data0);
void GrRectFIllBolymin(uchar lucXMin, uchar lucXMax, uchar lucYMin, uchar lucYMax, uchar lbFillColor, uchar lGlowRightmostColumn);
#include<reg51.h>
#define uchar unsigned char
int LED_speed = 500;	   		// �Ƶ��ٶȣ�1�룩
int LED_speed_max = 100;   		// �Ƶ��ٶȵ����ֵ��0.2�룩
int LED_speed_min = 1000;  		// �Ƶ��ٶȵ���Сֵ��2�룩
int LED_speed_change = 100;		// �Ƶ��ٶȵĸñ��� ��0.2�룩
int LED_cycle = 5000;	   		// �Ƶ����ڣ�5�룩
int LED_cycle_max = 10000; 		// �Ƶ��������ֵ��20�룩
int LED_cycle_min = 1000;  		// �Ƶ�������Сֵ��2�룩
int LED_cycle_change = 1000;    // �Ƶ����ڵĸñ�����2�룩
int LED_direction = 0;	   		// �Ƶ��ƶ�����
int	LED_number = 0; 	   		// �����ĸ�����0��һ���ƣ�
int LED_which_lighting = 7;		// ������λ��
int time=0;				   		// �жϼ�ʱ��λ
int key1_down=0,key2_down=0,key3_down=0,key4_down=0,key5_down=0;    // �����Ƿ���
int all_lighting_condition[3][8]={
									{0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80},
									{0x03,0x06,0x0C,0x18,0x30,0x60,0xC0,0x81},
									{0x07,0x0E,0x1C,0x38,0x70,0xE0,0xC1,0x83}
								 };                                 //���е��������
void delay(unsigned int x)	//��ʱ������ֻ���ڰ�����
{
	while(x--);
}
void LED_move(void);
#include<key_scan.c>
void timer0_init(void)	    //��ʼ��
{
	TMOD = 0x01;			//��ʱ��T0�����ڷ�ʽ1,��������Ϊ16λ��
	TH0 = 0xf8;             //��ֵ(65536 - 2000)/ 256;		 2e16	 TH0Ԥ�ã�63536ʮ�����Ƶ�8λ
	TL0 = 0x30;             //��ֵ(65536 - 2000)% 256;			   TL0Ԥ�ã�63536ʮ�����Ƹ�8λ
	EA = 1;					//���ö�ʱ���жϣ�ֱ�Ӷ�IEλ��ֵ	���ж��ܿ��أ�  
	ET0 = 1;			    //����T0�ж�	�������ж�����Ĵ���IE��ET0��λ�������ж�С���أ�
	TR0 = 1;			    //����������ʼ������
}
void timer0_isr(void) interrupt 1	//interrupt 1 ��ʱ���ж�
{

	TH0 = 0xf8;           //(65536 - 2000)/ 256;   ÿ2ms����һ���ж� TH0����Ԥ��
	TL0 = 0x30;           //(65536 - 2000)% 256;						TL0����Ԥ��
	time++;			   	  //ÿ�ж�һ�μ�һ��
	if(time%LED_speed==0) LED_move();		                //���ƶ�һ��
	if(time%LED_cycle==0) LED_direction = ~ LED_direction;	//�ƶ�����ı�
}
void main(void)
{
	timer0_init();	      //�жϳ�ʼ��
	P0 = all_lighting_condition[LED_number][LED_which_lighting]; //��ʼ���������һյ��
	while(1) key_scan();		  //һֱִ�м���ɨ��
}
void LED_move(void)
{
   if(LED_direction)	  //�������
	{
		LED_which_lighting++;	 
		if(LED_which_lighting == 8)	 LED_which_lighting=0;
	} else
	{
		LED_which_lighting--;
	    if(LED_which_lighting == -1) LED_which_lighting=7;
	}
	P0 = all_lighting_condition[LED_number][LED_which_lighting];
}
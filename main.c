#include<reg51.h>
#define uchar unsigned char
int LED_speed = 500;	   		// 灯的速度（1秒）
int LED_speed_max = 100;   		// 灯的速度的最大值（0.2秒）
int LED_speed_min = 1000;  		// 灯的速度的最小值（2秒）
int LED_speed_change = 100;		// 灯的速度的该变量 （0.2秒）
int LED_cycle = 5000;	   		// 灯的周期（5秒）
int LED_cycle_max = 10000; 		// 灯的周期最大值（20秒）
int LED_cycle_min = 1000;  		// 灯的周期最小值（2秒）
int LED_cycle_change = 1000;    // 灯的周期的该变量（2秒）
int LED_direction = 0;	   		// 灯的移动方向
int	LED_number = 0; 	   		// 灯亮的个数（0是一个灯）
int LED_which_lighting = 7;		// 灯亮的位置
int time=0;				   		// 中断计时单位
int key1_down=0,key2_down=0,key3_down=0,key4_down=0,key5_down=0;    // 按键是否按下
int all_lighting_condition[3][8]={
									{0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80},
									{0x03,0x06,0x0C,0x18,0x30,0x60,0xC0,0x81},
									{0x07,0x0E,0x1C,0x38,0x70,0xE0,0xC1,0x83}
								 };                                 //所有的亮灯情况
void delay(unsigned int x)	//延时函数，只用在按键处
{
	while(x--);
}
void LED_move(void);
#include<key_scan.c>
void timer0_init(void)	    //初始化
{
	TMOD = 0x01;			//定时器T0工作在方式1,（计数器为16位）
	TH0 = 0xf8;             //初值(65536 - 2000)/ 256;		 2e16	 TH0预置，63536十六进制低8位
	TL0 = 0x30;             //初值(65536 - 2000)% 256;			   TL0预置，63536十六进制高8位
	EA = 1;					//启用定时器中断，直接对IE位赋值	（中断总开关）  
	ET0 = 1;			    //允许T0中断	（设置中断允许寄存器IE中ET0的位，开启中断小开关）
	TR0 = 1;			    //软启动（开始计数）
}
void timer0_isr(void) interrupt 1	//interrupt 1 定时器中断
{

	TH0 = 0xf8;           //(65536 - 2000)/ 256;   每2ms发生一次中断 TH0重新预置
	TL0 = 0x30;           //(65536 - 2000)% 256;						TL0重新预置
	time++;			   	  //每中断一次计一次
	if(time%LED_speed==0) LED_move();		                //灯移动一次
	if(time%LED_cycle==0) LED_direction = ~ LED_direction;	//移动方向改变
}
void main(void)
{
	timer0_init();	      //中断初始化
	P0 = all_lighting_condition[LED_number][LED_which_lighting]; //初始在最左边亮一盏灯
	while(1) key_scan();		  //一直执行键盘扫描
}
void LED_move(void)
{
   if(LED_direction)	  //如果向左
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
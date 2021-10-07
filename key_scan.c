/*
按键扫描原理，P2后四个引脚确定行，前四个引脚确定列。每个按键由唯一的两个引脚确定。
*/
code P2_scan[] = {0x7F,0xBF,0xDF,0xEF};	         //P2默认值
code key_temp_value[] = {0xEE,0xED,0xEB,0xE7,0xDE,0xDD,0xDB,0xD7,
			0xBE,0xBD,0xBB,0xB7,0x7E,0x7D,0x7B,0x77};		 //16个按键对应的P2值
void key_scan(void)
{
	uchar i;
	for(i=0;i<4;i++)
	{
		P2 = P2_scan[i];
		if(P2!=P2_scan[i])	            
		{
			 delay(200);
			 if(P2!=P2_scan[i])					  //如果按下按键
			 {
			 	while(P2!=P2_scan[i])		 	  //当一直按着按键的时候
				{			 
				 if(P2 == key_temp_value[0])     	key1_down = 1;		
				 else if(P2 == key_temp_value[1])	key2_down = 1;	
				 else if(P2 == key_temp_value[2])	key3_down = 1;	
				 else if(P2 == key_temp_value[3])	key4_down = 1;	
				 else if(P2 == key_temp_value[4])	key5_down = 1;				 
				}
			 	 
			 }
		}
	}
	 if(key1_down == 1)		  // cycle_down 缩短周期
	 {
	  	key1_down = 0;
	  	if(LED_cycle > LED_cycle_min)LED_cycle -=LED_cycle_change; 
     }
	 if(key2_down == 1)		  // cycle_up  延长周期
	 {
	  	key2_down = 0;
	  	if(LED_cycle < LED_cycle_max)LED_cycle +=LED_cycle_change; 
	 }
	 if(key3_down == 1)		  // speed_up 增加速度
	 {
	  	key3_down = 0;
	  	if(LED_speed>LED_speed_max) LED_speed-=LED_speed_change;
	 }
	 if(key4_down == 1)		  // speed_down 减缓速度
	 {
	  	key4_down = 0;
		if(LED_speed<LED_speed_min) LED_speed+=LED_speed_change;
	 }
	 if(key5_down == 1)		  // LED_number 更改灯的个数
	 {
	  	key5_down = 0;
	  	LED_number++;
		if(LED_number==3)LED_number=0;
	 }
}
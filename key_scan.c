/*
����ɨ��ԭ��P2���ĸ�����ȷ���У�ǰ�ĸ�����ȷ���С�ÿ��������Ψһ����������ȷ����
*/
code P2_scan[] = {0x7F,0xBF,0xDF,0xEF};	         //P2Ĭ��ֵ
code key_temp_value[] = {0xEE,0xED,0xEB,0xE7,0xDE,0xDD,0xDB,0xD7,
			0xBE,0xBD,0xBB,0xB7,0x7E,0x7D,0x7B,0x77};		 //16��������Ӧ��P2ֵ
void key_scan(void)
{
	uchar i;
	for(i=0;i<4;i++)
	{
		P2 = P2_scan[i];
		if(P2!=P2_scan[i])	            
		{
			 delay(200);
			 if(P2!=P2_scan[i])					  //������°���
			 {
			 	while(P2!=P2_scan[i])		 	  //��һֱ���Ű�����ʱ��
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
	 if(key1_down == 1)		  // cycle_down ��������
	 {
	  	key1_down = 0;
	  	if(LED_cycle > LED_cycle_min)LED_cycle -=LED_cycle_change; 
     }
	 if(key2_down == 1)		  // cycle_up  �ӳ�����
	 {
	  	key2_down = 0;
	  	if(LED_cycle < LED_cycle_max)LED_cycle +=LED_cycle_change; 
	 }
	 if(key3_down == 1)		  // speed_up �����ٶ�
	 {
	  	key3_down = 0;
	  	if(LED_speed>LED_speed_max) LED_speed-=LED_speed_change;
	 }
	 if(key4_down == 1)		  // speed_down �����ٶ�
	 {
	  	key4_down = 0;
		if(LED_speed<LED_speed_min) LED_speed+=LED_speed_change;
	 }
	 if(key5_down == 1)		  // LED_number ���ĵƵĸ���
	 {
	  	key5_down = 0;
	  	LED_number++;
		if(LED_number==3)LED_number=0;
	 }
}
void key(void)
{
			 if(key1 ==0)
	   		 {
	   		  	 key1 = 1;
				 delay(200);
			     if(key1 == 0)key1_down = 1;
	   		 }
			 if(key1 == 1 && key1_down == 1)
			 {
	  			key1_down = 0;
	  		    if(LED_cycle > LED_cycle_min)LED_cycle -=LED_cycle_change; 
			 }
			 if(key2 ==0)
			 {
			 	 key2 = 1;
				 delay(200);
			     if(key2 == 0)key2_down = 1;
			 }
			 if(key2 == 1 && key2_down == 1)
			 {
	  			key2_down = 0;
	  			 if(LED_cycle < LED_cycle_max)LED_cycle +=LED_cycle_change; 
			 }
			 if(key3 ==0)
			 {
			 	 key3 = 1;
				 delay(200);
			     if(key3 == 0)key3_down = 1;
			 }
			 if(key3 == 1 && key3_down == 1)
			 {
	  			key3_down = 0;
	  			if(LED_speed>LED_speed_max) LED_speed-=LED_speed_change;
			 }
			  if(key4 ==0)
			 {
			 	 key4 = 1;
				 delay(200);
			     if(key4 == 0)key4_down = 1;
			 }
			 if(key4 == 1 && key4_down == 1)
			 {
	  			key4_down = 0;
				if(LED_speed<LED_speed_min) LED_speed+=LED_speed_change;
			 }
			  if(key5 ==0)
			 {
			 	 key5 = 1;
				 delay(200);
			     if(key5 == 0)key5_down = 1;
			 }
			 if(key5 == 1 && key5_down == 1)
			 {
	  			key5_down = 0;
	  			LED_number++;
				if(LED_number==3)LED_number=0;
			 }
}
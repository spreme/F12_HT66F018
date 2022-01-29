void SendData(unsigned char cmd)
{ 
	int i; 
	sda = 0; 
	Delay100us(10); 
	sda = 1; 
	Delay100us(90); 
	sda = 0; 
	Delay100us(45); 
	for(i = 0; i < 8 ;i++) 
	{ 
		if(cmd & 0x80) 
		{ 
			sda = 1; 
			Delay100us(12);//12 
			sda = 0; 
			Delay100us(4);//4 
		}
		else 
		{ 
			sda = 1; 
			Delay100us(4); 
			sda = 0; 
			Delay100us(12); 
		}
		cmd <<= 1; 
	}
	sda = 0; 
}
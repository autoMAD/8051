#include<STRING.H>

unsigned char ch[15],i;

void serial(void) interrupt 4
{
	if(RI)
	{
		ch[i]=SBUF;
		i++;
	}
	RI=0;
}

char rfidread()
{
	uart_init();

	EA=1;
	ES=1;

	i=0;
	while(i==0);
	delay(1000);
	i=i-2;
	ch[i]='\0';
	delay(100);
	lcd_string(ch);
	delay(1000);

	return (ch);
}

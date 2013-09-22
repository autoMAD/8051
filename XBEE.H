void xbee_init(void);
void xbee_data(unsigned char);
void xbee_string(unsigned char[]);
char xbee_rec(void);
void xbee_delay(unsigned int);

void xbee_init(void)
{
	TMOD=0x20;
	SCON=0x50;
	TH1=0xFD;
	TR1=1;
}

void xbee_data(unsigned char mad)
{
	SBUF=mad;
	while(TI==0);
	TI=0;
}

void xbee_string(unsigned char mad[])
{
	unsigned int i;

	for(i=0;mad[i]!='\0';i++)
		xbee_data(mad[i]);
}

char xbee_rec(void)
{
	unsigned char dat;
	
	while(RI==0);
	dat=SBUF;
	RI=0;

	return(dat);
}

void xbee_delay(unsigned int mad)
{
	unsigned int i,j;

	for(i=0;i<mad;i++)
		for(j=0;j<100;j++);
}

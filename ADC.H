
#define adc_data P3

sbit ALE	=P2^0;
sbit SC		=P2^1;
sbit EOC	=P2^2;
sbit OE		=P2^3;
sbit A0		=P2^4;
sbit A1		=P2^5;
sbit A2		=P2^6;

unsigned char out;

void adcinit(void);
void adcdelay(unsigned int);
char adcread(unsigned int, unsigned int, unsigned int);

void adcinit(void)
{
	adc_data=0xff;
	ALE=0;
	SC=0;
	EOC=1;
	OE=0;
}

char adcread(unsigned int a, unsigned int b, unsigned int c)
{
	A0=a;
	A1=b;
	A2=c;

	ALE=1;
	adcdelay(10);
	SC=1;
	adcdelay(10);
	ALE=0;
	SC=0;
	while(EOC==1);
	OE=1;
	delay(150);
	out=adc_data;
	OE=0;

	return (out);
}

void adcdelay(unsigned int mad)
{
	unsigned int i;

	for(i=0;i<mad;i++)
		_nop_();
}

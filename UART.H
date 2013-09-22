// Function Declarations

void uart_init(void);
void uart_data(unsigned char);
void uart_string(unsigned char []);
void uart_num(unsigned int);
void uart_enter(void);
void uart_delay(unsigned int);
unsigned char uart_rx();

// Function Intializations

// UART_INIT();
void uart_init()
{
	TMOD=0x20;
	SCON=0x50;
	TH1=0xFD;
	TR1=1;
}

// UART_DATA();
void uart_data(unsigned char mad)
{
	SBUF=mad;
	while(TI==0);
	TI=0;
}

// UART_STRING();
void uart_string(unsigned char mad[])
{
	unsigned int j;

	for(j=0;mad[j]!='\0';j++)
		uart_data(mad[j]);
}

// UART_ENTER();
void uart_enter()
{
	uart_data(13);
	uart_delay(10);
	uart_data(10);
}

// UART_DELAY();
void uart_delay(unsigned int mad)
{
	unsigned int i,j;
   	for(i=0;i<mad;i++)
    	for(j=0;j<100;j++);
}

// UART_RX();
unsigned char uart_rx()
{

 unsigned char ch;
 while(RI==0);
 ch=SBUF;
 return (ch);
}

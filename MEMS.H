// Port Declarations
sbit SCL=P3^6;		   
sbit SDA=P3^7;

char memsdata;

// Function Declarations
char mems_start(void);
void mems_init(void);
void mems_stop(void);
void start(void);
void write_eeprom(unsigned char,unsigned char);
unsigned char read_eeprom(unsigned char);
void send_to_eeprom(unsigned char );
void stop(void);
void i2cdelay(unsigned int );

// MEMS_START();
char mems_start(void)
{
	memsdata=read_eeprom(3)&0x3f;

	return (memsdata);
}

// MEMS_INIT();
void mems_init(void)
{
	write_eeprom(7,0x00);
    delay(500);
    write_eeprom(7,0x01);
    delay(500);
    write_eeprom(8,0x3F);
    delay(500);
}

// MEMS_STOP();
void mems_stop(void)
{
	write_eeprom(7,0x00);
  delay(200);

  write_eeprom(7,0x01);
  delay(200);
}

// WRITE_EEPROM();
void write_eeprom(unsigned char add,unsigned char dat)
{
	start();
  send_to_eeprom(0X98); //device addr in write mode//
  send_to_eeprom(add); //byte addr//
  send_to_eeprom(dat); //data//
  stop();
}

//%%%%%%%%%%%%%%%%%%%%  READING FUNCTION    %%%%%%%%%%%%%%%%%%%%%%%%%

unsigned char read_eeprom(unsigned char add)
{
	unsigned char v,i;  
	start();
	send_to_eeprom(0X98); //device addr in write mode//
	send_to_eeprom(add); //byte addr//
	_nop_();
	start();
	send_to_eeprom(0X99); //device addr in read mode//
	v=0;
  SDA=1;
  for(i=0;i<=7;i++)
  {
  	SCL=0;
    _nop_();
    _nop_();
    SCL=1;
    v=v|SDA;
    if(i<=6)
      v=v<<1;
  }
  SCL=0;
 	i2cdelay(100); 
 	stop();
	return(v);
}

//$$$$$$$$$$$$$$$$$$$$$$$$$  START FUNCTION $$$$$$$$$$$$$$$$$$$$$$$
		     				   
void start(void)
{
	SCL=1;
	SDA=1;
	_nop_();
	_nop_();
	SDA=0;
	SCL=0;
}

//aaaaaaaaaaaaaaaaaaaaaaaaa   DATA SENDING TO EEPRAM IN READ MODE AAAAAAAAAAAAAAAAAA

void send_to_eeprom(unsigned char a)
{
	unsigned char i,c;
	for(i=0;i<=7;i++)
	{
		c=a&128;
		if(c==0)
			SDA=0;
		else
			SDA=1;

		SCL=1;
		_nop_();
		_nop_();
		SCL=0;
        a=a<<1;
	}	
	
	SDA=1;
	_nop_();
	_nop_();
	SCL=1;
	_nop_();
	_nop_();
	SCL=0;
}

//SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS  STOP FUNCTION  SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
void stop(void)
{
	SDA=0;
	SCL=1;
	_nop_();
	_nop_();
	SDA=1;
	SCL=0;
}

// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV     DELAY FUNCTION   VVVVVVVVVVVVVVVVVVVVVVVVVVVVV
void i2cdelay(unsigned int s)
{
	unsigned int i,j;
	for(i=0;i<=s;i++)
		for(j=0;j<=250;j++);
}

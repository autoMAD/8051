// Library Functions

void lcd_init();
void lcd_data(unsigned char);
void lcd_string(unsigned char[]);
void lcd_cmd(unsigned char);
void lcd_num(unsigned int);

// Port Declarations
#define lcd P1

sbit rs=P1^2;
sbit en=P1^3;

// Function Declarations

// LCD_INIT(); 
void lcd_init(void)
{
	lcd_cmd(0x02);
 	lcd_cmd(0x28);
 	lcd_cmd(0x0e);
 	lcd_cmd(0x06);
 	lcd_cmd(0x01);
	lcd_cmd(0x0c);
}

// LCD_CMD();
void lcd_cmd(unsigned char mad)
{
  lcd=(mad)&(0xf0);
	rs=0;
	en=1;
	delay(3);
	en=0;

	lcd=(mad<<4)&(0xf0);
	rs=0;
	en=1;
	delay(3);
	en=0;
}

//LCD_DATA();
void lcd_data(unsigned char mad)
{
  lcd=(mad)&(0xf0);
	rs=1;
	en=1;
	delay(3);
	en=0;

	lcd=(mad<<4)&(0xf0);
	rs=1;
	en=1;
	delay(3);
	en=0;
}

//LCD_STRING();
void lcd_string(unsigned char s[])
{
   unsigned int i;
   for(i=0;s[i]!='\0';i++)
   {
	  if(i==16)    
		  lcd_cmd(0xc0);

	 lcd_data(s[i]);
	}

}

//LCD_NUM();
void lcd_num(unsigned int lcd_value)
{
 unsigned int lcd_arr[10],lcd_val;
 
 for(lcd_val=1;lcd_val<5;lcd_val++)
 {
  lcd_arr[lcd_val] = lcd_value%10;
  lcd_value  = lcd_value/10;
 }
 
 for(lcd_val=4; lcd_val!=0 ; lcd_val--)					//sending data to LCD
 {
  lcd_data(lcd_arr[lcd_val]+48);
 }
}

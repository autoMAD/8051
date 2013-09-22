unsigned char xx,msg[15],mobilenum[10];
unsigned char newmsg=0;

void gsm_init(void);
void gsm_readmsg(void);
void gsm_sendmsg(unsigned char mad[]);
void gsm_sendmsg_mob(unsigned char[],unsigned char[]);

void serial(void) interrupt 4
{
	if(RI==1)
	{
		xx=SBUF;
		if(xx=='+')
			newmsg=1;
		RI=0;
	}
}

void gsm_init(void)
{
	lcd_string("WELCOME");
	delay(1000);
	lcd_cmd(0x01);
	lcd_string("Searching for");
	lcd_cmd(0xc0);
	lcd_string("GSM Modem");
	delay(300);
	uart_string("ate0");
	uart_enter();

	again:	
		uart_string("at");
		uart_enter();
		if(!RI)
			goto again;

		RI=0;

		EA=1;
		ES=1;
		lcd_cmd(0x01);
		lcd_string("SYSTEM");
		lcd_cmd(0xc0);
		lcd_string("CONNECTED");
		delay(100);
		uart_string("at+creg=0");
		uart_enter();
		delay(300);
		newmsg=0;

	xxx:
		lcd_cmd(0x01);
		lcd_string("CHECKING SIM");
		uart_string("at+cpin?");
		uart_enter();
		delay(500);
		if(newmsg==0)
			goto xxx;

		lcd_cmd(0xc0);
		lcd_string("SIM CONNECTED");
		delay(500);

		uart_string("at+cmgf=1");
		uart_enter();

		uart_string("at+cmgd=1");
		uart_enter();

		uart_string("at+cmgd=2");
		uart_enter();
		
		uart_string("at+cmgd=3");
		uart_enter();

		delay(500);

		lcd_cmd(1);
		lcd_string("SYSTEM READY");
		delay(1000);

		/*newmsg=0;
		while(newmsg==0);
		ES=0;
		gsm_readmsg();
		delay(1500);*/
}

void gsm_readmsg(void)         
{
 unsigned char a,b,i,count,numcnt;
  delay(100);
 ES=1;
 delay(300);
 ES=0;
  
 while(RI==1)
  {
    RI=0;
    delay(100);
   }
 
 lcd_cmd(0x01); 
 uart_string("at+cmgr=1");
 uart_enter();
 
 count=0;
 i=0;
 a=0;
 numcnt=0;

 while(count!=3)
  {
     while(RI==0);
     b=SBUF;
    
	 
	 if((b==',')||(a==1))
      {
        if(numcnt<15)
 	    {
 	     if(numcnt>4)
	      {
     	   mobilenum[numcnt-5]=b;
	       }
    	  a=1;
	      numcnt++;
		}
		 else
		    a=0;
	    }
		if(count==2)
		 {
		  msg[i++]=SBUF;
  	   	 
		 }
	    
		RI=0;
		if(b==10)
		 count+=1;
	}
		      
			  msg[--i]='\0';
		      msg[--i]='\0';
		      mobilenum[10]='\0';
		     uart_string("at+cmgd=1");
            uart_enter();
		  	 	 
 }

void gsm_sendmsg(unsigned char mad[])
{
		lcd_cmd(0x01);
		lcd_string("sending message");

		uart_string("at+cmgs=");
		uart_data('"');
		uart_string(mobilenum);
		uart_data('"');
		uart_enter();
		uart_string(mad);
		delay(100);
		uart_data(0x1a);
		newmsg=0;
		while(newmsg==0);
		newmsg=0;
		delay(1500);
		lcd_cmd(0x01);
		lcd_string("message sent");
		delay(1500);
}

void gsm_sendmsg_mob(unsigned char mob[], unsigned char msg1[])
{
		lcd_cmd(0x01);
		lcd_string("sending message");

		uart_string("at+cmgs=");
		uart_data('"');
		uart_string(mob);
		uart_data('"');
		uart_enter();
		uart_string(msg1);
		delay(100);
		uart_data(0x1a);
		newmsg=0;
		while(newmsg==0);
		newmsg=0;
		delay(1500);
		lcd_cmd(0x01);
		lcd_string("message sent");
		delay(1500);
}

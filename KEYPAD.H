// Keypad Function Declaration

unsigned char keypad();

/****** keypad connections********/
sbit row0=P2^0;
sbit row1=P2^1;
sbit row2=P2^2;
sbit row3=P2^3;
sbit col0=P2^4;
sbit col1=P2^5;
sbit col2=P2^6;

unsigned char key[4][3]    =     {'1','2','3',  // KEYPAD MATRIX INITILIZATION
                                  '4','5','6',
	                              '7','8','9',
	                              '*','0','#'};


// KEYPAD();
unsigned char keypad()
{
 unsigned char K,c0,c1,c2,r; 

 while(1)
 {
  row0=0x00;
  row1=0x00;
  row2=0x00;
  row3=0x00;
  col0=0x01;
  col1=0x01;
  col2=0x01;														     			
  do
  {	
   c0=col0;
   c1=col1;
   c2=col2;
  }while((c0!=0x01)||(c1!=0x01)||(c2!=0x01));   // To check all keys are relesead or not
  
  
  do
  {
   c0=col0;
   c1=col1;
   c2=col2;
  }while((c0==0x01)&&(c1==0x1)&&(c2==0x01));   // To check any key is pressed or not
  
  while(1)
  {
   row0=0x00;	  // If row0 is pressed
   row1=0x01;
   row2=0x01;
   row3=0x01;
   c0=col0;
   c1=col1;
   c2=col2;
  
  if((c0!=1)||(c1!=1)||(c2!=1))
  {
   r=0;
   break;
  }
	
  row0=1;	  // If row1 is pressed
  row1=0;
  row2=1;
  row3=1;
  c0=col0;
  c1=col1;
  c2=col2;
  
  if((c0!=1)||(c1!=1)||(c2!=1))
  {
   r=1;
   break;
  }
		
  row0=1;	  // If row2 is pressed
  row1=1;
  row2=0;
  row3=1;
  c0=col0;
  c1=col1;
  c2=col2;
  
  if((c0!=0x01)||(c1!=0x01)||(c2!=0x01))
  {
   r=2;
   break;
  }

  row0=1;	  // If row3 is pressed
  row1=1;
  row2=1;
  row3=0;
  c0=col0;
  c1=col1;
  c2=col2;
  
  if((c0!=1)||(c1!=1)||(c2!=1))
  {
   r=3;
   break;
  }
 }

 if((c0==0)&&(c1==1)&&(c2==1))
 {
  K=key[r][0];
  return K;
 }
 else
 if((c0==1)&&(c1==0)&&(c2==1))
 {
  K=key[r][1];
  return K;
 } 

  else
  {
  	K=key[r][2];
	return K;
  }
 }
}

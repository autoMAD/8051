// Function Declarations
void forward();
void back();
void left();
void right();
void stop();

// Port Declarations
#define L293D P2

// FORWARD();
void forward()
{
 L293D=0xD7;
}

//BACK();
void back()
{
 L293D=0xEB;
}

//LEFT();
void left()
{
 L293D=0xDE;
}

//RIGHT();
void right()
{
 L293D=0xF5;
}

//STOP();
void stop()
{
 L293D=0x00;
}

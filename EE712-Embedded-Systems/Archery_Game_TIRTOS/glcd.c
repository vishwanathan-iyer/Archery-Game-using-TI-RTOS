
#include "common.h"
#include "glcd.h"
#include "buzzer.h"

//---------------------------------------
// Globals
//---------------------------------------
unsigned int position=1;
unsigned char bow_width=4;
unsigned char Bx=0,By=0;
unsigned char Ax=5, Ay=7;
unsigned char Tx=0,Ty=0;
unsigned char Tym=0,Aym=0;

unsigned char last_xB=0, last_yB=0;
unsigned char last_xA=0, last_yA=0;
unsigned char last_xT=0, last_yT=0;

unsigned char upDownBarTarget=0;
unsigned char targetIncrCount=1;

extern uint32_t LEFT_RIGHT;
extern uint32_t UP_DOWN;
extern unsigned char shooting;
unsigned char startNotLatched=1;
unsigned char currAx;
unsigned int score=0;
unsigned int scoreArray[]={50,50,50,100,100,100,200,200,250,300,300,250,200,200,100,100,50,50,50};
unsigned char arrow=6;
unsigned char missed[]="  Missed  ";
unsigned char bullsEye[]=" Bull's Eye";
unsigned char twoFifty[]="  250  ";
unsigned char twoHundered[]="  200  ";
unsigned char hundered[]="  100  ";
unsigned char fifty[]="  50  ";

unsigned char Character5x8[]= {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00,// (space)
0x00, 0x00, 0x5F, 0x00, 0x00, 0x00,// !
0x00, 0x07, 0x00, 0x07, 0x00, 0x00,// "
0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00,// #
0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00,// $
0x23, 0x13, 0x08, 0x64, 0x62, 0x00,// %
0x36, 0x49, 0x55, 0x22, 0x50, 0x00,// &
0x00, 0x05, 0x03, 0x00, 0x00, 0x00,// '
0x00, 0x1C, 0x22, 0x41, 0x00, 0x00,// (
0x00, 0x41, 0x22, 0x1C, 0x00, 0x00,// )
0x08, 0x2A, 0x1C, 0x2A, 0x08, 0x00,// *
0x08, 0x08, 0x3E, 0x08, 0x08, 0x00,// +
0x00, 0x50, 0x30, 0x00, 0x00, 0x00,// ,
0x08, 0x08, 0x08, 0x08, 0x08, 0x00,// -
0x00, 0x30, 0x30, 0x00, 0x00, 0x00,// .
0x20, 0x10, 0x08, 0x04, 0x02, 0x00,// /
0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00,// 0
0x00, 0x42, 0x7F, 0x40, 0x00, 0x00,// 1
0x42, 0x61, 0x51, 0x49, 0x46, 0x00,// 2
0x21, 0x41, 0x45, 0x4B, 0x31, 0x00,// 3
0x18, 0x14, 0x12, 0x7F, 0x10, 0x00,// 4
0x27, 0x45, 0x45, 0x45, 0x39, 0x00,// 5
0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00,// 6
0x01, 0x71, 0x09, 0x05, 0x03, 0x00,// 7
0x36, 0x49, 0x49, 0x49, 0x36, 0x00,// 8
0x06, 0x49, 0x49, 0x29, 0x1E, 0x00,// 9
0x00, 0x36, 0x36, 0x00, 0x00, 0x00,// :
0x00, 0x56, 0x36, 0x00, 0x00, 0x00,// ;
0x00, 0x08, 0x14, 0x22, 0x41, 0x00,// <
0x14, 0x14, 0x14, 0x14, 0x14, 0x00,// =
0x41, 0x22, 0x14, 0x08, 0x00, 0x00,// >
0x02, 0x01, 0x51, 0x09, 0x06, 0x00,// ?
0x32, 0x49, 0x79, 0x41, 0x3E, 0x00,// @
0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00,// A
0x7F, 0x49, 0x49, 0x49, 0x36, 0x00,// B
0x3E, 0x41, 0x41, 0x41, 0x22, 0x00,// C
0x7F, 0x41, 0x41, 0x22, 0x1C, 0x00,// D
0x7F, 0x49, 0x49, 0x49, 0x41, 0x00,// E
0x7F, 0x09, 0x09, 0x01, 0x01, 0x00,// F
0x3E, 0x41, 0x41, 0x51, 0x32, 0x00,// G
0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00,// H
0x00, 0x41, 0x7F, 0x41, 0x00, 0x00,// I
0x20, 0x40, 0x41, 0x3F, 0x01, 0x00,// J
0x7F, 0x08, 0x14, 0x22, 0x41, 0x00,// K
0x7F, 0x40, 0x40, 0x40, 0x40, 0x00,// L
0x7F, 0x02, 0x04, 0x02, 0x7F, 0x00,// M
0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00,// N
0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00,// O
0x7F, 0x09, 0x09, 0x09, 0x06, 0x00,// P
0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00,// Q
0x7F, 0x09, 0x19, 0x29, 0x46, 0x00,// R
0x46, 0x49, 0x49, 0x49, 0x31, 0x00,// S
0x01, 0x01, 0x7F, 0x01, 0x01, 0x00,// T
0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00,// U
0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00,// V
0x7F, 0x20, 0x18, 0x20, 0x7F, 0x00,// W
0x63, 0x14, 0x08, 0x14, 0x63, 0x00,// X
0x03, 0x04, 0x78, 0x04, 0x03, 0x00,// Y
0x61, 0x51, 0x49, 0x45, 0x43, 0x00,// Z
0x00, 0x00, 0x7F, 0x41, 0x41, 0x00,// [
0x02, 0x04, 0x08, 0x10, 0x20, 0x00,// "\"
0x41, 0x41, 0x7F, 0x00, 0x00, 0x00,// ]
0x04, 0x02, 0x01, 0x02, 0x04, 0x00,// ^
0x40, 0x40, 0x40, 0x40, 0x40, 0x00,// _
0x00, 0x01, 0x02, 0x04, 0x00, 0x00,// `
0x20, 0x54, 0x54, 0x54, 0x78, 0x00,// a
0x7F, 0x48, 0x44, 0x44, 0x38, 0x00,// b
0x38, 0x44, 0x44, 0x44, 0x20, 0x00,// c
0x38, 0x44, 0x44, 0x48, 0x7F, 0x00,// d
0x38, 0x54, 0x54, 0x54, 0x18, 0x00,// e
0x08, 0x7E, 0x09, 0x01, 0x02, 0x00,// f
0x08, 0x14, 0x54, 0x54, 0x3C, 0x00,// g
0x7F, 0x08, 0x04, 0x04, 0x78, 0x00,// h
0x00, 0x44, 0x7D, 0x40, 0x00, 0x00,// i
0x20, 0x40, 0x44, 0x3D, 0x00, 0x00,// j
0x00, 0x7F, 0x10, 0x28, 0x44, 0x00,// k
0x00, 0x41, 0x7F, 0x40, 0x00, 0x00,// l
0x7C, 0x04, 0x18, 0x04, 0x78, 0x00,// m
0x7C, 0x08, 0x04, 0x04, 0x78, 0x00,// n
0x38, 0x44, 0x44, 0x44, 0x38, 0x00,// o
0x7C, 0x14, 0x14, 0x14, 0x08, 0x00,// p
0x08, 0x14, 0x14, 0x18, 0x7C, 0x00,// q
0x7C, 0x08, 0x04, 0x04, 0x08, 0x00,// r
0x48, 0x54, 0x54, 0x54, 0x20, 0x00,// s
0x04, 0x3F, 0x44, 0x40, 0x20, 0x00,// t
0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00,// u
0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00,// v
0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00,// w
0x44, 0x28, 0x10, 0x28, 0x44, 0x00,// x
0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00,// y
0x44, 0x64, 0x54, 0x4C, 0x44, 0x00,// z
0x00, 0x08, 0x36, 0x41, 0x00, 0x00,// {
0x00, 0x00, 0x7F, 0x00, 0x00, 0x00,// |
0x00, 0x41, 0x36, 0x08, 0x00, 0x00,// }
0x08, 0x08, 0x2A, 0x1C, 0x08, 0x00,// ->
0x08, 0x1C, 0x2A, 0x08, 0x08,  0x00,// <-
};

void GLCD_Write_Ver(unsigned char x, unsigned char y, unsigned int value, int digits)
	{
	unsigned char flag=0;


	GLCD_GoTo(x,y);

		if(digits==5 || flag==1)
		{
			lcd_wr_char((value/10000)+48,x,y);
			flag=1;
		}
		if(digits==4 || flag==1)
		{
			lcd_wr_char(((value/1000)%10)+48,x,y);
			flag=1;
		}
		if(digits==3 || flag==1)
		{
			lcd_wr_char(((value/100)%10)+48,x,y);
			flag=1;
		}
		if(digits==2 || flag==1)
		{
			lcd_wr_char(((value/10)%10+48),x,y);
			flag=1;
		}
		if(digits==1 || flag==1)
		{
			lcd_wr_char((value%10)+48,x,y);
		}
		if(digits>5)
		{
			GLCD_WriteString(x, y,"OUT Rng", FONT5,BLACK);
		}
	}


void lcd_wr_char(unsigned char a,unsigned char x, unsigned char y)
	{
			unsigned char i=0;
			unsigned char side;
				a-=32;
			  a*=6;
			  for(i=0;i<FONT_WIDTH5;i++)
			  		{
			  		side = GLCD_LEFT;  // Stores which chip to use on the LCD
			  	   if(x > 63)              // Check for first or second display area
			  	   side = GLCD_RIGHT;
			  	   GLCD_ReadStatus(side);
			  	   GLCD_EnableController(side); 							//enable the selected controller
			  	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0,0xff);			//sbi(GPORTC_1,GLCD_DI); // SELECT Data REGISTER // Set for data
			  	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1,0x00);			//cbi(GPORTC_1,GLCD_RW);// Set for writing

			  		 GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0,Character5x8[a+i]);//GPORTD=GLCD_ReadByteFromROMMemory(dataToWrite++);            // Put the data on the port
			  		 GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2,Character5x8[a+i]);

			  		 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2,0xff);	//sbi(GPORTC_1,GLCD_E);       // Pulse the enable pin
			  		 GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);	//cbi(GPORTC_1,GLCD_E);

			  	  GLCD_DisableController(side);
			  		  if(x >= 127);
			  		  x++;
			  		}
			  }


void glcd_WriteByte(unsigned char x,unsigned char y,unsigned char val)
{

  if(x<64)
  {
   glcd_writeCmd(GLCD_LEFT,  0xB8+y);    // Set the page address to 0
   glcd_writeCmd(GLCD_LEFT, 0x40+x);
   glcd_writeData(GLCD_LEFT, val);
  }
  else
  {
   glcd_writeCmd(GLCD_RIGHT,  0xB8+y);    // Set the page address to 0
   glcd_writeCmd(GLCD_RIGHT, x);
   glcd_writeData(GLCD_RIGHT, val);

  }
}

void glcd_pixel(unsigned char x, unsigned char y, unsigned char color)
	{

	unsigned char tmp;
	 unsigned char side = GLCD_LEFT;  // Stores which chip to use on the LCD

	   if(x > 63)              // Check for first or second display area
		   {
		   side = GLCD_RIGHT;
		   }
	tmp=0;
	GLCD_GoTo(x, (y / 8));
	tmp  = glcd_readByte(side);                  //  at new address
	GLCD_GoTo(x, (y / 8));
	tmp = glcd_readByte(side);                  //  at new address
	GLCD_GoTo(x, (y / 8));
	if(color==2)
		{
			if(tmp & (1 << (y % 8)))
			tmp &= ~(1 << (y % 8));
			else
			tmp |= (1 << (y % 8));
		}
	else if(color==1)
		tmp |= (1 << (y % 8));
	else
		tmp &= ~(1 << (y % 8));
	glcd_writeData(side, tmp);   // Write the pixel data
	}

unsigned char glcd_readByte(unsigned char side)
	{
	   unsigned char dataH=0,dataL=0,data=0; // Stores the data read from the LCD

	   GLCD_ReadStatus(side);
	   GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2);//GDDRD=0X00; // Set port A to in
	   GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0);
	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1,0xFF);	//sbi(GPORTC_1,GLCD_RW);// Set for reading
	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0,0xff);	//sbi(GPORTC_1,GLCD_DI);// SELECT Data REGISTER // Set for data
	   GLCD_EnableController(side);
	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0xff);	//sbi(GPORTC_1,GLCD_E); // Pulse the enable pin
	   dataH =GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2);	// data PINA ;// Get the data from the display's output register
	   dataL=GPIOPinRead(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_0);
	   data=dataH|dataL;
	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);	//cbi(GPORTC_1,GLCD_E);

	   GLCD_DisableController(side);
	   GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2);//GDDRD=0Xff Set portA to input set ports to be output
	   GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0);
	   return data;               						// Return the read data
	}

void glcd_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color)
	{
	   unsigned int       dy, dx;
	   signed  char  addx=1, addy=1;
	   signed  int P, diff;
	   unsigned char i=0;
	   dx = abs((signed  char)(x2 - x1));
	   dy = abs((signed  char)(y2 - y1));

	   if(x1 > x2)
		  addx = -1;
	   if(y1 > y2)
		  addy = -1;
	   if(dx >= dy)
	   {
		  dy *= 2;
		  P = dy - dx;
		  diff = P - dx;
		  for(; i<=dx; ++i)
		  {
			 glcd_pixel(x1, y1, color);

			 if(P < 0)
			 {
				P  += dy;
				x1 += addx;
			 }
			 else
			 {
				P  += diff;
				x1 += addx;
				y1 += addy;
			 }
		  }
	   }
	   else
	   {
		  dx *= 2;
		  P = dx - dy;
		  diff = P - dy;

		  for(; i<=dy; ++i)
		  {
			 glcd_pixel(x1, y1, color);

			 if(P < 0)
			 {
				P  += dx;
				y1 += addy;
			 }
			 else
			 {
				P  += diff;
				x1 += addx;
				y1 += addy;
			 }
		  }
	   }
	}
	
void UpdateBow()
{
	 if (UP_DOWN<500&& UP_DOWN>2)
			{
			 By+=3;
			Ay=By+7;
			 DrawBow(5,By);
			 DrawArrow(Ax,Ay);
			}
	 else if (UP_DOWN<1000 && UP_DOWN>500)
		   {
		   By+=2;
			Ay=By+7;
		   DrawBow(5,By);
		   DrawArrow(Ax,Ay);
		   }
	 else if (UP_DOWN<1900 && UP_DOWN>1000)
			{
			By+=1;
			Ay=By+7;
			 DrawBow(5,By);
			 DrawArrow(Ax,Ay);
			}

	 else if (UP_DOWN>2200 && UP_DOWN<3100)
			 {
			By-=1;
			Ay=By+7;
			  DrawBow(5,By);
			 DrawArrow(Ax,Ay);
			 }
	 else if (UP_DOWN>3100 && UP_DOWN<3600)
			{
			  By-=2;
			Ay=By+7;
			  DrawBow(5,By);
			 DrawArrow(Ax,Ay);
			}
	 else if (UP_DOWN>3600 && UP_DOWN<4096)
		   {
			By-=3;
			Ay=By+7;
			DrawBow(5,By);
			DrawArrow(Ax,Ay);
			}
	
}
	
void DrawBow(signed char x,signed char y)
	{
		if(x<=0){x=0;}
		if(x>=128)
			{
			x=127;
			}
		if(y<=0)
			{
			y=0;
			By=0;
			}
		if(y>43)
			{
			y=43;
			By=43;
			}

		glcd_rect(last_xB, last_yB, last_xB, last_yB+20, FILL, WHITE);
		glcd_rect(last_xB+1, last_yB, last_xB+6, last_yB+1, FILL, WHITE);
		glcd_rect(last_xB+7, last_yB+2, last_xB+8, last_yB+3, FILL, WHITE);
		glcd_rect(last_xB+9, last_yB+4, last_xB+10, last_yB+7, FILL, WHITE);
		glcd_rect(last_xB+7, last_yB+8, last_xB+8, last_yB+12, FILL, WHITE);
		glcd_rect(last_xB+9, last_yB+13, last_xB+10, last_yB+16, FILL, WHITE);
		glcd_rect(last_xB+7, last_yB+17, last_xB+8, last_yB+18, FILL, WHITE);
		glcd_rect(last_xB+1, last_yB+19, last_xB+6, last_yB+20, FILL, WHITE);

	glcd_rect(x, y, x, y+20, FILL, BLACK);
	glcd_rect(x+1, y, x+6, y+1, FILL, BLACK);
	glcd_rect(x+7, y+2, x+8, y+3, FILL, BLACK);
	glcd_rect(x+9, y+4, x+10, y+7, FILL, BLACK);
	glcd_rect(x+7, y+8, x+8, y+12, FILL, BLACK);
	glcd_rect(x+9, y+13, x+10, y+16, FILL, BLACK);
	glcd_rect(x+7, y+17, x+8, y+18, FILL, BLACK);
	glcd_rect(x+1, y+19, x+6, y+20, FILL, BLACK);
	last_xB=x;
	last_yB=y;
	}
void UpdateArrow()
{
	if ( LEFT_RIGHT<100 )
		{
			if(Ax<11)
			{
				Ax+=1;
			}
			Ay=By+7;
			DrawArrow(Ax,Ay);
		}
	if (LEFT_RIGHT>3900)
	   {
			if(Ax>0)
			{
				Ax-=1;
			}
			Ay=By+7;
			DrawArrow(Ax,Ay);
	   }
	 
	
	
}
void DrawArrow(signed char x,signed char y)
	{
		if(last_yA<=1)
		{
			last_yA=2;
		}
		if(x<=0)
		{
			x=0;
		}
		if(x>83)
		{
			x=83;
		}
		
		if(y<=7)
		{
			y=7;
		}
		if(y>50)
		{
			y=50;
		}
			glcd_rect(last_xA, last_yA, last_xA, last_yA+5, FILL, WHITE);
			glcd_rect(last_xA+1, last_yA+2, last_xA+20, last_yA+3, FILL, WHITE);
			glcd_rect(last_xA+17, last_yA, last_xA+18, last_yA+5, FILL, WHITE);
			glcd_rect(last_xA+15, last_yA+6, last_xA+16, last_yA+7, FILL, WHITE);
			glcd_rect(last_xA+15, last_yA-2, last_xA+16, last_yA-1, FILL, WHITE);

		glcd_rect(x, y, x, y+5, FILL, BLACK);
		glcd_rect(x+1, y+2, x+20, y+3, FILL, BLACK);
		glcd_rect(x+17, y, x+18, y+5, FILL, BLACK);
		glcd_rect(x+15, y-2, x+16, y-1, FILL, BLACK);
		glcd_rect(x+15, y+6, x+16, y+7, FILL, BLACK);
		last_xA=x;
		last_yA=y;
	}
	
void showScore(unsigned char *msg)
{
	unsigned char i=0;
	
	GLCD_WriteString(20,18,msg,FONT5,BLACK);
	buzzerOn();
			
	for(i=0;i<4;i++)
	{
		buzzerToggle();
		glcd_rect(16,13,84, 26, FILL, 2);		
		buzzerToggle();
		SysCtlDelay(6700000/5);		
	}
	glcd_rect(16,13,88, 26, FILL,WHITE);
	buzzerOff();
}
void shootArrow()
{

	if(startNotLatched)
	{
		currAx=Ax;
		startNotLatched=0;
	}	
	if(Ax<64)
	{
		
		switch(currAx)
		{
			case 0:case 1:
				 Ax+=5;

			break;
			case 2:case 3:
				 Ax+=4;

			break;
			case 4:case 5:
				 Ax+=3;

			break;
			case 6:case 7:
				 Ax+=2;

			break;

			default:
				Ax+=1;
			
		}
	DrawArrow(Ax,Ay);
	DrawBow(5,By);
	}
	else
	{
		shooting=0;
		startNotLatched=1;
		Aym=Ay+3;
		if(Aym<Ty || Aym> (Ty+19)) //missed target!!!
		{
				score+=0;
				showScore(missed);
		}
		else 
		{
			score+=scoreArray[Aym-Ty];
			
			if (scoreArray[Aym-Ty]==300)
			{
				showScore(bullsEye);
			}
			else if (scoreArray[Aym-Ty]==250)
			{
				showScore(twoFifty);
			}
			else if (scoreArray[Aym-Ty]==200)
			{
				showScore(twoHundered);
			}

			else if (scoreArray[Aym-Ty]==100)
			{
				showScore(hundered);
			}
			else if (scoreArray[Aym-Ty]==50)
			{
				showScore(fifty);
			}

		}
		GLCD_Write_Ver(95, 54, score, 5);
		Ax=Bx+4;
		DrawArrow(Ax,Ay);
		arrow-=1;
		switch(arrow)
		{
		case 0:
			GLCD_WriteString(94,27,"      ",FONT5,BLACK);
			GLCD_WriteString(94,36,"      ",FONT5,BLACK);
			/*
				reinitialising variables
			position=1;
			bow_width=4;
			Bx=0;By=0;
			Ax=5; Ay=7;
			Tx=0;Ty=0;
			Tym=0;Aym=0;
			last_xB=0; last_yB=0;
			last_xA=0; last_yA=0;
			last_xT=0; last_yT=0;

			upDownBarTarget=0;
			targetIncrCount=1;
		
			score=0;
			arrow=6;
			
			*/
			/****************************************************************/
			delay(2);
			glcd_fillScreen(WHITE);
			GLCD_WriteString(35,0,"Game Over",FONT5,BLACK);
			glcd_rect(33,0,88,7, FILL,2);
			GLCD_WriteString(20,18,"You Have Scored",FONT5,BLACK);
			GLCD_Write_Ver(35,36,score,5);
			GLCD_WriteString(5,54,"Press reset to start",FONT5,BLACK);
			while(1)
				{				
				glcd_rect(0,47,127,55, FILL,2);
				}
			
			
			/*****************************************************************/
			break;
		case 1:
			GLCD_WriteString(94,27,"->    ",FONT5,BLACK);
			GLCD_WriteString(94,36,"      ",FONT5,BLACK);
			break;
		case 2:
			GLCD_WriteString(94,27,"->->  ",FONT5,BLACK);
			GLCD_WriteString(94,36,"      ",FONT5,BLACK);
			break;
		case 3:
			GLCD_WriteString(94,27,"->->->",FONT5,BLACK);
			GLCD_WriteString(94,36,"      ",FONT5,BLACK);
			break;
		case 4:
			GLCD_WriteString(94,27,"->->->",FONT5,BLACK);
			GLCD_WriteString(94,36,"->    ",FONT5,BLACK);
			break;
		case 5:
			GLCD_WriteString(94,27,"->->->",FONT5,BLACK);
			GLCD_WriteString(94,36,"->->  ",FONT5,BLACK);
			break;
		default:
			break;

		}

		}


	
}
void UpdateTarget()
{
	if(upDownBarTarget==0)
	{
		if(Ty<44)
		{
			Ty+=targetIncrCount;
			DrawTarget(TARGETX_INIT,Ty);
		}
		else
		{
			upDownBarTarget=1;
			Ty-=targetIncrCount;
			DrawTarget(TARGETX_INIT,Ty);
		}
	}	
	else
	{
		if(Ty>0)
		{
			Ty-=targetIncrCount;
			DrawTarget(TARGETX_INIT,Ty);
		}
		else
		{
			upDownBarTarget=0;
			Ty+=targetIncrCount;
			DrawTarget(TARGETX_INIT,Ty);
		}
	}	
	
}
	
void DrawTarget(signed char x,signed char y)
	{
	if(last_xT<=3)
			{
			last_xT=3;
			}
	if(Ty>63)
		{
		y=0;
		Ty=0;
		}

	glcd_rect(last_xT, last_yT, last_xT-3, last_yT+19, FILL, WHITE);

	glcd_rect(x, y, x, y+19, FILL, BLACK);
	glcd_rect(x-1, y+3, x-1, y+16, FILL, BLACK);
	glcd_rect(x-2, y+6, x-2, y+13, FILL, BLACK);
	glcd_rect(x-3, y+8, x-2, y+11, FILL, BLACK);
	last_xT=x;
	last_yT=y;
	}


void glcd_rect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill, unsigned char color)
{

   if(fill)
   {
      #ifdef LARGE_LCD
      unsigned char6 i, xmin, xmax, ymin, ymax;
      #else
      unsigned char  i, xmin, xmax, ymin, ymax;
      #endif

      if(x1 < x2)                            //  Find x min and max
      {
         xmin = x1;
         xmax = x2;
      }
      else
      {
         xmin = x2;
         xmax = x1;
      }

      if(y1 < y2)                            // Find the y min and max
      {
         ymin = y1;
         ymax = y2;
      }
      else
      {
         ymin = y2;
         ymax = y1;
      }

      for(; xmin <= xmax; ++xmin)
      {
         for(i=ymin; i<=ymax; ++i)
         {
            glcd_pixel(xmin, i, color);
         }
      }
   }
   else
   {
      glcd_line(x1, y1, x2, y1, color);      // Draw the 4 sides
      glcd_line(x1, y2, x2, y2, color);
      glcd_line(x1, y1, x1, y2, color);
      glcd_line(x2, y1, x2, y2, color);
   }
}

void GLCD_WriteString(unsigned char x, unsigned char y,unsigned char*stringToWrite,unsigned char width,unsigned char color)
	{
	unsigned int a;
	 unsigned char i;
	 unsigned char side;
	   GLCD_GoTo(x,y);
	while(*stringToWrite)
		{
		  a=*stringToWrite;
		  a-=32;
		  a*=6;
		  for(i=0;i<FONT_WIDTH5;i++)
			{
		  		side = GLCD_LEFT;  // Stores which chip to use on the LCD
				if(x > 63)              // Check for first or second display area
					side = GLCD_RIGHT;
		  	   
				GLCD_ReadStatus(side);
				GLCD_EnableController(side); 							//enable the selected controller
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0,0xff);			//sbi(GPORTC_1,GLCD_DI); // SELECT Data REGISTER // Set for data
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1,0x00);			//cbi(GPORTC_1,GLCD_RW);// Set for writing

				GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0,Character5x8[a+i]);//GPORTD=GLCD_ReadByteFromROMMemory(dataToWrite++);            // Put the data on the port
				GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2,Character5x8[a+i]);

				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2,0xff);	//sbi(GPORTC_1,GLCD_E);       // Pulse the enable pin
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);	//cbi(GPORTC_1,GLCD_E);

				GLCD_DisableController(side);
				
				if(x >= 127)
		  		  break;  //return(x)??
			  
				x++;
			}
		  stringToWrite++;
		}

	}
	


void glcd_fillScreen(unsigned char color)
	{
	  unsigned char i, j;
	  for(j = 0; j < GLCD_HEIGHT/8; j++)
	  {
		  GLCD_GoTo(0,j);
		  for(i = 0; i <GLCD_WIDTH; i++)
		  {
		   if(i<64)
		   glcd_writeData(GLCD_LEFT, 0xFF*color);
		   else
		   glcd_writeData(GLCD_RIGHT, 0xFF*color);  // Turn pixels on or off
		   }
	  }
	}

void GLCD_GoTo(unsigned char col, unsigned char row)
	{
	unsigned char i;
	for(i = 0; i < GLCD_WIDTH/64; i++)
		{
		   glcd_writeCmd(i,  0xC0);    // Specify first RAM line at the top of the screen
		   glcd_writeCmd(i,  0x40);    // Set the column address to 0
		   glcd_writeCmd(i,  0xB8);    // Set the page address to 0
		}
	 if(col<=GLCD_HEIGHT)
		 {
			glcd_writeCmd(GLCD_LEFT,0x40 | (col & 63));	 // find the col position by mod then decide the chip(if <64 ,as it is,0. if > 64,-64,1)
			glcd_writeCmd(GLCD_RIGHT,0x40 | 0);	 // find the col position by mod then decide the chip(if <64 ,as it is,0. if > 64,-64,1)
		 }
	 else
		 {
			glcd_writeCmd(GLCD_LEFT,0x40 | 63);	 // find the col position by mod then decide the chip(if <64 ,as it is,0. if > 64,-64,1)
			glcd_writeCmd(GLCD_RIGHT,0x40 | ((col - 64)&63));	 // find the col position by mod then decide the chip(if <64 ,as it is,0. if > 64,-64,1)
		  }
	glcd_writeCmd(GLCD_LEFT,0xb8  | row);// find the page by adding with base page no
	glcd_writeCmd(GLCD_RIGHT,0xb8  | row);// find the page by adding with base page no
	}

unsigned char GLCD_ReadByteFromROMMemory(char * ptr)
		{
		return 0xAA;
		}

void  GLCD_init(unsigned char mode)
	{
		SysCtlDelay(6700000/50);							// creates ~10ms delay - TivaWare fxn
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x00);	//cbi(GPORTC_2,GLCD_RST);
		SysCtlDelay(6700000/50);							// creates ~10ms delay - TivaWare fxn
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0x20);	//sbi(GPORTC_2,GLCD_RST);  //reset the chip
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0x00);	//cbi(GPORTC_1,GLCD_E);
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0x00);	//cbi(GPORTC_2,GLCD_CS1);;
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00);	//cbi(GPORTC_2,GLCD_CS2);

		glcd_writeCmd(GLCD_LEFT,  0xC0);    // Specify first RAM line at the top
		glcd_writeCmd(GLCD_RIGHT, 0xC0);    //   of the screen
		glcd_writeCmd(GLCD_LEFT,  0x40);    // Set the column address to 0
		glcd_writeCmd(GLCD_RIGHT, 0x40);
		glcd_writeCmd(GLCD_LEFT,  0xB8);    // Set the page address to 0
		glcd_writeCmd(GLCD_RIGHT, 0xB8);

	   if(mode == ON)
	   {
	      glcd_writeCmd(GLCD_LEFT,  0x3F); // Turn the display on
	      glcd_writeCmd(GLCD_RIGHT, 0x3F);
	   }
	   else
	   {
	      glcd_writeCmd(GLCD_LEFT,  0x3E); // Turn the display off
	      glcd_writeCmd(GLCD_RIGHT, 0x3E);
	   }

	   glcd_fillScreen(OFF);                // Clear the display
	}


void glcd_writeData(unsigned char side, unsigned char data)
{

   GLCD_ReadStatus(side);
   GLCD_EnableController(side); //enable the selected controller
   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0,0xff); //sbi(GPORTC_1,GLCD_DI); 	// SELECT Data REGISTER // Set for data
   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1,0x00); //cbi(GPORTC_1,GLCD_RW);		// Set for writing

   GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0,data);					//GPORTD=data;     // Put the data on the port
   GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2,data);

   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2,0xff);	//sbi(GPORTC_1,GLCD_E);       		// Pulse the enable pin
   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2,0x00);	//cbi(GPORTC_1,GLCD_E);

   GLCD_DisableController(side);
}



void glcd_writeCmd(unsigned char side, unsigned char data)
	{
	    GLCD_EnableController(side); 					//enable the selected controller

	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0,0x00);	//cbi(GPORTC_1,GLCD_DI); 			// SELECT command REGISTER // Set for instruction
	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1,0x00);	//cbi(GPORTC_1,GLCD_RW);			// Set for writing

	   GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0,data);							//GPORTD=data;     // Put the data on the port
	   GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2,data);

	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2,0xff);	//sbi(GPORTC_1,GLCD_E);       		// Pulse the enable pin
	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2,0x00);	//cbi(GPORTC_1,GLCD_E);

	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3,0x00);	//cbi(GPORTC_2,GLCD_CS1);      	// Reset the chip select lines
	   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0x00);	//cbi(GPORTC_2,GLCD_CS2);
	}

void GLCD_ReadStatus(unsigned char controller)
	{
		unsigned char status;
		GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2);     //GDDRD  Set port A to input
		GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0);
		do
			{
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1,0x02);			//sbi(GPORTC_1,GLCD_RW); // Set for reading
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0,0x00);			//cbi(GPORTC_1,GLCD_DI); // SELECT COMMAND REGISTER // Set for instruction
			GLCD_EnableController(controller);
			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2,0xff);			//sbi(GPORTC_1,GLCD_E);
		

			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2,0x00);			//cbi(GPORTC_1,GLCD_E);;
			status=GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7);					 //status = PINA &0x80;
			GLCD_DisableController(controller);
			}
		while(status & 0x80);
		GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2);//GDDRD=0Xff;  // Set port A to out
		GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0);
	}


void GLCD_EnableController(unsigned char controller)

	{
	switch(controller)
		{
		case 0 : GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3,0xff);	//sbi(GPORTC_2,GLCD_CS1);
			break;
		case 1 : GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0xff);		//sbi(GPORTC_2,GLCD_CS2);
			break;
		}
	}

void GLCD_DisableController(unsigned char controller)
	{
	switch(controller)
		{
		case 0 : GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3,0x00);	//cbi(GPORTC_2,GLCD_CS1);
			break;
		case 1 : GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0x00);	//cbi(GPORTC_2,GLCD_CS2);
			break;
		}
	}

//---------------------------------------------------------------------------
// hardware_init()
//
// inits GPIO pins for toggling the LED
//---------------------------------------------------------------------------
void lcdInit(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_0);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2);

	GPIOPadConfigSet(GPIO_PORTB_BASE,(GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0),GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTE_BASE,(GPIO_PIN_1|GPIO_PIN_0),GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTA_BASE,(GPIO_PIN_7|GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2),GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);

}

	

//---------------------------------------------------------------------------------
// Project: Blink TM4C BIOS Using Task (SOLUTION)
// Author: Eric Wilbur
// Date: June 2014
//
// Note: The function call TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT) HAS
//       to be in the ISR. This fxn clears the TIMER's interrupt flag coming
//       from the peripheral - it does NOT clear the CPU interrupt flag - that
//       is done by hardware. The author struggled figuring this part out - hence
//       the note. And, in the Swi lab, this fxn must be placed in the
//       Timer_ISR fxn because it will be the new ISR.
//
// Follow these steps to create this project in CCSv6.0:
// 1. Project -> New CCS Project
// 2. Select Template:
//    - TI-RTOS for Tiva-C -> Driver Examples -> EK-TM4C123 LP -> Example Projects ->
//      Empty Project
//    - Empty Project contains full instrumentation (UIA, RTOS Analyzer) and
//      paths set up for the TI-RTOS version of MSP430Ware
// 3. Delete the following files:
//    - Board.h, empty.c, EK_TM4C123GXL.c/h, empty_readme.txt
// 4. Add main.c from TI-RTOS Workshop Solution file for this lab
// 5. Edit empty.cfg as needed (to add/subtract) BIOS services, delete given Task
// 6. Build, load, run...
//----------------------------------------------------------------------------------


//----------------------------------------
// BIOS header files
//----------------------------------------
#include <xdc/std.h>  						//mandatory - have to include first, for BIOS types
#include <ti/sysbios/BIOS.h> 				//mandatory - if you call APIs like BIOS_start()
#include <xdc/runtime/Log.h>				//needed for any Log_info() call
#include <xdc/cfg/global.h> 				//header file for statically defined objects/handles

//---------------------------------------
// Globals
//---------------------------------------
volatile int16_t i16ToggleCount = 0;
char  buff[10],buff1[10];
uint32_t ui32ADC0Value[4];
uint32_t ui32ADC1Value[4];
uint32_t LEFT_RIGHT;
uint32_t UP_DOWN;
volatile uint32_t tickCount=0;
unsigned int xpos = 0;
signed char originalPriReadADC,originalPriShoot,originalPriLED,originalPriLCD;
unsigned char shooting=0;
extern unsigned char targetIncrCount;
//------------------------------------------
// TivaWare Header Files
//------------------------------------------
#include "common.h"
#include "led.h"
#include "timer2.h"
#include "buzzer.h"
#include "joystick.h"
#include "glcd.h"


//----------------------------------------
// Prototypes
//----------------------------------------

void ledToggle(void);
void Timer_ISR(void);

//---------------------------------------------------------------------------
// main()
//---------------------------------------------------------------------------
void main(void)
   {

   hardware_init();							// init hardware via Xware

	BIOS_start();
}

//---------------------------------------------------------------------------
// hardware_init()
//
// inits GPIO pins for toggling the LED
//---------------------------------------------------------------------------
void hardware_init(void)
{

	//Set CPU Clock to 40MHz. 400MHz PLL/2 = 200 DIV 5 = 40MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	lcdInit();
	joystickInit();



	buzzerInit();
	ledsInit();

	setup();

	//
	// Check to see if the registers are locked, and if so, unlock them.
	//
	//if(WatchdogLockState(WATCHDOG0_BASE) == true)
	//{
	//WatchdogUnlock(WATCHDOG0_BASE);
	//	}
	//
	// Initialize the watchdog timer.
	//
	//WatchdogReloadSet(WATCHDOG0_BASE, 0xFEEFEE);






	//WatchdogIntClear(WATCHDOG0_BASE);
	//WatchdogIntEnable(WATCHDOG0_BASE);




}

void setup()
{
	GLCD_init(ON);
	glcd_fillScreen(OFF);
	GLCD_GoTo(1,1);

	glcd_rect(4,4, 88, 60, FILL, BLACK);
	GLCD_WriteString(8,9, " Archery Game",FONT5,WHITE);
	GLCD_WriteString(8,18,"    using    ",FONT5,WHITE);
	GLCD_WriteString(8,27,"   TI-RTOS   ",FONT5,WHITE);

	GLCD_WriteString(8,45," Group No: 21",FONT5,WHITE);

	glcd_line(90,0,90,64,BLACK);
	glcd_line(91,0,91,64,BLACK);
	GLCD_WriteString(95,0,"Set",FONT5,BLACK);
	GLCD_WriteString(95,9,"Level",FONT5,BLACK);

	GLCD_WriteString(94,36,"Press",FONT5,BLACK);
	GLCD_WriteString(93,45,"Key to",FONT5,BLACK);
	GLCD_WriteString(94,54,"Enter",FONT5,BLACK);
	targetIncrCount=1;
	while(1)
	{
			ADCIntClear(ADC0_BASE, 1);
			ADCProcessorTrigger(ADC0_BASE, 1);
			while(!ADCIntStatus(ADC0_BASE, 1, false))
			{
			}
			ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
			UP_DOWN = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
			if(UP_DOWN>3900)
				{
				targetIncrCount++;
				if(targetIncrCount>=5)
					{
					targetIncrCount=5;
					}
				while(UP_DOWN>3900){
					ADCIntClear(ADC0_BASE, 1);
					ADCProcessorTrigger(ADC0_BASE, 1);
					while(!ADCIntStatus(ADC0_BASE, 1, false))
					{
					}
					ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
					UP_DOWN = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
				}

				}
			if(UP_DOWN<200)
				{
				targetIncrCount--;
				if(targetIncrCount<=1)
					{
					targetIncrCount=1;
					}
				while(UP_DOWN<200){
					ADCIntClear(ADC0_BASE, 1);
					ADCProcessorTrigger(ADC0_BASE, 1);
					while(!ADCIntStatus(ADC0_BASE, 1, false))
					{
					}
					ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
					UP_DOWN = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;
				}

				}
			GLCD_Write_Ver(107, 18, targetIncrCount, 1);

			if(GPIOPinRead(GPIO_PORTE_BASE, 16))
			{
				continue;
			}
			else
			{
				break;
			}
	}
	glcd_rect(92, 0, 127, 64, FILL, WHITE);

	GLCD_WriteString(95,0,"Level",FONT5,BLACK);
	GLCD_Write_Ver(107, 9, targetIncrCount, 1);
	GLCD_WriteString(95,18,"Done",FONT5,BLACK);
	delay(2);

	GLCD_Write_Ver(107, 9, targetIncrCount, 1);
	GLCD_WriteString(93,18,"Arrows",FONT5,BLACK);
	GLCD_WriteString(94,27,"->->->",FONT5,BLACK);
	GLCD_WriteString(94,36,"->->->",FONT5,BLACK);
	GLCD_WriteString(95,45,"Score",FONT5,BLACK);
	GLCD_Write_Ver(95, 54, 00000, 5);
	glcd_rect(4,4, 88, 60, FILL, WHITE);
	DrawBow(5,0);
	DrawArrow(5,7);

	//
	// Enable the reset.
	//
	//WatchdogResetEnable(WATCHDOG0_BASE);
	//
	// Enable the watchdog timer.
	//
	//WatchdogEnable(WATCHDOG0_BASE);

	timer2Init();



}

//---------------------------------------------------------------------------
// ledToggle()
//
// toggles LED on Tiva-C LaunchPad
//---------------------------------------------------------------------------
void ledToggle()   //task
{
	originalPriLED=Task_getPri(ledToggleTask);

	while(1)
	{

		Semaphore_pend(LEDSem, BIOS_WAIT_FOREVER);				// wait for Sem from ISR

		// LED values - 2=RED, 4=BLUE, 8=GREEN
		if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		}
		else
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
		}


	}

}

//---------------------------------------------------------------------------
// readADC()
//
// reads the values of Joystick
//---------------------------------------------------------------------------
void readADC(void)
{
	originalPriReadADC=Task_getPri(readADCTask);

	while(1)
	{
		Semaphore_pend(ADCSem, BIOS_WAIT_FOREVER);				// wait for Sem from ISR

		ADCIntClear(ADC0_BASE, 1);
		ADCProcessorTrigger(ADC0_BASE, 1);
		while(!ADCIntStatus(ADC0_BASE, 1, false))
		{
		}
		ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
		UP_DOWN = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3] + 2)/4;

		ADCIntClear(ADC1_BASE, 1);
		ADCProcessorTrigger(ADC1_BASE, 1);
		while(!ADCIntStatus(ADC1_BASE, 1, false))
		{
		}
		ADCSequenceDataGet(ADC1_BASE, 1, ui32ADC1Value);
		LEFT_RIGHT = (ui32ADC1Value[0] + ui32ADC1Value[1] + ui32ADC1Value[2] + ui32ADC1Value[3] + 2)/4;
		UpdateArrow();
		UpdateBow();




	}

}


//---------------------------------------------------------------------------
// readLCD()
//
// Update LCD
//---------------------------------------------------------------------------
void updateLCD(void)
{
	originalPriLCD=Task_getPri(updateLCDTask);
	while(1)
	{
		Semaphore_pend(LCDSem, BIOS_WAIT_FOREVER);				// wait for Sem from ISR
		UpdateTarget();  //x 128 y 64 target height 20
	}
}
//---------------------------------------------------------------------------
// shoot()
//
// Shoot
//---------------------------------------------------------------------------
void shoot(void)
{
	originalPriShoot=Task_getPri(shootTask);

	while(1)
	{
		Semaphore_pend(ShootSem, BIOS_WAIT_FOREVER);				// wait for Sem from ISR
		buzzerOn();
		shootArrow();
		buzzerOff();


	}
}
//---------------------------------------------------------------------------
// Timer ISR - called by BIOS Hwi (see app.cfg)
//
// Posts Swi (or later a Semaphore) to toggle the LED
//---------------------------------------------------------------------------
void Timer_ISR(void)
{
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);			// must clear timer flag FROM timer
    tickCount++;





    if(tickCount%3==0)   //10 ms check switch
	{
    	if(detectKeyPress() && shooting==0)
    	{
        	Semaphore_post(ShootSem);
        	shooting=1;

    	}
	}

    //if(tickCount==13||tickCount==26||tickCount==39||tickCount==52||tickCount==65||tickCount==78||tickCount==91)
    if(tickCount==15)
    	if(shooting)
    	{
    		Semaphore_post(ShootSem);
    		Semaphore_post(LEDSem);

    	}

    if(tickCount==35)
    {
    	Semaphore_post(LCDSem); //updateTarget

    }
    if(tickCount==55 && shooting==0)
       {
       	Semaphore_post(ADCSem);

       }
    if(tickCount==55)
    	tickCount=0;

}



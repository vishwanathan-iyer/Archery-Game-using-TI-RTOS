#include "common.h"
void buzzerInit()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);
}
void buzzerOn()
{
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);	
}
void buzzerOff()
{
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1);
}
void buzzerToggle()
{
	if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_0))
	{
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1);
	}	
}

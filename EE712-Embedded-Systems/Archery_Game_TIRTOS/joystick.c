#include "common.h"
#include "joystick.h"
#define IDLE 0
#define PRESS 1
#define RELEASE 2

unsigned char state=IDLE;
void joystickInit()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	//* * * * * * * * * * * Switch Configuration* * * * * * * * * * * * * *
	GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_4,GPIO_STRENGTH_12MA,GPIO_PIN_TYPE_STD_WPU);
	
	//* * * * * * * * * * * ADC Configuration* * * * * * * * * * * * * *
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_CH0|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC0_BASE, 1);


	ADCSequenceConfigure(ADC1_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
	ADCSequenceStepConfigure(ADC1_BASE, 1, 0, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC1_BASE, 1, 1, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC1_BASE, 1, 2, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC1_BASE,1,3,ADC_CTL_CH1|ADC_CTL_IE|ADC_CTL_END);
	ADCSequenceEnable(ADC1_BASE, 1);

	//* * * * * * * * * * * Uart Configuration* * * * * * * * * * * * * *
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);

	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
	(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
	
	
	UARTSend("Ready! Connect your joystick and let's play!");
	
}
//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void UARTSend(char *pui8Buffer)
{
    //
    // Loop while there are more characters to send.
    //
    while(*pui8Buffer)
    {
    	UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

void int2dec(uint32_t x, char *s, uint8_t len)
{
	uint8_t i=0;
	uint32_t dec;
	const int Ten[] = {1,10,100,1000,10000,100000,1000000,10000000};
	dec = Ten[len--];
	x = x%(10^dec);
	while(x>9){
		s[i++] = x/dec + 0x30;
		x = x%dec;
		dec = Ten[len--];
	}
	s[i] = x + 0x30;
	s[i+1] = 0x00;
}

unsigned char detectKeyPress()
{
	if(state==IDLE)
	{
		if(GPIOPinRead(GPIO_PORTE_BASE, 16))	
		{
			state=IDLE;
		}
		else
		{
			state=PRESS;
		}
	}
	else if(state==PRESS)
	{
		if(GPIOPinRead(GPIO_PORTE_BASE, 16))	
		{
			state=IDLE;

		}
		else
		{
			state=RELEASE;
			return 1;
		}
	}
	else if(state==RELEASE)
	{
		if(GPIOPinRead(GPIO_PORTE_BASE, 16))	
		{
			state=IDLE;

		}
		else
		{
			state=RELEASE;

		}
	
	}
	else
		return 0;

	
	return 0;
}


#include "common.h"
//---------------------------------------------------------------------------
// delay()
//
// Creates a 500ms delay via TivaWare fxn
//---------------------------------------------------------------------------
void delay(char multiplier)
	{
		 SysCtlDelay(6700000*multiplier);		// creates ~500ms delay - TivaWare fxn

	}


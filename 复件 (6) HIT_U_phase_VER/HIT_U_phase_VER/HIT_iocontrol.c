#ifndef HITIOCONTROLC
#define HITIOCONTROLC
#include "iodefine.h"
void HIT_iocontrol()
{
	PORT9.DDR.BIT.B6=1;
	PORT2.DDR.BIT.B4=1;
	PORT9.DR.BIT.B6=0;
	PORT9.DDR.BIT.B2 = 1;//alarm 
	PORT9.DR.BIT.B2 = 1; 
	PORTA.DDR.BIT.B3 = 1;	
}

#endif
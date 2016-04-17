#ifndef HITZEROTO2HUNDREDMSC
#define HITZEROTO2HUNDREDMSC
#include"iodefine.h"
#include"HIT_zeroto2hundredms.h"
void HIT_zeroto2hundredms()
{
	HIT_system_count++;	
	GPT0.GTONCR.BIT.OAE = 0;
	GPT0.GTONCR.BIT.OBE = 0;
	GPT1.GTONCR.BIT.OAE = 0;
	GPT1.GTONCR.BIT.OBE = 0;
	GPT2.GTONCR.BIT.OAE = 0;
	GPT2.GTONCR.BIT.OBE = 0;
	if(HIT_system_count == 800)
	{
		PORTA.DR.BIT.B3 = 1;	
	}
		
	
}

#endif
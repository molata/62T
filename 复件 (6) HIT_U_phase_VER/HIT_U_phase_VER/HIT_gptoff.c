#ifndef HITGPTOFFC
#define HITGPTOFFC
#include "iodefine.h"
void HIT_gptoff()
{
	GPT0.GTONCR.BIT.OAE = 0;
	GPT0.GTONCR.BIT.OBE = 0;
	GPT1.GTONCR.BIT.OAE = 0;
	GPT1.GTONCR.BIT.OBE = 0;
	GPT2.GTONCR.BIT.OAE = 0;
	GPT2.GTONCR.BIT.OBE = 0;	
}

#endif
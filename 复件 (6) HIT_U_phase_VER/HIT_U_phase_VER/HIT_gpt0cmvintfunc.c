#ifndef GPT0CMVINTFUNCC
#define GPT0CMVINTFUNCC
#include "iodefine.h"
#include "HIT_current_pi.h"
#include "HIT_check_table.h"
#include "HIT_make_angle.h"
#include "HIT_make_angleab.h"
#include "HIT_vectorcontrol.h"
#include "HIT_spacevectorcontrol.h"
#include "HIT_gpt0cmvintfunc.h"
#include "HIT_servoon.h"
#include "HIT_controlsystem_servoon.h"	
extern char HIT_ready_go;

void Gpt0CmVIntFunc()
{
	PORTA.DR.BIT.B4=1;

	GPT0.GTST.BIT.TCFPO =0;	


	switch(HIT_systemcontrol_mode)
	{
		case 1:
		if(HIT_ready_go == 1)
		{
			HIT_controlsystem_servoon();
		}
		break;	
		case 2:
		HIT_identification();
		break;	
		
		
	}

	PORTA.DR.BIT.B4=0;
		
}

#endif
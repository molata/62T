#ifndef CONTROLSYSTEM_SERVOONC
#define CONTROLSYSTEM_SERVOONC
#include "HIT_controlsystem_servoon.h"	
void HIT_controlsystem_servoon()
{
	if(HIT_system_count > 30000)//300ms-
	{

		if(HIT_servofirst_begin == 0)
		{
			HIT_servoon();
		}
		else
		{
			HIT_servofirst();	///the first angle value

		}
	
	}
	else
	{
		if(HIT_system_count >20000)//200-300ms
		{
			HIT_2hundredto3hundredms();
		}
		else//0-200ms
		{
			HIT_zeroto2hundredms();
		 }
	}
}
#endif
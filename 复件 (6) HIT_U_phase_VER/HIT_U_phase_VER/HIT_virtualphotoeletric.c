#ifndef VITTUALPHOTOELETRIC
#define VITTUALPHOTOELETRIC
#include "HIT_virtualphotoeletric.h"
void HIT_virtualphotoeletric()
{

//	if(HIT_virtual_ps_cycle_count == 1831)//36//180
	{
		HIT_virtual_ps_sig_int = HIT_virtual_ps_sig_int+3;
		HIT_virtual_ps_cycle_count = 0;
	}
	HIT_virtual_ps_cycle_count++;
	if(HIT_virtual_ps_sig_int >= 65536)
	{
		HIT_virtual_ps_sig_int = HIT_virtual_ps_sig_int - 65536;	
		
	}
	HIT_virtual_ps_int = HIT_virtual_ps_sig_int;	
}
#endif
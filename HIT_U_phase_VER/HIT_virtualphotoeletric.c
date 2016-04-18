#ifndef VITTUALPHOTOELETRIC
#define VITTUALPHOTOELETRIC
#include "HIT_virtualphotoeletric.h"
#include"iodefine.h"
int HITsita_photo_T = 0;
short HITsita_photo_T_short = 0;
extern float HIT_run_mode;
unsigned short HIT_sifu_shangdian = 1;
extern float fpPC_to_motor_angle;
float fpPC_to_motor_angle_1;
float fpPC_to_motor_angle_2;
float HIT_kkkkk = 0.0;
void HIT_virtualphotoeletric()
{

//	if(HIT_virtual_ps_cycle_count == 1831)//36//180
/*	{
		HIT_virtual_ps_sig_int = HIT_virtual_ps_sig_int+3;
		HIT_virtual_ps_cycle_count = 0;
	}
	HIT_virtual_ps_cycle_count++;
	if(HIT_virtual_ps_sig_int >= 65536)
	{
		HIT_virtual_ps_sig_int = HIT_virtual_ps_sig_int - 65536;	
		
	}*/
	HITsita_photo_T_short=MTU1.TCNT;
	if(HIT_run_mode == 21)
	{
		fpPC_to_motor_angle = HIT_kkkkk + 0.001;
		fpPC_to_motor_angle_1 = fpPC_to_motor_angle;
		if((fpPC_to_motor_angle > 50)||(fpPC_to_motor_angle < -50))
		{
			fpPC_to_motor_angle = fpPC_to_motor_angle_2;	
		}
		fpPC_to_motor_angle_2 = fpPC_to_motor_angle_1;
		HIT_virtual_ps_int = fpPC_to_motor_angle/360*65535;	//HIT_jg_ang/360*65535;	
	}
	
/*	if(HITsita_photo_T > 32767)
	{
		HITsita_photo_T = HITsita_photo_T - 32768;	
	}
	HIT_virtual_ps_sig_int = HITsita_photo_T*2;*/
/*	if(HIT_run_mode == 3)
	{
		if(HITsita_photo_T_short > 32767)
		{
			HITsita_photo_T_short = HITsita_photo_T_short - 32768;	
		}
		HITsita_photo_T_short = HITsita_photo_T_short*2;
		HIT_virtual_ps_sig_int = (int)HITsita_photo_T_short;
		HIT_virtual_ps_int = HIT_virtual_ps_sig_int;
	}
	if(HIT_run_mode == 4)
	{
		if(HIT_sifu_shangdian < 10000)
		{
			HITsita_photo_T_short = 0;	
		}
		else
		{
			HIT_sifu_shangdian = 10002;	
		}
		HIT_sifu_shangdian++;
		HITsita_photo_T_short = 65535 - HITsita_photo_T_short;
		HIT_virtual_ps_sig_int = (int)HITsita_photo_T_short;
		HIT_virtual_ps_int = HIT_virtual_ps_sig_int;	
	}*/

/*
	HIT_virtual_ps_sig_int = HITsita_photo_T;
	HIT_virtual_ps_int = HIT_virtual_ps_sig_int;*/
}
#endif
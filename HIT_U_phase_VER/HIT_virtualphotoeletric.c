#ifndef VITTUALPHOTOELETRIC
#define VITTUALPHOTOELETRIC
#include "HIT_virtualphotoeletric.h"
#include"iodefine.h"
#define HIT_PIE 3.1415926
int HITsita_photo_T = 0;
short HITsita_photo_T_short = 0;
extern float HIT_run_mode;
unsigned short HIT_sifu_shangdian = 1;
extern float fpPC_to_motor_angle;
float HIT_pone_re = 0.0;
int HIT_pone_re_int = 0;
extern float fpMotor_to_pc_deg;
extern float fpMotor_to_pc_velo;
extern float HIT_speedlpf_out;
extern unsigned short HIT_new_angle_short;
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
	if(HIT_run_mode == 38)
	{
			if((fpPC_to_motor_angle < 18) && (fpPC_to_motor_angle > -18) )
			{
				HIT_pone_re = fpPC_to_motor_angle;//HIT_we_re;
				HIT_pone_re = HIT_pone_re/360*65535;
			}//xg
			
			
				/*					HIT_speedlpf_re = HIT_lpfv1A * HIT_speedlpf_re;
							HIT_speedlpf_re = HIT_speedlpf_re + HIT_lpfv1B * HIT_wone_re;
							HIT_speedlpf_re = HIT_speedlpf_re + HIT_lpfv1B * (HIT_wtwo_re-HIT_speedlpf_re);
							HIT_wtwo_re = HIT_wone_re;*/ 
			HIT_pone_re_int = (int)HIT_pone_re;
			HIT_virtual_ps_int = HIT_pone_re_int;//HIT_speedlpf_re;//xg	
//					HIT_WLw_ref = HIT_gyo_n_da;
	}
	
	fpMotor_to_pc_deg = ((float)HIT_new_angle_short)/65536*360 - 169.1;         // 
	fpMotor_to_pc_velo = HIT_speedlpf_out/2/HIT_PIE*360; 
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
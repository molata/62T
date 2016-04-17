#ifndef HITVECTORCONTROLC
#define HITVECTORCONTROLC
#include "HIT_vectorcontrol.h"
#include <math.h>
#include <mathf.h>
void HIT_vectorcontrol()
	{
		HIT_Uu_3to2 = HIT_coszhi_a*HIT_Ud - HIT_sinzhi_a*HIT_Uq;
		HIT_Uv_3to2 = HIT_coszhi_c*HIT_Ud - HIT_sinzhi_c*HIT_Uq;
		HIT_Uw_3to2 = HIT_coszhi_b*HIT_Ud - HIT_sinzhi_b*HIT_Uq;

		if(HIT_Uu_3to2 > HIT_Um)
		{
			HIT_Uu_3to2 = HIT_Um;
		}
		if(HIT_Uu_3to2 < -HIT_Um)
		{
			HIT_Uu_3to2 = -HIT_Um;
		}
		HIT_pwm_af = (HIT_Uu_3to2/HIT_Um*1000+1000);//*HIT_Vol_adj_fac;
		if(HIT_Uv_3to2 > HIT_Um)
		{
			HIT_Uv_3to2 = HIT_Um;
		}
		if(HIT_Uv_3to2 < -HIT_Um)
		{
			HIT_Uv_3to2 = -HIT_Um;
		}
		HIT_pwm_bf = (HIT_Uv_3to2/HIT_Um*1000+1000);//*HIT_Vol_adj_fac;
		if(HIT_Uw_3to2 > HIT_Um)
		{
			HIT_Uw_3to2 = HIT_Um;
		}
		if(HIT_Uw_3to2 < -HIT_Um)
		{
			HIT_Uw_3to2 = -HIT_Um;
		}
		HIT_pwm_cf = (HIT_Uw_3to2/HIT_Um*1000+1000);//*HIT_Vol_adj_fac;
		
/*dead off*/
//		HIT_pwm_af = HIT_pwm_af-HITpwm_deadoff;
			
//		HIT_pwm_bf = HIT_pwm_bf-HITpwm_deadoff;
		
//		HIT_pwm_cf = HIT_pwm_cf-HITpwm_deadoff;
/*dead off end*/

		if(HIT_pwm_af < HIT_pwm_off_vector_min)
		{
			HIT_pwm_af = HIT_pwm_off_vector_min;		
		}
		if(HIT_pwm_bf < HIT_pwm_off_vector_min)
		{
			HIT_pwm_bf = HIT_pwm_off_vector_min;		
		}
		if(HIT_pwm_cf < HIT_pwm_off_vector_min)
		{
			HIT_pwm_cf = HIT_pwm_off_vector_min;		
		}
		if(HIT_pwm_af > HIT_PWMOUTULIM)
		{
			HIT_pwm_af = HIT_PWMOUTULIM;
		}
		if(HIT_pwm_bf > HIT_PWMOUTULIM)
		{
			HIT_pwm_bf = HIT_PWMOUTULIM;
		}
		if(HIT_pwm_cf > HIT_PWMOUTULIM)
		{
			HIT_pwm_cf = HIT_PWMOUTULIM;
		}
	}
#endif
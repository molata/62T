#ifndef MECH_PI
#define MECH_PI
#include"HIT_mechanicalpi.h"
#include<math.h>
#include<mathf.h>
void HIT_mechanicalpi()
{
		HIT_sitafir = HIT_sita;
/*		if(HIT_lpfcount < 3)
		{
			HIT_sita1 = HIT_sitafir;
			HITlpf_count++;	
		}*/
		HIT_sitaerr = HIT_sitafir - HIT_sita1;//HIT_sita1 - HIT_sitafir;//HITsitafir - HITsita1;
		HIT_sita1 = HIT_sitafir;
	
		
		if(HIT_sitaerr>HIT_PIE)//avoid happen the jump of the sitaerr
		{
			HIT_sitaerr = HIT_sitaerr-HIT_TWOPIE;	
		}
		if(HIT_sitaerr<-HIT_PIE)
		{
			HIT_sitaerr = HIT_TWOPIE+HIT_sitaerr;
		}
		HIT_we = HIT_sitaerr/HIT_Tsa;//*HIT_speedpar;//////* calculate speed rad/s */
	
		HIT_wone = HIT_we;/*speed filter*/
		HIT_speedlpf = HIT_lpfv1A * HIT_speedlpf;
		HIT_speedlpf = HIT_speedlpf + HIT_lpfv1B * HIT_wone;
		HIT_speedlpf = HIT_speedlpf + HIT_lpfv1B * (HIT_wtwo-HIT_speedlpf);
		HIT_wtwo = HIT_wone;/*filter end*/ 
		
		HIT_speedlpf_pole = HIT_speedlpf*HIT_poles;
		
		HIT_WLw_err_orig = HIT_WLw_ref-HIT_speedlpf;/*speed PI*/
/*		if(HITWLw_err_orig>50)
		{
			HIT_pwm_stop = 0;//stop PWM
			
		}
		else if(HITWLw_err_orig<-50)
		{
			HIT_pwm_stop = 0;//stop PWM
		}*/
		HIT_WLw_err = HIT_WLw_err_orig;
		HIT_WLw_err = HIT_WLMech_Ki*HIT_WLw_err;
		HIT_WLw_org = HIT_WLw_err+HIT_WLw_org;
		
		HIT_WL_Mech_spee_out = HIT_WLw_org + HIT_Mech_alfa*HIT_WLw_ref;/////calculate 
		HIT_WL_Mech_spee_out = HIT_WL_Mech_spee_out - HIT_speedlpf;
		HIT_WL_Mech_spee_out = HIT_WL_Mech_spee_out*HIT_WLMechkv;
		HIT_WL_Mech_spee_out_Tmc = HIT_WL_Mech_spee_out*HIT_WL_Jm;/////calculate Tmc
		/*speed PI end*/
//		HIT_iq_ref = HIT_WL_Mech_spee_out_Tmc/HIT_WL_T_factor;
}


#endif